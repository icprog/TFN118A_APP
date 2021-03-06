#include "configpage.h"
#include "packet.h"

ConfigPage::ConfigPage(QWidget *parent) : QWidget(parent)
{
     //时间
     QGroupBox *timeGroup = new QGroupBox("时间");
     timeGroup->setMaximumHeight(100);
     timeGroup->setMaximumWidth(180);
     getTimeBtn = new QPushButton("获取时间");
     setTimeBtn = new QPushButton("时间设置");

     QDialogButtonBox *dlgBtnBox = new QDialogButtonBox(Qt::Horizontal);
     dlgBtnBox->addButton(getTimeBtn, QDialogButtonBox::ActionRole);
     dlgBtnBox->addButton(setTimeBtn, QDialogButtonBox::ActionRole);
//     QLabel *timeLabel = new QLabel("时间:");
     dateEdit = new QDateTimeEdit(QDateTime::currentDateTime());
     dateEdit->setDisplayFormat("yyyy/MM/dd  HH:mm:ss");


     QGridLayout *timeLayout = new QGridLayout;
     timeLayout->addWidget(dlgBtnBox, 0, 0,1,1);
     timeLayout->addWidget(setTimeBtn, 0, 1,1,1);
     timeLayout->addWidget(dateEdit, 1, 0,1,2);
     timeGroup->setLayout(timeLayout);

     //参数
     QGroupBox *paraGroup = new QGroupBox("腕带参数");
     paraGroup->setMaximumHeight(240);
     paraGroup->setMaximumWidth(180);
     QLabel *TargetIDLabel = new QLabel("目标ID:");
     TargetIDLineEdt = new QLineEdit;
     TargetIDLineEdt->setMaxLength(8);
     //发射功率
     QLabel *pwrLabel = new QLabel("发射功率:");
     pwrCombo = new QComboBox;

     pwrCombo->addItem(tr("-30dBm"));
     pwrCombo->addItem(tr("-20dBm"));
     pwrCombo->addItem(tr("-16dBm"));
     pwrCombo->addItem(tr("-12dBm"));
     pwrCombo->addItem(tr("-8dBm"));
     pwrCombo->addItem(tr("-4dBm"));
     pwrCombo->addItem(tr("0dBm"));
     pwrCombo->addItem(tr("4dBm"));
     pwrCombo->setCurrentIndex(6);
//     QLabel *pwrUnitLabel = new QLabel("dBm");

     //工作模式
     QLabel *wModeLabel = new QLabel("工作模式:");
     wModeCombo = new QComboBox;
     wModeCombo->addItem("活动模式");
     wModeCombo->addItem("保存模式");
//     QLabel *spaceLabel = new QLabel;

     //报警时间
     QLabel *alarmLabel = new QLabel("报警时间:");
     alarmCombo = new QComboBox;
     alarmCombo->addItem(tr("1s"));
     alarmCombo->addItem(tr("2s"));
     alarmCombo->addItem(tr("3s"));
     alarmCombo->addItem(tr("4s"));

     alarmCombo->addItem(tr("5s"));
     alarmCombo->addItem(tr("6s"));
     alarmCombo->setCurrentIndex(3);


//     QLabel *alarmUnitLabel = new QLabel("s");
     //设置按钮
     setParaBtn = new QPushButton("参数设置");
     //layout
     QGridLayout *paraLayout = new QGridLayout;
     paraLayout->addWidget(TargetIDLabel, 0,0);
     paraLayout->addWidget(TargetIDLineEdt, 0,1);
     paraLayout->addWidget(pwrLabel, 1,0);
     paraLayout->addWidget(pwrCombo, 1,1);
//     paraLayout->addWidget(pwrUnitLabel,0,3);

     paraLayout->addWidget(wModeLabel, 2, 0);
     paraLayout->addWidget(wModeCombo, 2,1);
//     paraLayout->addWidget(spaceLabel,1,3);

     paraLayout->addWidget(alarmLabel, 3, 0);
     paraLayout->addWidget(alarmCombo, 3, 1);
//     paraLayout->addWidget(alarmUnitLabel, 2, 3);

     paraLayout->addWidget(setParaBtn,4,0,1,2);
     paraGroup->setLayout(paraLayout);

     //消息
     QGroupBox *messageGroup = new QGroupBox("消息");
     messageGroup->setMaximumHeight(150);
     messageGroup->setMaximumWidth(180);
     messageTedt = new QTextEdit;
     QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB18030"));
     messageTedt->setText("小朋友，你们好！");
     messageTedt->setMaximumHeight(50);
     messageTedt->setMaximumWidth(160);
     messageBtn = new QPushButton("发送消息");
     QGridLayout *messageLayout = new QGridLayout;
     messageLayout->addWidget(messageTedt,0,0,1,2);
     messageLayout->addWidget(messageBtn,1,0,1,2);
     messageGroup->setLayout(messageLayout);
     //文件操作
     QGroupBox *fileGroup = new QGroupBox("文件操作");
     fileGroup->setMaximumHeight(280);
     fileGroup->setMaximumWidth(180);
     //QButtonGroup无布局管理，需要layout布局管理
     QButtonGroup *WRBtnGroup = new QButtonGroup;
     readRadioBtn = new QRadioButton("读操作");
     writeRadioBtn = new QRadioButton("写操作");
     WRBtnGroup->addButton(readRadioBtn,0);
     WRBtnGroup->addButton(writeRadioBtn,1);
     WRBtnGroup->setExclusive(true);//按钮互斥

     QLabel* TargetIDLabel1 = new QLabel("目标ID:");

     TargetIDLineEdt1 = new QLineEdit;
     TargetIDLineEdt1->setMaxLength(8);

     QLabel *modeLabel = new QLabel("模式:");

     QLabel *OTLabel = new QLabel("命令超时:");//超时时间
     OverTime = new QComboBox();
     OverTime->addItem("无超时");
     QStringList OTList;
     for(uint8_t i = 1; i< 10 ;i++)
     {

         QString OTStr = QString::number(i);
         OTStr += "s";
         OTList << OTStr;
     }
     OverTime->addItems(OTList);
     OverTime->setCurrentIndex(9);

     modeCombo = new QComboBox;
     modeCombo->addItem("参数区");
     modeCombo->addItem("保留区");
     modeCombo->addItem("用户区1");
     modeCombo->addItem("用户区2");

     QLabel *offsetLabel = new QLabel("偏移:");
     offsetCombo = new QComboBox;
     offsetCombo->addItem("最新记录");
     QStringList offsetList;
     for(int i=0;i<32;i++)
     {
         QString offsetstr = QString::number(i);
         offsetList << offsetstr;
     }
     offsetCombo->addItems(offsetList);
     offsetCombo->setCurrentIndex(0);

     QLabel *lenthLabel = new QLabel("长度:");
     lenthCombo = new QComboBox;

     QStringList lenthList;
     for(int i=0;i<17;i++)
     {
         QString LengthStr = QString::number(i);
         lenthList+=LengthStr;
     }
     lenthCombo->addItems(lenthList);
     lenthCombo->setCurrentIndex(16);
     QLabel *dataLabel = new QLabel("数据:");
     dataTedt = new QTextEdit;
     dataTedt->setText("01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16");
     dataTedt->setMaximumHeight(40);
     dataTedt->setMaximumWidth(160);

     WRFileBtn = new QPushButton("文件操作");

     QGridLayout *fileLayout = new QGridLayout;
     fileLayout->addWidget(readRadioBtn,0,0);
     fileLayout->addWidget(writeRadioBtn,0,1);
     fileLayout->addWidget(TargetIDLabel1, 1,0);
     fileLayout->addWidget(TargetIDLineEdt1, 1,1);
     fileLayout->addWidget(OTLabel,2,0);
     fileLayout->addWidget(OverTime,2,1);
     fileLayout->addWidget(modeLabel,3,0);
     fileLayout->addWidget(modeCombo,3,1);
     fileLayout->addWidget(offsetLabel,4,0);
     fileLayout->addWidget(offsetCombo,4,1);
     fileLayout->addWidget(lenthLabel,5,0);
     fileLayout->addWidget(lenthCombo,5,1);
     fileLayout->addWidget(dataLabel,6,0);
     fileLayout->addWidget(dataTedt,7,0,1,2);
     fileLayout->addWidget(WRFileBtn,8,0,1,2);
     fileGroup->setLayout(fileLayout);

     //射频测试
     QGroupBox *radioGroup = new QGroupBox("射频性能");
     radioGroup->setMaximumHeight(70);
     radioGroup->setMaximumWidth(180);
     radioBtn = new QPushButton("射频性能测试");
     QGridLayout *radioLayout = new QGridLayout;
     radioLayout->addWidget(radioBtn,0,0,1,2);
     radioGroup->setLayout(radioLayout);

     radioBtn->setCheckable(true);

 //! [0]
     radioBtn->setAutoDefault(false);
     //扩展窗口放在主界面
//     createExtension();
 //! [1]

     //整机测试
      testBtn = new QPushButton("整机测试");
//     QLabel *stateLable = new QLabel("执行成功");
//     stateLable->setAlignment(Qt::AlignBottom | Qt::AlignLeft);
//     stateLable->setFrameStyle(QFrame::Panel | QFrame::Sunken);
//     QHBoxLayout *bottomLayout = new QHBoxLayout;
//     bottomLayout->addWidget(testBtn);
//     bottomLayout->addWidget(stateLable);

     QVBoxLayout *leftLayout = new QVBoxLayout;
     leftLayout->addWidget(timeGroup);
     leftLayout->addWidget(paraGroup);
     leftLayout->addWidget(messageGroup);
     leftLayout->addSpacing(12);
     leftLayout->addWidget(testBtn);
     leftLayout->addStretch(1);

     QVBoxLayout *rightLayout = new QVBoxLayout;
     rightLayout->addWidget(fileGroup);
     rightLayout->addWidget(radioGroup);
     rightLayout->addStretch(12);

     QGridLayout *mainLayout = new QGridLayout;
     mainLayout->addLayout(leftLayout,0,0,1,1);
     mainLayout->addLayout(rightLayout,0,1,1,1);
//     mainLayout->addWidget(extension,0,2,1,1);
     setLayout(mainLayout);

}

