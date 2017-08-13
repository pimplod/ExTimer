/**************************************************************************//**
 *  @File:
 *
 *     user.h
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
 *     Created      : July 17, 2017
 *
 *  R Hanlen <implod@gmail.com>
 * ***************************************************************************/

#ifndef USER_H
#define	USER_H

/**
        @Section: Included Files
 */


#include "system.h"

/**
        @Section: Macro Declarations
 */


/**
        @Section: System APIs
 */

//void ButtonCheck(volatile t_button * button);

void NewButtonCheck(void);

int16_t GetLastTime(void);

void SaveTime(int16_t time);
void SetTimer(void);
void HandleButtons(void);
#endif	/* USER_H */

