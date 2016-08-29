#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>

sem_t resource;

void* thread_1(void* arg){
	for (int i=0;i<4;i++) {
		sem_wait(&resource);
		printf("Thread: 1, Loop: %i\n", i);
		sem_post(&resource);
	}
}

void* thread_2(void* arg){
	for (int i=0;i<4;i++) {
		sem_wait(&resource);
		printf("Thread: 2, Loop: %i\n", i);
		sem_post(&resource);
	}
}

void* thread_3(void* arg){
	for (int i=0;i<4;i++) {
		sem_wait(&resource);
		printf("Thread: 3, Loop: %i\n", i);
		sem_post(&resource);
	}
}

void* thread_4(void* arg){
	for (int i=0;i<4;i++) {
		sem_wait(&resource);
		printf("Thread: 4, Loop: %i\n", i);
		sem_post(&resource);
	}
}

void* thread_5(void* arg){
	for (int i=0;i<4;i++) {
		sem_wait(&resource);
		printf("Thread: 5, Loop: %i\n", i);
		sem_post(&resource);
	}
}

int main(void){
	sem_init(&resource, 0, 3);
	
	pthread_t thread1;
	pthread_t thread2;
	pthread_t thread3;
	pthread_t thread4;
	pthread_t thread5;

	pthread_create(&thread1, NULL, &thread_1, NULL);
	pthread_create(&thread2, NULL, &thread_2, NULL);
	pthread_create(&thread3, NULL, &thread_3, NULL);
	pthread_create(&thread4, NULL, &thread_4, NULL);
	pthread_create(&thread5, NULL, &thread_5, NULL);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);
	pthread_join(thread4, NULL);
	pthread_join(thread5, NULL);
}
