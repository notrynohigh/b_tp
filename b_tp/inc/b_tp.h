#ifndef __B_TP_H__
#define __B_TP_H__

#include "b_tp_config.h"

typedef enum
{
   B_TP_SUM,
   B_TP_CRC16,
   B_TP_CRC32
}b_tp_checkout_t;


#define B_TP_PACKET_HEAD_LEN        (sizeof(b_tp_head_t))

typedef struct
{
    b_tp_head_t head;
	b_TPU8 *pbuf;
#if (B_TP_CHECK_TYPE == B_TP_SUM)
    b_TPU8  crc;
#elif (B_TP_CHECK_TYPE == B_TP_CRC16)
    b_TPU16 crc;
#else
    b_TPU32 crc;
#endif
}










#endif



