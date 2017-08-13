/**************************************************************************//**
 *  @File:
 *
 *     encoder.h
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

#ifndef ENCODER_H
#define	ENCODER_H

/**
        @Section: Included Files
 */

#include "system.h"

/**
        @Section: Macro Declarations
 */

#define ENC_A_PORT  PORTBbits.RB4
#define ENC_B_PORT  PORTBbits.RB5
#define ENC_A_TRIS  TRISBbits.RB4
#define ENC_B_TRIS  TRISBbits.RB5
#define ENC_A_WPU   WPUBbits.WPUB4
#define ENC_B_WPU   WPUBbits.WPUB5
#define ENC_A_IOC   IOCBbits.IOCB4
#define ENC_B_IOC   IOCBbits.IOCB5
#define READ_ENCODER()  ((PORTB >> 4) & 0x03)
#define ENC_BUTTON  PORTBbits.RB6
#define ENC_BUTTON_TRIS TRISBbits.RB6
#define ENC_BUTTON_WPU  WPUBbits.WPUB6


//#define LED_BUTTON  PORTCbits.RC0
//#define LED_BUTTON_TRIS TRISCbits.RC0

/**
        @Section: System APIs
 */


void InitEncoder(void);
void EncoderISR(void);
//void InitSwitches(void);
#endif	/* ENCODER_H */

