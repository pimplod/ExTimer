/* ************************************************************************//**
 *  @File:
 *
 *     pins.c
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
#include <stdbool.h>
#include <pic18f14k22.h>    /* For true/false definition */

//Project
#include "pins.h"

/* ***********************************************************************//**
 *              @Section: GLOBAL VARIABLES
 *****************************************************************************/

/* ***********************************************************************//**
 *              @Section: FUNCTION DEFINITIONS
 *****************************************************************************/

void InitPins(void){
    TRISTATE_PINS();
    ANALOG_OFF();
    PULLUPS_OFF();
}

void InitButtons(void){
    LED_BUTTON_TRIS = INPUT;
    BUTTON_LED_TRIS = OUTPUT;
    //STOP_BUTTON_TRIS = INPUT;
    
    BUTTON_LED_ON();
}

void InitBuzzer(void){
    BUZZER_TRIS = OUTPUT;
    //turn off auto shut down
    ECCP1ASbits.ECCPAS = 0x00;
    //outputs off always start with full period
    PSTRCON = 0x10;
    /*
    * PWM Freq = 2731 desired...actual: 2732
    * Prescaler Value = 4
    * PR2 = 182
    * Maximum duty value = 732 
    * Requested Duty Value = 366
     */
    
    PR2 = 0b10110110;
    T2CON = 0b00000101;
   // CCPR1L = 0b01011011;
    CCPR1L = 0b00010010;
    CCP1CON = 0b00111100;
}

void InitRelay(void){
    
    RELAY_LAT = LOW;
    RELAY_TRIS = OUTPUT;
}

void Buzzer(void) {
    static uint16_t count = 0;
    static uint8_t step = 0;

    if (signal.buzzer) {
        step = 0;
        count = 0;
        signal.buzzer = false;
    }
    
    switch (step) {
        case 0:
            if (count < tmrCount) {
                BUZZER_ON();
                count = tmrCount + 500;
                step = 1;
            }
            break;
        case 1:
            if (count < tmrCount) {
                BUZZER_OFF();
                count = tmrCount + 500;
                step = 0;
            }
            break;

    }
//    if (signal.buzzer) {
//        signal.buzzer = false;
//        count = tmrCount + 500;
//        BUZZER_ON();
//    }
//    if (count < tmrCount) {
//        BUZZER_OFF();
//        count = 0;
//    }
}


