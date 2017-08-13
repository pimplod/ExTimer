/**************************************************************************//**
 *  @File:
 *
 *     globals.h
 *
 *  @Project: 
 *
 *     TODO -> Project Name
 *
 *  @Description:
 *
 *     Target       : PIC18F14K22
 *     Compiler     : XC8
 *     IDE          : MPLABX v3.35
 *     Created      : July 3, 2017
 *
 *  R Hanlen <implod@gmail.com>
 * ***************************************************************************/

#ifndef GLOBALS_H
#define	GLOBALS_H

#include "system.h"
/**
        @Section: Macro Declarations
 */

extern volatile uint16_t tmrCount;
extern volatile uint16_t t3Count;
//extern volatile uint8_t mainState;
extern volatile int16_t mainCount;

enum mStates {POWER_ON = 0 , SET_TIMER, READY, TIMER_ON, TIMER_OVER, STOP_CALLED, ON_NO_TIMER};

extern volatile enum mStates mainState; 
/*      GENERAL SYSTEM bitFLAGS        */
typedef struct flagStruct {
    unsigned secTick : 1;
    unsigned encode : 1;
    unsigned halfsec : 1;
    unsigned on : 1;
    unsigned main : 1;
    unsigned stop : 1;
    unsigned ready : 1;
    unsigned blinkled: 1;
} t_flags;

extern volatile t_flags flag;

typedef struct signalStruct{
    unsigned buzzer : 1;
    unsigned blink_led : 1;
    unsigned relay :1;
    unsigned display :1;
    unsigned scrollbreak :1;
    unsigned no_timer :1;
    unsigned :2;    
}t_signal;

extern volatile t_signal signal;



typedef struct hwflagStruct{
    unsigned encoder        : 1;
    unsigned disp_on        : 1;
    unsigned buzzer         : 1;
    unsigned relay          : 1;
    unsigned bled           : 1;
    unsigned dp_on          : 1;
    unsigned : 2;
} t_hwflags;

extern volatile t_hwflags hwflag;

/*      TIME STRUCTURE for external watch crystal    */
typedef struct timeStruct {
    uint8_t sec;
    uint8_t min;
    uint8_t hour;
} t_time;

extern volatile t_time time;

/*      MAIN TIMER STRUCT           */
//typedef struct countDownStruct {
//    int16_t total;
//    uint8_t hundreds;
//    uint8_t tens;
//    uint8_t ones;
//    int8_t marker;
//} t_countDown;

//extern volatile t_countDown countDown;

/*      BUTTON STRUCT               */
typedef struct buttonStruct {
    struct {
        unsigned down : 1; //button pressed down
        unsigned latched : 1; //button held down
        unsigned pressed : 1; //button pressed/held/and released
        unsigned : 5;
    };
    volatile unsigned char * port;
    uint8_t pin;
    int16_t debounce;
} t_button;

extern volatile t_button encoderButton;
extern volatile t_button ledButton;
//extern volatile t_button stopButton;
extern volatile t_button* buts[];

/*              ENCODER STRUCT          */
typedef struct encoderStruct{
    uint8_t newstate;
    uint8_t oldstate;
    uint8_t fullstate;
    int8_t direction;
    int16_t count;
}t_coder;

extern volatile t_coder coder;

/*Function Declarations*/

void InitStuctures(void);
void ClearFlags(void);
void ClearButtonsAndTimers(void);
void ClearButtons(void);
#endif	/* GLOBALS_H */