#include "b_tp.h"
#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include "stdlib.h"
#include "unistd.h"


#define BUF_LEN      256

uint8_t  b_table[BUF_LEN];
uint32_t b_len = 0;

uint8_t  number = 0;

void command_handle(uint8_t *pbuf, uint32_t len)
{
    uint32_t i = 0;
    printf("cmd: %d, len: %d\n\r", pbuf[0], len);
    for(i = 1;i < len;i++)
    {
        printf("%d ", pbuf[i]);
    }
    printf("\n\r\n\r");
    free(pbuf);
}

b_TPS32 _b_tp_rec_check_head(b_tp_head_t *phead)
{
//    printf("phead->number: %d number: %d",phead->number, number);
    if(phead->number == (number - 1))
    {
        return 0;
    }
    return -1;
}

void _b_tp_send_set_head(b_tp_head_t *phead)
{
 //   printf("number: %d", number);
    phead->number = number++;
}

void main()
{
    uint8_t test_data[50];
    uint8_t i = 0;
    for(i = 0;i < 50;i++)
    {
        test_data[i] = i;
    }
    b_tp_reg_callback(command_handle);
    while(1)
    {
        for(i = 0;i < 50;i++)
        {
            test_data[i] += 1;
        }
        memset(b_table, 0, BUF_LEN);
	b_len = 0;
        b_tp_send_data(test_data, 50);
	printf("\\n\r------------------------------------------\n\r");
        i = 0;
        for(i = 0;i < (b_len / B_TP_MTU);i++)
        {
            b_tp_receive_data(&(b_table[i * B_TP_MTU]), B_TP_MTU);            
        }
        if(b_len % B_TP_MTU)
        {
            b_tp_receive_data(&(b_table[i * B_TP_MTU]), b_len - (i * B_TP_MTU)); 
        }
        sleep(5);
    }
}









