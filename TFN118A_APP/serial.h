#ifndef SERIAL_H
#define SERIAL_H

#include <QWidget>
#include "QSerialPort"
#include <QSerialPortInfo>
#include "QtWidgets"
class serial : public QWidget
{
    Q_OBJECT
public:
    explicit serial(QWidget *parent = 0);
    ~serial();
    QSerialPort *m_serialPort;//串口类
    int m_buadRate;//波特率
    QString m_portName;//端口号
    QComboBox *serialPortComboBox;//选择串口号
    QPushButton *COMBtn;//串口按钮
    void sendData(QByteArray data);
private:
    QLabel *COMInf;
    QTimer *timer;
//    QStringList SerialPortList;
    QStringList oldPortStringList;
signals:
    void recieveData(QByteArray);
public slots:
    bool COMBtnClick(void);
    void UpdatePort();//更细端口号



};

#endif // SERIAL_H
