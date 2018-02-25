#include "crc16.h"


uint16_t crc16(uint8_t const *pbuf, uint32_t len)
{
    uint16_t crc = 0xFFFF;
    uint32_t i;
    for ( i = 0; i < len; i++)
    {
        crc  = (uint8_t)(crc >> 8) | (crc << 8);
        crc ^= pbuf[i];
        crc ^= (uint8_t)(crc & 0xFF) >> 4;
        crc ^= (crc << 8) << 4;
        crc ^= ((crc & 0xFF) << 4) << 1;
    }
    return crc;
}




















