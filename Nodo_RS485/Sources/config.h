#define LED_STATUS             PTAD_PTAD0 // PTBD_PTBD3 primero
#define SENSOR_TXD             PTBD_PTBD5 
/* 
 Esto determina el tipo de aplication y utility Layer
 TIPO_ROBOT 0 MASTER
 TIPO_ROBOT 1 SENSOR
 TIPO_ROBOT 2 ACTUADOR
 
1)
  MODELO      0 temperatura ambiente
              1 temperatura liquido
              2 porcentaje humedad ambiente
              3 luz
              4 CO2
  
2)
  MODELO      1 SWITCH ON-OFF
              2 MOTOR PASO A PASO
 
 */
#define TIPO_ROBOT      2
#define MODELO          1
