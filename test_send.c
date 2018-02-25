#include "b_tp.h"
#include "stdio.h"
#include "stdint.h"
#include "string.h"

void main()
{
    uint8_t test_data[50];
    uint8_t i = 0;
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
        b_tp_send_data(test_data, 50);
        sleep(5);
    }
}










