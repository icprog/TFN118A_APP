#include "packet.h"
#define packet_head "AAAA"

packet::packet()
{

}

void packet::packet_append(QByteArray *des, QByteArray *src)
{
    des += packet_head1;
    des += packet_head2;//包头
    des += WFILE_LEN;//长度

}
