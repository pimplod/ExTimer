/* ************************************************************************//**
 *  @File:
 *
 *     encoder.c
 *
 *  @Project: 
 *
 *     UV_UnitControl
 *
 *  @Description:
 *
 *     Target       : PIC18F14K22
 *     Compiler     : XC8
 *     IDE          : MPLABX v3.35
 *     Created      : May 12, 2017
 *
 *  R Hanlen <implod@gmail.com>
 * ***************************************************************************/
/*
 In this example, the rotary encoder outputs are connected to pins RB2 and RB3 of the Pic16F883.
Rotating the encoder clockwise produced the following sequence at RB2 and RB3:

0 0
1 0
1 1
0 1

Rotating the encoder anti-clockwise produced the following sequence at RB2 and RB3:

0 0
0 1
1 1
1 0

If you combine the current state of the outputs with the previous state of the outputs, 
you get a unique sequence for the clockwise and anticlockwise rotation.

Clockwise:

0 1 0 0  Decimal 4
0 0 1 0  Decimal 2
1 0 1 1  Decimal 11
1 1 0 1  Decimal 13

Anticlockwise:

1 0 0 0  Decimal 8
0 0 0 1  Decimal 1
0 1 1 1  Decimal 7
1 1 1 0  Decimal 14 

These unique values are used to index into a lookup table to increment or decrement the encoder count.
 */

/* ************************************************************************//**
 *              @Section: INCLUDED FILES
 *****************************************************************************/

//Compiler-Standard
#include <xc.h>
#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

//Project
#include "encoder.h"

/* ***********************************************************************//**
 *              @Section: GLOBAL VARIABLES
 *****************************************************************************/

/*--- Global encoder count ---*/
//encoderStruct (which includes a global count) is defined in externs.h

/*--- Encoder lookup table ---*/

const signed char table[] = {0, -1, +1, 0, +1, 0, 0, -1, -1, 0, 0, +1, 0, +1, -1, 0};

/* ***********************************************************************//**
 *              @Section: FUNCTION DEFINITIONS
 *****************************************************************************/

/*--- Initialise Encoder ---*/

void InitEncoder(void) {
    //SET QUADATURE PINS AND BUTTON PIN AS INPUTS
    ENC_A_TRIS = INPUT;
    ENC_B_TRIS = INPUT;
    ENC_BUTTON_TRIS = INPUT;
    //set individual pin pullups, and enable global pullup bit
    ENC_A_WPU = ENABLED;
    ENC_B_WPU = ENABLED;
    ENC_BUTTON_WPU = ENABLED;
    GLOBAL_PULLUPS_ENABLE();
    //Interrupts set on both quadature pins 
    ENC_A_IOC = ENABLED;
    ENC_B_IOC = ENABLED;
    //initialize varaibles within the encoder struct
    coder.newstate = READ_ENCODER();
    coder.oldstate = coder.newstate;
    coder.direction = 0;
    coder.count = 0;
    //clear interrupt flag
    INTCONbits.RABIF = 0;
    //interrupt is low priority -- can be interrupted itself by more time sensitive flags
    //INTCON2bits.RABIP = LOW;
    //Enable global IOC bit
    INTCONbits.RABIE = ENABLED;
}


void EncoderISR(void) {
    
    unsigned char temp = 5;
    static int8_t ticks = 0;
   
    //small debounce delay
    while(temp--);
   //move the last state over 
    coder.oldstate = coder.newstate;
    //get new pin states
    coder.newstate = READ_ENCODER();
    //combine the last two reads, use as index into array to get direction of rotation
    coder.fullstate = ((coder.oldstate << 2) | (coder.newstate));
    coder.direction = table[(coder.fullstate & 0x0f)]; /* Index into table */
    //only accept reading when given same value twice 
    ticks += coder.direction;
    if(ticks == 2){
        coder.count++;
        flag.encode = true;
        ticks = 0;
    }else if (ticks == -2){
        coder.count--;
        flag.encode = true;
        ticks = 0;
    }
}





