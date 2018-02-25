/**
 ****************************************************************************
 * MIT License
 * @file b_tp.h  
 * @version v0.0.1
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

#include "b_tp_config.h"

/**
 * @addtogroup B_TP
 * @{
 */

/**
 * @addtogroup B_TP_CODE
 * @{
 */

#define B_TP_SUM    0
#define B_TP_CRC16  1
#define B_TP_CRC32  2



#define B_TP_PACKET_HEAD_LEN        (sizeof(b_tp_head_t))

#if (B_TP_CHECK_SELECT == B_TP_SUM)
#define B_TP_CHECK_LEN     1
#define B_TP_CHECK_TYPE    b_TPU8
#elif (B_TP_CHECK_SELECT == B_TP_CRC16)
#define B_TP_CHECK_LEN     2
#define B_TP_CHECK_TYPE    b_TPU16
#else
#define B_TP_CHECK_LEN     4
#define B_TP_CHECK_TYPE    b_TPU32
#endif

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

#pragma pack()

/**
 * @addtogroup B_TP_PUBLIC_FUNC
 * @{
 */

void b_tp_receive_data(b_TPU8 *pbuf, b_TPU32 len);
void b_tp_send_data(b_TPU8 *pbuf, b_TPU32 len);

void b_tp_reg_callback(pb_tp_callback_t pfunc);



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




