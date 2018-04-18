/**
 ****************************************************************************
 * MIT License
 * @file b_tp.h  
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
#ifndef __B_TP_H__
#define __B_TP_H__

/**
 * @addtogroup B_TP
 * @{
 */

/**
 * @addtogroup B_TP_CODE
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
#define B_TP_CHECK_TYPE           b_TPU16
#define B_TP_CHECK_LEN            2

#define B_TP_HEAD                 0XA5
#define B_TP_MTU                  20

#define B_TP_SEND_REPEAT          1


#define B_TP_STATIC_BUF_LEN       256
#define B_TP_RESULT_MAX_LEN       256
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

 
 

#define B_TP_PACKET_HEAD_LEN        (sizeof(b_tp_head_t))



typedef enum
{
    STA_WAIT_HEAD,
    STA_PACKING,
}b_tp_status_t;

typedef enum
{
    B_TP_SUCCESS,
    B_TP_MEM_ERR,
    B_TP_CHECK_ERR,
    B_TP_PARAM_ERR,
    B_TP_HEAD_ERR,
    B_TP_F_NUM_ERR,
    B_TP_BUSY,
    B_TP_OTHER_ERR
}b_tp_err_code_t;



typedef void (*pb_tp_callback_t)(b_TPU8 *, b_TPU32);


#pragma pack(1)

typedef struct
{
    b_tp_head_t head;
    b_TPU8      buf[1];
}b_tp_pack_info_t;

typedef struct
{
    B_TP_FRAME_NUMBER_TYPE     number;
    b_TPU8                     buf[1];
}b_tp_unpack_info_t;

typedef struct
{
    B_TP_TOTAL_LEN_TYPE   c_packet_number;
    B_TP_TOTAL_LEN_TYPE   total_len;
    B_TP_TOTAL_LEN_TYPE   rec_len;
    b_tp_pack_info_t      *pbuf;
    b_tp_status_t         status;
}b_tp_rec_info_t;

typedef struct
{
	b_TPS32 len;
	b_TPU8  buf[B_TP_RESULT_MAX_LEN];
}b_tp_result_t;


#pragma pack()

/**
 * @addtogroup B_TP_PUBLIC_FUNC
 * @{
 */

b_tp_err_code_t b_tp_receive_data(b_TPU8 *pbuf, b_TPU32 len, b_tp_result_t *presult);
b_tp_err_code_t b_tp_send_data(b_TPU8 *pbuf, b_TPU32 len, b_tp_result_t *presult);

/**
 * @}
 */


/**
 * @}
 */

/**
 * @}
 */

#endif




