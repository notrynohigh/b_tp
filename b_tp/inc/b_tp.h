











typedef enum
{
    STA_WAIT_HEAD,
	STA_PACKING,
}b_tp_status_t;

#pragma pack(1)

typedef struct
{
    b_tp_head_t head;
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










