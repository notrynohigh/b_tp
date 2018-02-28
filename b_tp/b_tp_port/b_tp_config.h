/**
 ****************************************************************************
 * MIT License
 * @file b_tp_config.h  
 * @version v1.1.1
 * Copyright (c) [2018-2019] [Bean  email: notrynohigh@outlook.com]
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *****************************************************************************
 */
#ifndef __B_TP_CONFIG_H__
#define __B_TP_CONFIG_H__

/**
 * @addtogroup B_TP
 * @{
 */


/**
 * @defgroup B_TP_CONFIG global configuration
 * @{
 */

/**
 * @defgroup B_TP_VA_TYPE variable type 
 * @{
 */
typedef unsigned char      b_TPU8;
typedef unsigned short     b_TPU16;
typedef unsigned int       b_TPU32;

typedef signed char        b_TPS8;
typedef signed short       b_TPS16;
typedef signed int         b_TPS32;

#define b_TP_NULL          ((void *)0)
/**
 * @}
 */


/** | B_TP_HEAD | B_TP_FRAME_NUMBER | TOTAL_LEN | DATA (N) | CHECK */
/**  configure start  ----------------------------------------------------------*/
#define B_TP_HEAD_TYPE            b_TPU8
#define B_TP_FRAME_NUMBER_TYPE    b_TPU8
#define B_TP_TOTAL_LEN_TYPE       b_TPU8
#define B_TP_CHECK_SELECT         B_TP_CRC16         /**< B_TP_SUM / B_TP_CRC16 / B_TP_CRC32 */


#define B_TP_HEAD                 0XA5
#define B_TP_MTU                  20

#define B_TP_SEND_REPEAT          1
#define B_TP_SEND_LOCK_ENABLE     1
#define B_TP_STATIC_BUF_ENABLE    1

#if B_TP_SEND_LOCK_ENABLE
#define B_TP_STATIC_BUF_LEN       160
#else
#define B_TP_STATIC_BUF_LEN       160
#define B_TP_STATIC_REC_BUF_LEN   64
#endif

#define B_TP_DEBUG_NO_CHECK       0
/** configure end ---------------------------------------------*/

#pragma pack(1)

typedef struct
{
  B_TP_HEAD_TYPE          head;
  B_TP_FRAME_NUMBER_TYPE  f_num;
  b_TPU8                  number;
  B_TP_TOTAL_LEN_TYPE     total_len;
}b_tp_head_t;

#pragma pack()

/**
 * @}
 */


/**
 * @}
 */


#endif
