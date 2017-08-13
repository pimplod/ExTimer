
/* ************************************************************************//**
 *  @File:
 *
 *     main.c
 *
 *  @Project: 
 *      TimerControl
 *     
 *
 *  @Description:
 *
 *     Target       : PIC18F14K22
 *     Compiler     : XC8
 *     IDE          : MPLABX v3.35
 *     Created      : 8/7/17 
 *
 *  R Hanlen <implod@gmail.com>
 * ***************************************************************************/



#include <xc.h>
#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>      /* For true/false definition */
#include <stdlib.h>

#include "system.h"
//#include "user.h"


void TimerOn(void);
void NoTimer(void);
uint16_t pCount = 0;

/*
                         Main application
 */

void main(void) {

    // Initialize the device

    INTERRUPT_DISABLE();

    InitSystem();

    InitDisplay();

    INT_ENABLE();

    flag.ready = true;
    ClearButtonsAndTimers();
    while (1) {

        switch (mainState) {

            case POWER_ON:
                if (flag.ready) {
                    flag.ready = false;
                    ScrollMessage("READY");
                    pCount = tmrCount + 750;
                }else if (pCount < tmrCount){
                    flag.ready = true;
                }
                
                if(signal.scrollbreak){
                    signal.scrollbreak = false;
                    ClearButtonsAndTimers();
                    mainState = SET_TIMER;
                }
                break;

            case SET_TIMER:
                ClearFlags();
                SetTimer();
                break;

            case READY:
                FlashDisplay();
                break;

            case TIMER_ON:
                TimerOn();
                break;

            case TIMER_OVER:
                FlashDisplay();
                Buzzer();
                break;

            case STOP_CALLED:
                if (hwflag.disp_on == false)
                    DisplayOn();
                if (hwflag.buzzer)
                    BUZZER_OFF();

                if (flag.stop) {
                    flag.stop = false;
                    ScrollMessage("STOPPED");
                    pCount = tmrCount + 750;
                }else if (pCount < tmrCount) {
                    flag.stop = true;
                }

                if (signal.scrollbreak) {
                    signal.scrollbreak = false;
                    flag.stop = true;
                }
                break;
                
            case ON_NO_TIMER:
                if (signal.no_timer) {
                    signal.no_timer = false;
                    pCount = tmrCount + 500;
                    while (pCount > tmrCount) {
                        if (ledButton.down || ledButton.latched)
                            pCount = tmrCount + 500;
                    }
                    ClearButtonsAndTimers();
                    flag.on = true;
                }
                NoTimer();
                
                break;
            default:
                mainState = 0;
                break;
        }

        HandleButtons();

    }
}

void TimerOn(void) {
    if (flag.on) {
        flag.on = false;
        flag.secTick = false;
        while (flag.secTick == false);
        RELAY_ON();
        flag.secTick = false;
        flag.blinkled = true;
        return;
    }

    if (flag.secTick == true) {
        flag.secTick = false;
        mainCount -= 1;
        DisplayValue(mainCount);
    }
    if (mainCount <= 0) {
        RELAY_OFF();
        flag.blinkled = false;
         BUTTON_LED_ON();
        signal.buzzer = true;
        DisplayMsg("FIN");
        mainState = TIMER_OVER;
    }

}

void NoTimer(void){
    if(flag.on){
        flag.on = false;
        RELAY_ON();
        flag.blinkled = true;
         return;
    }
    if (flag.secTick == true)
        flag.secTick = false;
}

/**
 End of File
 */