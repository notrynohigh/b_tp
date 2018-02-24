#include "sum_8bit.h"



uint8_t sum_8bit(uint8_t *pbuf, uint32_t len)
{
    uint8_t sum = 0;
	uint32_t i = 0;
	for(i = 0;i < len;i++)
	{
        sum += pbuf[i];
	}
	return sum;
}













