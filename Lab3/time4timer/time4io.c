#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

int getsw(void);
int getbtns(void);





int getsw(void) 
{
	int retVal = PORTD>>8;
	retVal = retVal & 0x000F;
	return retVal;
}

int getbtns(void) {
	int retBtn = PORTD>>5;
	retBtn = retBtn & 0x0007;
	return retBtn;
}