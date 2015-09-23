/*
 prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/

//Kod skriven av Johan Keck

#include <stdio.h>
/*
Bajsinvecklad funktion
Basically:
	if n<2 return 0
	if n < 4 return 1
	if n > 4 
		for i-> n      	<-------------\
			if n not divisible by i --/
			if n divisible by i return 0
		No i (0<i<n) was a divisor to n -> is prime, return 1

	if n = 4 return 0

	Sluta spaghettikoda så jäkla mycket!

*/
int is_prime(int n){
	int i;
	if(n<2) {} //1, 0 eller negativa nummer sorteras bort
	else if(n<4) //Om n är 2 eller 3 är de primtal
		return 1;
	else if(n>4) {
		for(i=3; i<n; i++) {
			if(n%i != 0) //Om n ej är jämt delbar med i, fortsätt
				continue;
			return 0;
		}
		return 1;
	}
	return 0;
}

int main(void){
  printf("%d\n", is_prime(11));  // 11 is a prime.      Should print 1.
  printf("%d\n", is_prime(383)); // 383 is a prime.     Should print 1.
  printf("%d\n", is_prime(987)); // 987 is not a prime. Should print 0.
}
