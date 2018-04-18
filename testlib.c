#include "b_tp.h"


#include "b_tp.h"
#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include "stdlib.h"
#include "unistd.h"


#define BUF_LEN      256

uint8_t  b_table[BUF_LEN];
uint32_t b_len = 0;

void main()
{
    uint8_t test_data[50];
    uint8_t i = 0;
	uint32_t pi = 0;
	b_tp_result_t result;
	b_tp_result_t result2;
    for(i = 0;i < 50;i++)
    {
        test_data[i] = i;
    }
    
    while(1)
    {
        for(i = 0;i < 50;i++)
        {
            test_data[i] += 1;
        }
        memset(b_table, 0, BUF_LEN);
	    b_len = 0;
        b_tp_send_data(test_data, 50, &result);
		if(result.len > 0)
		{
			for(pi = 0;pi < result.len;pi++)
		    {
				if((pi % 10) == 0)
				{
					printf("\n\r");
				}					
				printf("%d ", result.buf[pi]);

			}
			
		}
		printf("\\n\r------------------------------------------\n\r");
        i = 0;
		b_len = result.len;
        for(i = 0;i < (b_len / B_TP_MTU);i++)
        {
            b_tp_receive_data(&(result.buf[i * B_TP_MTU]), B_TP_MTU, &result2); 
			if(result2.len > 0)
			{
				for(pi = 0;pi < result2.len;pi++)
				{					
					printf("%d ", result2.buf[pi]);

				}
			}
        }
        if(b_len % B_TP_MTU)
        {
            b_tp_receive_data(&(result.buf[i * B_TP_MTU]), b_len - (i * B_TP_MTU), &result2); 
			if(result2.len > 0)
			{
				for(pi = 0;pi < result2.len;pi++)
				{					
					printf("%d ", result2.buf[pi]);

				}
			}
        }
        sleep(1);
    }
}


