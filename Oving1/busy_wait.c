#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/times.h>

void busy_wait_delay(int seconds)
{
	int i, dummy;
 	int tps = sysconf(_SC_CLK_TCK);
 	clock_t start; 
 	struct tms exec_time;

 	times(&exec_time);
 	start = exec_time.tms_utime;

	while( (exec_time.tms_utime - start) < (seconds * tps)){
 		for(i=0; i<1000; i++){
 			dummy = i;
 		}
 	times(&exec_time);
 	}
}

void* thread_1(void* arg){
	printf("Thread 1 before sleep\n");
	busy_wait_delay(5);
	printf("Thread 1 after sleep\n");
}

void* thread_2(void* arg){
	printf("Thread 2 before sleep\n");
	busy_wait_delay(5);
	printf("Thread 2 after sleep\n");
}

int main(void){
	pthread_t thread1;
	pthread_t thread2;

	pthread_create(&thread1, NULL, &thread_1, NULL);
	pthread_create(&thread2, NULL, &thread_2, NULL);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
}