void ConfigPage::createExtension()
{
    extension = new QWidget;
    //列出标签
    QGroupBox *searchDeviceGroup = new QGroupBox("查询设备");
    QLabel *searchDevicelabel = new QLabel("查询时间");
    searchTimeCombox = new QComboBox;

    QStringList searchTimeList;
    for(uint8_t i = 1; i< 8 ;i++)
    {

        QString searchTimeStr = QString::number(i);
        searchTimeStr += "s";
        searchTimeList << searchTimeStr;
    }
    searchTimeCombox->addItems(searchTimeList);
    searchTimeCombox->setCurrentIndex(2);

    lpfilterCheckBox = new QCheckBox("低电过滤");
    rssiCheckBox = new QCheckBox("RSSI过滤");
    rssiCombox = new QComboBox;
    QStringList rssiList;
    for(uint8_t i = 0; i< 128 ;i++)
    {

        QString rssistr = QString::number(i);
        rssistr += "dBm";
        rssiList << rssistr;
    }
    rssiCombox->addItems(rssiList);
    rssiCombox->setCurrentIndex(64);
    rssiCombox->setDisabled(true);

    searchTagBtn = new QPushButton("查询标签");
    searchReaderBtn = new QPushButton("查询读写器");

    QGridLayout *searchDeviceLayout = new QGridLayout;
    searchDeviceLayout->addWidget(searchDevicelabel,0,0);
    searchDeviceLayout->addWidget(searchTimeCombox,0,1);
    searchDeviceLayout->addWidget(lpfilterCheckBox,1,0,1,2);
    searchDeviceLayout->addWidget(rssiCheckBox,2,0);
    searchDeviceLayout->addWidget(rssiCombox,2,1);
    searchDeviceLayout->addWidget(searchTagBtn,3,0);
    searchDeviceLayout->addWidget(searchReaderBtn,3,1);

    searchDeviceGroup->setLayout(searchDeviceLayout);

    //自动上报
    QGroupBox *autoreportGroup = new QGroupBox("自动上报");
    QLabel *leaveTimeLabel = new QLabel("离开时间:");
    leaveTimeCombox = new QComboBox;

    QStringList leaveTimeList;
    for(uint8_t i = 1; i< 11 ;i++)
    {

        QString leaveTimeStr = QString::number(i);
        leaveTimeStr += "s";
        leaveTimeList << leaveTimeStr;
    }
    leaveTimeCombox->addItems(leaveTimeList);
    leaveTimeCombox->setCurrentIndex(2);

    QLabel *reportTimeLabel = new QLabel("上报间隔:");
    reportTimeCombox = new QComboBox;

    QStringList reportTimeList;
    for(uint8_t i = 1; i< 8 ;i++)
    {
        QString reportTimeStr = QString::number(i);
        reportTimeStr += "s";
        reportTimeList << reportTimeStr;
    }
    reportTimeCombox->addItems(reportTimeList);
    reportTimeCombox->setCurrentIndex(2);


    lpfilterAutoCheckBox = new QCheckBox("低电过滤");
    rssiAutoCheckBox = new QCheckBox("RSSI过滤");
    rssiAutoCombox = new QComboBox;
    QStringList rssiAutoList;
    for(uint8_t i = 0; i< 128 ;i++)
    {

        QString rssiAutostr = QString::number(i);
        rssiAutostr += "dBm";
        rssiAutoList << rssiAutostr;
    }
    rssiAutoCombox->addItems(rssiAutoList);
    rssiAutoCombox->setCurrentIndex(64);
    rssiAutoCombox->setDisabled(true);
    AutoReportOpenBtn = new QPushButton("打开自动上报");
    AutoReportCloseBtn = new QPushButton("关闭自动上报");

    QGridLayout *autoreportLayout = new QGridLayout;
    autoreportLayout->addWidget(leaveTimeLabel,0,0);
    autoreportLayout->addWidget(leaveTimeCombox,0,1);
    autoreportLayout->addWidget(reportTimeLabel,2,0);
    autoreportLayout->addWidget(reportTimeCombox,2,1);
    autoreportLayout->addWidget(lpfilterAutoCheckBox,3,0);
    autoreportLayout->addWidget(rssiAutoCheckBox,4,0);
    autoreportLayout->addWidget(rssiAutoCombox,4,1);
    autoreportLayout->addWidget(AutoReportOpenBtn,5,0);
    autoreportLayout->addWidget(AutoReportCloseBtn,5,1);
    autoreportGroup->setLayout(autoreportLayout);


    //设备信息
    infoDevice = new QTableView;
    device_model = new QStandardItemModel();
    device_model->setHorizontalHeaderItem(0,new QStandardItem(QObject::tr("TYPE")));//传感类型
    device_model->setHorizontalHeaderItem(1,new QStandardItem(QObject::tr("ID")));
    device_model->setHorizontalHeaderItem(2,new QStandardItem(QObject::tr("State")));
    device_model->setHorizontalHeaderItem(3,new QStandardItem(QObject::tr("RSSI")));
    device_model->setHorizontalHeaderItem(4,new QStandardItem(QObject::tr("DATA")));
    device_model->setHorizontalHeaderItem(5,new QStandardItem(QObject::tr("BASEID")));//边界管理器ID
    device_model->setHorizontalHeaderItem(6,new QStandardItem(QObject::tr("VER")));
     //利用setModel()方法将数据模型与QTableView绑定
    infoDevice->setModel(device_model);
//    infoDevice->setEditTriggers(QAbstractItemView::NoEditTriggers);//只读
    //如果你用在QTableView中使用右键菜单，需启用该属性
    infoDevice->setContextMenuPolicy(Qt::CustomContextMenu);

//    device_model->setItem(0,1,new QStandardItem("张三"));
//    device_model->setItem(1,1,new QStandardItem("张三"));
    QGridLayout *extensionLayout = new QGridLayout;
    extensionLayout->addWidget(searchDeviceGroup,0,0,1,1);
    extensionLayout->addWidget(autoreportGroup,0,1,1,1);
    extensionLayout->addWidget(infoDevice,1,0,1,3);


    //扩展窗口
    connect(radioBtn, &QAbstractButton::toggled, extension, &QWidget::setVisible);

    QVBoxLayout *extensionMainLayout = new QVBoxLayout;
    extensionMainLayout->setMargin(0);
    extensionMainLayout->addLayout(extensionLayout);
    extension->setLayout(extensionMainLayout);
    extension->setMinimumHeight(400);
    extension->setMinimumWidth(600);
    extension->setMaximumHeight(400);
    extension->setMaximumWidth(800);
    extension->hide();
    event_init();
    //
}

