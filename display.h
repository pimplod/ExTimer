/**************************************************************************//**
 *  @File:
 *
 *     display.h
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
 *     Created      : July 4, 2017
 *
 *  R Hanlen <implod@gmail.com>
 * ***************************************************************************/

#ifndef DISPLAY_H
#define	DISPLAY_H

/**
        @Section: Included Files
 */

#include "system.h"

/**
        @Section: Macro Declarations
 */
#define NUMBER_OF_DIGITS    3
#define USE_DECODE          0
#define INITIAL_INTENSITY   7
#define BUFFER_MAX          2

#define PRNTMSG(msg)    DisplayMsg(#msg)
#define SCROLLMSG(msg)  ScrollMessage(#msg)
#define SYNC_DISP()    DisplaySync()
#define BLANK   32
#define DISP_ON()       DisplayOn()
#define CLEAR_DISP()    DisplayClear()
/**
        @Section: System APIs
 */
void InitDisplay(void);
void DisplayDP(uint8_t digit);
void DisplayValue(uint16_t number);
void DisplayNumber(uint8_t digit, uint8_t value);
void DisplayChar(uint8_t digit, uint8_t value);
void DisplayMsg(const char *msg);
void ScrollMessage(const char *string);
void ShiftDisplayLeft(void);
void FlashDisplay(void);
void DisplayOn(void);
void DisplayOff(void);
void DisplayClear(void);
void DisplaySync(void);
#endif	/* DISPLAY_H */

