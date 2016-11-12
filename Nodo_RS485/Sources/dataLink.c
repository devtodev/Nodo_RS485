#include "dataLink.h"
#include "timer.h"
#include "serial.h"
//#include "aplicationLayer.h"

#pragma DATA_SEG DIRECT MY_ZEROPAGE

unsigned char estado_bus = 0;
unsigned char cursor_trama = 0;
unsigned char trama[10];

unsigned char tramaCRC(void);
unsigned char verificarTrama(void);

struct tipo_trama getTrama(void) 
{
  struct tipo_trama resp;
  int i = 0;
  resp.ID[0] = trama[DIRECCION];
  resp.ID[1] = trama[DIRECCION + 1];
  resp.funcion = trama[FUNCION];
  for (i = 0; i < 5; i++)
    resp.datos[i] = trama[DATOS + i];
  resp.crc = trama[CRC];
  return resp;
}

void responderTRAMA(unsigned char funcion, unsigned char conclucion) 
{
//  setEstadoBus(conclucion);
  trama[0] = ID1;
  trama[1] = ID2;
  trama[2] = funcion;
  trama[3] = conclucion;
  trama[4] = 0;
  trama[5] = 0;
  trama[6] = 0;
  trama[7] = 0;
  trama[8] = tramaCRC();
  
  enviarTrama();
}

void responder(unsigned char funcion, unsigned char datos[5]) 
{
//  setEstadoBus(TRAMA_ENVIANDO);
  trama[0] = ID1;
  trama[1] = ID2;
  trama[2] = funcion;
  trama[3] = datos[0];
  trama[4] = datos[1];
  trama[5] = datos[2];
  trama[6] = datos[3];
  trama[7] = datos[4];
  trama[8] = tramaCRC();
  
  enviarTrama();
}

void enviarTrama(void) 
{
  int i = 0;
  
  for (i = 0; i < LARGOTRAMA; i++)   
  {  
    delay_ms(DELAY_ENTRE_TRAMA);
    txdata(trama[i]); // verificar flag
  }
  
}

unsigned char evaluarBusDatos(void) 
{
 unsigned char respuesta;
 if (cursor_trama == 0) 
 {
  return ESPERA_TRAMA;
 }
 
 if ((cursor_trama > 0) && (getCronometro() == 0))
 {
  cursor_trama = 0;
  return TIMEOUT;
 }
 
 if (cursor_trama == LARGOTRAMA) 
 {
  respuesta = verificarTrama(); // CRC, lenght
  cursor_trama = 0; // reinicia la trama
  return respuesta;
 }
 
 return TRAMA_RECIBIENDO;
}

unsigned char verificarTrama(void) 
{
  unsigned char codigoCRC = trama[CRC];
  unsigned char calcCRC = tramaCRC();
  
  if (codigoCRC != calcCRC)
    return CRC_ERROR;
  
  if ( (trama[DIRECCION] == ID1) && (trama[DIRECCION + 1] == ID2) )   
    return TRAMA_COMPLETA;     
    
  if ((trama[DIRECCION] == ID1BROADCAST) && (trama[DIRECCION + 1] == ID2BROADCAST) )
    return TRAMA_COMPLETA;   
  
  return OTRO_DESTINATARIO;
}

void tramaAdd(unsigned char dato)
{
//  setEstadoBus(TRAMA_RECIBIENDO);
  trama[cursor_trama] = dato;
  cursor_trama++;
  // resetea el contador del timeout
  setCronometro(TIME_TO_TIMEOUT);
}

/*
unsigned char getEstadoBus(void) 
{
  return estado_bus;
}

void setEstadoBus(unsigned char estado) 
{
  estado_bus = estado;
} */

unsigned char tramaCRC(void)
{
	unsigned char crc = 0xFF;
	unsigned char tempCRC;
	
	unsigned char tempLSB, flag;
	int i, j;
	
	for (i = 0; i < CRC; i++) {
		tempLSB = 0xFF & crc;

		crc = tempLSB ^ trama[i];

		for (j = 0; j < 8; j++) {
			tempCRC = crc;
			flag = tempCRC & 0x01;
			crc = crc >> 1;

			if (flag)
				crc = crc ^ 0xA1;
		} 
	} 
	return crc;
}