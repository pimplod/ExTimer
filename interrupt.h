/**************************************************************************//**
 *  @File:
 *
 *     interrupt.h
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

#ifndef INTERRUPT_H
#define	INTERRUPT_H

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

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    This macro will enable high priority global interrupts.
 * @Example
    INTERRUPT_GlobalInterruptHighEnable();
 */
#define INTERRUPT_HIGH_ENABLE() (INTCONbits.GIEH = 1)

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    This macro will disable high priority global interrupts.
 * @Example
    INTERRUPT_GlobalInterruptHighDisable();
 */
#define INTERRUPT_HIGH_DISABLE() (INTCONbits.GIEH = 0)

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    This macro will enable low priority global interrupts.
 * @Example
    INTERRUPT_GlobalInterruptLowEnable();
 */
#define INTERRUPT_LOW_ENABLE() (INTCONbits.GIEL = 1)

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    This macro will disable low priority global interrupts.
 * @Example
    INTERRUPT_GlobalInterruptLowDisable();
 */
#define INTERRUPT_LOW_DISABLE() (INTCONbits.GIEL = 0)

#define INTERRUPT_DISABLE()     (INTCONbits.GIEH = 0)
#define INT_ENABLE()        INTCONbits.GIEH = 1; INTCONbits.GIEL = 1
/**
        @Section: System APIs
 */
void InitInterrupt(void);

void interrupt high_priority IntHigh(void);

void interrupt low_priority IntLow(void);
#endif	/* INTERRUPT_H */

