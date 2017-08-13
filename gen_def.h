/**************************************************************************//**
 *  @File:
 *
 *     gen_def.h
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
 *     Created      : April 24, 2017
 *
 *  R Hanlen <implod@gmail.com>
 * ***************************************************************************/

#ifndef GEN_DEF_H
#define	GEN_DEF_H


/**
        @Section: Macro Declarations
 */

#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105

//#define min(a,b) ((a)<(b)?(a):(b))
//#define max(a,b) ((a)>(b)?(a):(b))
#define abs(x) ((x)>0?(x):-(x))
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
//#define round(x)     ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))
#define radians(deg) ((deg)*DEG_TO_RAD)
#define degrees(rad) ((rad)*RAD_TO_DEG)
#define sq(x) ((x)*(x))
#define map(x,in_min,in_max,out_min,out_max) ((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min)
#define swap(a, b) { uint8_t t = a; a = b; b = t; }

#define random(a, b) ((rand() % (b-a)) + a)

#define BCD_TO_DEC(bcd) ((bcd & 0x0F) + ((bcd >> 4) * 10))
#define DEC_TO_BCD(dec) (((dec / 10) << 4) + (dec % 10))
// another bcdtodec  x - 6*(x >> 4)
#define PRECAT(x,y)   x ## y
#define CAT(x,y)     PRECAT(x,y)

//#define SMOOTHSTEP(x) ((x) * (x) * (3 - (2 * (x))))
//#define ENABLED     1
//#define DISABLED    0
/* MASK */

//Example:
//x=0b001;
//bits_on(x,0b100)  //now x=0b101

#define bits_on(var,mask) var |= mask
#define bits_off(var,mask) var &= ~0 ^ mask

/* BITNUMBER */

//Example
//x = 0b001;
//bitset(x,1)	//now x = 0b011

#define BIT(x) (0x01 << (x))
#define bit_get(p,m) ((p) & (m))
#define bitset(var, bitno)    ((var) |= 1UL << (bitno))
#define bitclr(var, bitno)    ((var) &= ~(1UL << (bitno)))
#define bitflip(var, bitno)   ((var) ^= (0x01 << bitno))
#define set_bit(var, bitno)    ((var) |= 1UL << (bitno))
#define clear_bit(var, bitno)    ((var) &= ~(1UL << (bitno)))
#define flip_bit(var, bitno)   ((var) ^= (1UL << bitno))

#endif	/* GEN_DEF_H */

