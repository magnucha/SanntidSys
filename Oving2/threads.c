#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int global = 0;

void* thread_1(void* arg){
	for (int i=0;i<10;i++) {
		printf("Thread: 1, Global: %i, Local: %i\n", global++, (*(int*)arg)++);
	}
}

void* thread_2(void* arg){
	for (int i=0;i<10;i++) {
		printf("Thread: 2, Global: %i, Local: %i\n", global++, (*(int*)arg)++);
	}
}

int main(void){
	int *local = malloc(sizeof(*local));
	*local = 0;

	pthread_t thread1;
	pthread_t thread2;

	pthread_create(&thread1, NULL, &thread_1, local);
	pthread_create(&thread2, NULL, &thread_2, local);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
}
