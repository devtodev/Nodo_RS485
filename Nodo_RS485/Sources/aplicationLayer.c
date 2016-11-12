// SEP16
#include "derivative.h"   
#include "dataLink.h"
#include "aplicationLayer.h"
#include "utilityLayer.h"
#include "gendefs.h"
#include "config.h"

// variables ambientales

#pragma DATA_SEG DIRECT MY_ZEROPAGE

unsigned char status = NEW;
unsigned char ledMode;

unsigned char isBroadcast(struct tipo_trama tramaCompleta) 
{
  return ( (tramaCompleta.ID[0] == ID1BROADCAST) && (tramaCompleta.ID[1] == ID2BROADCAST) );
}

// comandos broadcast & unicast  


unsigned char nuevo(struct tipo_trama tramaCompleta) 
{
  // SI ES NUEVO SE PRESENTA
  if ( ((status == NEW) && (isBroadcast(tramaCompleta))) ||
       (!isBroadcast(tramaCompleta)) )
  {
    return respondeTipo(); 
  }
  // si es nuevo tiene que recibir respuesta enviada, de lo contrario reintentar
  return TRAMA_PROCESADA_CORRECTAMENTE;
}

unsigned char respondeTipo(void) 
{
  unsigned char datos[5];
  datos[0] = TIPO_ROBOT;
  datos[1] = MODELO;
  datos[2] = 0;
  datos[3] = 0;
  datos[4] = 0;
  responder(GETNUEVO, datos);  
  return TRAMA_PROCESADA_CORRECTAMENTE;  
}

unsigned char setLedMode(struct tipo_trama tramaCompleta) 
{
  ledMode = tramaCompleta.datos[0];
  if (ledMode == 0) 
  {
   LED_STATUS = OFF;
  }
  if (ledMode == 1) 
  {
   LED_STATUS = ON;
  }
  if (ledMode == 2)
  {
   LED_STATUS = ON;
  }
  responderTRAMA(GETNUEVO, TRAMA_PROCESADA_CORRECTAMENTE);
  
  return TRAMA_PROCESADA_CORRECTAMENTE;
}

unsigned char setSwitch(struct tipo_trama tramaCompleta) 
{
  shift_out_switches(tramaCompleta.datos[0]);
  return TRAMA_PROCESADA_CORRECTAMENTE;
}

// comandos de capa


unsigned char ejecutarFuncion(void) 
{
  struct tipo_trama trama = getTrama();
  // Broadcast o ID
  if (trama.funcion == GETNUEVO) return nuevo(trama);
  if (trama.funcion == GETTIPO)  return respondeTipo();
  if (trama.funcion == SETLED)   return setLedMode(trama);
  if (trama.funcion == SETSWITCHES) return setSwitch(trama);
  if (trama.funcion == GETSWITCHES) return setSwitch(trama);
  
  return FUNCION_DESCONOCIDA;
}

void setAppStatus(unsigned char estado) 
{
  status = estado;
}

unsigned char getAppStatus(void) 
{
  return status;
}