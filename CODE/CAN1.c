/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : CAN1.c
**     Project   : DiagnosticDemo
**     Processor : MC9S12G128VLH
**     Component : Init_MSCAN
**     Version   : Component 01.067, Driver 01.11, CPU db: 3.00.017
**     Compiler  : CodeWarrior HC12 C Compiler
**     Date/Time : 2016/10/13, 13:48
**     Abstract  :
**          This file implements the MSCAN (MSCAN) module initialization
**          according to the Peripheral Initialization Bean settings,
**          and defines interrupt service routines prototypes.
**          The Motorola Scalable Controller Area Network (MSCAN) definition
**          is based on the MSCAN12 definition which is the specific
**          implementation of the Motorola Scalable CAN concept targeted
**          for the Freescale MC68HC12 Microcontroller Family.
**
**          The basic features of the MSCAN are as follows:
**          - Implementation of the CAN protocol - Version 2.0A/B
**          � Standard and extended data frames
**          � 0 - 8 bytes data length
**          � Programmable bit rate up to 1 Mbps1
**          � Support for remote frames
**          � 5 receive buffers with FIFO storage scheme
**          - 3 transmit buffers with internal prioritization using a �local
**          priority concept
**          - Flexible maskable identifier filter supports two full size
**          extended identifier filters (two 32-bit) or four 16-bit filters
**          or eight 8-bit filters
**          - Programmable wake-up functionality with integrated low-pass
**          filter
**          - Programmable loop back mode supports self-test operation
**          - Programmable listen-only mode for monitoring of CAN bus
**          - Separate signalling and interrupt capabilities for all CAN
**          receiver and transmitter error states
**          (Warning, Error Passive, Bus-Off)
**          - Programmable MSCAN clock source either Bus Clock or Oscillator
**          Clock
**          - Internal timer for time-stamping of received and transmitted
**          messages
**          - Three low power modes: Sleep, Power Down and MSCAN Enable
**          - Global initialization of configuration registers
**     Settings  :
**          Bean name                                      : CAN1
**          Device                                         : MSCAN
**          Clock Source                                   : Bus Clock
**          Baud Rate Prescaler                            : 2
**          Synchr. Jump Width                             : 1
**          Sampling                                       : One sample per bit
**          Time Segment 1                                 : 13
**          Time Segment 2                                 : 2
**          CAN frequency                                  : 8 MHz
**          Time quantum                                   : 125 ns
**          Bit rate                                       : 500 kbit/s
**          CAN Stops in Wait Mode                         : no
**          Wake-Up Mode                                   : None
**          Loop Back Test Mode                            : Disabled
**          Listen Only Mode                               : Normal operation
**          Sleep Mode Request                             : Disabled
**          Time Stamp                                     : Disabled
**          Acceptance mode                                : Two 32 bit Acceptance Filters
**          Rx acceptance ID(1st bank)                     : 0
**          Rx acceptance ID(2nd bank)                     : 0
**          Rx acceptance ID mask (1st bank)               : FFFFFFFF
**          Rx acceptance ID mask (2nd bank)               : FFFFFFFF
**          RXCAN pin                                      : PM0_RXCAN
**          RXCAN pin signal                               : 
**          TXCAN pin                                      : PM1_TXCAN
**          TXCAN pin signal                               : 
**          Wake up                                        : 
**          Wake up                                        : Disabled
**          Interrupt                                      : Vcanwkup
**          Wake interrupt priority                        : 1
**          ISR name                                       : 
**          Error                                          : 
**          Error Interrupt                                : Vcanerr
**          Status Change Interrupt                        : Disabled
**          Receiver Status Change                         : do not generate
**          Transmitt. Status Change                       : do not generate
**          Overrun Interrupt                              : Disabled
**          Error interrupt priority                       : 1
**          ISR name                                       : 
**          Receiver Full                                  : 
**          Receiver Full                                  : Enabled
**          Receiver Interrupt                             : Vcanrx
**          Rx interrupt priority                          : 1
**          ISR name                                       : Can_Rx_Interrupt
**          Transmitter empty                              : 
**          Transmitter Interrupt                          : Vcantx
**          Tx Empty Interrupt 0                           : Disabled
**          Tx Empty Interrupt 1                           : Disabled
**          Tx Empty Interrupt 2                           : Disabled
**          Tx interrupt priority                          : 1
**          ISR name                                       : 
**          Call Init in CPU init. code                    : yes
**          CAN Enable                                     : yes
**     Contents  :
**         Init - void CAN1_Init(void);
**
**     Copyright : 1997 - 2011 Freescale Semiconductor, Inc. All Rights Reserved.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/
/* MODULE CAN1. */
#include "CAN1.h"

