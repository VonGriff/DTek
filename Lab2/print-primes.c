/*
 print-prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/

//Kod skriven av Johan Käck
//i grupp med Alexander Viklund

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define COLUMNS 6

int c = 0;

int is_prime(int n){
  if (n < 2) //if n is negative, 0 or 1 then it's not a prime 
    return 0;
  int max = sqrt(n);

  int i;
  for(i = 2; i <= max; i++) {
    if (n%i == 0)
      return 0;
  }
  return 1;
}

void print_number(int n) {
  //Här händer grejer
  printf("%10d", n);
  c++;                //Inkrementerar c varje gång vi får ett primtal
  if(c == COLUMNS) {  //Printar ny rad då c uppnått antalet COLUMNS och återställer till 0
    printf("\n");
    c = 0;
  }
}

void print_primes(int n){ // Klarar ca 110 000 på 2 sekunder
  // Should print out all prime numbers less than 'n'
  // with the following formatting. Note that
  // the number of columns is stated in the define
  // COLUMNS

  int i;

  for(i=2; i<n; i++) {
    if(is_prime(i)) {
      print_number(i);

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

 
