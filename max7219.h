/**************************************************************************//**
 *  @File:
 *
 *     max7219.h
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
 *     Created      : April 22, 2017
 *
 *  R Hanlen <implod@gmail.com>
 * ***************************************************************************/

#ifndef MAX7219_H
#define	MAX7219_H

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

//OPCODES for MAX7219 Registers

#define OP_NOOP   0x00
#define OP_DIGIT0 0x01
#define OP_DIGIT1 0x02
#define OP_DIGIT2 0x03
#define OP_DIGIT3 0x04
#define OP_DIGIT4 0x05
#define OP_DIGIT5 0x06
#define OP_DIGIT6 0x07
#define OP_DIGIT7 0x08
#define OP_DECODEMODE  0x09
#define OP_INTENSITY   0x0A
#define OP_SCANLIMIT   0x0B
#define OP_SHUTDOWN    0x0C
#define OP_DISPLAYTEST 0x0F


#define MAX7219_CS          LATC6
#define MAX7219_CS_TRIS     TRISC6
#define MAX7219_CLK         LATC3
#define MAX7219_CLK_TRIS    TRISC3
#define MAX7219_DATA        LATC7
#define MAX7219_DATA_TRIS   TRISC7


#ifndef NUMBER_OF_DIGITS
#define NUMBER_OF_DIGITS    3
#endif
#ifndef USE_DECODE
#define USE_DECODE          0
#endif
#ifndef INITIAL_INTENSITY
#define INITIAL_INTENSITY   9
#endif
/*
*********************************************************************************************************
* LED Segments:         a
*                    #######
*                   f##   ##b
*                    ## g ##
*                    #######
*                   e##   ##c
*                    ##   ##
*                    #######  o dp
*                       d
*   Register bits:
*      bit:  7  6  5  4  3  2  1  0
*           dp  a  b  c  d  e  f  g
*********************************************************************************************************
*/
#define DIGITS_ARRAY_LENGTH 10
const uint8_t digitsArray[DIGITS_ARRAY_LENGTH] = {
    0b01111110, // 0
    0b00110000, // 1
    0b01101101, // 2
    0b01111001, // 3
    0b00110011, // 4
    0b01011011, // 5
    0b01011111, // 6
    0b01110000, // 7
    0b01111111, // 8
    0b01110011, // 9
};
const uint8_t segmentFont[101] = {
    0x00, // SPACE
    0xA0, // !
    0x22, // "
    0x36, // #
    0x4B, // $
    0x5A, // %
    0x6F, // &
    0x02, // '
    0x4E, // (
    0x78, // )
    0x63, // *
    0x07, // +
    0x18, // ,
    0x01, // -
    0x80, // .
    0x25, // / 
    0x7E, // 0
    0x30, // 1
    0x6D, // 2
    0x79, // 3
    0x33, // 4
    0x5B, // 5
    0x5F, // 6
    0x70, // 7
    0x7F, // 8        
    0x7B, // 9
    0x09, // :
    0x19, // ;
    0x43, // <
    0x41, // =
    0x61, // >
    0x65, // ?
    0x7D, // @
    0x77, // A
    0x1F, // B
    0x4E, // C
    0x3D, // D
    0x4F, // E
    0x47, // F
    0x5E, // G
    0x37, // H
    0x30, // I
    0x38, // J
    0x57, // K
    0x0E, // L
    0x54, // M
    0x76, // N
    0x7E, // O
    0x67, // P
    0x73, // Q
    0x66, // R
    0x5B, // S
    0x0F, // T
    0x3E, // U
    0x3A, // V
    0x2A, // W
    0x37, // X
    0x3B, // Y
    0x69, // Z
    0x4E, // [
    0x13, // |
    0x78, // ]
    0x62, // ^
    0x08, // _ 
    0x02, // '      
    0x77, // a
    0x1F, // b
    0x4E, // c
    0x3D, // d
    0x4F, // e
    0x47, // f
    0x5E, // g
    0x37, // h
    0x30, // i
    0x38, // j
    0x57, // k
    0x0E, // l
    0x54, // m
    0x76, // n
    0x7E, // o
    0x67, // p
    0x73, // q
    0x66, // r
    0x5B, // s
    0x0F, // t
    0x3E, // u
    0x3A, // v
    0x2A, // w
    0x37, // x
    0x3B, // y
    0x69  // z
};     

/**
        @Section: System APIs
 */




/***************FUNCTION PROTOTYPES**********************/

/*
 * initialize the max7219
 */
void MAX7219_Init(void);
void MAX7219_New(void);
/*
 * Set the shutdown (power saving) mode for the device
 */
void MAX7219_Shutdown(void);

/*
 * Turn off the shutdown mode of the device
 */
void MAX7219_TurnOn(void);

/*
 * Turn on BCD decode for given digits
 */
void MAX7219_SetDecode(uint8_t digits);

/*
 * Set device to normal of test mode
 */
void MAX7219_NormalMode(void);
void MAX7219_TestMode(void);

/*
 * Set the number of digits (or rows) to be displayed.
 * See data sheet for side effects of the scan limit on the brightness
 * of the display.
 * Params :
 * limit	number of digits to be displayed (1..8)
 */
void MAX7219_SetScanLimit(uint8_t limit);

/*
 * Set the brightness of the display.
 * Params:
 * intensity	the brightness of the display. (0..15)
 */
void MAX7219_SetIntensity(uint8_t intensity);

/*
 * Switch all Leds on the display off.
 * Params:
 * none
 */
void MAX7219_Clear(void);


//void MAX7219_SetDigit(uint8_t row, uint8_t value, bool sync);

//void MAX7219_BufferDigit(uint8_t row, uint8_t value);

void MAX7219_WriteBuffer(uint8_t row, uint8_t value);

void MAX7219_Write(uint8_t row, uint8_t value);

uint8_t MAX7219_Read(uint8_t row);

void MAX7219_SyncBuffer(void);


/*
 *PRIVATE FUNCTIONS-
 *shifts command to matrix
 */

void MAX7219_ShiftByte(uint8_t data);
void MAX7219_SetRegister(uint8_t reg, uint8_t data);
void MAX7219_SyncRow(uint8_t row);


#endif	/* MAX7219_H */

