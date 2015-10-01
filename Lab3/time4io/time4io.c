#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

int getsw(void);






int getsw(void) 
{
	int retVal = PORTD>>8;
	retval = retval & 0x000F;
	return retVal;
}