#ifndef PACKET_H
#define PACKET_H
#include "QWidget"
#include <QtWidgets>
#define packet_head1 0XAA
#define packet_head2 0XAA
#define ReaderID_LEN 4
#define GPS_LEN      1
#define Seq_LEN      1
#define CMD_LEN      1
#define WFILE_DATA_LEN    16
#define CRC16        2
#define WFILE_LEN   ReaderID_LEN+GPS_LEN+Seq_LEN+CMD_LEN+WFILE_DATA_LEN
class packet
{
public:
    packet();
    void packet_append(QByteArray *des,QByteArray *src);

//    typedef struct
//    {
//        uint8_t head;
//        uint8_t Command;//包
//        uint8_t nDataLen;//包长度

//    }packet;
//    QString

};

#endif // PACKET_H
