#ifndef CRC16_H
#define CRC16_H
#include "QByteArray"

class crc16
{
public:
    crc16();
    ~crc16();
    uint16_t getcrc16(uint8_t *src,uint16_t len);
};

#endif // CRC16_H
