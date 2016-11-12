#include "derivative.h" /* include peripheral declarations */
#include "gendefs.h"
#include "serial.h"
#include "timer.h"
#include "config.h"
#include "dataLink.h"
#include "aplicationLayer.h"
#include "utilityLayer.h"

void MCU_init(void); /* Device initialization function declaration */

void 
main(void) 
{   
    unsigned char rta = 0, value = 0;
    
    MCU_init();
    Enable_Interrupts;   
    
    LED_STATUS = ON;
    
    forever
    {   
        if (getCronometro() == 0) 
        {
        //  value = getValue();
          setCronometro(500);
        }
        

        if (evaluarBusDatos() == TRAMA_COMPLETA) 
        {
          // si es broadcast o el ID del dispositivo          
          rta = ejecutarFuncion();
        }        
    }
}                       