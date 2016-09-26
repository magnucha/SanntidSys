#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/mman.h>
#include <native/task.h>
#include <native/timer.h>
#include <native/sem.h>
#include <native/mutex.h>
#include <rtdk.h>
#include "io.h"

RT_SEM sem;
RT_MUTEX resource1;
RT_MUTEX resource2;

int resource_prio = 10;

int set_cpu(int cpu_number){
	// setting cpu set to the selected cpu
	cpu_set_t cpu;
	CPU_ZERO(&cpu);
	CPU_SET(cpu_number, &cpu);
	// set cpu set to current thread and return
	return pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t),&cpu);
}

void print_pri(RT_TASK *task, char *s) {
	struct rt_task_info temp;
	rt_task_inquire(task, &temp);
	rt_printf("b:%i c:%i ", temp.bprio, temp.cprio);
	rt_printf(s);
}

int rt_task_sleep_ms(unsigned long delay){
	return rt_task_sleep(1000*1000*delay);
}

void busy_wait_ms(unsigned long delay) {
	unsigned long count = 0;
	while (count <= delay*10){
		rt_timer_spin(1000*100);
		count++;
	}
}

void task_L() {
	rt_sem_p(&sem, TM_INFINITE);
	rt_mutex_acquire(&resource1, TM_INFINITE);
	rt_task_set_priority(rt_task_self(), resource_prio);
	print_pri(rt_task_self(), "Task L\n");
	busy_wait_ms(3);
	rt_mutex_acquire(&resource2, TM_INFINITE);
	busy_wait_ms(3);
	rt_mutex_release(&resource2);
	rt_mutex_release(&resource1);
	print_pri(rt_task_self(), "Task L\n");
	rt_task_set_priority(rt_task_self(), 2);
	busy_wait_ms(1);
	print_pri(rt_task_self(), "Task L\n");
}

void task_H() {
	rt_sem_p(&sem, TM_INFINITE);
	rt_task_sleep_ms(1);
	rt_mutex_acquire(&resource2, TM_INFINITE);
	rt_task_set_priority(rt_task_self(), resource_prio);
	print_pri(rt_task_self(), "Task H\n");
	busy_wait_ms(1);
	rt_mutex_acquire(&resource1, TM_INFINITE);
	busy_wait_ms(2);
	rt_mutex_release(&resource1);
	rt_mutex_release(&resource2);
	print_pri(rt_task_self(), "Task H\n");
	rt_task_set_priority(rt_task_self(), 3);
	busy_wait_ms(1);
	print_pri(rt_task_self(), "Task H\n");
}


int main(){
	io_init();
	set_cpu(1);
	rt_print_auto_init(1);
	
	mlockall(MCL_CURRENT|MCL_FUTURE);
	
	RT_TASK task_A;
	RT_TASK task_B;
	
	rt_sem_create(&sem, "Semaphore", 0, S_PRIO);
	rt_mutex_create(&resource1, "Mutex1");
	rt_mutex_create(&resource2, "Mutex2");

	rt_task_shadow(NULL, "Main", 99, 0);
	rt_task_create(&task_A, "Task A", 0, 3, T_CPU(0)|T_JOINABLE);
	rt_task_create(&task_B, "Task B", 0, 2, T_CPU(0)|T_JOINABLE);

	rt_task_start(&task_A, &task_H, NULL);
	rt_task_start(&task_B, &task_L, NULL);

	rt_task_sleep_ms(100);
	rt_sem_broadcast(&sem);
	rt_task_sleep_ms(100);
	
	rt_task_join(&task_A);
	rt_task_join(&task_B);

	rt_sem_delete(&sem);
	rt_mutex_delete(&resource1);
	rt_mutex_delete(&resource2);
	
	return 0;
}
