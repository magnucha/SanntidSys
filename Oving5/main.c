#include <pthread.h>
#include <unistd.h>
#include "io.h"

void* test_A(void* arg){
	while(1){
		while(io_read(1));
		io_write(1, 0);
		usleep(5);
		io_write(1, 1);
	}
}
void* test_B(void* arg){
	while(1){
		while(io_read(2));
		io_write(2, 0);
		usleep(5);
		io_write(2, 1);
	}
}
void* test_C(void* arg){
	while(1){
		while(io_read(3));
		io_write(3, 0);
		usleep(5);
		io_write(3, 1);
	}
}

int main(){
	io_init();
	pthread_t thread_A;
	pthread_t thread_B;
	pthread_t thread_C;
	
	pthread_create(&thread_A, NULL, test_A, NULL);
	pthread_create(&thread_B, NULL, test_B, NULL);
	pthread_create(&thread_C, NULL, test_C, NULL);

	pthread_join(thread_A, NULL);
	pthread_join(thread_B, NULL);
	pthread_join(thread_C, NULL);

	return 0;
}
