#include "dialog.h"
#include <QtWidgets>
#include "packet.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{

    //list界面，可选
    contentsWidget = new QListWidget;
    contentsWidget->setViewMode(QListView::IconMode);
    contentsWidget->setIconSize(QSize(96, 84));//图片大小不会超过96*84
    contentsWidget->setMovement(QListView::Static);
    contentsWidget->setMaximumWidth(150);//设置最大宽度
    contentsWidget->setMinimumHeight(380);
    contentsWidget->setSpacing(12);
    //页
    pagesWidget = new QStackedWidget;
    configpage = new ConfigPage;
    pagesWidget->addWidget(configpage);
    pagesWidget->addWidget(new UpdatePage);
    pagesWidget->addWidget(new UserPage);
    //扩展窗口
    configpage->createExtension();
    helpButton = new QPushButton(tr("帮助"));
    closeButton = new QPushButton(tr("关闭"));

    //创建页列表
    createIcons();
    contentsWidget->setCurrentRow(0);
    //创建串口类
    my_serial = new serial;
    //读写器ID
    QLabel *ReaderLabel = new QLabel("读写器ID:");
    ReaderLabel->setMinimumWidth(60);
    ReaderLabel->setMaximumWidth(60);
    ReaderIDLineEdt = new QLineEdit;
    ReaderIDLineEdt->setText("FFFFFF01");
    ReaderIDLineEdt->setMaxLength(8);
    ReaderIDLineEdt->setMinimumWidth(60);
    ReaderIDLineEdt->setMaximumWidth(60);
    //顶部
    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(my_serial);
    topLayout->addWidget(ReaderLabel);
    topLayout->addWidget(ReaderIDLineEdt);
    topLayout->addStretch(1);
    //中间
    QHBoxLayout *horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(contentsWidget);
    horizontalLayout->addWidget(pagesWidget, 1);

    //底部
    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(helpButton);
    buttonsLayout->addWidget(closeButton);

    QVBoxLayout *showLayout = new QVBoxLayout;
    showLayout->addLayout(topLayout);
    showLayout->addLayout(horizontalLayout);
    showLayout->addStretch(1);
    showLayout->addSpacing(12);
    showLayout->addLayout(buttonsLayout);
    //扩展窗口
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(showLayout);
    mainLayout->addWidget(configpage->extension);
    setLayout(mainLayout);
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    setWindowTitle("校园腕带");
    this->conectEventtinit();
    //crc16初始化
    m_crc16 = new crc16;
}

Dialog::~Dialog()
{

}

void Dialog::conectEventtinit()
{
    connect(closeButton, &QAbstractButton::clicked, this, &QWidget::close);//关闭按钮事件
    connect(configpage,&ConfigPage::sendsignal,this,&Dialog::SendData);//configdialog 数据更新
    connect(helpButton,&QPushButton::clicked,this,&Dialog::OnHelp);//帮助
    connect(my_serial->m_serialPort,&QSerialPort::readyRead,this,)
}

void Dialog::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (!current)
        current = previous;
    pagesWidget->setCurrentIndex(contentsWidget->row(current));
}
//帮助文档
void Dialog::OnHelp()
{
    QString runPath = QCoreApplication::applicationDirPath();       //获取exe路劲。
    QString helpName = "帮助文档.txt";
    QString helpPath = QString("%1/%2").arg(runPath).arg(helpName);
    QFile bfilePath(helpPath);
    if(!bfilePath.exists()){
        return;
    }
    QString filePath = "file:///" + helpPath;   //打开文件夹用filse:///,打开网页用http://
    QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
}



