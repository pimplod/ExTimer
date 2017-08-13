/* ************************************************************************//**
 *  @File:
 *
 *     system.c
 *
 *  @Project: 
 *
 *     TODO -> Project Name %<%PROJECT_NAME%>% %<%DEFAULT_NAME%>%
 *
 *  @Description:
 *
 *     Target       : TODO -> Provide MCU
 *     Compiler     : XC8
 *     IDE          : MPLABX v3.35
 *     Created      : May 14, 2017
 *
 *  R Hanlen <implod@gmail.com>
 * ***************************************************************************/

/* ************************************************************************//**
 *              @Section: INCLUDED FILES
 *****************************************************************************/

//Compiler-Standard
#include <xc.h>
#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

//Project
#include "system.h"

/* ***********************************************************************//**
 *              @Section: GLOBAL VARIABLES
 *****************************************************************************/

/* ***********************************************************************//**
 *              @Section: FUNCTION DEFINITIONS
 *****************************************************************************/

void InitSystem(void){
    
    //INTERRUPT_HIGH_DISABLE();
    PERIPHERALS_OFF();
    InitOscillator();
    InitInterrupt();
    InitPins();
    InitTMR0();
    InitTMR1();
    InitTMR3();
    InitEncoder();
    InitButtons();
    InitBuzzer();
    InitRelay();
    InitStuctures();
    //INTERRUPT_LOW_ENABLE();
    //INTERRUPT_HIGH_ENABLE();
}

void InitOscillator(void){
    
    //ICRF defined by _XTAL_FREQ
    OSCCONbits.IRCF = OSC_ICRF;
    //SCS defined by CONFIG
    OSCCONbits.SCS = 0x00;
    // SCS INTOSC; IRCF 8MHz; IDLEN disabled; 
    //OSCCON = 0x62;
    
    // PRI_SD disabled; 
    OSCCON2bits.PRI_SD = 0;
    // INTSRC  LFINTOSC; PLLEN disabled;
    OSCTUNEbits.PLLEN = 0;
    OSCTUNEbits.INTSRC = 0;
}





