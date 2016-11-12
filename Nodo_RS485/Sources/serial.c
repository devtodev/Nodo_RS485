#include "derivative.h"
#include "gendefs.h"
#include "serial.h"

#pragma DATA_SEG DIRECT MY_ZEROPAGE 

static void txdata_packet(char c);

static
void
txdata_packet(char c)
{
  SCID = c;
	while ( SCIS1_TC == 0 )	/* wait for transmission */
		wait();
}

void
txdata( unsigned char c )
{
//  FIJARSE EL FLAG ! ! ! ! ! !
  TR485 = ON ;
  asm "NOP"; // buffers 
	SCID = c;
	while ( SCIS1_TC == 0 )	/* wait for transmission */
		wait();
  asm "NOP";// buffers
  TR485 = OFF ;
}

int
rxdata(void)
{
	if(  SCIS1_RDRF == 0 )	/* wait for incoming char */
		return -1;
	return (int) SCID;	                   
}

/*
void
tx_print( const char *s )
{
	char i;
	
	i = 0;
	
    TR485 = ON ;
	while( s[i] != '\0' )
		txdata_packet(s[i++]);
    TR485 = OFF ;		
}
*/
