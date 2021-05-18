#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include "threadpool.h"


static const size_t num_threads = 4;
static const size_t num_items   = 100;

//Work Queue linked list
struct threadpool_work{
	thread_function func;
	void *arg;
	struct threadpool_work *next;
};
typedef struct threadpool_work threadpool_work_t;

struct threadpool{
	threadpool_work_t 	*first_work;
	threadpool_work_t 	*last_work;
	pthread_mutex_t 	work_mutex;		//pthread_cond_t operates on conditions 
	pthread_cond_t		work_cond; 		//Sends the signal that there is work to be processed 
	pthread_cond_t		working_cond;	//Sends the signal that there are no threads processing
	size_t				working_cnt;	//Tells how many threads are actively processing
	size_t				thread_cnt;		//Threads which are working (Helps premature destruction of threads)
	bool				stop; 			//Stops the thread
};

//Creating work in the Queue
static threadpool_work_t *threadpool_work_create(thread_function func, void *arg){
	threadpool_work_t  *work;
	if(func == NULL)
		return NULL;
	//malloc allocate memory
	work = malloc(sizeof(*work));
	work->func = func;
	work->arg = arg;
	return work;
}
//Destroying work in the queue
static void threadpool_work_destroy(threadpool_work_t *work){
	if (work==NULL)
		return;
    //free allocated memory
	free(work);
}

//Getting work from the queue and decrement of value in the queue
static threadpool_work_t *threadpool_work_get(threadpool_t *tp){
	threadpool_work_t *work;
	if(tp==NULL)
		return NULL;
	work=tp->first_work;
	if(work==NULL)
		return NULL;
	if(work->next==NULL){
		tp->first_work=NULL;
		tp->last_work=NULL;		
	}
	else{
		tp->first_work=work->next;		
	}
	return work;
}
static void *threadpool_worker(void *arg){
	threadpool_t *tp=arg;
	threadpool_work_t *work;
	
	while(1){										//Keeps the thread running
		pthread_mutex_lock(&(tp->work_mutex)); 		//Looking the mutex, nothing manuplates the members
		while(tp->first_work==NULL && !tp->stop){
			pthread_cond_wait(&(tp->work_cond),&(tp->work_mutex)); 
            //Check for running work
		if(tp->stop)
			break;
		work=threadpool_work_get(tp);
		tp->working_cnt++;							//Pool knows thread is processing
		pthread_mutex_unlock(&tp->work_mutex);
		if(work!=NULL){
			work->func(work->arg);
			threadpool_work_destroy(work);
		}
		pthread_mutex_lock(&(tp->work_mutex));
		tp->working_cnt--;
		if(!tp->stop && tp->working_cnt == 0 && tp->first_work == NULL)
			pthread_cond_signal(&(tp->working_cond));
		pthread_mutex_unlock(&(tp->work_mutex));
		tp->thread_cnt--;
		pthread_cond_signal(&(tp->working_cond));
		pthread_mutex_unlock(&(tp->work_mutex));
		return NULL;	
		
		}
	}
}

threadpool_t *threadpool_create(size_t num){
	threadpool_t *tp;
	pthread_t thread;
	size_t i;
	if(num==0)
		num=2;
	tp=calloc(1,sizeof(*tp));
	tp->thread_cnt=num;
	pthread_mutex_init(&(tp->work_mutex), NULL);
    pthread_cond_init(&(tp->work_cond), NULL);
    pthread_cond_init(&(tp->working_cond), NULL);
    
    tp->first_work = NULL;
    tp->last_work  = NULL;

    for (i=0; i<num; i++) {
        pthread_create(&thread, NULL, threadpool_worker, tp);
        pthread_detach(thread);
    }

    return tp
	
	;
}


void threadpool_destroy(threadpool_t *tp)
{
    threadpool_work_t *work;
    threadpool_work_t *work2;

    if (tp == NULL)
        return;

    pthread_mutex_lock(&(tp->work_mutex));
    work = tp->first_work;
    while (work != NULL) {
        work2 = work->next;
        threadpool_work_destroy(work);
        work = work2;
    }
    tp->stop = true;
    pthread_cond_broadcast(&(tp->work_cond));
    pthread_mutex_unlock(&(tp->work_mutex));

    threadpool_wait(tp);

    pthread_mutex_destroy(&(tp->work_mutex));
    pthread_cond_destroy(&(tp->work_cond));
    pthread_cond_destroy(&(tp->working_cond));

    free(tp);
}

void threadpool_wait(threadpool_t *tp)
{
    if (tp == NULL)
        return;

    pthread_mutex_lock(&(tp->work_mutex));
    while (1) {
        if ((!tp->stop && tp->working_cnt != 0) || (tp->stop && tp->thread_cnt != 0)) {
            pthread_cond_wait(&(tp->working_cond), &(tp->work_mutex));
        } else {
            break;
        }
    }
    pthread_mutex_unlock(&(tp->work_mutex));
}
void worker(void *arg)
{
    int *val = arg;
    int  old = *val;

    *val += 1000;
    printf("tid=%p, old=%d, val=%d\n", pthread_self(), old, *val);

    if (*val%2)
        usleep(100000);
}
bool threadpool_add_work(threadpool_t *tp, thread_function func, void *arg)
{
    threadpool_work_t *work;

    if (tp == NULL)
        return false;

    work = threadpool_work_create(func, arg);
    if (work == NULL)
        return false;

    pthread_mutex_lock(&(tp->work_mutex));
    if (tp->first_work == NULL) {
        tp->first_work = work;
        tp->last_work  = tp->first_work;
    } else {
        tp->last_work->next = work;
        tp->last_work       = work;
    }

    pthread_cond_broadcast(&(tp->work_cond));
    pthread_mutex_unlock(&(tp->work_mutex));

    return true;
}

int main(int argc, char **argv)
{
    threadpool_t *tp;
    int     *vals;
    size_t   i;

    tp   = threadpool_create(num_threads);
    vals = calloc(num_items, sizeof(*vals));

    for (i=0; i<num_items; i++) {
        vals[i] = i;
        threadpool_add_work(tp, worker, vals+i);
    }

    threadpool_wait(tp);

    for (i=0; i<num_items; i++) {
        printf("%d\n", vals[i]);
    }

    free(vals);
    threadpool_destroy(tp);
    return 0;
}













