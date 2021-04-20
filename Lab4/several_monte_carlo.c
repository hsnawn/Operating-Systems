#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define SEED 35791246
#define NR_PTS 10000000
#define NR_THREADS 20
#define NR_PTRS_PER_THREAD NR_PTS/NR_THREADS

int count = 0;	
pthread_t *threads;		
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *calculate_pi(void *tid) {

	long i;							
	int a = (int) tid;		/* Thread Number */
	long thread_in = 0; 		/* count for points in the circle */
	
	double x,y,z;
	
	/* Check for ponits lie within circle or not */
	
	for (i = 0; i < NR_PTRS_PER_THREAD; i++) 
	{
		
		x = (double)rand()/RAND_MAX;
        y = (double)rand()/RAND_MAX;
        z = x*x+y*y;
        if (z<=1) thread_in++;

	}

	/* value of pi for this thread */
	
	double pi =  ((double)thread_in / ((double)NR_PTRS_PER_THREAD) * 4);
	printf("Vlaue of Pi in Thread %d is %g. \n" ,a,pi);
	pthread_mutex_lock(&mutex);
	count += thread_in;
	pthread_mutex_unlock(&mutex);

return NULL;

}


void createThreads(){
	
	int i, s; //Thread count variables
	threads = malloc(NR_THREADS * sizeof(pthread_t)); //memory allocation
	pthread_attr_t attr; //Thread attr
	pthread_attr_init(&attr); //Assigning attr
	
	/* Creating separate threads */
	
	for (i = 0; i < NR_THREADS; i++)
	 {
		s = pthread_create(&threads[i], &attr, calculate_pi,  (void *) i);
	}

}


void joinThreads()
{
	int i, s; 	// Thread count variables
	for (i = 0; i < NR_THREADS; i++) 
	{
		s = pthread_join(threads[i], NULL);	
	}

	pthread_mutex_destroy(&mutex);
	free(threads);
}

int main() 
{

	double pi;
	createThreads();
	joinThreads();
	pi = (((double)count) / ((double)NR_PTRS_PER_THREAD * NR_THREADS))*4;
	printf("\nValue of Pi after all threads is %g.", pi);
	
return 0;

}
