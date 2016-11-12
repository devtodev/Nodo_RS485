#include "derivative.h"
#include "gendefs.h"
#include "vectors_QE8.h"
#include "timer.h"
#include "serial.h"
#include "dataLink.h"
#include "aplicationLayer.h"


  //SCIS1_PF 
  //SCIS1_FE Frame Error
  //SCIS1_NF 
  //SCIS1_OR 
  //SCIS1_TC Transmit Complete
  //SCIS1_RDRF Receive Data Register is full (es 1 cuando se recive un dato en SCID)
  //SCIS1_IDLE 1 cuando IDLE line is detecte, 0 no IDLE line
  //SCIS1_TDRE Transmit Data Receive Empty
    
/*  llamada desde el Rx input del puerto serial */
interrupt 
SCI_RECEIVE_VECTOR
void
SCI_RECEIVE_interrupt(void) 
{
  byte dato = SCID;
     
  if ( (SCIS1_RDRF == 1) // TDRE
      && (SCIS1_PF == 0) // Parity error Flag
      && (SCIS1_NF == 0) // Noise Flag
      && (SCIS1_FE == 0))// Framing Error
  { 
    tramaAdd(dato);    
  }
  
  SCIS1 = 0;  // baja el flag
}


/* llamada desde el hardware por una interrupcion
    de evento de Timer Overflow ( bit TOF ) */
int countSeg = 0;
struct tipo_trama testy;
unsigned char caracter = 0;

interrupt  
TIMER1_OVF_VECTOR
void
TIMERTICK_interrupt(void)
{
  countSeg++;
  if (countSeg > 1000) {
    countSeg = 0;
    if (caracter <200) caracter++; else caracter = 0;
    testy.ID[0] = 0;
    testy.ID[1] = 0;
    testy.datos[0] = caracter;
    testy.datos[1] = 0;
    testy.datos[2] = 0;
    testy.datos[3] = 0;
    testy.datos[4] = 0;
    testy.datos[5] = 0;
    testy.crc = setSwitch(testy);
  }
    /* aqui cada 1 ms */
 	TPM1SC_TOF = 0; /* bajar el flag de interrupt por TOF */
	timer();
}

