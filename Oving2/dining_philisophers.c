#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t fork1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t fork2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t fork3 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t fork4 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t fork5 = PTHREAD_MUTEX_INITIALIZER;

void* philisopher_1(void* arg){
	while(1){
		pthread_mutex_lock(&fork1);
		pthread_mutex_lock(&fork2);
		printf("Philospher 1 is eating\n");
		usleep(10);
		pthread_mutex_unlock(&fork2);
		pthread_mutex_unlock(&fork1);
		usleep(10);
	}
}

void* philisopher_2(void* arg){
	while(1){
		pthread_mutex_lock(&fork2);
		pthread_mutex_lock(&fork3);
		printf("Philospher 2 is eating\n");
		usleep(10);
		pthread_mutex_unlock(&fork3);
		pthread_mutex_unlock(&fork2);
		usleep(10);
	}
}

void* philisopher_3(void* arg){
	while(1){
		pthread_mutex_lock(&fork3);
		pthread_mutex_lock(&fork4);
		printf("Philospher 3 is eating\n");
		usleep(10);
		pthread_mutex_unlock(&fork4);
		pthread_mutex_unlock(&fork3);
		usleep(10);
	}
}

void* philisopher_4(void* arg){
	while(1){
		pthread_mutex_lock(&fork4);
		pthread_mutex_lock(&fork5);
		printf("Philospher 4 is eating\n");
		usleep(10);
		pthread_mutex_unlock(&fork5);
		pthread_mutex_unlock(&fork4);
		usleep(10);
	}
}

void* philisopher_5(void* arg){
	while(1){
		pthread_mutex_lock(&fork5);
		pthread_mutex_lock(&fork1);
		printf("Philospher 5 is eating\n");
		usleep(10);
		pthread_mutex_unlock(&fork1);
		pthread_mutex_unlock(&fork5);
		usleep(10);
	}
}

int main(void){
	pthread_t philisopher1;
	pthread_t philisopher2;
	pthread_t philisopher3;
	pthread_t philisopher4;
	pthread_t philisopher5;

	pthread_create(&philisopher1, NULL, &philisopher_1, NULL);
	pthread_create(&philisopher2, NULL, &philisopher_2, NULL);
	pthread_create(&philisopher3, NULL, &philisopher_3, NULL);
	pthread_create(&philisopher4, NULL, &philisopher_4, NULL);
	pthread_create(&philisopher5, NULL, &philisopher_5, NULL);


	pthread_join(philisopher1, NULL);
	pthread_join(philisopher2, NULL);
	pthread_join(philisopher3, NULL);
	pthread_join(philisopher4, NULL);
	pthread_join(philisopher5, NULL);
}
