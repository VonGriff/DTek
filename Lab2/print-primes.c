/*
 print-prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/


#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 6

int is_prime(int n){
  int i;
  if(n<2) {} //1, 0 eller negativa tal sorteras bort
  else if(n<4) //Om n är 2 eller 3 är de primtal
    return 1;
  else if(n>4) { //Om n är större än 4, kör for loop då 4 ej är ett primtal
    for(i=3; i<n; i++) {
      if(n%i != 0) //Om n ej är jämt delbar med i, fortsätt
        continue;
      return 0;
    }
    return 1;
  }
  return 0;
}

void print_number(int n) {
  //Här händer grejer
  printf("%10d", n);
}

void print_primes(int n){
  // Should print out all prime numbers less than 'n'
  // with the following formatting. Note that
  // the number of columns is stated in the define
  // COLUMNS

  int i, c=0;

  for(i=1; i<n; i++) {
    if(is_prime(i)) {
      print_number(i);
      c++;                //Inkrementerar c varje gång vi får ett primtal
      if(c == COLUMNS) {  //Printar ny rad då c uppnått antalet COLUMNS och återställer till 0
        printf("\n");
        c = 0;
      }
    }
  }

  /*printf("%10d ", 2);
  printf("%10d ", 3);
  printf("%10d ", 5);
  printf("%10d ", 7);
  printf("%10d ", 11);
  printf("%10d ", 13);
  printf("\n");
  printf("%10d ", 17);
  printf("%10d ", 19); */

  printf("\n");
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

 