void ConfigPage::event_init()
{
    connect(getTimeBtn,&QPushButton::clicked,this,&ConfigPage::updateTime);//获取时间
    connect(setTimeBtn,&QPushButton::clicked,this,&ConfigPage::setTimebuf);//设置时间
    connect(setParaBtn,&QPushButton::clicked,this,&ConfigPage::setParaBuf);//设置参数
    connect(WRFileBtn,&QPushButton::clicked,this,&ConfigPage::WriteReadFile);//文件操作
    connect(rssiCheckBox,&QCheckBox::clicked,rssiCombox,&QComboBox::setEnabled);//选择
    connect(rssiAutoCheckBox,&QCheckBox::clicked,rssiAutoCombox,&QComboBox::setEnabled);
    connect(messageTedt,&QTextEdit::textChanged,this,&ConfigPage::msgMaxLength);//消息最大长度
    connect(messageBtn,&QPushButton::clicked,this,&ConfigPage::msgSend);//消息下发
    connect(searchTagBtn,&QPushButton::clicked,this,&ConfigPage::SearchTag);//查询标签
    connect(searchReaderBtn,&QPushButton::clicked,this,&ConfigPage::SearchReader);//查询读写器
    connect(AutoReportOpenBtn,&QPushButton::clicked,this,&ConfigPage::AutoReportOpen);//打开自动上报
    connect(AutoReportCloseBtn,&QPushButton::clicked,this,&ConfigPage::AutoReportClose);//关闭自动上报
    connect(testBtn,&QPushButton::clicked,this,&ConfigPage::DeviceTest);//整机测试
}
//清空数据
void ConfigPage::ClearReadFileData()
{
    dataTedt->clear();
}
//显示读取内容数据
void ConfigPage::ShowReadFileData(QByteArray Data_Src)
{
    QString StrDataDes = QString::fromLatin1(Data_Src.toHex(' '));
//    QString StrDes;
//    for(int i=0;i<StrDataDes.length();)
//    {
//        StrDes+=StrDataDes[i];
//        StrDes+=StrDataDes[i+1];
//        StrDes+=" ";
//        i=i+2;
//    }

    qDebug() <<"数据内容"<< StrDataDes;
    dataTedt->setPlainText(StrDataDes);
}


