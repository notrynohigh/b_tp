#include "crc32.h"


uint32_t crc32(uint8_t const *pbuf, uint32_t len)
{
    uint32_t crc;
    uint32_t i = 0, j = 0;
    crc = 0xFFFFFFFF;
    for (i = 0; i < size; i++)
    {
        crc = crc ^ p_data[i];
        for (j = 8; j > 0; j--)
        {
            crc = (crc >> 1) ^ (0xEDB88320U & ((crc & 1) ? 0xFFFFFFFF : 0));
        }
    }
    return ~crc;
}





















