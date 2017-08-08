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
    m_configpage = new ConfigPage;
    pagesWidget->addWidget(m_configpage);
    pagesWidget->addWidget(new UpdatePage);
    pagesWidget->addWidget(new UserPage);
    //扩展窗口
    m_configpage->createExtension();
    //底部
    QLabel *RunStateStaticLabel = new QLabel("执行状态:");
    RunStateLabel = new QLabel;
    helpButton = new QPushButton(tr("帮助"));
    closeButton = new QPushButton(tr("关闭"));

    //创建页列表
    createIcons();
    contentsWidget->setCurrentRow(0);
    //创建串口类
    my_serial = new serial;
    //读写器ID
    ReaderBtn = new QPushButton("读写器ID:");
    ReaderBtn->setMinimumWidth(60);
    ReaderBtn->setMaximumWidth(60);
    ReaderIDLineEdt = new QLineEdit;
    ReaderIDLineEdt->setMaxLength(8);
    ReaderIDLineEdt->setMinimumWidth(60);
    ReaderIDLineEdt->setMaximumWidth(60);
    //顶部
    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(my_serial);
    topLayout->addWidget(ReaderBtn);
    topLayout->addWidget(ReaderIDLineEdt);
    topLayout->addStretch(1);
    //中间
    QHBoxLayout *horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(contentsWidget);
    horizontalLayout->addWidget(pagesWidget, 1);

    //底部
    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(RunStateStaticLabel);
    buttonsLayout->addWidget(RunStateLabel);
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
    mainLayout->addWidget(m_configpage->extension);
    setLayout(mainLayout);
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    setWindowTitle("校园腕带");
    this->conectEventtinit();
    //crc16初始化
    m_crc16 = new crc16;
}