//时间更新
void ConfigPage::updateTime()
{
    dateEdit->setDateTime(QDateTime::currentDateTime());
}
//更新时间数据
/****************************************************
串口通信 上位机->接收器 命令字90
时间设置信息内容
年月日时分秒：6字节 2017-08-01 14：40：30-> 17 08 01 14 40 30
******************************************************/
void ConfigPage::setTimebuf()
{
    QByteArray timebuff;

    QString datasrc= dateEdit->text();
    timebuff = QByteArray::fromHex(datasrc.toLatin1());
    timebuff.remove(0,1);
//    qDebug() << timebuff;
    config_Btn = settimeBtnPD;//按键按下
    emit sendsignal(timebuff);
}
//更新参数buff
#define TAGP_PWR_IDX                                    1
#define TAGP_PWR_Pos									4
#define TAGP_WORKMODE_IDX                               2
#define TAGP_WORKMODE_Pos								0
#define TAGP_WORKMODE_Msk								0x0f
#define TAGP_WORKMODE_MAX_VALUE							0x01
#define TAGP_KEYALARM_IDX								4
#define OVER_TIME                                       9//9S
/****************************************************
串口通信 上位机->接收器 命令F0
参数设置信息内容
目标ID：XXXXXXXX 4字节
超时时间:0~9  0：无超时时间  单位s
保留：0000
写参数区：01
写最新参数:FFFF
写长度：10
数据内容：16字节
******************************************************/
void ConfigPage::setParaBuf()
{

    //参数buff
    QByteArray parabuff;
    QString DestIDSrc = TargetIDLineEdt->text();
    config_Btn = setparaBtnPD;//按键按下
    if(DestIDSrc.length()<8)
    {
        QByteArray error;
        emit sendsignal(error);
    }
    else
    {
        char txpower = 0x00;
        char workmode = 0x00;
        for(int i=0;i< 16;i++)
            parabuff[i] = 0;
        QString tag_txpower = pwrCombo->currentText();
        if(tag_txpower == "-30dBm")
            txpower |= (0<<TAGP_PWR_Pos);
        else if(tag_txpower == "-20dBm")
            txpower |= (1<<TAGP_PWR_Pos);
        else if(tag_txpower == "-16dBm")
            txpower |= (2<<TAGP_PWR_Pos);
        else if(tag_txpower == "-12dBm")
            txpower |= (3<<TAGP_PWR_Pos);
        else if(tag_txpower == "-8dBm")
            txpower |= (4<<TAGP_PWR_Pos);
        else if(tag_txpower == "-4dBm")
            txpower |= (5<<TAGP_PWR_Pos);
        else if(tag_txpower == "0dBm")
            txpower |= (6<<TAGP_PWR_Pos);
        else if(tag_txpower == "4dBm")
            txpower |= (7<<TAGP_PWR_Pos);
        else
            txpower|=(6<<TAGP_PWR_Pos);
        QString tag_workmode = wModeCombo->currentText();
        if("保存模式" == tag_workmode)
            workmode|=0x00;
        else
            workmode|=0x01;

        QString tag_alarmtime = alarmCombo->currentText();
        tag_alarmtime.chop(1);//移除最后一位s
        char alarmtimeSrc = tag_alarmtime.toInt();
        parabuff[TAGP_PWR_IDX] = txpower;//发射功率
        parabuff[TAGP_WORKMODE_IDX] =workmode;//工作模式
        parabuff[TAGP_KEYALARM_IDX] = alarmtimeSrc;//报警时间
         QByteArray sendparabuff;
//        QString DestIDSrc = TargetIDLineEdt->text();
        QByteArray DestIDDec = QByteArray::fromHex(DestIDSrc.toLatin1());//目标ID
        sendparabuff+=DestIDDec;//目标ID
        sendparabuff+=OVER_TIME;//超时时间
        sendparabuff+=(char)(U_FILE_RESERVER>>8);//保留
        sendparabuff+=(char)U_FILE_RESERVER;//保留
        sendparabuff+=U_FILE_MODE_PARA;//内部参数区
        sendparabuff+=(char)(U_FILE_OFFSET_RNEW>>8);
        sendparabuff+=(char)U_FILE_OFFSET_RNEW;//写最新参数
        sendparabuff+=(char)0x10;//长度
        sendparabuff+=parabuff;
        qDebug() << "获取参数值:" << sendparabuff.toHex();
        config_Btn = setparaBtnPD;//按键按下
        emit sendsignal(sendparabuff);
    }

}

