#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "QtWidgets"
#include "configpage.h"
#include "updatepage.h"
#include "userpage.h"
#include "serial.h"
#include "packet.h"
class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = 0);
    ~Dialog();
    ConfigPage *configpage;
    serial *my_serial;
    packet *m_packet;
public slots:
    //串口发送数据
    void SendData(QByteArray);
    void changePage(QListWidgetItem *current, QListWidgetItem *previous);

private:
    void createIcons();
    QLineEdit *ReaderIDLineEdt;
    QListWidget *contentsWidget;
    QStackedWidget *pagesWidget;



};

#endif // DIALOG_H