/*
** ###################################################################
**
**  The interrupt service routine(s) must be implemented
**  by user in one of the following user modules.
**
**  If the "Generate ISR" option is enabled, Processor Expert generates
**  ISR templates in the CPU event module.
**
**  User modules:
**      DiagnosticDemo.c
**      Events.c
**
** ###################################################################
#pragma CODE_SEG __NEAR_SEG NON_BANKED
ISR(Can_Rx_Interrupt)
        {
        // NOTE: The routine should include the following actions to obtain
        //       correct functionality of the hardware.
        //
        //      The ISR is invoked by RXF flag. The RXF flag is cleared
        //      if a "1" is written to the flag in CANRFLG register.
        //      Example: CANRFLG = CANRFLG_RXF_MASK;
        }
#pragma CODE_SEG DEFAULT
*/
/*
** ===================================================================
**     Method      :  CAN1_Init (component Init_MSCAN)
**
**     Description :
**         This method initializes registers of the CAN module
**         according to this Peripheral Initialization Bean settings.
**         Call this method in user code to initialize the module.
**         By default, the method is called by PE automatically; see
**         "Call Init method" property of the bean for more details.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void CAN1_Init(void)
{
  /* CANRFLG: WUPIF=1,CSCIF=1,OVRIF=1,RXF=1 */
  setReg8Bits(CANRFLG, 0xC3U);          
  /* CANTFLG: TXE2=1,TXE1=1,TXE0=1 */
  setReg8Bits(CANTFLG, 0x07U);          

  /* CANCTL0: INITRQ=1 */
  setReg8Bits(CANCTL0, 0x01U);          
  while(CANCTL1_INITAK == 0U) {        /* Wait for init acknowledge */
  }
  /* CANCTL1: CANE=1,CLKSRC=1,LOOPB=0,LISTEN=0,BORM=0,WUPM=0,SLPAK=0,INITAK=1 */
  setReg8(CANCTL1, 0xC1U);              
  /* CANBTR1: SAMP=0,TSEG22=0,TSEG21=0,TSEG20=1,TSEG13=1,TSEG12=1,TSEG11=0,TSEG10=0 */
  setReg8(CANBTR1, 0x1CU);              
  /* CANBTR0: SJW1=0,SJW0=0,BRP5=0,BRP4=0,BRP3=0,BRP2=0,BRP1=0,BRP0=1 */
  setReg8(CANBTR0, 0x01U);              
  /* CANIDAC: ??=0,??=0,IDAM1=0,IDAM0=0,??=0,IDHIT2=0,IDHIT1=0,IDHIT0=0 */
  setReg8(CANIDAC, 0x00U);              
  /* CANIDAR0: AC7=0,AC6=0,AC5=0,AC4=0,AC3=0,AC2=0,AC1=0,AC0=0 */
  setReg8(CANIDAR0, 0x00U);             
  /* CANIDAR1: AC7=0,AC6=0,AC5=0,AC4=0,AC3=0,AC2=0,AC1=0,AC0=0 */
  setReg8(CANIDAR1, 0x00U);             
  /* CANIDAR2: AC7=0,AC6=0,AC5=0,AC4=0,AC3=0,AC2=0,AC1=0,AC0=0 */
  setReg8(CANIDAR2, 0x00U);             
  /* CANIDAR3: AC7=0,AC6=0,AC5=0,AC4=0,AC3=0,AC2=0,AC1=0,AC0=0 */
  setReg8(CANIDAR3, 0x00U);             
  /* CANIDAR4: AC7=0,AC6=0,AC5=0,AC4=0,AC3=0,AC2=0,AC1=0,AC0=0 */
  setReg8(CANIDAR4, 0x00U);             
  /* CANIDAR5: AC7=0,AC6=0,AC5=0,AC4=0,AC3=0,AC2=0,AC1=0,AC0=0 */
  setReg8(CANIDAR5, 0x00U);             
  /* CANIDAR6: AC7=0,AC6=0,AC5=0,AC4=0,AC3=0,AC2=0,AC1=0,AC0=0 */
  setReg8(CANIDAR6, 0x00U);             
  /* CANIDAR7: AC7=0,AC6=0,AC5=0,AC4=0,AC3=0,AC2=0,AC1=0,AC0=0 */
  setReg8(CANIDAR7, 0x00U);             
  /* CANIDMR0: AM7=1,AM6=1,AM5=1,AM4=1,AM3=1,AM2=1,AM1=1,AM0=1 */
  setReg8(CANIDMR0, 0xFFU);             
  /* CANIDMR1: AM7=1,AM6=1,AM5=1,AM4=1,AM3=1,AM2=1,AM1=1,AM0=1 */
  setReg8(CANIDMR1, 0xFFU);             
  /* CANIDMR2: AM7=1,AM6=1,AM5=1,AM4=1,AM3=1,AM2=1,AM1=1,AM0=1 */
  setReg8(CANIDMR2, 0xFFU);             
  /* CANIDMR3: AM7=1,AM6=1,AM5=1,AM4=1,AM3=1,AM2=1,AM1=1,AM0=1 */
  setReg8(CANIDMR3, 0xFFU);             
  /* CANIDMR4: AM7=1,AM6=1,AM5=1,AM4=1,AM3=1,AM2=1,AM1=1,AM0=1 */
  setReg8(CANIDMR4, 0xFFU);             
  /* CANIDMR5: AM7=1,AM6=1,AM5=1,AM4=1,AM3=1,AM2=1,AM1=1,AM0=1 */
  setReg8(CANIDMR5, 0xFFU);             
  /* CANIDMR6: AM7=1,AM6=1,AM5=1,AM4=1,AM3=1,AM2=1,AM1=1,AM0=1 */
  setReg8(CANIDMR6, 0xFFU);             
  /* CANIDMR7: AM7=1,AM6=1,AM5=1,AM4=1,AM3=1,AM2=1,AM1=1,AM0=1 */
  setReg8(CANIDMR7, 0xFFU);             
  /* CANCTL0: INITRQ=0 */
  clrReg8Bits(CANCTL0, 0x01U);          
  while(CANCTL1_INITAK) {              /* Wait for init exit */
  }
  /* CANCTL0: RXFRM=0,RXACT=0,CSWAI=0,SYNCH=0,TIME=0,WUPE=0,SLPRQ=0,INITRQ=0 */
  setReg8(CANCTL0, 0x00U);              
  /* CANRIER: WUPIE=0,CSCIE=0,RSTATE1=0,RSTATE0=0,TSTATE1=0,TSTATE0=0,OVRIE=0,RXFIE=1 */
  setReg8(CANRIER, 0x01U);              
  /* CANTIER: ??=0,??=0,??=0,??=0,??=0,TXEIE2=0,TXEIE1=0,TXEIE0=0 */
  setReg8(CANTIER, 0x00U);              
}

<<<<<<< HEAD
=======


int main()
{

  
}


int uds_init()
{
  
}

int uds()
{
  
}
>>>>>>> parent of 3f445fd (Revert "add main function")
/* END CAN1. */

/*
** ###################################################################
**
**     This file was created by Processor Expert 3.05 [04.46]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/
