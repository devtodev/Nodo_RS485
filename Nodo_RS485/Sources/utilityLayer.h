#define LAT         PTBD_PTBD2
#define CLK         PTBD_PTBD4
#define DATA        PTBD_PTBD3
#define SHMASK      0x80
#define MAXBITS     8

void shift_out_switches(unsigned char c); // actuadores
unsigned char getValue(); // actuadores