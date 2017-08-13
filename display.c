/* ************************************************************************//**
 *  @File:
 *
 *     display.c
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
 *     Created      : July 4, 2017
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
#include <string.h>

//Project
#include "display.h"
#include "max7219.h"
/* ***********************************************************************//**
 *              @Section: GLOBAL VARIABLES
 *****************************************************************************/
extern volatile uint8_t maxBuffer[];
/* ***********************************************************************//**
 *              @Section: FUNCTION DEFINITIONS
 *****************************************************************************/

void InitDisplay(void) {
    MAX7219_New();
    hwflag.disp_on = true;
}

void DisplayDP(uint8_t digit) {

    set_bit((maxBuffer[digit]),7);
    
}

void DisplayNumber(uint8_t digit, uint8_t value) {

    uint8_t digitValue = digitsArray[value];
    maxBuffer[digit] = digitValue; 

}

void DisplayValue(uint16_t number) {
    
    uint8_t hund = (number / 100) % 10;
    uint8_t tens = (number / 10) % 10;
    uint8_t ones = number % 10;
    maxBuffer[0] = digitsArray[hund];
    maxBuffer[1] = digitsArray[tens];
    maxBuffer[2] = digitsArray[ones]; 
}

void DisplayChar(uint8_t digit, uint8_t value) {

    uint8_t fontValue = segmentFont[value - 32];
    maxBuffer[digit] = fontValue;

}

void DisplayMsg(const char *msg) {

    uint8_t fValue;
    for (uint8_t i = 0; i < NUMBER_OF_DIGITS; i++) {
        fValue = segmentFont[*(msg + i) - 32];
        maxBuffer[i] = fValue;
    }

}

void ScrollMessage(const char *string) {

    uint8_t i = 0;
    uint8_t digit;
    uint16_t delayCount;

    DisplayClear();
    
    while (string[i] != '\0') {
        if (ledButton.pressed == true || encoderButton.pressed == true){
            ledButton.pressed = false;
            encoderButton.pressed = false;
            signal.scrollbreak = true;
            return;
        }
        digit = string[i];
        for (uint8_t x = 0; x < BUFFER_MAX; x++) {
            maxBuffer[x] = maxBuffer[x + 1];
        }
        maxBuffer[BUFFER_MAX] = segmentFont[digit - 32];
        DisplaySync();
        delayCount = t3Count + 20;
        while (delayCount > t3Count);
        i++;
    }
    
    for (i = 0; i < 3; i++) {
        ShiftDisplayLeft();
        delayCount = t3Count + 20;
        while (delayCount > t3Count);
    }
}

void ShiftDisplayLeft(void){
    for (uint8_t x = 0; x < BUFFER_MAX; x++) {
            maxBuffer[x] = maxBuffer[x + 1];
        }
        maxBuffer[BUFFER_MAX] = 0x00;
}

void FlashDisplay(void) {
    if(flag.halfsec == true && signal.display == true){
        DisplayOff();
        signal.display = false;
    }else if(flag.halfsec == false && signal.display == false){
        DisplayOn();
        signal.display = true;
    }
}

void DisplayOn(void) {

    MAX7219_TurnOn();
    hwflag.disp_on = true;
}

void DisplayOff(void){
    
    MAX7219_Shutdown();
    hwflag.disp_on = false;
}

void DisplayClear(void) {

    //MAX7219_Clear();
    for (uint8_t x = 0; x < NUMBER_OF_DIGITS; x++) {
        maxBuffer[x] = 0;
    }
}

void DisplaySync(void) {

    MAX7219_SyncBuffer();
}