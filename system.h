/**************************************************************************//**
 *  @File:
 *
 *     system.h
 *
 *  @Project: 
 *
 *     TODO -> Project Name
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

#ifndef SYSTEM_H
#define	SYSTEM_H

/**
        @Section: Included Files
 */

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>


#include "gen_def.h"
#include "globals.h"
#include "user.h"
#include "pins.h"
#include "timers.h"
#include "interrupt.h"
#include "encoder.h"
#include "display.h"


/**
        @Section: Macro Declarations
 */
#define _XTAL_FREQ  8000000
#define INTERNAL_OSC
//#define PROTOBOARD
//#define BEGINNG_EEP

#define LAST_ONES       0x03
#define LAST_TENS       0x04
#define LAST_HUND       0x05

#ifdef INTERNAL_OSC
#if _XTAL_FREQ == 16000000
#define OSC_ICRF 0x07
#elif _XTAL_FREQ == 8000000
#define OSC_ICRF 0x06
#elif _XTAL_FREQ == 4000000
#define OSC_ICRF 0x05
#elif _XTAL_FREQ == 2000000
#define OSC_ICRF 0x04
#elif _XTAL_FREQ == 1000000
#define OSC_ICRF 0x03
#endif
#endif


#define ECCP_OFF()   CCP1CON = 0x00
#define MSSP_OFF()  SSPCON1bits.SSPEN = 0x00
#define EUART_OFF() RCSTAbits.SPEN = 0x00
#define ADC_OFF()   ADCON0bits.ADON = 0x00
#define COMPS_OFF() CM1CON0bits.C1ON = 0x00; CM2CON0bits.C2ON = 0x00
#define SRLATCH_OFF() SRCON0bits.SRLEN = 0x00
#define FVR_OFF()   VREFCON0bits.FVR1EN = 0x00
#define DAC_OFF()  VREFCON1bits.D1EN = 0x00
#define PINS_OFF()  LATA = 0x00;LATB = 0x00;LATC = 0x00;TRISA = 0xFF;TRISB = 0xFF;TRISC = 0xFF
#define ANALOG_OFF()    ANSEL = 0x00; ANSELH = 0x00

#define PERIPHERALS_OFF()   ECCP_OFF();MSSP_OFF();EUART_OFF();ADC_OFF();COMPS_OFF();SRLATCH_OFF();\
                            FVR_OFF();DAC_OFF()

#define GLOBAL_PULLUPS_ENABLE()     (INTCON2bits.nRBPU = 0)
#define GLOBAL_PULLUPS_DISABLE()     (INTCON2bits.nRBPU = 1)
/**
        @Section: System APIs
 */

void InitSystem(void);
void InitOscillator(void);
#endif	/* SYSTEM_H */

