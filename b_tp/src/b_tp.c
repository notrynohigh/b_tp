#include "b_tp.h"
#include "string.h"

static pb_tp_callback_t gps_rec_success_cb = b_TP_NULL;

static b_tp_rec_info_t  gs_b_tp_rec_info = 
{
    .status = STA_WAIT_HEAD,
};



static b_tp_err_code_t _b_tp_check_data(b_tp_pack_info_t *pb_tp_pack_info)
{
    B_TP_CHECK_TYPE check_tmp; 
	B_TP_CHECK_TYPE check_calculate = 0;
	b_TPU8 *ptmp = (b_TPU8 *)pb_tp_pack_info;
	if(pb_tp_pack_info == b_TP_NULL)
	{
        return B_TP_MEM_ERR;
	}
    check_tmp = ((B_TP_CHECK_TYPE *)(&(pb_tp_pack_info->buf[pbuf->head.total_len])))[0];
	
#if (B_TP_CHECK_SELECT == B_TP_SUM)
    check_calculate = sum_8bit(ptmp, pb_tp_pack_info->head.total_len + B_TP_PACKET_HEAD_LEN);
#elif (B_TP_CHECK_SELECT == B_TP_CRC16)
    check_calculate = crc16(ptmp, pb_tp_pack_info->head.total_len + B_TP_PACKET_HEAD_LEN);
#else
    check_calculate = crc32(ptmp, pb_tp_pack_info->head.total_len + B_TP_PACKET_HEAD_LEN);
#endif
    if(check_tmp != check_calculate)
    {
        return B_TP_CHECK_ERR;
	}
	return B_TP_SUCCESS;
}


static b_tp_err_code_t _b_tp_create_check_code(b_tp_pack_info_t *pb_tp_pack_info)
{
	b_TPU8 *ptmp = (b_TPU8 *)pb_tp_pack_info;
	B_TP_CHECK_TYPE check_calculate = 0;
	if(pb_tp_pack_info == b_TP_NULL)
	{
        return B_TP_MEM_ERR;
	}   
#if (B_TP_CHECK_SELECT == B_TP_SUM)
    check_calculate = sum_8bit(ptmp, pb_tp_pack_info->head.total_len + B_TP_PACKET_HEAD_LEN);
#elif (B_TP_CHECK_SELECT == B_TP_CRC16)
    check_calculate = crc16(ptmp, pb_tp_pack_info->head.total_len + B_TP_PACKET_HEAD_LEN);
#else
    check_calculate = crc32(ptmp, pb_tp_pack_info->head.total_len + B_TP_PACKET_HEAD_LEN);
#endif	
    ((B_TP_CHECK_TYPE *)(&(pb_tp_pack_info->buf[pbuf->head.total_len])))[0] = check_calculate;
    return B_TP_SUCCESS;
}


static void _b_tp_analyse_single_packet(b_TPU8 *pbuf, b_TPU32 len)
{
    b_tp_pack_info_t *pb_tp_pack_info = (b_tp_pack_info_t *)pbuf;
    b_TPU8 *p = b_TP_NULL;
	if(B_TP_SUCCESS != _b_tp_check_data(pb_tp_pack_info))
	{
        return;
	}
	p = malloc(pb_tp_pack_info->head.total_len);
	if(b_TP_NULL == p)
	{
        return;
	}
	memcpy(p, pb_tp_pack_info->buf, pb_tp_pack_info->head.total_len);
    gps_rec_success_cb(p, pb_tp_pack_info->head.total_len);
}

static void _b_tp_collect_packet(b_TPU8 *pbuf, b_TPU32 len)
{
    b_tp_unpack_info_t *pb_tp_unpack_info = (b_tp_unpack_info_t *)pbuf;
	b_TPU8 *p = b_TP_NULL;
	if(pb_tp_unpack_info->number != (gs_b_tp_rec_info.c_packet_number + 1))
	{
        gs_b_tp_rec_info.status = STA_WAIT_HEAD;
		free(gs_b_tp_rec_info.pbuf);
		return;
	}
	gs_b_tp_rec_info.c_packet_number++;
	memcpy(gs_b_tp_rec_info.pbuf->buf + gs_b_tp_rec_info.rec_len, pb_tp_unpack_info->buf, len - sizeof(pb_tp_unpack_info->number));
	gs_b_tp_rec_info.rec_len += len - sizeof(pb_tp_unpack_info->number);
	if(gs_b_tp_rec_info.rec_len == gs_b_tp_rec_info.total_len)
	{
	    if(B_TP_SUCCESS == _b_tp_check_data(gs_b_tp_rec_info.pbuf))
	    {
            p = malloc(gs_b_tp_rec_info.pbuf->head.total_len);
			if(p != b_TP_NULL)
			{
                memcpy(p, gs_b_tp_rec_info.pbuf->buf, gs_b_tp_rec_info.pbuf->head.total_len);
				gps_rec_success_cb(p, gs_b_tp_rec_info.pbuf->head.total_len);
			}
	    }  
		gs_b_tp_rec_info.status = STA_WAIT_HEAD;
		free(gs_b_tp_rec_info.pbuf);
	}
}