/****************************************************
串口通信 上位机->接收器
写命令F0
参数设置信息内容
目标ID：XXXXXXXX 4字节
超时时间:0~9  0：无超时时间  单位s
保留：0000
区选择：01~04
写最新参数:FFFF
写长度：01~10
数据内容：字节数，最大16字节
-----------------------------------------------------
读命令F1
目标ID：XXXXXXXX 4字节
超时时间:0~9  0：无超时时间  单位s
保留：0000
区选择：01~04
读最新参数:FFFF  参数区 保留区 0~15 用户区1、2 0~31
长度 01~10
******************************************************/
void ConfigPage::WriteReadFile()
{
    QString DestIDSrc1 = TargetIDLineEdt1->text();
    if(DestIDSrc1.length()<8)
    {
        QByteArray error;
        config_Btn = WriteFileBtnPD;//按键按下
        emit sendsignal(error);
    }
    else
    {
        //超时时间
        char OverTimeDest;
        QString OverTimeSrc = OverTime->currentText();
        if("无超时" == OverTimeSrc)
        {
            OverTimeDest = 0x00;
        }
        else
        {
            OverTimeSrc.chop(1);//去掉单位s
            OverTimeDest = OverTimeSrc.toInt();
        }
        //参数区
        char AreaDest=0;
        QString AreaSrc = modeCombo->currentText();
        if("参数区" == AreaSrc)
        {
            AreaDest = U_FILE_MODE_PARA;
        }
        else if("保留区" == AreaSrc)
        {
            AreaDest = U_FILE_MODE_RESERVER;
        }
        else if("用户区1" == AreaSrc)
        {
            AreaDest = U_FILE_MODE_USER1;
        }
        else if("用户区2" == AreaSrc)
        {
            AreaDest = U_FILE_MODE_USER2;
        }
        //长度
        char LenthDest;
        QString LenthSrc = lenthCombo->currentText();
        LenthDest = LenthSrc.toInt();
        //写命令
        if(writeRadioBtn->isChecked())//写操作
        {
            QByteArray WriteBuff;
    //        QString DestIDSrc1 = TargetIDLineEdt1->text();
            QByteArray DestIDDec1 = QByteArray::fromHex(DestIDSrc1.toLatin1());//目标ID
            WriteBuff+=U_CMD_FILE_WRITE;//命令
            WriteBuff+=DestIDDec1;//目标ID
            WriteBuff+=OverTimeDest;//超时时间
            WriteBuff+=(char)(U_FILE_RESERVER>>8);//保留
            WriteBuff+=(char)U_FILE_RESERVER;//保留
            WriteBuff+=AreaDest;//操作区
            WriteBuff+=(char)(U_FILE_OFFSET_RNEW>>8);
            WriteBuff+=(char)U_FILE_OFFSET_RNEW;//写最新参数
            WriteBuff+=LenthDest;//长度
            QString DataSrc = dataTedt->toPlainText();
            QByteArray DataDes = QByteArray::fromHex(DataSrc.toLatin1());
            WriteBuff.append(DataDes,(int)LenthDest);
            qDebug() << WriteBuff.toHex();
            config_Btn = WriteFileBtnPD;//按键按下
            emit sendsignal(WriteBuff);
        }
        else if(readRadioBtn->isChecked())//读操作
        {
            QByteArray ReadBuff;
            QString DestIDSrc1 = TargetIDLineEdt1->text();
            QByteArray DestIDDec1 = QByteArray::fromHex(DestIDSrc1.toLatin1());//目标ID

            ReadBuff+=U_CMD_FILE_READ;//命令
            ReadBuff+=DestIDDec1;//目标ID
            ReadBuff+=OverTimeDest;//超时时间
            ReadBuff+=(char)(U_FILE_RESERVER>>8);//保留
            ReadBuff+=(char)U_FILE_RESERVER;//保留
            ReadBuff+=AreaDest;//操作区
            //偏移
            QString OffsetSrc =offsetCombo->currentText();
            if("最新记录" == OffsetSrc)
            {
                ReadBuff+=(char)(U_FILE_OFFSET_RNEW>>8);
                ReadBuff+=(char)U_FILE_OFFSET_RNEW;//写最新参数
            }
            else
            {
                char OffsetDest = OffsetSrc.toInt();
                ReadBuff+=(char)0x00;
                ReadBuff+=OffsetDest;
            }
            ReadBuff+=LenthDest;//长度
            qDebug() << ReadBuff.toHex();
            config_Btn = ReadFileBtnPD;//按键按下
            emit sendsignal(ReadBuff);
        }
    }


}
//qstring(unicode)->gbk
QByteArray ConfigPage::U2GBK(QString unic)
{
    QTextCodec* pCodec = QTextCodec::codecForName("GB18030");
    QByteArray gbk = pCodec->fromUnicode(unic);
    return gbk;
}
//qstring(unicode)->unicode
QByteArray ConfigPage::QString2Unicode(QString src)
{
    QByteArray unic;
    for(int i=0;i<src.length();i++)
    {
        const QChar a = src.at(i);
        ushort s = a.unicode();
        char data_h = (char)(s>>8);
        char data_l = (char)(s);
        unic+=data_h;
        unic+=data_l;
    }
    return unic;
}
/****************************************************
串口通信 上位机->接收器
消息命令89
信息内容构成：消息长度+消息内容
消息长度1字节
消息内容
******************************************************/
#define GBK 1
void ConfigPage::msgSend()
{
    QByteArray MsgBuff;//消息缓存
    QString MsgSrc = messageTedt->toPlainText();
#if GBK
    QByteArray MsgDest = this->U2GBK(MsgSrc);
#else
    QByteArray MsgDest = this->QString2Unicode(MsgSrc);
#endif
    char MsgLen = MsgDest.length();
    MsgBuff+=U_CMD_MSG_PUSH;//消息命令
    MsgBuff+=MsgLen;//消息长度
    MsgBuff+=MsgDest;//消息内容
    config_Btn = MsgBtnPD;//按键按下
    qDebug() <<"消息命令内容"<< MsgBuff.toHex();
    emit sendsignal(MsgBuff);
}
/****************************************************
串口通信 上位机->接收器
整机测试命令F3
信息内容
0：0x01
消息长度1字节
消息内容
******************************************************/
void ConfigPage::DeviceTest()
{
    QString DestIDSrc = TargetIDLineEdt->text();
    config_Btn = DeviceTestPD;//按键按下
    if(DestIDSrc.length()<8)
    {
        QByteArray error;
        emit sendsignal(error);
    }
    else
    {
        QByteArray DeviceTestBuf;
        DeviceTestBuf[0] = (char)U_CMD_DEVICE_TEST;
        QByteArray DestIDDec = QByteArray::fromHex(DestIDSrc.toLatin1());//目标ID
        DeviceTestBuf+=DestIDDec;
        DeviceTestBuf+= (char)0x01;
        qDebug() <<"整机测试"<< DeviceTestBuf.toHex();
        emit sendsignal(DeviceTestBuf);
    }
}

