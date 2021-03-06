#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void* thread_1(void* arg){
	printf("Thread 1 before sleep\n");
	sleep(5);
	printf("Thread 1 after sleep\n");
}

void* thread_2(void* arg){
	printf("Thread 2 before sleep\n");
	sleep(5);
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