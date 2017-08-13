/* ************************************************************************//**
 *  @File:
 *
 *     interrupt.c
 *
 *  @Project: 
 *
 *     
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

/* ************************************************************************//**
 *              @Section: INCLUDED FILES
 *****************************************************************************/

//Compiler-Standard
#include <xc.h>
#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>    /* For true/false definition */

//Project
#include "interrupt.h"
//#include "user.h"
/* ***********************************************************************//**
 *              @Section: GLOBAL VARIABLES
 *****************************************************************************/

/* ***********************************************************************//**
 *              @Section: FUNCTION DEFINITIONS
 *****************************************************************************/

void InitInterrupt(void) {

    // Enable Interrupt Priority Vectors
    RCONbits.IPEN = 1;

    // Assign peripheral interrupt priority vectors

    // TMRI - high priority
    IPR1bits.TMR1IP = HIGH;

    // TMRI - high priority
    INTCON2bits.TMR0IP = LOW;

    // TMR3 - low priority
    IPR2bits.TMR3IP = HIGH;

    // Encoder, AB interrupt on change - Low priority
    INTCON2bits.RABIP = LOW;
}

void interrupt high_priority IntHigh(void) {

    // interrupt handler
    if (PIE1bits.TMR1IE == 1 && PIR1bits.TMR1IF == 1) {
        TMR1_ISR();
    }else if (PIE2bits.TMR3IE == 1 && PIR2bits.TMR3IF == 1) {
        TMR3_ISR();
    }
}

void interrupt low_priority IntLow(void) {

    if (INTCONbits.TMR0IE == 1 && INTCONbits.TMR0IF == 1) {
        TMR0_ISR();
    }else if (INTCONbits.RABIE == 1 && INTCONbits.RABIF == 1) {
        EncoderISR();
        //flag.encode = true;
        PORTA;
        PORTB;
        INTCONbits.RABIF = 0;
    }
}
