/* ************************************************************************//**
 *  @File:
 *
 *     max7219.c
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
 *     Created      : April 22, 2017
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
#include "max7219.h"

/* ***********************************************************************//**
 *              @Section: GLOBAL VARIABLES
 *****************************************************************************/
volatile uint8_t maxBuffer[NUMBER_OF_DIGITS];


/* ***********************************************************************//**
 *              @Section: FUNCTION DEFINITIONS
 *****************************************************************************/
void MAX7219_New(void){
    
    uint8_t numberDigits = NUMBER_OF_DIGITS - 1;
    
    MAX7219_Init();
    MAX7219_SetScanLimit(numberDigits);
    
    if(USE_DECODE){
        uint8_t codeMask = 0x01;
        while(numberDigits){
            codeMask |= (0x01 << (numberDigits));
            numberDigits -= 1;
        }
         MAX7219_SetDecode(codeMask);
    }
    
    MAX7219_SetIntensity(INITIAL_INTENSITY);
    
    MAX7219_TurnOn();   
}

void MAX7219_Init(void) {

    //set control pins low
    MAX7219_CS = LOW;
    MAX7219_CLK = LOW;
    MAX7219_DATA = LOW;
    NOP();

    //set control pins as output
    MAX7219_DATA_TRIS = OUTPUT;
    MAX7219_CLK_TRIS = OUTPUT;
    MAX7219_CS_TRIS = OUTPUT;
    NOP();

    //CS is active low
    MAX7219_CS = HIGH;


    //clear display test register
    MAX7219_NormalMode();
    //clear to initialize buffer
    MAX7219_Clear();
}

void MAX7219_Shutdown(void) {

    MAX7219_SetRegister(OP_SHUTDOWN, 0x00);
}

void MAX7219_TurnOn(void){

    MAX7219_SetRegister(OP_SHUTDOWN, 0x01);
}

void MAX7219_SetDecode(uint8_t digits){

    MAX7219_SetRegister(OP_DECODEMODE, digits);
}

void MAX7219_NormalMode(void){

    MAX7219_SetRegister(OP_DISPLAYTEST, 0x00);
}

void MAX7219_TestMode(void){

    MAX7219_SetRegister(OP_DISPLAYTEST, 0x01);
}

void MAX7219_ShiftByte(uint8_t value){

    uint8_t i = 0;

    for(i=0;i<8;i++){

        if (value & 0x80){
            MAX7219_DATA = 1;
        }else{
            MAX7219_DATA = 0;
        }
        MAX7219_CLK = 1;
        NOP();
        //__delay_us(100);
        MAX7219_CLK = 0;
        
        value <<= 1;
    }
}

void MAX7219_SetRegister(uint8_t reg, uint8_t data){

    MAX7219_CS = LOW;
    MAX7219_ShiftByte(reg);
    NOP();
    //__delay_us(100);
    MAX7219_ShiftByte(data);
    MAX7219_CS = HIGH;

}

void MAX7219_SyncRow(uint8_t row){

    if (row >=8){
        return;
    }
    MAX7219_CS = LOW;
    MAX7219_ShiftByte(row+1); //register
    NOP();
    // __delay_us(100);
    MAX7219_ShiftByte(maxBuffer[row]); //data
    MAX7219_CS = HIGH; //latch in data

}



void MAX7219_SetScanLimit(uint8_t limit) {

    MAX7219_SetRegister(OP_SCANLIMIT, limit & 0x07);
}

void MAX7219_SetIntensity(uint8_t intensity) {

    MAX7219_SetRegister(OP_INTENSITY, intensity & 0x0F);

}

void MAX7219_Clear(void) {

    for (uint8_t i = 0; i < NUMBER_OF_DIGITS; i++) {
        maxBuffer[i] = 0x00;
    }
    for (uint8_t i = 0; i< NUMBER_OF_DIGITS; ++i){
        MAX7219_SetRegister((i+1),0x00);
    }
}



//void MAX7219_SetDigit(uint8_t row, uint8_t value, bool sync) {
//
//    if (row > (NUMBER_OF_DIGITS -1)){
//        return;
//    }
//    if (value >= DIGITS_ARRAY_LENGTH)
//        return;
//    
//    maxBuffer[row] = digitsArray[value];
//    
//    if(sync)
//        MAX7219_SetRegister((row+1),maxBuffer[row]);
//}
//
//void MAX7219_BufferDigit(uint8_t row, uint8_t value) {
//
//    if (row > (NUMBER_OF_DIGITS -1)){
//        return;
//    }
//    if (value >= DIGITS_ARRAY_LENGTH)
//        return;
//    
//    maxBuffer[row] = digitsArray[value];  
//}

void MAX7219_Write(uint8_t row, uint8_t value) {

    if (row > (NUMBER_OF_DIGITS -1)){
        return;
    }

    maxBuffer[row] = value;
    MAX7219_SetRegister((row+1),maxBuffer[row]);
}

void MAX7219_WriteBuffer(uint8_t row, uint8_t value) {

    if (row > (NUMBER_OF_DIGITS -1)){
        return;
    }

    maxBuffer[row] = value;
}

uint8_t MAX7219_Read(uint8_t row){
    
    if (row > (NUMBER_OF_DIGITS -1)){
        return 0;
    }
    return (maxBuffer[row]);
}

void MAX7219_SyncBuffer(void){
    uint8_t i = 0;
    for (i = 0; i< NUMBER_OF_DIGITS; ++i){
        MAX7219_SetRegister((i+1),maxBuffer[i]);
    }
}







