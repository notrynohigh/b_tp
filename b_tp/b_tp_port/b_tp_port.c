/**
 ****************************************************************************
 * MIT License
 * @file b_tp_port.c  
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
#include "b_tp_port.h"
#include "stdio.h"
#include "string.h"
/**
 * @addtogroup B_TP
 * @{
 */

/**
 * @defgroup B_TP_PORT
 * @{
 */

#define TEST_REC      1

#if TEST_REC 
extern uint8_t  b_table[];
extern uint32_t b_len = 0;
#endif


int b_tp_port_send(uint8_t *pbuf, uint32_t len)
{
#if TEST_REC
    memcpy(b_table + b_len, pbuf, len);
    b_len += len;        
#else
    uint32_t i = 0;
    for(i = 0;i < len;i++)
    {
        printf("%x ", pbuf[i]);
    }
    printf("\n\r");
#endif
    return len;
}



/**
 * @}
 */

/**
 * @}
 */