/****************************************************
串口通信 上位机->接收器
列出标签命令F4 列出读写器命令F5
信息内容
0：bit3~1 查询时间
   bit0：1使能低电过滤；0不使能低电过滤
1: bit7:1:使能RSSI过滤；0:不使能RSSI过滤
   bit6~0  0~127 RSSI过滤值
消息长度1字节
消息内容
******************************************************/
#define LP_FILTEREN_Pos   0
#define LP_FILTEREN_Msk   0x01  //使能低电过滤
#define RSSI_FILTEREN_Pos 7
#define RSSI_FILTEREN_Msk 0x80  //使能RSSI过滤
#define RSSI_FILTERVALUE_Pos 0
#define RSSI_FILTERVALUE_Msk 0x7F  //RSSI过滤值
#define SEARCH_TIME_Pos     1
#define SEARCH_TIME_Msk     0x0E   //
void ConfigPage::SearchTag()
{
    QByteArray SearchTagBuf;
    char temp[2]={0,0};
    QString SearchTimeSrc = searchTimeCombox->currentText();
    SearchTimeSrc.chop(1);//移除最后一位s
    char SearchTime = SearchTimeSrc.toInt();
    temp[0] = (SearchTime<<SEARCH_TIME_Pos)&SEARCH_TIME_Msk;
    if(lpfilterCheckBox->isChecked())
    {
        temp[0]|=LP_FILTEREN_Msk;
    }
    if(rssiCheckBox->isChecked())
    {
        temp[1] = RSSI_FILTEREN_Msk;
        QString SearchRSSISrc = rssiCombox->currentText();
        SearchRSSISrc.chop(3);//移除dbm
        char SearchRSSI = SearchRSSISrc.toInt();
        temp[1] |= (SearchRSSI&RSSI_FILTERVALUE_Msk)<<RSSI_FILTERVALUE_Pos;
    }
    else
    {
        temp[1] = 0x00;
    }

    SearchTagBuf[0] = (char)U_CMD_LIST_TAG;
    SearchTagBuf[1] = temp[0];
    SearchTagBuf[2] = temp[1];
    config_Btn = SesrchTagPD;//按键按下
    device_model->clear();
    device_model->setHorizontalHeaderItem(0,new QStandardItem(QObject::tr("TYPE")));//传感类型
    device_model->setHorizontalHeaderItem(1,new QStandardItem(QObject::tr("ID")));
    device_model->setHorizontalHeaderItem(2,new QStandardItem(QObject::tr("State")));
    device_model->setHorizontalHeaderItem(3,new QStandardItem(QObject::tr("RSSI")));
    device_model->setHorizontalHeaderItem(4,new QStandardItem(QObject::tr("DATA")));
    device_model->setHorizontalHeaderItem(5,new QStandardItem(QObject::tr("BASEID")));//边界管理器ID
    device_model->setHorizontalHeaderItem(6,new QStandardItem(QObject::tr("VER")));
    qDebug() <<"查询标签"<< SearchTagBuf.toHex();
    emit sendsignal(SearchTagBuf);
}
//查询读写器
void ConfigPage::SearchReader()
{
    QByteArray SearchReaderBuf;
    char temp[2]={0,0};
    QString SearchTimeSrc = searchTimeCombox->currentText();
    SearchTimeSrc.chop(1);//移除最后一位s
    char SearchTime = SearchTimeSrc.toInt();
    temp[0] = (SearchTime<<SEARCH_TIME_Pos)&SEARCH_TIME_Msk;
    if(lpfilterCheckBox->isChecked())
    {
        temp[0]|=LP_FILTEREN_Msk;
    }
    if(rssiCheckBox->isChecked())
    {
        temp[1] = RSSI_FILTEREN_Msk;
        QString SearchRSSISrc = rssiCombox->currentText();
        SearchRSSISrc.chop(3);//移除dbm
        char SearchRSSI = SearchRSSISrc.toInt();
        temp[1] |= (SearchRSSI&RSSI_FILTERVALUE_Msk)<<RSSI_FILTERVALUE_Pos;
    }
    else
    {
        temp[1] = 0x00;
    }

    SearchReaderBuf[0] = (char)U_CMD_LIST_READER;
    SearchReaderBuf[1] = temp[0];
    SearchReaderBuf[2] = temp[1];
    config_Btn = SesrchTagPD;//按键按下
    device_model->clear();
    device_model->setHorizontalHeaderItem(0,new QStandardItem(QObject::tr("TYPE")));//传感类型
    device_model->setHorizontalHeaderItem(1,new QStandardItem(QObject::tr("ID")));
    device_model->setHorizontalHeaderItem(2,new QStandardItem(QObject::tr("RSSI")));
    device_model->setHorizontalHeaderItem(3,new QStandardItem(QObject::tr("DATA")));
    device_model->setHorizontalHeaderItem(4,new QStandardItem(QObject::tr("VER")));
    qDebug() <<"查询读写器"<< SearchReaderBuf.toHex();
    emit sendsignal(SearchReaderBuf);
}

