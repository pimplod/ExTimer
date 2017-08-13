/* ************************************************************************//**
 *  @File:
 *
 *     user.c
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
 *     Created      : July 17, 2017
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
//#include <math.h>

//Project
#include "user.h"

/* ***********************************************************************//**
 *              @Section: GLOBAL VARIABLES
 *****************************************************************************/

/* ***********************************************************************//**
 *              @Section: FUNCTION DEFINITIONS
 *****************************************************************************/

//void ButtonCheck(volatile t_button * button) {
//    //static uint16_t debounce = 0;
//    bool test = (*(button->port) & (1UL << (button->pin)));
//    button->down = !(test);
//
//    if ((button->debounce) > tmrCount)
//        return;
//    if (button->down == true && button->latched == false) {
//        button->latched = true;
//        button->debounce = (tmrCount + 30);
//    }
//    if (button->down == false && button->latched == true) {
//        button->pressed = true;
//        button->latched = false;
//    }
//}

void NewButtonCheck(void) {
    buts[0]->down = !(ENC_BUTTON);
    buts[1]->down = !(LED_BUTTON);
    buts[2]->down = !(STOP_BUTTON);

    //    for (uint8_t i = 0; i < BUTTONS_LEN; i++) {
    //        buts[i]->down = ((*(buts[i]->port) & (1 << (buts[i]->pin))) != 0);
    //    }

    for (uint8_t i = 0; i < BUTTONS_LEN; i++) {
        if (buts[i]->debounce > tmrCount)
            continue;
        if (buts[i]->down == true && buts[i]->latched == false) {
            buts[i]->latched = true;
            buts[i]->debounce = tmrCount + 30;
        }
        if (buts[i]->down == false && buts[i]->latched == true) {
            buts[i]->pressed = true;
            buts[i]->latched = false;
        }
    }
}

int16_t GetLastTime(void) {
    uint8_t read = 0;
    int16_t value = 0;
    uint8_t scale = 1;

    for (uint8_t i = 0; i < 3; i++) {
        read = EEPROM_READ((LAST_ONES) + i);
        if (read == 0xFF)
            read = 0;
        value += (int16_t) (read * scale);
        scale *= 10;
    }
    return value;
}

void SaveTime(int16_t time) {
    uint8_t value;

    value = (uint8_t) (time % 10);
    EEPROM_WRITE(LAST_ONES, value);
    value = (uint8_t) (time / 10) % 10;
    EEPROM_WRITE(LAST_TENS, value);
    value = (uint8_t) (time / 100) % 10;
    EEPROM_WRITE(LAST_HUND, value);


}

void SetTimer(void) {
    // switch variable that determines the increment value
    uint8_t switchState = 2;
    int8_t amount = 0;
    uint16_t wait;
    static uint16_t holdTime = 0;
    //get timer value saved in eeprom
    mainCount = GetLastTime();

    wait = tmrCount + 100;
    while (wait > tmrCount) {
        if (ledButton.latched)
            wait = tmrCount + 100;
    }
    ScrollMessage("SET");
    amount = mainCount % 10;
    //clear all button struct variables
    ClearButtonsAndTimers();

    do {
        //Display timer value every loop      
        DisplayValue(mainCount);
        //flash dp of unit being changed
        if (flag.halfsec)
            DisplayDP(switchState);

        switch (switchState) {
            case 2:
                //Pressing encoder button changes the increment of setting
                if (encoderButton.pressed) {
                    ClearButtonsAndTimers();
                    switchState = 1;
                    amount = (mainCount / 10) % 10;
                    break;
                }
                //total changes with rotation of encoder
                if (flag.encode == true) {
                    flag.encode = false;
                    amount += coder.direction;
                    if (amount < 0) {
                        amount = 9;
                        mainCount += 9;
                    }else if (amount > 9) {
                        amount = 0;
                        mainCount -= 9;
                    }else {
                        mainCount += (int16_t) (coder.direction);
                    }
                }
                break;
            case 1:
                //Pressing encoder button changes the increment of setting
                if (encoderButton.pressed) {
                    ClearButtonsAndTimers();
                    switchState = 0;
                    amount = (mainCount / 100) % 10;
                    break;
                }
                //total changes with rotation of encoder
                if (flag.encode == true) {
                    flag.encode = false;
                    amount += coder.direction;
                    if (amount < 0) {
                        amount = 9;
                        mainCount += 90;
                    }else if (amount > 9) {
                        amount = 0;
                        mainCount -= 90;
                    }else {
                        mainCount += (int16_t) (10 * coder.direction);
                    }
                }
                break;
            case 0:
                //Pressing encoder button changes the increment of setting
                if (encoderButton.pressed) {
                    ClearButtonsAndTimers();
                    switchState = 2;
                    amount = mainCount % 10;
                    break;
                }
                //total changes with rotation of encoder 
                if (flag.encode == true) {
                    flag.encode = false;
                    amount += coder.direction;
                    if (amount < 0) {
                        amount = 9;
                        mainCount += 900;
                    }else if (amount > 9) {
                        amount = 0;
                        mainCount -= 900;
                    }else {
                        mainCount += (int16_t) (100 * coder.direction);
                    }
                }
                break;
        }//switch
        //The ledButton signals end of timer setting
        if (ledButton.pressed) {
            DisplayValue(mainCount);
            SaveTime(mainCount);
            ClearButtonsAndTimers();
            mainState = READY;
            return;
        }
        
        if(ledButton.latched && holdTime < tmrCount){
            DisplayMsg("PWR");
            signal.no_timer = true;
            mainState = ON_NO_TIMER;
            return;
        }else if(!ledButton.latched){
            holdTime = tmrCount + 1500L;
        }
        
    } while (1);
}//SetTimer()

void HandleButtons(void) {
    static uint16_t holdCount = 0;

    if (RELAY_LAT == true || hwflag.relay == true) {
        if (ledButton.pressed || encoderButton.pressed) {
            RELAY_OFF();
            BUTTON_LED_ON();
            ClearButtonsAndTimers();
            flag.blinkled = false;
            flag.stop = true;
            mainState = STOP_CALLED;
        }
    }else {
        switch (mainState) {
            case POWER_ON:
                if (ledButton.pressed) {
                    ClearButtonsAndTimers();
                    flag.ready = false;
                    mainState = SET_TIMER;
                }
                break;
            case READY:
                if (ledButton.pressed) {
                    ClearButtonsAndTimers();
                    if (hwflag.disp_on == false) {
                        DisplayOn();
                    }
                    flag.on = true;
                    mainState = TIMER_ON;
                }
                break;
            case TIMER_OVER:
                if (ledButton.pressed) {
                    ClearButtonsAndTimers();
                    if (hwflag.disp_on == false)
                        DisplayOn();
                    if (hwflag.buzzer)
                        BUZZER_OFF();
                    mainState = SET_TIMER;
                }
                break;

            case STOP_CALLED:
                if (ledButton.latched && (holdCount < tmrCount)) {
                     DisplayClear();
                    uint16_t wait = tmrCount + 250;
                    while (wait > tmrCount){
                        if(ledButton.latched)
                            wait = tmrCount + 250;
                    }
                    ClearButtonsAndTimers();              
                    flag.stop = false;
                    flag.ready = true;
                    mainState = POWER_ON;
                }else if (!ledButton.latched) {
                    holdCount = tmrCount + 750L;
                }
                break;
        }
    }
}
