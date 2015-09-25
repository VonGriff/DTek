#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Kod skriven av Johan Käck
//i grupp med Alexander Viklund

typedef char bool;

#define TRUE 1
#define FALSE 0
#define COLUMNS 6

int c = 0;

void print_number(int n) {
	//Här händer grejer
	printf("%10d", n);
	c++;
	if(c == COLUMNS) {
		printf("\n");
		c = 0;
	}
}

int print_sieves(int n) { 	//Nära 300 000 000 under 10 sekunder
							//ca 50 000 000 under 2 sekunder
	if(n < 2)		//Om mindre än 2, negativt tal eller ej primtal
		return 0;

	int *sieves = &n;
	//bool sieves[n];
	int i;
	int max = sqrt(n);

	sieves = malloc(n*sizeof(int));
	if(sieves == NULL)
		printf("ERROR: out of memory. \n");
	else {
		for(i = 2; i < n; i++) { //Sätter alla index från 2 - n till 1
			sieves[i] = TRUE;
		}

		for(i = 2; i <= max; i++) { // Går igenom alla index från 2 - (roten ur n)
			if(sieves[i]) {
				int j;
				for(j = i*i; j < n; ) { 
					sieves[j] = FALSE;
					j += i;
				}
			}
		}

		for(i = 2; i < n; i++) {
			if(sieves[i]) {
				print_number(i);
			}
		}
	}
	free(sieves);
	printf("\n");
	return 0;
}

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
	if(argc == 2)
    	print_sieves(atoi(argv[1]));
	else
		printf("Please state an interger number.\n");
	return 0;
}