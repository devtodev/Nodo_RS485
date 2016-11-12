/*
** ###################################################################
**     This code is generated by the Device Initialization Tool.
**     It is overwritten during code generation.
**     USER MODIFICATION ARE PRESERVED ONLY INSIDE INTERRUPT SERVICE ROUTINES
**     OR EXPLICITLY MARKED SECTIONS
**
**     Project   : Sensor
**     Processor : MC9S08QE8CPG
**     Version   : Component 01.002, Driver 01.06, CPU db: 3.00.045
**     Datasheet : MC9S08QE8RM Rev. 3 1/2008
**     Date/Time : 28/01/2014, 05:40 a.m.
**     Abstract  :
**         This module contains device initialization code 
**         for selected on-chip peripherals.
**     Contents  :
**         Function "MCU_init" initializes selected peripherals
**
**     Copyright : 1997 - 2009 Freescale Semiconductor, Inc. All Rights Reserved.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################
*/

/* MODULE MCUinit */

#include <MC9S08QE8.h>                 /* I/O map for MC9S08QE8CPG */
#include "MCUinit.h"

/* User declarations and definitions */
/*   Code, declarations and definitions here will be preserved during code generation */
/* End of user declarations and definitions */


/*
** ===================================================================
**     Method      :  MCU_init (component MC9S08QE8_16)
**
**     Description :
**         Device initialization code for selected peripherals.
** ===================================================================
*/
void MCU_init(void)
{
  asm SEI;                             /* Disable interrupts */
  /* ### MC9S08QE8_16 "Cpu" init code ... */
  /*  PE initialization code after reset */

  /* Common initialization of the write once registers */
  /* SOPT1: COPE=0,COPT=1,STOPE=0,BKGDPE=1,RSTPE=0 */
  SOPT1 = 66;                                      
  /* SOPT2: COPCLKS=0,TPM2CH2PS=0,TPM1CH2PS=0,ACIC2=0,IICPS=0,ACIC1=0 */
  SOPT2 = 0;                                      
  /* SPMSC1: LVDF=0,LVDACK=0,LVDIE=0,LVDRE=1,LVDSE=1,LVDE=1,BGBE=0 */
  SPMSC1 = 28;                                      
  /* SPMSC2: LPR=0,LPRS=0,LPWUI=0,PPDF=0,PPDACK=0,PPDE=1,PPDC=0 */
  SPMSC2 = 2;                                      
  /* SPMSC3: LVWIE=0 */
  SPMSC3 &= (unsigned char)~8;                     
  /*  System clock initialization */
  if (*(unsigned char*far)65455 != 255) { /* Test if the device trim value is stored on the specified address */
    ICSTRM = *(unsigned char*far)65455; /* Initialize ICSTRM register from a non volatile memory */
    ICSSC = (unsigned char)((*(unsigned char*far)65454) & (unsigned char)1); /* Initialize ICSSC register from a non volatile memory */
  }
  /* ICSC1: CLKS=0,RDIV=0,IREFS=1,IRCLKEN=1,IREFSTEN=0 */
  ICSC1 = 6;                           /* Initialization of the ICS control register 1 */
  /* ICSC2: BDIV=0,RANGE=0,HGO=0,LP=0,EREFS=0,ERCLKEN=0,EREFSTEN=0 */
  ICSC2 = 0;                           /* Initialization of the ICS control register 2 */
  while(!ICSSC_IREFST) {               /* Wait until the source of reference clock is internal clock */
   {asm sta SRS;}                      /* Reset watchdog counter */
  }
  /* ICSSC: DRST_DRS=0,DMX32=0 */
  ICSSC &= (unsigned char)~224;        /* Initialization of the ICS status and control */
  while((ICSSC & 192) != 0) {          /* Wait until the FLL switches to Low range DCO mode */
   {asm sta SRS;}                      /* Reset watchdog counter */
  }
  /* SCGC1: TPM2=1,TPM1=1,ADC=1,IIC=1,SCI=1 */
  SCGC1 = 255;                                      
  /* SCGC2: DBG=1,FLS=1,IRQ=1,KBI=1,ACMP=1,RTC=1,SPI=1 */
  SCGC2 = 255;                                      
  /* Common initialization of the CPU registers */
  /* PTASE: PTASE4=0,PTASE3=0,PTASE2=0,PTASE1=0,PTASE0=0 */
  PTASE &= (unsigned char)~31;                     
  /* PTBSE: PTBSE7=0,PTBSE6=0,PTBSE5=0,PTBSE4=0,PTBSE3=0,PTBSE2=0,PTBSE1=0,PTBSE0=0 */
  PTBSE = 0;                                      
  /* PTADS: PTADS7=0,PTADS6=0,PTADS5=0,PTADS4=0,PTADS3=0,PTADS2=0,PTADS1=0,PTADS0=0 */
  PTADS = 0;                                      
  /* PTBDS: PTBDS7=0,PTBDS6=0,PTBDS5=0,PTBDS4=0,PTBDS3=0,PTBDS2=0,PTBDS1=0,PTBDS0=0 */
  PTBDS = 0;                                      
  /* ### Init_SCI init code */
  /* SCIC2: TIE=0,TCIE=0,RIE=0,ILIE=0,TE=0,RE=0,RWU=0,SBK=0 */
  SCIC2 = 0;                           /* Disable the SCI module */
  (void)(SCIS1 == 0);                  /* Dummy read of the SCIS1 register to clear flags */
  (void)(SCID == 0);                   /* Dummy read of the SCID register to clear flags */
  /* SCIS2: LBKDIF=1,RXEDGIF=1,RXINV=0,RWUID=0,BRK13=0,LBKDE=0,RAF=0 */
  SCIS2 = 192;                                      
  /* SCIBDH: LBKDIE=0,RXEDGIE=0,SBR12=0,SBR11=0,SBR10=0,SBR9=0,SBR8=0 */
  SCIBDH = 0;                                      
  /* SCIBDL: SBR7=0,SBR6=0,SBR5=1,SBR4=1,SBR3=0,SBR2=1,SBR1=1,SBR0=1 */
  SCIBDL = 55;                                      
  /* SCIC1: LOOPS=0,SCISWAI=0,RSRC=0,M=0,WAKE=0,ILT=0,PE=0,PT=0 */
  SCIC1 = 0;                                      
  /* SCIC3: R8=0,T8=0,TXDIR=0,TXINV=0,ORIE=0,NEIE=0,FEIE=0,PEIE=0 */
  SCIC3 = 0;                                      
  /* SCIC2: TIE=0,TCIE=0,RIE=1,ILIE=0,TE=1,RE=1,RWU=0,SBK=0 */
  SCIC2 = 44;                                      
  /* ### Init_COP init code */
  SRS = 255;                           /* Clear WatchDog counter */
  /* ### Init_GPIO init code */
  /* PTAD: PTAD3=0 */
  PTAD &= (unsigned char)~8;                     
  /* PTADD: PTADD3=1,PTADD0=1 */
  PTADD |= (unsigned char)9;                      
  /* ### Init_GPIO init code */
  /* PTBD: PTBD5=0 */
  PTBD &= (unsigned char)~32;                     
  /* PTBDD: PTBDD5=1 */
  PTBDD |= (unsigned char)32;                      
  /* ### Init_TPM init code */
  /* TPM1SC: TOF=0,TOIE=0,CPWMS=0,CLKSB=0,CLKSA=0,PS2=0,PS1=0,PS0=0 */
  TPM1SC = 0;                          /* Stop and reset counter */
  TPM1MOD = 9216U;                     /* Period value setting */
  (void)(TPM1SC == 0);                 /* Overflow int. flag clearing (first part) */
  /* TPM1SC: TOF=0,TOIE=1,CPWMS=0,CLKSB=0,CLKSA=1,PS2=0,PS1=0,PS0=0 */
  TPM1SC = 72;                         /* Int. flag clearing (2nd part) and timer control register setting */
  /* ### Init_SPI init code */
  /* SPIC1: SPIE=0,SPE=0,SPTIE=0,MSTR=0,CPOL=0,CPHA=0,SSOE=0,LSBFE=0 */
  SPIC1 = 0;                           /* The SPRF interrupt flag is cleared when the SPI module is disabled. */
  /* SPIC2: MODFEN=0,BIDIROE=0,SPISWAI=0,SPC0=0 */
  SPIC2 = 0;                                      
  /* SPIBR: SPPR2=0,SPPR1=0,SPPR0=1,SPR2=0,SPR1=1,SPR0=0 */
  SPIBR = 18;                                      
  (void)(SPIS == 0);                   /* Dummy read of the SPIS registr to clear the MODF flag */
  /* SPIC1: SPIE=1,SPE=1,SPTIE=0,MSTR=1,CPOL=0,CPHA=1,SSOE=0,LSBFE=0 */
  SPIC1 = 212;                                      
  /* ### */
} /*MCU_init*/


/* Initialization of the CPU registers in FLASH */

/* NVPROT: FPS7=1,FPS6=1,FPS5=1,FPS4=1,FPS3=1,FPS2=1,FPS1=1,FPDIS=1 */
const unsigned char NVPROT_INIT @0x0000FFBD = 255;

/* NVOPT: KEYEN=0,FNORED=1,SEC01=1,SEC00=0 */
const unsigned char NVOPT_INIT @0x0000FFBF = 126;





/* END MCUinit */

/*
** ###################################################################
**
**     This file was created by Processor Expert 3.07 [04.34]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/
