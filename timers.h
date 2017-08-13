/**************************************************************************//**
 *  @File:
 *
 *     timers.h
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
 *     Created      : May 15, 2017
 *
 *  R Hanlen <implod@gmail.com>
 * ***************************************************************************/

#ifndef TIMERS_H
#define	TIMERS_H

/**
        @Section: Included Files
 */

//#include <xc.h>
//#include <stdint.h>
//#include <stdbool.h>

#include "system.h"
/**
        @Section: Macro Declarations
 */
#define TIMER0_RELOAD_VALUE     (0x06)

//  TMR3(16 bit) Overflows at a count of 65535. Need to shorten that to a count of 40000 
//  65536 - 40000 = 25536 = 0x63C0
#define TIMER3_RELOAD_VALUE     (0x63C0)

#define TIMER3_START()      do {T3CONbits.TMR3ON = 1;} while(0)
#define TIMER3_STOP()       do {T3CONbits.TMR3ON = 0;} while(0)

/**
        @Section: System APIs
 */
void InitTMR0(void);
void TMR0_Start(void);
void TMR0_Stop(void);
uint8_t TMR0_Read(void);
void TMR0_Write(uint8_t value);
void TMR0_ISR(void);

void InitTMR1(void);
void TMR1_Start(void);
void TMR1_Stop(void);
uint16_t TMR1_Read(void);
void TMR1_Write(uint16_t value);
void TMR1_ISR(void);

void InitTMR3(void);
void TMR3_Start(void);
void TMR3_Stop(void);
void TMR3_ISR(void);
#endif	/* TIMERS_H */

