#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 6

void print_number(int n) {
	//Här händer grejer
	printf("%10d", n);
}

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
	if(argc == 2)
    	print_primes(atoi(argv[1]));
	else
		printf("Please state an interger number.\n");
	return 0;
}