/**
  * Kod skriven av Alexander Viklund
  * i grupp med Johan Käck
  *
  * 
  *
 **/
#include <stdio.h>



char* text1 = "This is a string.";
char* text2 = "Yet another thing.";

int list1[20]; 
int list2[20]; 

int count = 0;



void printlist(const int* lst){
  printf("ASCII codes and corresponding characters.\n");
  while(*lst != 0){
    printf("0x%03X '%c' ", *lst, (char)*lst);
    lst++;
  }
  printf("\n");
}

void endian_proof(const char* c){
  printf("\nEndian experiment: 0x%02x,0x%02x,0x%02x,0x%02x\n", 
         (int)*c,(int)*(c+1), (int)*(c+2), (int)*(c+3));
  
}

int main(void){
  work();

  printf("\nlist1: ");
  printlist(list1);
  printf("\nlist2: ");
  printlist(list2);
  printf("\nCount = %d\n", count);

  endian_proof((char*) &count);
}


/*
  PUSH  ($ra)
  la  $a0,text1
  la  $a1,list1
  la  $a2,count
  jal copycodes
  
  la  $a0,text2
  la  $a1,list2
  la  $a2,count
  jal copycodes
  POP ($ra)
*/
work(void) {
  copycodes(text1, list1, &count);
  copycodes(text2, list2, &count);
 }

/*
  lb  $t0,0($a0)  t0 = *a0
  sw  $t0,0($a1)  *a1 = t0
  beq $t0,$0,done

  addi  $a0,$a0,1 a0++
  addi  $a1,$a1,4 a1+=4 - it's an int though so a1++
  
  lw  $t1,0($a2) t1 = *a2     |
  addi  $t1,$t1,1 t1+=1       | *a2 +=1
  sw  $t1,0,($a2) *a2 = t1    |
  j loop
*/
copycodes(char* a0,int* a1, int* a2) {
  while (*a0 != 0) {
    *a1 = *a0;
    if (*a1 != 0) {
      a0++;
      a1++;

      *a2 = *a2 + 1;
    }
  }
}