void Dialog::createIcons()
{
    QListWidgetItem *configButton = new QListWidgetItem(contentsWidget);
    configButton->setIcon(QIcon(":/images/config.png"));
    configButton->setText(tr("Configuration"));
    configButton->setTextAlignment(Qt::AlignHCenter);
    configButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *updateButton = new QListWidgetItem(contentsWidget);
    updateButton->setIcon(QIcon(":/images/update.png"));
    updateButton->setText(tr("Update"));
    updateButton->setTextAlignment(Qt::AlignHCenter);
    updateButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *userButton = new QListWidgetItem(contentsWidget);
    userButton->setIcon(QIcon(":/images/query.png"));
    userButton->setText(tr("User"));
    userButton->setTextAlignment(Qt::AlignHCenter);
    userButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    connect(contentsWidget, &QListWidget::currentItemChanged, this, &Dialog::changePage);

    //packet
    m_packet = new packet;
}
/****************************************************
串口通信 接收器->上位机
描述	帧头	长度	协议版本 	读写器ID	定位信息	协议流水号
IDX	0~1	2~3	 	4	5~8		9/9~36	10/37
描述	命令字	信息内容
IDX	11/38	12/39
******************************************************/
void Dialog::ReadComData()
{
    RecieveData+=my_serial->m_serialPort->readAll();
}
/****************************************************
串口通信 上位机->接收器
描述	帧头	长度	协议版本	读写器ID	定位信息	协议流水号
IDX	0~1	2~3	4		5~8		9       10
描述	命令字	信息内容  CRC16校验
IDX	11		12      13
长度 “协议版本~信息内容"
CRC "长度~信息内容"
******************************************************/
void Dialog::SendData(QByteArray data)
{
    qDebug()<<"主界面";
    if(0 == my_serial->m_serialPort->isOpen())
    {
        QMessageBox msgBox;
        msgBox.setText("串口未打开");
        msgBox.exec();
        return;
    }
    QByteArray send_data;
    uint16_t CRC;
    //获取读写器ID,并且转成QByteArray
    QString ReaderIDSrc = ReaderIDLineEdt->text();
    QByteArray ReaderIDDec = QByteArray::fromHex(ReaderIDSrc.toLatin1());
    send_data[U_HEADER_IDX] = packet_head1;//帧头
    send_data[U_HEADER_IDX+1] = packet_head2;//帧头
    send_data[U_PROTOCOL_IDX] = U_PROTOCOL_VER;//协议
    send_data[U_ID_IDX] = ReaderIDDec[0];//读写器ID
    send_data[U_ID_IDX+1] = ReaderIDDec[1];//读写器ID
    send_data[U_ID_IDX+2] = ReaderIDDec[2];//读写器ID
    send_data[U_ID_IDX+3] = ReaderIDDec[3];//读写器ID
    send_data[U_TXGPS_IDX] = U_TXGPS_Value;//定位信息
    send_data[U_SEQ_IDX] = U_SEQ_Value;//流水号
    if(settimeBtnPD ==configpage->config_Btn)//时间设置按钮按下
    {
        send_data[U_LEN_IDX] = (char)(U_TIME_SET_LEN>>8);//长度
        send_data[U_LEN_IDX+1] = (char)U_TIME_SET_LEN;//长度
        send_data[U_CMD_IDX] = U_CMD_TIME_SET;//命令
        send_data+=data;
        //CRC
        char *crcsrc = send_data.data();
        CRC = m_crc16->getcrc16((uint8_t *)&crcsrc[U_LEN_IDX],(U_TIME_SET_LEN+U_LENTH_LEN));
        send_data+=(char)(CRC>>8);
        send_data+=(char)(CRC);
        my_serial->sendData(send_data);
        qDebug() << "时间设置";
        qDebug() << send_data.toHex();

    }
    else if(setparaBtnPD ==configpage->config_Btn)//参数设置按钮按下
    {
        send_data[U_LEN_IDX] = (char)(U_PARA_SET_LEN>>8);//长度
        send_data[U_LEN_IDX+1] = (char)U_PARA_SET_LEN;//长度
        send_data[U_CMD_IDX] = U_CMD_PARA_SET;//命令
        send_data+=data;
        //CRC
        char *crcsrc = send_data.data();
        CRC = m_crc16->getcrc16((uint8_t *)&crcsrc[U_LEN_IDX],(U_PARA_SET_LEN+U_LENTH_LEN));
        send_data+=(char)(CRC>>8);
        send_data+=(char)(CRC);
        my_serial->sendData(send_data);
        qDebug() << "参数设置";
        qDebug() << send_data.toHex();
    }
    //写文件
    else if(WriteFileBtnPD == configpage->config_Btn)
    {
        send_data+=data;//命令字+信息内容
        char U_LengthSrc = send_data.length()-U_HEAD_LEN-U_LENTH_LEN;//包长度-帧头-长度
        send_data[U_LEN_IDX] = (char)(U_LengthSrc>>8);//长度
        send_data[U_LEN_IDX+1] = (char)U_LengthSrc;//长度
        //CRC
        int U_CRCLengthSrc = send_data.length()-U_HEAD_LEN;//包长度-帧头
        char *crcsrc = send_data.data();
        CRC = m_crc16->getcrc16((uint8_t *)&crcsrc[U_LEN_IDX],U_CRCLengthSrc);
        send_data+=(char)(CRC>>8);
        send_data+=(char)(CRC);
        my_serial->sendData(send_data);
        qDebug() <<"写文件:"<< send_data.toHex();
    }
    //读文件
    else if(ReadFileBtnPD == configpage->config_Btn)
    {
        send_data+=data;//命令字+信息内容
        char U_LengthSrc = send_data.length()-U_HEAD_LEN-U_LENTH_LEN;//包长度-帧头-长度
        send_data[U_LEN_IDX] = (char)(U_LengthSrc>>8);//长度
        send_data[U_LEN_IDX+1] = (char)U_LengthSrc;//长度
        //CRC
        int U_CRCLengthSrc = send_data.length()-U_HEAD_LEN;//包长度-帧头
        char *crcsrc = send_data.data();//转化成CHAR* 类型
        CRC = m_crc16->getcrc16((uint8_t *)&crcsrc[U_LEN_IDX],U_CRCLengthSrc);
        send_data+=(char)(CRC>>8);
        send_data+=(char)(CRC);
        my_serial->sendData(send_data);
        qDebug() <<"读文件:"<< send_data.toHex();
    }
    //消息处理
    else if(MsgBtnPD == configpage->config_Btn)
    {
        send_data+=data;//命令字+信息内容
        char U_LengthSrc = send_data.length()-U_HEAD_LEN-U_LENTH_LEN;//包长度-帧头-长度
        send_data[U_LEN_IDX] = (char)(U_LengthSrc>>8);//长度
        send_data[U_LEN_IDX+1] = (char)U_LengthSrc;//长度
        //CRC
        int U_CRCLengthSrc = send_data.length()-U_HEAD_LEN;//包长度-帧头
        char *crcsrc = send_data.data();//转化成CHAR* 类型
        CRC = m_crc16->getcrc16((uint8_t *)&crcsrc[U_LEN_IDX],U_CRCLengthSrc);
        send_data+=(char)(CRC>>8);
        send_data+=(char)(CRC);
        my_serial->sendData(send_data);
        qDebug() <<"消息内容:"<< send_data.toHex();
    }
    RecieveData.clear();
    configpage->config_Btn = idleBtn;
}
