#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
int n=0, i;
int series[];
void *runner(void *param);
void modify_n(int y){
	n=y;
}
int main(int argc, char *argv[]) {
	int y;
	pthread_t tid; //Thread id
	pthread_attr_t attr; //Thread attr
	pthread_attr_init(&attr); //Assigning attr
	printf("Enter the number of terms: "); //User input
	scanf("%d", &y);
	modify_n(y); //Assigning value to global varable which is shared by all threads
	pthread_create(&tid,&attr,runner,argv[1]); //Thread creation which waits for the runner function to execute
	pthread_join(tid,NULL);
	printf("Fibonacci Series: "); //Output Fibonacci
	for (i = 0; i < n; i++) {
	printf("%d, ", series[i]);
	}
}

void *runner(void *param){
	int t1 = 0, t2 = 1, nextTerm,b=0;

    for (i = 1; i <= n; ++i) {
    	series[b]=t1;
    	b++;
        nextTerm = t1 + t2;
        t1 = t2;
        t2 = nextTerm;
    }
	pthread_exit(0);
}
