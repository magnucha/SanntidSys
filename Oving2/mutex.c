#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int running = 1;
int var1 = 0, var2 = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* thread_1(void* arg){
	while(running){
		pthread_mutex_lock(&mutex);
		var1++;
		var2 = var1;
		pthread_mutex_unlock(&mutex);
	}
}

void* thread_2(void* arg){
	for(int i = 0; i < 20; i++){
		pthread_mutex_lock(&mutex);
		printf("Number 1 is: %i, number 2 is: %i\n", var1, var2);
		pthread_mutex_unlock(&mutex);
		usleep(100000);
	}
	running = 0;
}

int main(void){
	pthread_t thread1;
	pthread_t thread2;

	pthread_create(&thread1, NULL, &thread_1, NULL);
	pthread_create(&thread2, NULL, &thread_2, NULL);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
}
