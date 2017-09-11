#include "serial.h"
//#include <QTimer>
serial::serial(QWidget *parent) : QWidget(parent)
{
    //串口
    serialPortComboBox = new QComboBox;
    serialPortComboBox->setMinimumWidth(80);
    serialPortComboBox->setMaximumWidth(80);
    COMBtn = new QPushButton("打开串口");
    COMBtn->setMinimumWidth(80);
    COMBtn->setMaximumWidth(80);
    COMInf = new QLabel;
    COMInf->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    COMInf->setAlignment(Qt::AlignBottom | Qt::AlignLeft);
    COMInf->setMinimumWidth(40);
    COMInf->setMaximumWidth(40);

    QHBoxLayout *COMLayout = new QHBoxLayout;
    COMLayout->addWidget(serialPortComboBox,1);
    COMLayout->addWidget(COMBtn,1);
    COMLayout->addWidget(COMInf,1);
//    COMLayout->addStretch(2);

    //获取串口号
    m_serialPort = new QSerialPort();
    oldPortStringList.clear();
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos)
        oldPortStringList << info.portName();
    serialPortComboBox->addItems(oldPortStringList);


    setLayout(COMLayout);
    timer = new QTimer;
    connect(COMBtn,&QPushButton::clicked,this,&serial::COMBtnClick);//打开串口
    connect(timer,&QTimer::timeout,this,&serial::UpdatePort);//更新端口号
    timer->start(1000);
    qDebug() << "串口类创建成功";
}

serial::~serial()
{
    delete m_serialPort;
    delete timer;
}


bool serial::COMBtnClick()
{
//    qDebug() << "进入串口按键中断";
    if(COMBtn->text()=="打开串口")
    {
        if(m_serialPort->isOpen())
        {
            return true;
        }
        QString num;
        int errflag;
        m_portName = serialPortComboBox->currentText();
        m_serialPort->setBaudRate(QSerialPort::Baud9600);
        m_serialPort->setPortName(m_portName);
        errflag = m_serialPort->open(QSerialPort::ReadWrite);
        if(true!=errflag)
        {
//           QMessageBox *err = new QMessageBox;
//           err->setText("打开串口失败");
            return false;
        }
        COMBtn->setText("关闭串口");
        COMInf->setText("Open");
//        edtTagInf->setText(tr("open"));
    }
    else if((COMBtn->text()=="关闭串口"))
    {
        if(m_serialPort->isOpen())
        {
            m_serialPort->close();
            COMBtn->setText("打开串口");
            COMInf->setText("Close");
//            edtTagInf->setText(tr("close"));
        }
    }
    return true;
}
//更新端口号
void serial::UpdatePort()
{
//    QString tSerialPortStr;
//    for(int i = 0; i < serialPortComboBox->count() ;i++)
//        tSerialPortStr +=  serialPortComboBox->itemText(i);
//    const auto infos = QSerialPortInfo::availablePorts();
//    for (const QSerialPortInfo &info : infos)
//    {
//        if( false == tSerialPortStr.contains(info.portName()))
//            serialPortComboBox->insertItem(1,info.portName());
//    }

    QStringList newPortStringList;
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos)
    {
        newPortStringList += info.portName();
    }
    //更新串口号
    if(newPortStringList.size() != oldPortStringList.size())
    {
        oldPortStringList = newPortStringList;
        serialPortComboBox->clear();
        serialPortComboBox->addItems(oldPortStringList);
    }

}

void serial::sendData(QByteArray data)
{
    m_serialPort->write(data);
}


