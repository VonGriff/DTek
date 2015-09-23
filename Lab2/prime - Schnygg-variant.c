/*
 prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/


//Kod skriven av Alexander Viklund

#include <stdio.h>
#include <math.h>

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

int main(void){
  printf("%d\n", is_prime(-5));  // -5 is not a prime.      Should print 0.
  printf("%d\n", is_prime(0));  // 0 is not a prime.      Should print 0.
  printf("%d\n", is_prime(1));  // 1 is not a prime.      Should print 0.
  printf("%d\n", is_prime(2));  // 2 is a prime.      Should print 1.
  printf("%d\n", is_prime(6));  // 6 is not a prime.      Should print 0.
  // Added all tests above this line
  printf("%d\n", is_prime(11));  // 11 is a prime.      Should print 1.
  printf("%d\n", is_prime(383)); // 383 is a prime.     Should print 1.
  printf("%d\n", is_prime(987)); // 987 is not a prime. Should print 0.
}
