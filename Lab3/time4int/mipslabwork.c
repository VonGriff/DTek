/* mipslabwork.c

   This file written 2015 by F Lundevall

   This file should be changed by YOU! So add something here:

   This file modified 2015-12-24 by Ture Teknolog 

   Latest update 2015-08-28 by F Lundevall

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

#define T2CONCLR  PIC32_R(0x0804)
#define PR3 PIC32_R(0x0A20)
#define IEC0SET PIC32_R(0xBF881068)
#define IPC2SET PIC32_R(0xBF8810B8)

int mytime = 0x5957;
int prime = 1234567;
int timeoutcount = 0;

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void ) {
  if (IFS(0)&0x100) {
    timeoutcount++;
    IFS(0) = 0;
  }
  if (timeoutcount == 10) {
    time2string( textstring, mytime );
    display_string( 3, textstring );
    display_update();
    tick( &mytime );
    timeoutcount = 0;
  }
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  volatile int* trise = (int*) 0xbf886100;
  *trise = *trise & 0xFFFFFF00; //set the last 8 bits to 0.
  TRISDSET = 0xFE0; //Set bits 11-5

  T2CONSET = 0x0070; //x-x- ---- x111 x-x- From timer-ref.sheet
  T2CONCLR = 0x000A; //x-x- ---- xxxx 0-0-  --------||--------
  
  PR2 = 0x7A12; //                          --------||--------
  
  //interruptstuff
  IEC(0) = 0x0100;
  IPC(2) = 0x001F;
  //IEC0SET = 0x0100;
  //IPC2SET = 0x001F;
  enable_interrupt();
  T2CONSET = 0x8000; //Start the timer 
  //IFS(0) = 0x100;
  return;
}



/* This function is called repetitively from the main program */
void labwork( void ) {
  prime = nextprime( prime );
  display_string( 0, itoaconv( prime ) );
  display_update();
}
