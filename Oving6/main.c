#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/mman.h>
#include <native/task.h>
#include <native/timer.h>
#include <rtdk.h>
#include "io.h"

int set_cpu(int cpu_number){
	// setting cpu set to the selected cpu
	cpu_set_t cpu;
	CPU_ZERO(&cpu);
	CPU_SET(cpu_number, &cpu);
	// set cpu set to current thread and return
	return pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t),&cpu);
}

void test_A(void* arg){
	rt_task_set_periodic(NULL, TM_NOW, 100000);
	while(1){
		if(!io_read(1)){
			io_write(1, 0);
			usleep(5);
			io_write(1, 1);
		}
		rt_task_wait_period(NULL);
	}
}

void test_B(void* arg){
	rt_task_set_periodic(NULL, TM_NOW, 100000);
	while(1){
		if(!io_read(2)){
			io_write(2, 0);
			usleep(5);
			io_write(2, 1);
		}
		rt_task_wait_period(NULL);
	}
}

void test_C(void* arg){
	rt_task_set_periodic(NULL, TM_NOW, 100000);
	while(1){
		if(!io_read(3)){
			io_write(3, 0);
			usleep(5);
			io_write(3, 1);
		}
		rt_task_wait_period(NULL);
	}
}

void* disturbance(void* arg){
	int i=0;
	while (1) {
		if (i++ > 10049) {
			i /= 2;
		}
	}
}

int main(){
	io_init();
	set_cpu(1);
	rt_print_auto_init(1);
	
	mlockall(MCL_CURRENT|MCL_FUTURE);
	
	RT_TASK task_A;
	RT_TASK task_B;
	RT_TASK task_C;
	
	rt_task_create(&task_A, "Task A", 0, 50, T_JOINABLE);
	rt_task_create(&task_B, "Task B", 0, 50, T_JOINABLE);
	rt_task_create(&task_C, "Task C", 0, 50, T_JOINABLE);
	
	rt_task_start(&task_A, &test_A, NULL);
	rt_task_start(&task_B, &test_B, NULL);
	rt_task_start(&task_C, &test_C, NULL);
	
	
	pthread_t disturbances[10];
	int i;
	for(i = 0; i < 10; i++){
		pthread_create(&disturbances[i], NULL, disturbance, NULL);
	}
	for(i = 0; i < 10; i++){
		pthread_join(disturbances[i], NULL);
	}
	
	rt_task_join(&task_A);
	rt_task_join(&task_B);
	rt_task_join(&task_C);

	
	return 0;
}
