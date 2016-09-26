#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/mman.h>
#include <native/task.h>
#include <native/timer.h>
#include <native/sem.h>
#include <rtdk.h>
#include "io.h"

RT_SEM sem;

int set_cpu(int cpu_number){
	// setting cpu set to the selected cpu
	cpu_set_t cpu;
	CPU_ZERO(&cpu);
	CPU_SET(cpu_number, &cpu);
	// set cpu set to current thread and return
	return pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t),&cpu);
}

void test_A() {
	rt_sem_p(&sem, TM_INFINITE);
	rt_printf("Task A");
}

void test_B() {
	rt_sem_p(&sem, TM_INFINITE);
	rt_printf("Task B");
}


int main(){
	io_init();
	set_cpu(1);
	rt_print_auto_init(1);
	
	mlockall(MCL_CURRENT|MCL_FUTURE);
	
	RT_TASK task_A;
	RT_TASK task_B;
	
	rt_sem_create(&sem, "Semaphore", 1, S_PRIO);
	rt_sem_p(&sem, TM_INFINITE);

	rt_task_shadow(NULL, "Main", 99, NULL);
	rt_task_create(&task_A, "Task A", 0, 60, T_JOINABLE);
	rt_task_create(&task_B, "Task B", 0, 50, T_JOINABLE);

	rt_task_start(&task_A, &test_A, NULL);
	rt_task_start(&task_B, &test_B, NULL);

	usleep(100000);
	rt_sem_broadcast(&sem);
	usleep(100000);
	
	rt_task_join(&task_A);
	rt_task_join(&task_B);

	rt_sem_delete(&sem);

	
	return 0;
}