/****************************************************
串口通信 上位机->接收器
自动上报命令F6
信息内容
0：bit3~1 自动上报时间
   bit0：1使能低电过滤；0不使能低电过滤
1: bit7:1:使能RSSI过滤；0:不使能RSSI过滤
   bit6~0  0~127 RSSI过滤值
2：bit0: 1:打开自动上报命令，0：关闭自动上报
消息长度1字节
消息内容
******************************************************/
#define LEAVE_TIME_Msk 0xf0
#define LEAVE_TIME_Pos 4
void ConfigPage::AutoReportOpen()
{
    QByteArray AutoReportBuf;
    char temp[2]={0,0};
    //上报时间
    QString ReportTimeSrc = reportTimeCombox->currentText();
    ReportTimeSrc.chop(1);//移除最后一位s
    char ReportTime = ReportTimeSrc.toInt();
    //离开时间
    QString LeaveTimeSrc = leaveTimeCombox->currentText();
    LeaveTimeSrc.chop(1);//移除最后一位s
    char LeaveTime = LeaveTimeSrc.toInt();
    LeaveTime = (LeaveTime<<LEAVE_TIME_Pos)&LEAVE_TIME_Msk;//离开时间
    temp[0] = (ReportTime<<SEARCH_TIME_Pos)&SEARCH_TIME_Msk;//上报时间
    temp[0]|=LeaveTime;
    if(lpfilterAutoCheckBox->isChecked())
    {
        temp[0]|=LP_FILTEREN_Msk;
    }
    if(rssiAutoCheckBox->isChecked())
    {
        temp[1] = RSSI_FILTEREN_Msk;
        QString rssiAutoSrc = rssiAutoCombox->currentText();
        rssiAutoSrc.chop(3);//移除dbm
        char rssiAuto = rssiAutoSrc.toInt();
        temp[1] |= (rssiAuto&RSSI_FILTERVALUE_Msk)<<RSSI_FILTERVALUE_Pos;
    }
    else
    {
        temp[1] = 0x00;
    }

    AutoReportBuf[0] = (char)U_CMD_AUTO_REPORT;
    AutoReportBuf[1] = temp[0];
    AutoReportBuf[2] = temp[1];
    AutoReportBuf[3] = char(0x01);
    config_Btn = AutoReportPD;//按键按下
    device_model->clear();
    device_model->setHorizontalHeaderItem(0,new QStandardItem(QObject::tr("TYPE")));//传感类型
    device_model->setHorizontalHeaderItem(1,new QStandardItem(QObject::tr("ID")));
    device_model->setHorizontalHeaderItem(2,new QStandardItem(QObject::tr("State")));
    device_model->setHorizontalHeaderItem(3,new QStandardItem(QObject::tr("RSSI")));
    device_model->setHorizontalHeaderItem(4,new QStandardItem(QObject::tr("DATA")));
    device_model->setHorizontalHeaderItem(5,new QStandardItem(QObject::tr("BASEID")));//边界管理器ID
    device_model->setHorizontalHeaderItem(6,new QStandardItem(QObject::tr("VER")));
    qDebug() <<"打开自动上报"<< AutoReportBuf.toHex();
    emit sendsignal(AutoReportBuf);
}

