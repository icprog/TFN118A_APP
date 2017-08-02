#ifndef PACKET_H
#define PACKET_H
#include "QWidget"
#include <QtWidgets>

/****************************************************
串口通信 上位机->接收器
描述	帧头	长度	协议版本	读写器ID	定位信息	协议流水号
IDX	0~1	2~3	4		5~8		9       10
描述	命令字	信息内容  CRC16校验
IDX	11		12      13
长度 “协议版本~信息内容"
CRC "长度~信息内容"
******************************************************/
#define U_HEAD_LEN 2
#define U_LENTH_LEN 2
#define U_ID_LEN 4
#define U_PROTOCOL_LEN 1
#define U_ConfigOT_LEN 1   //下发配置指令，超时字节
#define U_HEADER_IDX 0
#define U_LEN_IDX 2
#define U_PROTOCOL_IDX 4
#define U_ID_IDX 5
#define	U_GPS_IDX 9

#define U_FIX_LEN 6 //帧长2+长度2+校验
#define U_AfterLEN_FIX_LEN (U_ID_LEN+1+1+1+1) //buf[2] - U_ReaderFIX_LEN = 信息内容长度
/****************************************************
串口通信 接收器->上位机
描述	帧头	长度	协议版本 	读写器ID	定位信息	协议流水号
IDX	0~1	2~3	 	4	5~8		9/9~36	10/37
描述	命令字	信息内容
IDX	11/38	12/39

******************************************************/
#ifdef GPS
#define	U_TXGPS_IDX 9
#define U_SEQ_IDX 37
#define U_TXCMD_IDX 38
#else
#define	U_TXGPS_IDX 9
#define U_SEQ_IDX 10
#define U_TXCMD_IDX 11
#define U_TXGPS_Value 0x80
#define U_SEQ_Value 0x00

#define U_CMD_IDX 11
#define U_DATA_IDX 12
#define U_FileData_IDX (U_CMD_IDX+6)
#endif

#define packet_head1 0XAA//帧头
#define packet_head2 0XAA
#define U_PROTOCOL_VER 0X00//协议

#define ReaderID_LEN 4
#define GPS_LEN      1
#define Seq_LEN      1
#define CMD_LEN      1
#define WFILE_DATA_LEN    16
#define CRC16        2
#define WFILE_LEN   ReaderID_LEN+GPS_LEN+Seq_LEN+CMD_LEN+WFILE_DATA_LEN
//时间设置
#define U_CMD_TIME_SET							0X90	//时间设置命令
#define U_TIME_SET_LEN                          0X000E  //长度
//参数设置
#define U_CMD_PARA_SET                          0XF0    //参数设置命令
#define U_PARA_SET_LEN                          0X0023    //长度
//文件操作
#define U_CMD_FILE_WRITE                        0XF0    //写命令
#define U_CMD_FILE_READ                         0XF1    //读命令
//模式
#define U_FILE_MODE_PARA						0X01	//内部参数区
#define U_FILE_MODE_RESERVER					0X02	//保留区
#define U_FILE_MODE_USER1						0X03	//用户区1
#define U_FILE_MODE_USER2						0X04	//用户区2
//读取最新记录
#define U_FILE_OFFSET_RNEW                      0XFFFF 	//最新记录
#define U_FILE_RESERVER                         0X0000  //保留
//消息
#define U_CMD_MSG_PUSH                          0X89   //消息命令

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
