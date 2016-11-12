#include "derivative.h"
#include "utilityLayer.h"
#include "config.h"
#include "gendefs.h"

// utility layer correspondiente al actuador

void shftdelay(void);

void shift_out_switches(unsigned char c)
{
    char x;
    unsigned char mask = SHMASK;
    
    for( x = 0 ; x < MAXBITS ; ++x )
    {
        if( c & mask )
            DATA = 1;
        else
            DATA = 0;

        mask >>= 1;
        
        CLK = 1;
        shftdelay();
        CLK = 0;                                        
    }
    LAT = 1;
    shftdelay();
    LAT = 0;
}

unsigned char getValue(void) 
{
  SENSOR_TXD = 0;
  shftdelay();
  shftdelay();
  SPID = 1;
  shftdelay();
  shftdelay();
  SENSOR_TXD = 1;
  return SPID;
}


void
shftdelay(void)
{
    asm "NOP";
    asm "NOP";
    asm "NOP";
    asm "NOP";
    asm "NOP";
}