void ConfigPage::AutoReportClose()
{
    QByteArray AutoReportBuf;
    char temp[2]={0,0};
    //上报时间
    QString ReportTimeSrc = reportTimeCombox->currentText();
    ReportTimeSrc.chop(1);//移除最后一位s
    char ReportTime = ReportTimeSrc.toInt();
    //离开时间
    QString LeaveTimeSrc = leaveTimeCombox->currentText();
    LeaveTimeSrc.chop(1);//移除最后一位s
    char LeaveTime = LeaveTimeSrc.toInt();
    LeaveTime = (LeaveTime<<LEAVE_TIME_Pos)&LEAVE_TIME_Msk;//离开时间
    temp[0] = (ReportTime<<SEARCH_TIME_Pos)&SEARCH_TIME_Msk;//上报时间
    temp[0]|=LeaveTime;
    if(lpfilterAutoCheckBox->isChecked())
    {
        temp[0]|=LP_FILTEREN_Msk;
    }
    if(rssiAutoCheckBox->isChecked())
    {
        temp[1] = RSSI_FILTEREN_Msk;
        QString rssiAutoSrc = rssiAutoCombox->currentText();
        rssiAutoSrc.chop(3);//移除dbm
        char rssiAuto = rssiAutoSrc.toInt();
        temp[1] |= (rssiAuto&RSSI_FILTERVALUE_Msk)<<RSSI_FILTERVALUE_Pos;
    }
    else
    {
        temp[1] = 0x00;
    }

    AutoReportBuf[0] = (char)U_CMD_AUTO_REPORT;
    AutoReportBuf[1] = temp[0];
    AutoReportBuf[2] = temp[1];
    AutoReportBuf[3] = char(0x00);
    config_Btn = AutoReportPD;//按键按下
    device_model->clear();
    device_model->setHorizontalHeaderItem(0,new QStandardItem(QObject::tr("TYPE")));//传感类型
    device_model->setHorizontalHeaderItem(1,new QStandardItem(QObject::tr("ID")));
    device_model->setHorizontalHeaderItem(2,new QStandardItem(QObject::tr("State")));
    device_model->setHorizontalHeaderItem(3,new QStandardItem(QObject::tr("RSSI")));
    device_model->setHorizontalHeaderItem(4,new QStandardItem(QObject::tr("DATA")));
    device_model->setHorizontalHeaderItem(5,new QStandardItem(QObject::tr("BASEID")));//边界管理器ID
    device_model->setHorizontalHeaderItem(6,new QStandardItem(QObject::tr("VER")));
    qDebug() <<"关闭自动上报"<< AutoReportBuf.toHex();
    emit sendsignal(AutoReportBuf);
}



//消息最大长度
void ConfigPage::msgMaxLength()
{
    QString textContent = messageTedt->toPlainText();
    int length = textContent.count();
    int maxLength = 64; // 最大字符数
    if(length > maxLength)
    {
        int position = messageTedt->textCursor().position();
        QTextCursor textCursor = messageTedt->textCursor();
        textContent.remove(position - (length - maxLength), length - maxLength);
        messageTedt->setText(textContent);
        textCursor.setPosition(position - (length - maxLength));
        messageTedt->setTextCursor(textCursor);
    }
}


