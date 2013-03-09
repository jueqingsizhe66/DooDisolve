#ifndef _TYPE_DEF_H_
#define _TYPE_DEF_H_

typedef signed long  s64;
typedef signed int     s32;
typedef signed short s16;
typedef signed char   s8;

typedef signed long   const sc64;  /* Read Only */
typedef signed int      const sc32;
typedef signed short  const sc16;  /* Read Only */
typedef signed char   const sc8;   /* Read Only */

typedef volatile signed long  vs64;
typedef volatile signed int     vs32;
typedef volatile signed short vs16;
typedef volatile signed char   vs8;

typedef volatile signed long  const vsc64;  /* Read Only */
typedef volatile signed int     const vsc32;
typedef volatile signed short const vsc16;  /* Read Only */
typedef volatile signed char  const vsc8;   /* Read Only */

typedef unsigned long  u64;
typedef unsigned int     u32;
typedef unsigned short u16;
typedef unsigned char  u8;

typedef unsigned long  const uc64;  /* Read Only */
typedef unsigned int     const uc32; 
typedef unsigned short const uc16;  /* Read Only */
typedef unsigned char  const uc8;   /* Read Only */

typedef volatile unsigned long  vu64;
typedef volatile unsigned int     vu32;
typedef volatile unsigned short vu16;
typedef volatile unsigned char  vu8;

typedef volatile unsigned long  const vuc64;  /* Read Only */
typedef volatile unsigned int     const vuc32;
typedef volatile unsigned short const vuc16;  /* Read Only */
typedef volatile unsigned char  const vuc8;   /* Read Only */

/*
typedef enum {FALSE = 0, TRUE = !FALSE} bool;

typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;

typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;

#define U8_MAX     ((u8)255)
#define S8_MAX     ((s8)127)
#define S8_MIN     ((s8)-128)
#define U16_MAX    ((u16)65535u)
#define S16_MAX    ((s16)32767)
#define S16_MIN    ((s16)-32768)
#define U32_MAX    ((u32)4294967295uL)
#define S32_MAX    ((s32)2147483647)
#define S32_MIN    ((s32)-2147483648)
*/

#endif 