static void _b_tp_wait_first_packet(b_TPU8 *pbuf, b_TPU32 len)
{
    b_tp_head_t *pb_tp_head = (b_tp_head_t *)pbuf;
    
    if(pb_tp_head->head != B_TP_HEAD || pb_tp_head->total_len <= B_TP_PACKET_HEAD_LEN)
    {
        return;
    }
    if(pb_tp_head->f_num != 0 && pb_tp_head->total_len <= (B_TP_MTU - B_TP_PACKET_HEAD_LEN))
    {
        return;
    }
	
    if(pb_tp_head->f_num == 0x1)
    {  
	    gs_b_tp_rec_info.total_len = pb_tp_head->total_len + B_TP_CHECK_LEN;
	    gs_b_tp_rec_info.pbuf = (b_tp_pack_info_t *)malloc(pb_tp_head->total_len + B_TP_PACKET_HEAD_LEN + B_TP_CHECK_LEN);
	    if(b_TP_NULL == gs_b_tp_rec_info.pbuf)
	    {
            return;
	    }
	    memcpy(&(gs_b_tp_rec_info.pbuf->head), pbuf, B_TP_PACKET_HEAD_LEN);
	    memcpy(gs_b_tp_rec_info.pbuf->buf, pbuf + B_TP_PACKET_HEAD_LEN, len - B_TP_PACKET_HEAD_LEN);
	    gs_b_tp_rec_info.status = STA_PACKING;
	    gs_b_tp_rec_info.c_packet_number = 1;
		gs_b_tp_rec_info.rec_len = len - B_TP_PACKET_HEAD_LEN;
    }
    else
    {
        _b_tp_analyse_single_packet(pbuf, len);
    }
}



static void _b_tp_unpack_send(b_tp_pack_info_t *pb_tp_pack_info)
{
    b_TPU32 len, send_len = 0;
	b_TPU8  *ptmp = (b_TPU8 *)pb_tp_pack_info;
	b_TPU8  frame_table[B_TP_MTU];
    B_TP_FRAME_NUMBER_TYPE frames = 0, i = 0, j = 0;
	if(pb_tp_pack_info == b_TP_NULL)
	{
        return;
	}
	len = pb_tp_pack_info->head.total_len + B_TP_PACKET_HEAD_LEN + B_TP_CHECK_LEN;
	frames = 1 + (len - B_TP_MTU) / (B_TP_MTU - sizeof(B_TP_FRAME_NUMBER_TYPE));
	for(i = 0;i < frames;i++)
	{
	    if(i == 0)
	    {
	        memcpy(frame_table, ptmp + send_len, B_TP_MTU);
			send_len += B_TP_MTU;
	    }
		else
		{
            ((B_TP_FRAME_NUMBER_TYPE *)frame_table)[0] = i + 1;
			memcpy(&(frame_table[sizeof(B_TP_FRAME_NUMBER_TYPE)]), ptmp + send_len, B_TP_MTU - sizeof(B_TP_FRAME_NUMBER_TYPE));
			send_len += B_TP_MTU - sizeof(B_TP_FRAME_NUMBER_TYPE);
		}
        b_tp_port_send(frame_table, B_TP_MTU);
	}
	if(send_len < len)
	{
        ((B_TP_FRAME_NUMBER_TYPE *)frame_table)[0] = i + 1;
		memcpy(&(frame_table[sizeof(B_TP_FRAME_NUMBER_TYPE)]), ptmp + send_len, len - send_len);
		b_tp_port_send(frame_table, len - send_len + sizeof(B_TP_FRAME_NUMBER_TYPE));
	}
}







void b_tp_receive_data(b_TPU8 *pbuf, b_TPU32 len)
{
    b_tp_head_t  *pb_tp_head = b_TP_NULL;
    if(pbuf == b_TP_NULL || len == 0 || b_TP_NULL == gps_rec_success_cb)
    {
        return;
	}	
	if(gs_b_tp_rec_info.status == STA_WAIT_HEAD)
	{
        _b_tp_wait_first_packet(pbuf, len);
	}
	else if(gs_b_tp_rec_info.status == STA_PACKING)
	{
        _b_tp_collect_packet(pbuf, len);
	}
}


void b_tp_send_data(b_TPU8 *pbuf, b_TPU32 len)
{
    b_tp_pack_info_t *pb_tp_pack_info = b_TP_NULL;
    if(pbuf == b_TP_NULL && len == 0)
    {
        return;
	}
	pb_tp_pack_info = (b_tp_pack_info_t *)malloc(len + B_TP_CHECK_LEN + B_TP_PACKET_HEAD_LEN);
	if(pb_tp_pack_info == b_TP_NULL)
	{
        return;
	}
	pb_tp_pack_info->head.head = B_TP_HEAD;
	pb_tp_pack_info->head.total_len = len;	
	if((len + B_TP_CHECK_LEN + B_TP_PACKET_HEAD_LEN) > B_TP_MTU)
	{
        pb_tp_pack_info->head.f_num = 0X1;
	}
	else
	{
        pb_tp_pack_info->head.f_num = 0X0;
	}	
    memcpy(pb_tp_pack_info.buf, pbuf, len);
    if(B_TP_SUCCESS != _b_tp_create_check_code(pb_tp_pack_info))
    {
        return;
	}
    _b_tp_unpack_send(pb_tp_pack_info);	
}



void b_tp_reg_callback(pb_tp_callback_t pfunc)
{
    if(pfunc == b_TP_NULL)
    {
        return;
	}
	gps_rec_success_cb = pfunc;
}







