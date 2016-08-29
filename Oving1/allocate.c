#include <stdlib.h>
#include <stdio.h>


//This will allocate memory until there are no more memory to give and the computer freezes
void allocate(int value){
	int *ptr = NULL;
	ptr = malloc(100000 * sizeof(int));
	if(ptr == NULL){
		perror("Error: ");
		exit(1);
	}
 	*ptr = value;
 	printf("test of allocate memory: %i\n", *ptr);
} 

int main(){
	time_t t;

	srand((unsigned) time(&t));
	while(1){
		allocate(rand());
	}
}