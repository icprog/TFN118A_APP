#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "QtWidgets"
#include "configpage.h"
#include "updatepage.h"
#include "userpage.h"
#include "serial.h"
#include "packet.h"
#include "crc16.h"
class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = 0);
    ~Dialog();

    void conectEventtinit();//连接事件
    QPushButton *closeButton;//关闭按钮
    QPushButton *helpButton;//帮助按钮
    QByteArray ReceiveData;//串口数据
    QByteArray CopyData;//copy数据
    int DataLen;//长度


public slots:
    //串口发送数据
    void SendData(QByteArray);
    void changePage(QListWidgetItem *current, QListWidgetItem *previous);
    void OnHelp();//帮助
    void ReadComData();
    void GetReaderID();//获取读写器ID
    void ShowMsgBox(QString);


private:
    void createIcons();
    QPushButton *ReaderBtn;//读写器ID
    QLineEdit *ReaderIDLineEdt;//接收器ID
    QListWidget *contentsWidget;
    QStackedWidget *pagesWidget;
    QLabel *RunStateLabel;//串口执行状态
    void PacketDeal(QByteArray P_SRC);//包处理
    ConfigPage *m_configpage;
    serial *my_serial;//串口
    packet *m_packet;
    crc16 *m_crc16;//crc校验
    typedef struct
    {
        QString TYPE;//设备类型
        QString ID;//ID设备
        QString RSSI;//信号强度
        QString State;//状态
        QString DATA;//传感数据
        QString B_DOORID;//门口边界管理器ID
        QString B_NORMALID;//普通边界管理器ID
        QString VER;//版本信息
        int Device_Num;//设备数量
        int Device_idx;
        char PKT_Max_Num;//最大编号
        char PKT_Crt_Num;//当前包编号
        uint32_t report_cnt;//上报次数
    }Device_Info_Typedef;
    Device_Info_Typedef Device_Info;
    //    QString filePath;//帮助文件路径
};



#endif // DIALOG_H
