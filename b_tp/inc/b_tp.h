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

#if B_TP_CHECK_SELECT == B_TP_SUM
#define B_TP_CHECK_LEN     1
#define B_TP_CHECK_TYPE    b_TPU8
#elif B_TP_CHECK_SELECT == B_TP_CRC16
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



void b_tp_receive_data(b_TPU8 *pbuf, b_TPU32 len);
void b_tp_send_data(b_TPU8 *pbuf, b_TPU32 len);

void b_tp_reg_callback(pb_tp_callback_t pfunc);






#endif