Dialog::~Dialog()
{
    delete m_configpage;
    delete my_serial;
    delete m_packet;
    delete m_crc16;
}
//connect初始化
void Dialog::conectEventtinit()
{
    connect(closeButton, &QAbstractButton::clicked, this, &QWidget::close);//关闭按钮事件
    connect(m_configpage,&ConfigPage::sendsignal,this,&Dialog::SendData);//configdialog 数据更新
    connect(helpButton,&QPushButton::clicked,this,&Dialog::OnHelp);//帮助
    connect(my_serial->m_serialPort,&QSerialPort::readyRead,this,&Dialog::ReadComData);//读取串口数据
    connect(ReaderBtn,&QPushButton::clicked,this,&Dialog::GetReaderID);
}
//切换界面
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
    if(!bfilePath.exists())
    {
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
//包处理
void Dialog::PacketDeal(QByteArray P_SRC)
{
    const QByteArray P_HEAD = QByteArray::fromHex(packet_head);
    uint16_t u_cmd_state;//命令执行情况
    uint16_t P_Cnt = P_SRC.count(P_HEAD);//包个数
    for(uint16_t i = 0;i<P_Cnt;i++)
    {
        uint8_t u_cmd = (uint8_t)P_SRC[U_CMD_IDX];
        u_cmd_state = ((uint16_t)(P_SRC[U_DATA_IDX]<<8)|(uint8_t)P_SRC[U_DATA_IDX+1]);
        switch(u_cmd)
        {
            case U_CMD_FILE_WRITE://写文件
            {
                if(u_cmd_state == FILE_SUCCESS)
                    RunStateLabel->setText("写操作执行成功");
                else if(u_cmd_state == FILE_MODE_ERR)
                    RunStateLabel->setText("写操作区不存在");
                else if(u_cmd_state == FILE_BODER_ERR)
                    RunStateLabel->setText("写超出边界");
                else if(u_cmd_state == FILE_WDATA_ERR)
                    RunStateLabel->setText("写数据错误");
                else if(u_cmd_state == FILE_TIMEOUT_ERR)
                    RunStateLabel->setText("写命令超时");
            }
            break;
            case U_CMD_FILE_READ://读文件
            {
                if(u_cmd_state == FILE_SUCCESS)
                {
                    RunStateLabel->setText("读操作执行成功");
                    QByteArray P_DES = P_SRC;//包
                    uint16_t info_len = ((uint16_t)P_SRC[U_LEN_IDX]<<8)|(uint8_t)P_SRC[U_LEN_IDX+1];//信息长度

                    uint16_t pkt_len = U_HEAD_LEN + U_LENTH_LEN + info_len;//除了CRC长度
                    P_DES.truncate(pkt_len);//移除CRC后面的数据
                    P_DES.remove(0,U_DATA_IDX+U_FILE_STATE_LEN);//找到读到的数据内容,移除状态长度

                    m_configpage->ShowReadFileData(P_DES);
                }
                else if(u_cmd_state == FILE_MODE_ERR)
                    RunStateLabel->setText("读操作区不存在");
                else if(u_cmd_state == FILE_BODER_ERR)
                    RunStateLabel->setText("读超出边界");
                else if(u_cmd_state == FILE_WDATA_ERR)
                    RunStateLabel->setText("读数据错误");
                else if(u_cmd_state == FILE_WOFFSET_ERR)
                    RunStateLabel->setText("读偏移无效");
                else if(u_cmd_state == FILE_TIMEOUT_ERR)
                    RunStateLabel->setText("读命令超时");
            }
            break;
            case U_CMD_TIME_SET:
            {
                if(u_cmd_state == U_TIME_SUCESS)
                {
                    RunStateLabel->setText("时间下发成功");
                }
                else if(u_cmd_state == U_TIME_ERR)
                {
                    RunStateLabel->setText("时间内容错误");
                }
            }
            break;

            case U_CMD_MSG_PUSH://下发消息
            {
                char MsgSeq =P_SRC[U_DATA_IDX+2];
                if(u_cmd_state == U_MSG_SUCESS)
                {
                    QString StrState = "执行成功，最新消息序号:";
                    StrState+=QString::number(MsgSeq);
                    RunStateLabel->setText(StrState);
                }
                else if(u_cmd_state == U_MSG_ERR)
                {
                    QString StrState = "长度超出，最新消息序号:";
                    StrState+=QString::number(MsgSeq);
                    RunStateLabel->setText(StrState);
                }
            }
            break;
            case U_CMD_READER_ID://读写器ID
            {
                QByteArray P_DES = P_SRC;//包
                uint16_t info_len = ((uint16_t)P_SRC[U_LEN_IDX]<<8)|(uint8_t)P_SRC[U_LEN_IDX+1];//信息长度
                uint16_t pkt_len = U_HEAD_LEN + U_LENTH_LEN + info_len;//除了CRC长度
                P_DES.truncate(pkt_len);//移除CRC后面的数据
                P_DES.remove(0,U_DATA_IDX);//找到读到的数据内容
                QString DataDes = QString::fromLatin1(P_DES.toHex());
                RunStateLabel->setText("成功获取ID");
                qDebug()<<"读写器id"<<DataDes;
                ReaderIDLineEdt->setText(DataDes);
            }
            break;
            case U_CMD_LIST_TAG://列出标签
            case U_CMD_LIST_READER://列出读写器
            {
                RunStateLabel->setText("获取设备信息");
                QByteArray P_DES = P_SRC;//包
                uint16_t info_len = ((uint16_t)P_SRC[U_LEN_IDX]<<8)|(uint8_t)P_SRC[U_LEN_IDX+1];//信息长度
                uint16_t pkt_len = U_HEAD_LEN + U_LENTH_LEN + info_len;//除了CRC长度
                P_DES.truncate(pkt_len);//移除CRC后面的数据
                P_DES.remove(0,U_DATA_IDX);//找到读到的数据内容
                Device_Info.PKT_Max_Num = (char)((P_DES[0]>>4)&0x0f);//最大编号
                Device_Info.PKT_Crt_Num = (P_DES[0]&(char)(CRT_PKT_Msk));//当前包编号
                if(0x00 == Device_Info.PKT_Crt_Num)
                {
                    Device_Info.Device_idx = 0;//设备索引号清0
                    Device_Info.Device_Num = 0;//设备数量
                }
                if(Device_Info.PKT_Crt_Num <= Device_Info.PKT_Max_Num)
                {
                    Device_Info.Device_Num += P_DES[1];//设备数量
                }
                P_DES.remove(0,2);//标签内容
                QString TagDataDes = QString::fromLatin1(P_DES.toHex());
                for(;Device_Info.Device_idx<Device_Info.Device_Num;)
                {
                    Device_Info.ID = TagDataDes.left(8);//id
                    TagDataDes.remove(0,8);//删除ID*2
                    Device_Info.State = TagDataDes.left(2);//状态
                    TagDataDes.remove(0,2);//删除状态
                    Device_Info.VER = TagDataDes.left(2);//版本
                    TagDataDes.remove(0,2);//删除版本
                    Device_Info.RSSI = TagDataDes.left(2);//RSSI
                    TagDataDes.remove(0,2);//删除RSSI
                    Device_Info.TYPE = TagDataDes.left(2);//传感类型
                    if(u_cmd == U_CMD_LIST_TAG)
                    {
                        if(Device_Info.TYPE == "01")//校园腕带
                            Device_Info.TYPE = "校园腕带";
                    }
                    else if(u_cmd == U_CMD_LIST_READER)
                    {
                        if(Device_Info.TYPE == "01")//校园腕带
                            Device_Info.TYPE = "接收器";
                    }

                    TagDataDes.remove(0,2);//删除TYPE
                    Device_Info.DATA = TagDataDes.left(2);//传感数据
                    TagDataDes.remove(0,2);//删除data
                    Device_Info.BASEID = TagDataDes.left(4);//边界管理器
                    TagDataDes.remove(0,4);//删除边界管理器ID
                    if(u_cmd == U_CMD_LIST_TAG)
                    {
                        m_configpage->device_model->setItem(Device_Info.Device_idx,0,new QStandardItem(Device_Info.TYPE));
                        m_configpage->device_model->setItem(Device_Info.Device_idx,1,new QStandardItem(Device_Info.ID));
                        m_configpage->device_model->setItem(Device_Info.Device_idx,2,new QStandardItem(Device_Info.State));
                        m_configpage->device_model->setItem(Device_Info.Device_idx,3,new QStandardItem(Device_Info.RSSI));
                        m_configpage->device_model->setItem(Device_Info.Device_idx,4,new QStandardItem(Device_Info.DATA));
                        m_configpage->device_model->setItem(Device_Info.Device_idx,5,new QStandardItem(Device_Info.BASEID));
                        m_configpage->device_model->setItem(Device_Info.Device_idx,6,new QStandardItem(Device_Info.VER));
                    }
                    else if(u_cmd == U_CMD_LIST_READER)
                    {
                        m_configpage->device_model->setItem(Device_Info.Device_idx,0,new QStandardItem(Device_Info.TYPE));
                        m_configpage->device_model->setItem(Device_Info.Device_idx,1,new QStandardItem(Device_Info.ID));
                        m_configpage->device_model->setItem(Device_Info.Device_idx,2,new QStandardItem(Device_Info.RSSI));
                        m_configpage->device_model->setItem(Device_Info.Device_idx,3,new QStandardItem(Device_Info.DATA));
                        m_configpage->device_model->setItem(Device_Info.Device_idx,4,new QStandardItem(Device_Info.VER));
                    }

                    Device_Info.Device_idx++;
                }
            }
            break;
            case U_CMD_AUTO_REPORT:
            {

                QByteArray P_DES = P_SRC;//包
                uint16_t info_len = ((uint16_t)P_SRC[U_LEN_IDX]<<8)|(uint8_t)P_SRC[U_LEN_IDX+1];//信息长度
                uint16_t pkt_len = U_HEAD_LEN + U_LENTH_LEN + info_len;//除了CRC长度
                P_DES.truncate(pkt_len);//移除CRC后面的数据
                P_DES.remove(0,U_DATA_IDX);//找到读到的数据内容
                Device_Info.PKT_Max_Num = (char)((P_DES[0]>>4)&0x0f);//最大编号
                Device_Info.PKT_Crt_Num = (P_DES[0]&(char)(CRT_PKT_Msk));//当前包编号
                if(0x00 == Device_Info.PKT_Crt_Num)
                {
                    Device_Info.Device_idx = 0;//设备索引号清0
                    Device_Info.Device_Num = 0;//设备数量
                    Device_Info.report_cnt++;//上报次数++
                    QString str = "自动上报";
                    str+=QString::number(Device_Info.report_cnt);
                    RunStateLabel->setText(str);
                }
                if(Device_Info.PKT_Crt_Num <= Device_Info.PKT_Max_Num)
                {
                    Device_Info.Device_Num += P_DES[1];//设备数量
                }
                if(Device_Info.Device_Num == 0)
                {
                    m_configpage->device_model->clear();
                    m_configpage->device_model->setHorizontalHeaderItem(0,new QStandardItem(QObject::tr("TYPE")));//传感类型
                    m_configpage->device_model->setHorizontalHeaderItem(1,new QStandardItem(QObject::tr("ID")));
                    m_configpage->device_model->setHorizontalHeaderItem(2,new QStandardItem(QObject::tr("State")));
                    m_configpage->device_model->setHorizontalHeaderItem(3,new QStandardItem(QObject::tr("RSSI")));
                    m_configpage->device_model->setHorizontalHeaderItem(4,new QStandardItem(QObject::tr("DATA")));
                    m_configpage->device_model->setHorizontalHeaderItem(5,new QStandardItem(QObject::tr("BASEID")));//边界管理器ID
                    m_configpage->device_model->setHorizontalHeaderItem(6,new QStandardItem(QObject::tr("VER")));
                }
                P_DES.remove(0,2);//标签内容
                QString TagDataDes = QString::fromLatin1(P_DES.toHex());
                for(;Device_Info.Device_idx<Device_Info.Device_Num;)
                {
                    Device_Info.ID = TagDataDes.left(8);//id
                    TagDataDes.remove(0,8);//删除ID*2
                    Device_Info.State = TagDataDes.left(2);//状态
                    TagDataDes.remove(0,2);//删除状态
                    Device_Info.VER = TagDataDes.left(2);//版本
                    TagDataDes.remove(0,2);//删除版本
                    Device_Info.RSSI = TagDataDes.left(2);//RSSI
                    TagDataDes.remove(0,2);//删除RSSI
                    Device_Info.TYPE = TagDataDes.left(2);//传感类型
                    if(Device_Info.TYPE == "01")//校园腕带
                        Device_Info.TYPE = "校园腕带";
                    TagDataDes.remove(0,2);//删除TYPE
                    Device_Info.DATA = TagDataDes.left(2);//传感数据
                    TagDataDes.remove(0,2);//删除data
                    Device_Info.BASEID = TagDataDes.left(4);//边界管理器
                    TagDataDes.remove(0,4);//删除边界管理器ID

                    m_configpage->device_model->setItem(Device_Info.Device_idx,0,new QStandardItem(Device_Info.TYPE));
                    m_configpage->device_model->setItem(Device_Info.Device_idx,1,new QStandardItem(Device_Info.ID));
                    m_configpage->device_model->setItem(Device_Info.Device_idx,2,new QStandardItem(Device_Info.State));
                    m_configpage->device_model->setItem(Device_Info.Device_idx,3,new QStandardItem(Device_Info.RSSI));
                    m_configpage->device_model->setItem(Device_Info.Device_idx,4,new QStandardItem(Device_Info.DATA));
                    m_configpage->device_model->setItem(Device_Info.Device_idx,5,new QStandardItem(Device_Info.BASEID));
                    m_configpage->device_model->setItem(Device_Info.Device_idx,6,new QStandardItem(Device_Info.VER));
                    Device_Info.Device_idx++;

                }
            }
            break;
            default:break;
        }
        int HeadIdx = P_SRC.indexOf(P_HEAD,(P_SRC.indexOf(P_HEAD)+1));//查找下一个包头
        if(HeadIdx > 0)//找到包头
        {
            P_SRC.remove(0,HeadIdx);//跳到下一个包头位置
        }
    }

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
    if(my_serial->m_serialPort->bytesAvailable())
    {
        ReceiveData+=my_serial->m_serialPort->readAll();
        if(true == m_packet->unPACK(&CopyData,ReceiveData))
        {
            PacketDeal(CopyData);
            ReceiveData.remove(0,CopyData.length());
            CopyData.clear();
        }
    }
}
/****************************************************
读取读写器ID
串口通信 上位机->接收器
描述	帧头	长度	协议版本	读写器ID	定位信息	协议流水号
IDX	0~1	2~3	4		5~8		9       10
描述	命令字	信息内容  CRC16校验
IDX	11		12      13
长度 “协议版本~信息内容"
CRC "长度~信息内容"
命令字F2
信息内容：无
******************************************************/
void Dialog::GetReaderID()
{
    QByteArray ReaderIDBuff;
    ReaderIDBuff[U_HEADER_IDX] = packet_head1;//帧头
    ReaderIDBuff[U_HEADER_IDX+1] = packet_head2;//帧头
    ReaderIDBuff[U_PROTOCOL_IDX] = U_PROTOCOL_VER;//协议
    ReaderIDBuff[U_ID_IDX] = (char)0xff;//读写器ID
    ReaderIDBuff[U_ID_IDX+1] = (char)0xff;//读写器ID
    ReaderIDBuff[U_ID_IDX+2] = (char)0xff;//读写器ID
    ReaderIDBuff[U_ID_IDX+3] = (char)0xff;//读写器ID
    ReaderIDBuff[U_TXGPS_IDX] = U_TXGPS_Value;//定位信息
    ReaderIDBuff[U_SEQ_IDX] = U_SEQ_Value;//流水号
    ReaderIDBuff[U_CMD_IDX] = U_CMD_READER_ID;//命令
    char U_LengthSrc = ReaderIDBuff.length()-U_HEAD_LEN-U_LENTH_LEN;//包长度-帧头-长度
    ReaderIDBuff[U_LEN_IDX] = (char)(U_LengthSrc>>8);//长度
    ReaderIDBuff[U_LEN_IDX+1] = (char)U_LengthSrc;//长度
    //CRC
    int U_CRCLengthSrc = ReaderIDBuff.length()-U_HEAD_LEN;//包长度-帧头
    char *crcsrc = ReaderIDBuff.data();
    uint16_t CRC = m_crc16->getcrc16((uint8_t *)&crcsrc[U_LEN_IDX],U_CRCLengthSrc);
    ReaderIDBuff+=(char)(CRC>>8);
    ReaderIDBuff+=(char)(CRC);
    //清空状态
    RunStateLabel->clear();
    ReceiveData.clear();
    m_packet->Packet_Init();
    my_serial->sendData(ReaderIDBuff);
    qDebug() <<"读取ID:"<< ReaderIDBuff.toHex();
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
    if(settimeBtnPD ==m_configpage->config_Btn)//时间设置按钮按下
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
    else if(setparaBtnPD ==m_configpage->config_Btn)//参数设置按钮按下
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
    else if(WriteFileBtnPD == m_configpage->config_Btn)
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
    else if(ReadFileBtnPD == m_configpage->config_Btn)
    {
        m_configpage->ClearReadFileData();
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
    else if(MsgBtnPD == m_configpage->config_Btn)
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
    else if(SesrchTagPD == m_configpage->config_Btn )
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
        qDebug() <<"查询标签/读写器:"<< send_data.toHex();
    }
    else if(AutoReportPD == m_configpage->config_Btn)
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
        qDebug() <<"自动上报:"<< send_data.toHex();
        Device_Info.report_cnt = 0;//上报次数清0
    }
    RunStateLabel->clear();
    ReceiveData.clear();
    m_packet->Packet_Init();
    m_configpage->config_Btn = idleBtn;
}
