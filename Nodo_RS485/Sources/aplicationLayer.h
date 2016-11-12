// SEP16
// ESTADOS

#define NEW           0
#define REGISTRADO    1                                
/*                                
#define NEW           0
#define IDLE          1
#define VERIFICANDO   2
#define ENVIANDO      3
#define UPROCESANDO   4
#define BPROCESANDO   5
#define FORMATERROR   6
#define SENDERROR     7
#define SENDRESPUESTA 8       */

                   
// funciones
#define GETNUEVO              1
#define GETTIPO               2
#define SETLED                3
#define SETSWITCHES           4
#define GETSWITCHES           5

unsigned char ejecutarFuncion(void);

// comandos broadcast

unsigned char nuevo(struct tipo_trama tramaCompleta);

// comandos unicast

unsigned char getStatus(struct tipo_trama tramaCompleta);
unsigned char respondeTipo(void);
void setLed(struct tipo_trama tramaCompleta);

unsigned char setSwitch(struct tipo_trama tramaCompleta);

// comandos de capa
void setAppStatus(unsigned char estado);
unsigned char getAppStatus(void);