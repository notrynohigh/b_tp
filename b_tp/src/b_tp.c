


#define HEAD_FLAG        88

#define B_TP_HEAD_LEN    sizeof(b_tp_head_t)

#define B_TP_MTU         20

static b_tp_rec_info_t  gs_b_tp_rec_info = 
{
    .status = STA_WAIT_HEAD,
};



static void _b_tp_analyse_single_packet(uint8_t *pbuf, uint32_t len)
{
    b_tp_pack_info_t *pb_tp_pack_info = (b_tp_pack_info_t *)pbuf;
    uint8_t *p = NULL;
	if(B_TP_SUCCESS != _b_tp_check_data(pb_tp_pack_info))
	{
        return;
	}
	p = malloc(pb_tp_pack_info->head.total_len);
	if(NULL == p)
	{
        return;
	}
	memcpy(p, pb_tp_pack_info->buf, pb_tp_pack_info->head.total_len);
	// ?   add callback
}

static void _b_tp_collect_packet(uint8_t *pbuf, uint32_t len)
{
    b_tp_unpack_info_t *pb_tp_unpack_info = (b_tp_unpack_info_t *)pbuf;
	uint8_t *p = NULL;
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
			if(p != NULL)
			{
                memcpy(p, gs_b_tp_rec_info.pbuf->buf, gs_b_tp_rec_info.pbuf->head.total_len);
				// ?   add callback
			}
	    }  
		gs_b_tp_rec_info.status = STA_WAIT_HEAD;
		free(gs_b_tp_rec_info.pbuf);
	}
}


static void _b_tp_wait_first_packet(uint8_t *pbuf, uint32_t len)
{
    b_tp_head_t *pb_tp_head = (b_tp_head_t *)pbuf;
    
    if(pb_tp_head->head != HEAD_FLAG || pb_tp_head->total_len <= B_TP_HEAD_LEN)
    {
        return;
    }
    if(pb_tp_head->flag != 0 && pb_tp_head->total_len <= (B_TP_MTU - B_TP_HEAD_LEN))
    {
        return;
    }
	
    if(pb_tp_head->flag == 0x1)
    {  
	    gs_b_tp_rec_info.total_len = pb_tp_head->total_len + CHECK_LEN;
	    gs_b_tp_rec_info.pbuf = (b_tp_pack_info_t *)malloc(pb_tp_head->total_len + B_TP_HEAD_LEN + CHECK_LEN);
	    if(NULL == gs_b_tp_rec_info.pbuf)
	    {
            return;
	    }
	    memcpy(&(gs_b_tp_rec_info.pbuf->head), pbuf, B_TP_HEAD_LEN);
	    memcpy(gs_b_tp_rec_info.pbuf->buf, pbuf + B_TP_HEAD_LEN, len - B_TP_HEAD_LEN);
	    gs_b_tp_rec_info.status = STA_PACKING;
	    gs_b_tp_rec_info.c_packet_number = 1;
		gs_b_tp_rec_info.rec_len = len - B_TP_HEAD_LEN;
    }
    else
    {
        _b_tp_analyse_single_packet(pbuf, len);
    }
}




void b_tp_receive_data(uint8_t *pbuf, uint32_t len)
{
    b_tp_head_t  *pb_tp_head = NULL;
    if(pbuf == NULL || len == 0)
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


int b_tp_send_data(uint8_t *pbuf, uint32_t len)
{
    if(pbuf == NULL && len == 0)
    {
        return;
	}
	if((len + CHECK_LEN + B_TP_HEAD_LEN)
	{
        
	}
}











