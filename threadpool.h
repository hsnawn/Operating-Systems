// include guards
#ifndef _THREADPOOL_H
#define _THREADPOOL_H

#include <stdbool.h> //for bool variable bool x = true/false; 
#include <stddef.h>  //for NULL % size_t

struct threadpool;
typedef struct threadpool threadpool_t;
typedef void (*thread_function)(void *arguments);

threadpool_t *threadpool_create(size_t num); //size_t undefined integer
void threadpool_destroy(threadpool_t *tp);

bool threadpool_add_work(threadpool_t *tp, thread_function func, void *arg);
void threadpool_wait(threadpool_t *tp);

#endif //_THREADPOOL_H




//void execute(void (*somefunction)(void *p), void *p);
//int pool_submit(void (*somefunction)(void *p), void *p);
//void *worker(void *param);
//void pool_init(void);
//void pool_shutdown(void);

