#include <stdio.h>
#include <sys/types.h>

int global = 0;

int main(void) {
	int local = 0;
	
	vfork();
	pid_t pid = getpid();
	
	for (int i=0;i<10;i++) {
		printf("Process: %d, Global: %i, Local %i\n", pid, global++, local++);
	}
	_exit(2);
}
