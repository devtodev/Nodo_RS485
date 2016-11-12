/*
 *    Interfaz de comunicacion
 *    cmiguens@agrorobots
 *    05/11/13
 */

// Identificador unico de Dispositivo
#define ID1                   0
#define ID2                   3
#define ID1BROADCAST          0
#define ID2BROADCAST          0

// bytes de la trama
#define DIRECCION             0 //  XX00000000
#define FUNCION               2 //  00X0000000
#define DATOS                 3 //  000XXXXXX0
#define CRC                   9 //  000000000X
#define LARGOTRAMA            10

// estados
#define ESPERA_TRAMA                          0
#define TRAMA_ENVIANDO                        1
#define TRAMA_RECIBIENDO                      2
#define TRAMA_COMPLETA                        3
#define TRAMA_PROCESADA_CORRECTAMENTE       100

#define DELAY_ENTRE_TRAMA     5
#define TIME_TO_TIMEOUT       50

// excepciones
#define OTRO_DESTINATARIO     200
#define FUNCION_DESCONOCIDA   201
#define CRC_ERROR             203
#define TIMEOUT               204

typedef struct tipo_trama {
  unsigned char ID[2];
  unsigned char funcion;
  unsigned char datos[5];
  unsigned char crc;
};

//unsigned char getEstadoBus(void);
//void setEstadoBus(unsigned char estado);

void tramaAdd(unsigned char dato); // llamado desde la intrx

struct tipo_trama getTrama(void);
unsigned char analizarTrama(void);
void responder(unsigned char funcion, unsigned char datos[5]);
void responderTRAMA(unsigned char funcion, unsigned char conclucion);
void enviarTrama(void);
unsigned char evaluarBusDatos(void); // llamado desde el main
void enviarTramaCursor(unsigned char cursor);

/*
unsigned int calcularCRC(unsigned long int *data, unsigned char dataLen);
void addCRC(unsigned long int *data, unsigned char dataLen, unsigned int crc);
int testCRC(unsigned long int *data, unsigned char dataLen);
int modbusSendQuery(unsigned long int *data, unsigned char dataLen, unsigned char hasCRC);
int modbusReadResponse(unsigned long int *data, unsigned char hasCRC);
void modbusBuildQueryPacket(st_modbusQuery modbusQuery, unsigned long int *queryPacket);
void modbusExceptionVerify(unsigned long int *packet, st_modbusExceptionCode *exceptionCode);
int modbusRespErrorsVerify(unsigned long int *responsePacket, int byteCount, st_modbusExceptionCode *exceptionCode, unsigned char hasCrc);
int modbusReadCoilStatus(st_modbusQuery modbusQuery, st_modbusIOGeneric *coilStatus, st_modbusExceptionCode *exceptionCode, unsigned char hasCrc);
*/