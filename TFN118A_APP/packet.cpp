#include "packet.h"

packet::packet()
{
    m_crc16 = new crc16;
    Packet_Init();
}

packet::~packet()
{
    delete m_crc16;
}




//解包
bool packet::unPACK(QByteArray *des, QByteArray src)
{
    const QByteArray HEAD = QByteArray::fromHex(packet_head);
    bool rtn_flag;
    //无头，已丢失头部，数据不可靠，直接返回  clear->调用isNull()
    if(!src.contains(HEAD))
    {
        u_state = 0;
        qDebug() << "找不到帧头";
        return false;
    }
    else if(src.contains(HEAD))
    {
        uint16_t paket_cnt = src.count(HEAD);//检测包含几个包
        for(int i =0 ; i<paket_cnt;i++)
        {
            if(0 == u_state)
            {
                src.remove(0,src.indexOf(HEAD));//重新整合数组，帧头开始
                if(src.length()>(U_HEAD_LEN+U_HEAD_LEN))//有长度数据
                {
                    uint16_t LenSrc = ((uint16_t)(src[U_LEN_IDX]<<8)|(uint8_t)src[U_LEN_IDX+1]);
                    PacketLen = LenSrc + U_HEAD_LEN + U_LENTH_LEN + U_CRC_LEN;//获得整包数据长度
                    u_state = 1;
                    qDebug("获取长度%d",PacketLen);
                }
            }
            if(1==u_state)
            {
                if(src.length()>=PacketLen)
                {
                    uint16_t PktLen = this->CRC_Check(src);//crc校验，返回包长度
                    if(PktLen)
                    {
                        des->append(src,PktLen);
                        rtn_flag = true;
                        qDebug() <<"接收数据"<< des->toHex();
                    }
                    int HeadIdx = src.indexOf(HEAD,(src.indexOf(HEAD)+1));//查找下一个包头
                    if(HeadIdx > 0)//找到包头
                    {
                        src.remove(0,HeadIdx);//跳到下一个包头位置
                    }
                    u_state = 0;
                }
            }
        }
    }
    return rtn_flag;
}
//CRC校验,返回包长度
uint16_t packet::CRC_Check(QByteArray src)
{
    char *crcsrc = src.data();//转成char类型
    uint16_t pkt_len;//包长度
    uint16_t CRC;
    uint16_t crc_len = U_LENTH_LEN + ((uint16_t)src[U_LEN_IDX]|(uint8_t)src[U_LEN_IDX+1]);//CRC长度
    CRC = m_crc16->getcrc16((uint8_t *)&crcsrc[U_LEN_IDX],crc_len);//获取CRC校验值
    //获取crc值
    uint16_t info_len = (uint16_t)src[U_LEN_IDX]|(uint8_t)src[U_LEN_IDX+1];//信息长度
    uint16_t crc_idx = U_HEAD_LEN + U_LENTH_LEN + info_len;//crc索引号
    if( (char)(CRC>>8) == src[crc_idx] &&  (char)(CRC) == src[crc_idx+1] )
    {
        qDebug() <<"CRC校验OK";
        pkt_len = crc_idx + U_CRC_LEN;
        return pkt_len;
    }
    qDebug() <<"CRC校验Wrong";
    return 0;
}

void packet::Packet_Init()
{
    u_state = 0;
}
