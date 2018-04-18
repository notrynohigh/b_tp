#include "b_tp.h"
#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include "stdlib.h"
#include "unistd.h"


#define BUF_LEN      256

uint8_t  b_table[BUF_LEN];
uint32_t b_len = 0;
uint8_t result[256];
uint8_t result2[256];
void main()
{
	char retval;
    uint8_t test_data[50];
    uint8_t i = 0;
	uint32_t pi = 0;
	uint32_t lenlen = 0;
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
        b_tp_send(test_data, 50, result);
		lenlen = ((uint32_t *)result)[0];
		if(lenlen > 0)
		{
			for(pi = 0;pi < lenlen;pi++)
		    {
				if((pi % 20) == 0)
				{
					printf("\n\r");
				}					
				printf("%d ", result[pi + 4]);
				
			}
			
		}
		printf("\n\r------------------------------------------\n\r");
        i = 0;
		b_len = lenlen;
        for(i = 0;i < (b_len / B_TP_MTU);i++)
        {
            retval = b_tp_rec(&(result[4 + i * B_TP_MTU]), B_TP_MTU, result2); 
	printf("%d\n\r", retval);
			lenlen = ((uint32_t *)result2)[0];
			if(lenlen > 0)
			{
				for(pi = 0;pi < lenlen;pi++)
				{					
					printf("%d ", result2[pi + 4]);

				}
			}
        }
        if(b_len % B_TP_MTU)
        {
          retval =  b_tp_rec(&(result[4 + i * B_TP_MTU]), b_len - (i * B_TP_MTU), &result2); 

	printf("%d\n\r", retval);
			lenlen = ((uint32_t *)result2)[0];
			if(lenlen > 0)
			{
				for(pi = 0;pi < lenlen;pi++)
				{					
					printf("%d ", result2[pi + 4]);

				}
			}
        }
        sleep(1);
    }
}



