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


typedef enum
{
    STA_WAIT_HEAD,
	STA_PACKING,
}b_tp_status_t;

#pragma pack(1)

typedef struct
{
    b_tp_head_t head;
<<<<<<< HEAD
	b_TPU8 *pbuf;
#if (B_TP_CHECK_TYPE == B_TP_SUM)
    b_TPU8  crc;
#elif (B_TP_CHECK_TYPE == B_TP_CRC16)
    b_TPU16 crc;
#else
    b_TPU32 crc;
#endif
	uint8_t     buf[1];
}b_tp_pack_info_t;

typedef struct
{
    uint8_t     number;
	uint8_t     buf[1];
}b_tp_unpack_info_t;

typedef struct
{
    uint8_t            c_packet_number;
	uint16_t           total_len;
	uint16_t           rec_len;
	b_tp_pack_info_t   *pbuf;
	b_tp_status_t      status;
}b_tp_rec_info_t;

#pragma pack()

void b_tp_receive_data(uint8_t *pbuf, uint32_t len);

void b_tp_send_data(uint8_t *pbuf, uint32_t len);







<<<<<<< HEAD
#endif
=======
>>>>>>> origin/test_interface



