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
    ConfigPage *configpage;
    serial *my_serial;//串口
    packet *m_packet;
    crc16 *m_crc16;//crc校验
    void conectEventtinit();//连接事件
    QPushButton *closeButton;//关闭按钮
    QPushButton *helpButton;//帮助按钮
    QByteArray RecieveData;//串口数据

public slots:
    //串口发送数据
    void SendData(QByteArray);
    void changePage(QListWidgetItem *current, QListWidgetItem *previous);
    void OnHelp();//帮助
    void ReadComData();
private:
    void createIcons();
    QLineEdit *ReaderIDLineEdt;//接收器ID
    QListWidget *contentsWidget;
    QStackedWidget *pagesWidget;



};

#endif // DIALOG_H
