#ifndef PACKET_H
#define PACKET_H
#include "QWidget"
#include <QtWidgets>
#include "crc16.h"
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
#define U_CRC_LEN   2
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
描述	帧头	长度	协议版本 	读写器ID	协议流水号
IDX	0~1	2~3	 	4	5~9		10
描述	命令字	信息内容
IDX	11      12
******************************************************/
#ifdef GPS
#define	U_TXGPS_IDX 9
#define U_SEQ_IDX 37
#define U_TXCMD_IDX 38
#else
#define U_SEQ_Value 0x00
#define U_SEQ_IDX 10
#define U_CMD_IDX 11
#define U_DATA_IDX 12
#define U_FileData_IDX (U_DATA_IDX+6)
#endif

#define packet_head1 0XAA//帧头
#define packet_head2 0XAA
#define packet_head  "AAAA"
#define U_PROTOCOL_VER 0X00//协议
#define TagID_LEN 5
#define TagID_STR_LEN 10
#define ReaderID_LEN 5
#define ReaderID_STR_LEN 10
#define TagID_LEN 5
#define Seq_LEN      1
#define CMD_LEN      1
#define WFILE_DATA_LEN    16
//#define CRC16        2
#define WFILE_LEN   ReaderID_LEN+Seq_LEN+CMD_LEN+WFILE_DATA_LEN

/****************************************************
                命令
******************************************************/
typedef enum
{
    U_CMD_LIST_TAG=0XF4,//列出标签
    U_CMD_LIST_READER=0XF5,
    U_CMD_AUTO_REPORT=0XF6,
    U_CMD_PARA_SET = 0XF0,//参数设置命令
    U_CMD_WRITE_FILE = 0XF0,//写命令
    U_CMD_READ_FILE = 0XF1,//读命令
    U_CMD_ERASE_FILE = 0XF7,//擦除命令
    U_CMD_MSG_PUSH = 0X89,//消息命令
    U_CMD_READER_ID = 0XF2,  //读写器ID
    U_CMD_DEVICE_TEST = 0XF3    //整机测试
}U_CMD_Typdef;

typedef enum
{
    U_CMD_MSG_PUSH_ACK = 0X09//消息命令回复
}U_CMD_ACK_Typedef;
//参数设置
#define U_PARA_SET_LEN                          0X0023    //长度
//文件操作   
#define U_FILE_STATE_LEN                        2
typedef enum
{
    FILE_SUCCESS=0X0000,//执行成功
    FILE_MODE_ERR=0X0600,//操作区不存在
    FILE_BODER_ERR=0X0601,//超出边界，长度/读偏移量超出
    FILE_WOFFSET_ERR=0X0602,//写偏移错误
    FILE_WDATA_ERR=0X0603,//数据错误
    FILE_FULL_ERR=0X0604, //记录满
    FILE_TIMEOUT_ERR=0X0605//超时
}FILE_STATE_Typedef;
//模式
typedef enum
{
    U_FILE_MODE_PARA = 0x00,//内部参数区
    U_FILE_MODE_RESERVER = 0x01,//保留区
    U_FILE_MODE_USER1 = 0x02,//用户区1
    U_FILE_MODE_USER2 = 0x03,//用户区2
    U_FILE_MODE_RUNPARA = 0X04//运行参数
}MODE_Typedef;
//读取最新记录
#define U_FILE_OFFSET_RNEW                      0XFF //最新记录
#define U_FILE_RESERVER                         0X00  //保留
//写记录
#define U_FILE_OFFSET_WNEW_ERASE                      0XFF //最新记录,写满擦除
#define U_FILE_OFFSET_WNEW_NOERASE                    0XFE //最新记录，写满不擦除
//消息
#define MSG_DESTID_ALL "FFFFFFFFFF"
typedef enum
{
    msg_calendar = 0,//日历
    msg_news=1
}MsgType_Typedef;
#define U_MSG_TYPE_Pos  	4//消息类别
#define U_MSG_TYPE_Msk  	0xf0
#define U_MSG_SEQ_Pos		0//RF下发消息序号
#define U_MSG_SEQ_Msk		0x0f
#define U_MSG_SEQ_MAX       15
typedef struct
{
    uint8_t MSG1_Seq;//标签消息1序号，更新传感数据
    uint8_t MSG2_Seq;//标签消息2序号，更新消息2
}MSG_Store_Typedef;
#define MSG2_FIX_LEN  6

typedef enum
{
    U_MSG_SUCESS=0X0000,
    U_MSG_LEN_ERR = 0X0700,//超出最大长度
    U_MSG_DATA_ERR = 0X0701,//时间内容错误
    U_MSG_SEQ_ERR = 0X0702//编号错误
}UMSG_State_Typedef;

//列出标签
#define U_CMD_LIST_TAG                          0XF4    //列出标签
#define U_CMD_LIST_READER                       0XF5    //列出读写器
#define U_CMD_AUTO_REPORT                       0XF6    //列出读写器

#define MAX_TAG_NUM  21  //每包最大标签个数
#define TAG_INFO_LEN 11
#define MAX_PKT_Pos    4
#define MAX_PKT_Msk    0xf0
#define CRT_PKT_Msk    0x0f

//报警低电状态
//报警延时
#define TAG_KEYALARM_Pos								1
#define TAG_KEYALARM_Msk								0x02
#define TAG_LOWPOWER_Pos								1
#define TAG_LOWPOWER_Msk								0x01

class packet
{
public:
    packet();
    ~packet();
    void packet_append(QByteArray *des,QByteArray *src);
    bool unPACK(QByteArray *des,QByteArray src);//解包
    uint16_t CRC_Check(QByteArray src);
    void Packet_Init();

private:
    crc16 *m_crc16;
    uint16_t PacketLen;//一包总长度
    uint8_t u_state =0;//串口接收状态
//    typedef struct
//    {
//        uint8_t head;
//        uint8_t Command;//包
//        uint8_t nDataLen;//包长度

//    }packet;
//    QString

};

#endif // PACKET_H
