#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define SEED 35791246
int niter, count=0; //Global variable of number of points occuring within a circle
void modify_niter(int y){
	niter=y;
}
void *runner(void *param);
main(int argc, char* argv)
{
	pthread_t tid; //Thread id
	pthread_attr_t attr; //Thread attr
	pthread_attr_init(&attr); //Assigning attr
	int b=0;
	double pi;

   printf("Enter the number of iterations used to estimate pi: ");
   scanf("%d",&b);
   modify_niter(b);
   
   pthread_create(&tid,&attr,runner,argv[1]); //Thread creation which waits for the runner function to execute
   pthread_join(tid,NULL);
   
   pi=(double)count/niter*4;
   printf("# of trials= %d , estimate of pi is %g \n",niter,pi);
}
void *runner(void *param){
   double x,y;
   int i; /* # of points in the 1st quadrant of unit circle */
   double z;
   /* initialize random numbers */
   srand(SEED);
   count=0;
   for ( i=0; i<niter; i++) {
      x = (double)rand()/RAND_MAX;
      y = (double)rand()/RAND_MAX;
      z = x*x+y*y;
      if (z<=1) count++;
      }
	pthread_exit(0);
}
