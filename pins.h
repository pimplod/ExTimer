/**************************************************************************//**
 *  @File:
 *
 *     pins.h
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
 *     Created      : May 15, 2017
 *
 *  R Hanlen <implod@gmail.com>
 * ***************************************************************************/

#ifndef PINS_H
#define	PINS_H

/**
        @Section: Included Files
 */

#include "system.h"

/**
        @Section: Macro Declarations
 */

#define TRISTATE_PINS() PINS_OFF()
#define PULLUPS_OFF()   WPUB = 0x00; WPUA =0x00; INTCON2bits.nRBPU = 1

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define ENABLED      1
#define DISABLED     0

//#define SET_PIN_DIRECTON(pin,direction)  CAT(pin, _SetAs ## direction ## put)
#define SET_PIN_DIRECTION(pin,dir)  do { CAT(pin,_TRIS) = dir; } while (0)
//#define SET_PIN_MODE(pin,md)  CAT(pin,_Set ## md ## Mode)
#define SET_PIN_MODE(pin,md)    do { CAT(pin,_ANS) = md; } while (0)

#define SETPIN(port)        do { CAT(port,_LAT) = 1; } while(0)
#define CLEARPIN(port)      do { CAT(port,_LAT) = 0; } while(0)
#define TOGGLEPIN(port)     do { CAT(port,_LAT) = ~(CAT(port,_LAT)); } while(0)
#define MAKEOUTPUT(pin)    do { CAT(pin,_TRIS) = 0; } while(0)
#define MAKEINPUT(pin)     do { CAT(pin,_TRIS) = 1; } while(0)

#define LED_BUTTON  PORTCbits.RC0
#define LED_BUTTON_TRIS TRISC0
#define STOP_BUTTON PORTAbits.RA2
#define STOP_BUTTON_TRIS    TRISA2

#define BUTTONS_LEN     2

#define BUTTON_LED      PORTCbits.RC1
#define BUTTON_LED_TRIS TRISC1
#define BUTTON_LED_LAT  LATC1
#define BUTTON_LED_ON()     do {hwflag.bled = 1;LATC1 = 1;} while(0)
#define BUTTON_LED_OFF()    do {hwflag.bled = 0;LATC1 = 0;} while(0)
#define TOGGLE_BLED()       do {LATC1 = ~(LATC1);} while(0)

#define BUZZER_TRIS     TRISC5
#define BUZZER_LAT      LATC5
#define BUZZER_ENABLE_BIT   PSTRCONbits.STRA
#define BUZZER_ON()     do {hwflag.buzzer = 1;PSTRCONbits.STRA = 1;} while(0)
#define BUZZER_OFF()    do {hwflag.buzzer = 0;PSTRCONbits.STRA = 0;} while(0)

#define RELAY_TRIS      TRISB7
#define RELAY_LAT       LATB7
#define RELAY           PORTBbits.RB7
#define RELAY_ON()      do {hwflag.relay = 1;LATB7 = 1;} while(0)
#define RELAY_OFF()     do {hwflag.relay = 0;LATB7 = 0;} while(0)
/**
        @Section: System APIs
 */
void InitPins(void);
void InitButtons(void);
void InitRelay(void);
void InitBuzzer(void);
void Buzzer(void);
#endif	/* PINS_H */

