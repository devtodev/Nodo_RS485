#include "derivative.h"
#include "gendefs.h"
#include "timer.h"


#pragma DATA_SEG DIRECT MY_ZEROPAGE

static unsigned int delay ;


/* aqui cada 1 ms - llamada desde interrupt del timer */

void
timer(void)
{
	if( delay )
		--delay;
		
}

void setCronometro(unsigned int t) 
{
  delay = t;
}

unsigned int getCronometro(void) 
{
  return delay;
}

void
delay_ms(unsigned int t)
{
	delay = t;
	while( delay )
		wait();	
}


