/* ************************************************************************//**
 *  @File:
 *
 *     timers.c
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
#include <stdbool.h>       /* For true/false definition */

//Project
#include "timers.h"
//#include "user.h"
/* ***********************************************************************//**
 *              @Section: GLOBAL VARIABLES
 *****************************************************************************/

/* ***********************************************************************//**
 *              @Section: FUNCTION DEFINITIONS
 *****************************************************************************/

void InitTMR0(void) {
    // Set TMR0 
    //8000000Hz/4/8 = 250000Hz =  4 uS timer count * 256 = 1.026 mS overflow

    // T0PS 1:8; T08BIT 8-bit; T0SE Increment_hi_lo; T0CS FOSC/4; TMR0ON off; PSA assigned; 
    T0CON = 0x52;

    // TMR0H 0; 
    TMR0H = 0x00;

    // TMR0L 6; Shortens overflow to 1ms
    //TMR0L = 0x06;
    TMR0L = TIMER0_RELOAD_VALUE;

    // Clear Interrupt flag before enabling the interrupt
    INTCONbits.TMR0IF = 0;

    // Enabling TMR0 interrupt.
    INTCONbits.TMR0IE = 1;

    // Start TMR0
    TMR0_Start();
}

void TMR0_Start(void) {
    // Start the Timer by writing to TMR0ON bit
    T0CONbits.TMR0ON = 1;
}

void TMR0_Stop(void) {
    // Stop the Timer by writing to TMR0ON bit
    T0CONbits.TMR0ON = 0;
}

uint8_t TMR0_Read(void) {
    uint8_t readVal;

    // read Timer0, low register only
    readVal = TMR0L;

    return readVal;
}

void TMR0_WriteTimer(uint8_t value) {
    // Write to the Timer0 registers, low register only
    TMR0L = value;
}

void TMR0_ISR(void) {

    INTCONbits.TMR0IF = 0;
    tmrCount++;
    if(tmrCount % 2)
        NewButtonCheck();
    if (!(tmrCount % 500)) {
        flag.halfsec = ~flag.halfsec;
        if (flag.blinkled) {
            if (flag.halfsec) {
                BUTTON_LED_ON();
            }else {
                BUTTON_LED_OFF();
            }
        }
    }
    //NewButtonCheck();
 
    TMR0L = TIMER0_RELOAD_VALUE;

}

void InitTMR1(void) {

    /*
     T1CKPS 1:1
    T1OSCEN enabled; 
    TMR1CS External; 
    nT1SYNC do_not_synchronize; 
    TMR1ON off; 
    RD16 disabled
     */
    T1CON = 0x0E;
    //Write to msb of tmr1h to cause 1 sec overflow
    TMR1H = 0x80;

    // Clearing IF flag before enabling the interrupt.
    PIR1bits.TMR1IF = 0;

    // Enabling TMR1 interrupt.
    PIE1bits.TMR1IE = 1;

    // Start TMR1
    TMR1_Start();
}

void TMR1_Start(void) {
    // Start the Timer by writing to TMRxON bit
    T1CONbits.TMR1ON = 1;
}

void TMR1_Stop(void) {
    // Stop the Timer by writing to TMRxON bit
    T1CONbits.TMR1ON = 0;
}

uint16_t TMR1_Read(void) {
    uint16_t readVal;
    uint8_t readValHigh;
    uint8_t readValLow;

    readValLow = TMR1L;
    readValHigh = TMR1H;

    readVal = ((uint16_t) readValHigh << 8) | readValLow;

    return readVal;
}

void TMR1_Write(uint16_t value) {
    if (T1CONbits.nT1SYNC == 1) {
        // Stop the Timer by writing to TMRxON bit
        T1CONbits.TMR1ON = 0;

        // Write to the Timer1 register
        TMR1H = (value >> 8);
        TMR1L = (uint8_t) value;

        // Start the Timer after writing to the register
        T1CONbits.TMR1ON = 1;
    }else {
        // Write to the Timer1 register
        TMR1H = (value >> 8);
        TMR1L = (uint8_t) value;
    }
}

void TMR1_ISR(void) {

    //Set Register MSB so interrupt is every 1 second
    bitset(TMR1H, 7);
    //Clear interrupt flag
    PIR1bits.TMR1IF = 0;
    //Set firmware second flag
    flag.secTick = true;

    //Increase seconds counter. If seconds == 60, clear and increase minutes. 
    //If min == 60, clear increase hours.
    //If hours == 24, clear.
    time.sec++;
    if (time.sec == 60) {
        time.sec = 0;
        time.min++;
        if (time.min == 60) {
            time.min = 0;
            time.hour++;
            if (time.hour == 24)
                time.hour == 0;
        }
    }
}

void InitTMR3(void) {

    ///8000000Hz/4/8 = 250000Hz =  4 uS timer count * 256 = 1.026 mS overflow

    // T3CKPS = 1:8, TMR3CS = Internal Clock(Fosc/4)
    //T3CON = 0b00110000;
    //TMR3H = 0xFF;

    //8000000/4 = 0.5 uS timer count * 40,000 = 20 mS overflow
    T3CON = 0b10000000;

    // 65536 - 40000 = 25536 = 0x63C0   
    TMR3 = TIMER3_RELOAD_VALUE;

    //IPR2bits.TMR3IP = 1;
    PIR2bits.TMR3IF = 0;
    PIE2bits.TMR3IE = 1;

    TIMER3_START();
    // T3CONbits.TMR3ON = 1;
}

void TMR3_ISR(void) {
    PIR2bits.TMR3IF = 0;
    SYNC_DISP();

    t3Count++;

    TIMER3_STOP();
    TMR3 = TIMER3_RELOAD_VALUE;
    TIMER3_START();
}

void TMR3_Start(void) {

    T3CONbits.TMR3ON = 1;
}

void TMR3_Stop(void) {

    T3CONbits.TMR3ON = 0;
}

//void InitTM2(void) {
//    T2CON = 0x01;
//    PR2 = 0xB2;
//    CCP1CON = 0x2C;
//    CCPR1L = 0x57;
//}