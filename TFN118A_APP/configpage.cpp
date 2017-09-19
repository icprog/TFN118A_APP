#include "configpage.h"

#define MaxWidth   190
ConfigPage::ConfigPage(QWidget *parent) : QWidget(parent)
{
     //时间
//     QGroupBox *timeGroup = new QGroupBox("时间");
//     timeGroup->setMaximumHeight(100);
//     timeGroup->setMaximumWidth(MaxWidth);
//     getTimeBtn = new QPushButton("获取时间");
//     setTimeBtn = new QPushButton("时间设置");

//    QDialogButtonBox *dlgBtnBox = new QDialogButtonBox(Qt::Horizontal);
//    dlgBtnBox->addButton(getTimeBtn, QDialogButtonBox::ActionRole);
//    dlgBtnBox->addButton(setTimeBtn, QDialogButtonBox::ActionRole);
//    dateEdit = new QDateTimeEdit(QDateTime::currentDateTime());
//    dateEdit->setDisplayFormat("yyyy/MM/dd  HH:mm:ss");


//    QGridLayout *timeLayout = new QGridLayout;
//    timeLayout->addWidget(getTimeBtn,0,0,1,1);
//    timeLayout->addWidget(setTimeBtn,0,1,1,1);
////     timeLayout->addWidget(dlgBtnBox, 0, 0,1,2);
//    timeLayout->addWidget(dateEdit, 1,0,1,2);
//    timeGroup->setLayout(timeLayout);

     //参数
    QGroupBox *paraGroup = new QGroupBox("腕带参数");
    paraGroup->setMaximumHeight(280);
    paraGroup->setMaximumWidth(MaxWidth);
    QLabel *TargetIDLabel = new QLabel("目标ID:");
    TargetIDLineEdt = new QLineEdit;
    TargetIDLineEdt->setMaxLength(TagID_LEN*2);


//     QLabel *pwrUnitLabel = new QLabel("dBm");

    //工作模式
    QLabel *wModeLabel = new QLabel("工作模式:");
    wModeCombo = new QComboBox;
    wModeCombo->addItem("单激活发射");
    wModeCombo->addItem("自主发射");
    wModeCombo->addItem("自适应单激活发射");
    wModeCombo->addItem("自适应自主发射");
    wModeCombo->addItem("保存模式");
    wModeCombo->setCurrentIndex(1);
    //自动上报发射周期
    QLabel *SendPeriodLabel = new QLabel("发射周期:");
    P_SendPeriodCombo = new QComboBox;
    P_SendPeriodCombo->addItem(tr("250ms"));
    P_SendPeriodCombo->addItem(tr("500ms"));
    P_SendPeriodCombo->addItem(tr("1s"));
    P_SendPeriodCombo->addItem(tr("2s"));
    P_SendPeriodCombo->addItem(tr("4s"));
    P_SendPeriodCombo->addItem(tr("8s"));
    P_SendPeriodCombo->addItem(tr("16s"));
    P_SendPeriodCombo->addItem(tr("32s"));
    P_SendPeriodCombo->setCurrentIndex(2);

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
    QLabel *EventClearMothodLabel = new QLabel("事件清除:");
    P_EventClearMothodCombo = new QComboBox;
    P_EventClearMothodCombo->addItem("标签自动撤销");
    P_EventClearMothodCombo->addItem("读写器清除");
    P_EventClearMothodCombo->setCurrentIndex(1);
    //低频激励信号强度门限
    QLabel *BaseRssiThrLabel = new QLabel("低频过滤:");
    P_BaseRssiThrCombo = new QComboBox;
    QStringList BRTList;
    for(uint8_t i = 0; i<= 32 ;i++)
    {
        QString BRTStr = QString::number(i);
        BRTStr += "dbm";
        BRTList << BRTStr;
    }
    P_BaseRssiThrCombo->addItems(BRTList);
    P_BaseRssiThrCombo->setCurrentIndex(32);
    //传感器参数，自己填
    QLabel *SensorDataLabel = new QLabel("传感参数:");
    P_SensorParaLineEdt = new QLineEdit;
    P_SensorParaLineEdt->setAlignment(Qt::AlignRight);
    P_SensorParaLineEdt->setText("04");
    //报警时间
//     QLabel *alarmLabel = new QLabel("报警时间:");
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
    paraLayout->addWidget(wModeLabel, 1, 0);
    paraLayout->addWidget(wModeCombo, 1,1);
    paraLayout->addWidget(SendPeriodLabel, 2, 0);
    paraLayout->addWidget(P_SendPeriodCombo, 2,1);
    paraLayout->addWidget(pwrLabel, 3,0);
    paraLayout->addWidget(pwrCombo, 3,1);
    paraLayout->addWidget(EventClearMothodLabel, 4,0);
    paraLayout->addWidget(P_EventClearMothodCombo, 4,1);
    paraLayout->addWidget(BaseRssiThrLabel, 5,0);
    paraLayout->addWidget(P_BaseRssiThrCombo, 5,1);
    paraLayout->addWidget(SensorDataLabel, 6,0);
    paraLayout->addWidget(P_SensorParaLineEdt, 6,1);
    paraLayout->addWidget(setParaBtn,7,0,1,2);
//     paraLayout->setHorizontalSpacing(10);
    paraGroup->setLayout(paraLayout);

    //消息
    QGroupBox *messageGroup = new QGroupBox("消息");
    messageGroup->setMaximumHeight(300);
    messageGroup->setMaximumWidth(MaxWidth);
    QLabel *msgTypeLabel = new QLabel("类别:");
    QButtonGroup *msgTypeBtnGroup = new QButtonGroup;
    msgTypeCalRadioBtn = new QRadioButton("时间");
    msgTypeNewsRadioBtn = new QRadioButton("通知");
    msgTypeCalRadioBtn->setChecked(1);
    msgTypeBtnGroup->addButton(msgTypeCalRadioBtn,0);
    msgTypeBtnGroup->addButton(msgTypeNewsRadioBtn,1);
    msgTypeBtnGroup->setExclusive(true);//按钮互斥

    QLabel *msgDestLabel = new QLabel("方式:");
    QButtonGroup *msgBtnGroup = new QButtonGroup;
    msgAllRadioBtn = new QRadioButton("群发");
    msgDestRadioBtn = new QRadioButton("指定发送");
    msgAllRadioBtn->setChecked(1);//群发
    msgBtnGroup->addButton(msgAllRadioBtn,0);
    msgBtnGroup->addButton(msgDestRadioBtn,1);
    msgBtnGroup->setExclusive(true);//按钮互斥

    QGridLayout *msgtopLayout = new QGridLayout;
    msgtopLayout->addWidget(msgTypeLabel,0,0,1,1);//消息类别
    msgtopLayout->addWidget(msgTypeCalRadioBtn,0,1,1,1);//时间
    msgtopLayout->addWidget(msgTypeNewsRadioBtn,0,2,1,1);//通知
    msgtopLayout->addWidget(msgDestLabel,1,0,1,1);//消息方式
    msgtopLayout->addWidget(msgAllRadioBtn,1,1,1,1);//群发
    msgtopLayout->addWidget(msgDestRadioBtn,1,2,1,1);//指定发送
    msgtopLayout->setSpacing(5);
    messageTedt = new QTextEdit;
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB18030"));
    messageTedt->setText("小朋友，你们好！");
    messageTedt->setMaximumHeight(50);
    messageTedt->setMaximumWidth(MaxWidth);
    QGroupBox *msgGroup = new QGroupBox("时间");
    msgGroup->setMaximumHeight(100);
    msgGroup->setMaximumWidth(MaxWidth);
    getTimeBtn = new QPushButton("获取时间");
    setTimeBtn = new QPushButton("时间设置");
    messageBtn = new QPushButton("通知");
    QDialogButtonBox *dlgBtnBox = new QDialogButtonBox(Qt::Horizontal);
    dlgBtnBox->addButton(getTimeBtn, QDialogButtonBox::ActionRole);
    dlgBtnBox->addButton(setTimeBtn, QDialogButtonBox::ActionRole);
    dlgBtnBox->addButton(messageBtn,QDialogButtonBox::ActionRole);
    dateEdit = new QDateTimeEdit(QDateTime::currentDateTime());
    dateEdit->setDisplayFormat("yyyy/MM/dd  HH:mm:ss");

    QGridLayout *messageLayout = new QGridLayout;
    messageLayout->addLayout(msgtopLayout,0,0,2,3);
    messageLayout->addWidget(dateEdit,2,0,1,3);//时间窗口
    messageLayout->addWidget(messageTedt,3,0,1,3);
    messageLayout->addWidget(getTimeBtn,4,0,1,1);
    messageLayout->addWidget(setTimeBtn,4,1,1,1);
    messageLayout->addWidget(messageBtn,4,2,1,1);
    messageGroup->setLayout(messageLayout);
    //文件操作
    QGroupBox *fileGroup = new QGroupBox("文件操作");
    fileGroup->setMaximumHeight(300);
    fileGroup->setMaximumWidth(MaxWidth);
    //QButtonGroup无布局管理，需要layout布局管理
    QButtonGroup *WRBtnGroup = new QButtonGroup;
    readRadioBtn = new QRadioButton("读操作");
    writeRadioBtn = new QRadioButton("写操作");
    eraseRadioBtn = new QRadioButton("擦除");
    WRBtnGroup->addButton(readRadioBtn,0);
    WRBtnGroup->addButton(writeRadioBtn,1);
    WRBtnGroup->addButton(eraseRadioBtn,2);
    WRBtnGroup->setExclusive(true);//按钮互斥
    readRadioBtn->setChecked(1);
    QLabel* TargetIDLabel1 = new QLabel("目标ID:");

    TargetIDLineEdt1 = new QLineEdit;
    TargetIDLineEdt1->setMaxLength(TagID_LEN*2);

    QLabel *modeLabel = new QLabel("模式:");

    QLabel *OTLabel = new QLabel("命令超时:");//超时时间
    OverTime = new QComboBox();
    OverTime->addItem("无超时");
    QStringList OTList;
    for(uint8_t i = 1; i< 13 ;i++)
    {

     QString OTStr = QString::number(i);
     OTStr += "s";
     OTList << OTStr;
    }
    OverTime->addItems(OTList);
    OverTime->setCurrentIndex(11);

    modeCombo = new QComboBox;
    modeCombo->addItem("参数区");
    modeCombo->addItem("保留区");
    modeCombo->addItem("用户区1");
    modeCombo->addItem("用户区2");
    modeCombo->addItem("运行参数区");

    QLabel *offsetLabel = new QLabel("偏移:");
    offsetCombo = new QComboBox;
    offsetCombo->addItem("最新记录");
    offsetCombo->addItem("最新记录不擦除");
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
    dataTedt->setText("04 02 06 01 20 04 00 00 00 00 00 00 00 00 00 00");
    dataTedt->setMaximumHeight(40);
    dataTedt->setMaximumWidth(160);

    WRFileBtn = new QPushButton("文件操作");

    QGridLayout *fileLayout = new QGridLayout;
    fileLayout->addWidget(readRadioBtn,0,0);
    fileLayout->addWidget(writeRadioBtn,0,1);
    fileLayout->addWidget(eraseRadioBtn,1,0);
    fileLayout->addWidget(TargetIDLabel1, 2,0);
    fileLayout->addWidget(TargetIDLineEdt1, 2,1);
    fileLayout->addWidget(OTLabel,3,0);
    fileLayout->addWidget(OverTime,3,1);
    fileLayout->addWidget(modeLabel,4,0);
    fileLayout->addWidget(modeCombo,4,1);
    fileLayout->addWidget(offsetLabel,5,0);
    fileLayout->addWidget(offsetCombo,5,1);
    fileLayout->addWidget(lenthLabel,6,0);
    fileLayout->addWidget(lenthCombo,6,1);
    fileLayout->addWidget(dataLabel,7,0);
    fileLayout->addWidget(dataTedt,8,0,1,2);
    fileLayout->addWidget(WRFileBtn,9,0,1,2);
    fileGroup->setLayout(fileLayout);

    //射频测试
    QGroupBox *radioGroup = new QGroupBox("射频性能");
    radioGroup->setMaximumHeight(70);
    radioGroup->setMaximumWidth(MaxWidth);
    radioBtn = new QPushButton("射频性能测试");
    QGridLayout *radioLayout = new QGridLayout;
    radioLayout->addWidget(radioBtn,0,0,1,2);
    radioGroup->setLayout(radioLayout);
    radioBtn->setCheckable(true);
    radioBtn->setAutoDefault(false);
     //扩展窗口放在主界面
//     createExtension();


    //整机测试
    testBtn = new QPushButton("整机测试");
//     QLabel *stateLable = new QLabel("执行成功");
//     stateLable->setAlignment(Qt::AlignBottom | Qt::AlignLeft);
//     stateLable->setFrameStyle(QFrame::Panel | QFrame::Sunken);
//     QHBoxLayout *bottomLayout = new QHBoxLayout;
//     bottomLayout->addWidget(testBtn);
//     bottomLayout->addWidget(stateLable);

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addWidget(paraGroup);
    leftLayout->addWidget(messageGroup);
//    leftLayout->addWidget(timeGroup);
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
    device_model->setHorizontalHeaderItem(4,new QStandardItem(QObject::tr("数据")));//传感值
    device_model->setHorizontalHeaderItem(5,new QStandardItem(QObject::tr("门口边界")));//边界管理器ID
    device_model->setHorizontalHeaderItem(6,new QStandardItem(QObject::tr("普通边界")));//边界管理器ID
    device_model->setHorizontalHeaderItem(7,new QStandardItem(QObject::tr("版本")));
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



//更新参数buff
#if 0
#define TAGP_PWR_IDX                                    1
#define TAGP_PWR_Pos									4
#define TAGP_WORKMODE_IDX                               2
#define TAGP_WORKMODE_Pos								0
#define TAGP_WORKMODE_Msk								0x0f
#define TAGP_WORKMODE_MAX_VALUE							0x01
#define TAGP_KEYALARM_IDX								4
#endif
#define OVER_TIME                                       11//11S
/****************************************************
串口通信 上位机->接收器 命令F0
参数设置信息内容
目标ID：XXXXXXXX 5字节
超时时间:0~9  0：无超时时间  单位s
保留：00
写参数区：01
写最新参数:FF
写长度：10
数据内容：16字节
******************************************************/
void ConfigPage::setParaBuf()
{

    //参数buff
    QByteArray parabuff;
    QByteArray sendparabuff;
    QString DestIDSrc;
    DestIDSrc  = TargetIDLineEdt->text();
    if(DestIDSrc.length()<(TagID_LEN*2))
    {
        emit sendMsgBox("腕带参数框填写正确的目标ID");
        return;
    }
    else
    {
        //工作模式
        char workmode =0x00;
        QString workmodeStr = wModeCombo->currentText();
        if("单激活发射" == workmodeStr)
            workmode = 0x00;
        else if("自主发射" == workmodeStr)
            workmode = 0x04;
        else if("自适应单激活发射" == workmodeStr)
            workmode = 0x02;
        else if("自适应自主发射" == workmodeStr)
            workmode = 0x06;
        else if("保存模式" == workmodeStr)
            workmode = 0x01;
//        else
//            workmode = 0x04;

        //发送周期
        char sendperiod = 0x00;
        QString sendperiodStr = P_SendPeriodCombo->currentText();
        if("125ms" == sendperiodStr)
            sendperiod = 0x00;
        else if("500ms" == sendperiodStr)
            sendperiod = 0x01;
        else if("1s" == sendperiodStr)
            sendperiod = 0x02;
        else if("2s" == sendperiodStr)
            sendperiod = 0x03;
        else if("4s" == sendperiodStr)
            sendperiod = 0x04;
        else if("8s" == sendperiodStr)
            sendperiod = 0x05;
        else if("16s" == sendperiodStr)
            sendperiod = 0x06;
        else if("32s" == sendperiodStr)
            sendperiod = 0x07;
//        else
//            sendperiod = 0x02;


        //发射功率
        char txpower=0x00;
        QString txpowerStr = pwrCombo->currentText();
        if("-30dBm" == txpowerStr)
            txpower = 0x00;
        else if("-20dBm" == txpowerStr )
            txpower = 0x01;
        else if("-16dBm" == txpowerStr)
            txpower = 0x02;
        else if("-12dBm" == txpowerStr)
            txpower = 0x03;
        else if("-8dBm" == txpowerStr)
            txpower = 0x04;
        else if("-4dBm" == txpowerStr)
            txpower = 0x05;
        else if("0dBm" == txpowerStr)
            txpower = 0x06;
        else if("4dBm" == txpowerStr)
            txpower = 0x07;
//        else
//            txpower = 0x06;

        //事件清除
        char EventClearMothod=0x00;
        QString EventClearMothodStr = P_EventClearMothodCombo->currentText();
        if("标签自动撤销" == EventClearMothodStr)
            EventClearMothod = 0x00;
        else if("读写器清除" == EventClearMothodStr)
            EventClearMothod = 0x01;
        //低频信号门限
        char BaseRssiThr;
        QString BaseRssiThrStr = P_BaseRssiThrCombo->currentText();
        BaseRssiThrStr.remove("dbm");//去掉单位dbm
            BaseRssiThr = BaseRssiThrStr.toInt();
        //传感参数
        char SensorPara;
        QString SensorParaStr = P_SensorParaLineEdt->text();
        SensorPara = SensorParaStr.toInt();
        for(int i = 0; i<16;i++)
        {
            parabuff[i] = 0x00;
        }
        parabuff[0] = workmode;
        parabuff[1] = sendperiod;
        parabuff[2] = txpower;
        parabuff[3] = EventClearMothod;
        parabuff[4] = BaseRssiThr;
        parabuff[5] = SensorPara;
        QByteArray DestIDDest = QByteArray::fromHex(DestIDSrc.toLatin1());//目标ID
        sendparabuff += U_CMD_PARA_SET;//命令字
        sendparabuff += DestIDDest;//目标ID
        sendparabuff += OVER_TIME;//超时时间
        sendparabuff += (char)U_FILE_RESERVER;//保留
        sendparabuff += U_FILE_MODE_PARA;//内部参数区
        sendparabuff += (char)U_FILE_OFFSET_RNEW;//写最新参数
        sendparabuff += (char)0x10;//长度
        sendparabuff += parabuff;//参数
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
保留：00
区选择：00~04
写最新参数:FF
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
    if(false == readRadioBtn->isChecked()&& false == writeRadioBtn->isChecked()
            && false == eraseRadioBtn->isChecked())
    {
        emit sendMsgBox("请选择操作方式");
        return;
    }
    if(DestIDSrc1.length()<(TagID_LEN*2))
    {
        emit sendMsgBox("腕带参数框填写正确的目标ID");
        return;
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
            OverTimeSrc.remove("s");//去掉单位s
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
        else if("运行参数区")
        {
            AreaDest = U_FILE_MODE_RUNPARA;
        }
        //长度
        char LenthDest;
        QString LenthSrc = lenthCombo->currentText();
        LenthDest = LenthSrc.toInt();
        //目标ID
        QByteArray DestIDDest1 = QByteArray::fromHex(DestIDSrc1.toLatin1());//目标ID
        //写命令
        if(writeRadioBtn->isChecked())//写操作
        {
            QByteArray WriteBuff;            
            WriteBuff+=U_CMD_WRITE_FILE;//命令
            WriteBuff+=DestIDDest1;//目标ID
            WriteBuff+=OverTimeDest;//超时时间
            WriteBuff+=(char)U_FILE_RESERVER;//保留
            WriteBuff+=AreaDest;//操作区
            //偏移
            QString OffsetSrc =offsetCombo->currentText();
            if("最新记录" == OffsetSrc)
            {
                WriteBuff+=(char)U_FILE_OFFSET_WNEW_ERASE;//写最新参数，擦除
            }
            else if("最新记录不擦除" == OffsetSrc)
            {
                WriteBuff+=(char)U_FILE_OFFSET_WNEW_NOERASE;//写最新参数
            }
            else
            {
                emit sendMsgBox("写偏移错误");
                return;
            }
            WriteBuff+=LenthDest;//长度
            QByteArray DataDes;
            for(int i = 0; i<LenthDest;i++)
                DataDes[i] = 0xff;
            QString DataSrc = dataTedt->toPlainText();
            if(DataSrc.length() >0)
            {
                DataDes = QByteArray::fromHex(DataSrc.toLatin1());
            }
            WriteBuff.append(DataDes,(int)LenthDest);
            qDebug() << WriteBuff.toHex();
            config_Btn = WriteFileBtnPD;//按键按下
            emit sendsignal(WriteBuff);
        }
        else if(readRadioBtn->isChecked())//读操作
        {
            QByteArray ReadBuff;
            ReadBuff+=U_CMD_READ_FILE;//命令
            ReadBuff+=DestIDDest1;//目标ID
            ReadBuff+=OverTimeDest;//超时时间
            ReadBuff+=(char)U_FILE_RESERVER;//保留
            ReadBuff+=AreaDest;//操作区
            //偏移
            QString OffsetSrc =offsetCombo->currentText();
            if("最新记录" == OffsetSrc)
            {
                ReadBuff+=(char)U_FILE_OFFSET_RNEW;//写最新参数
            }
            else
            {
                char OffsetDest = OffsetSrc.toInt();
                ReadBuff+=OffsetDest;
            }
            ReadBuff+=LenthDest;//长度
            qDebug() << ReadBuff.toHex();
            config_Btn = ReadFileBtnPD;//按键按下
            emit sendsignal(ReadBuff);
        }
        else if(eraseRadioBtn->isChecked())//擦除
        {
            QByteArray EraseBuff;
            EraseBuff+=U_CMD_ERASE_FILE;//命令
            EraseBuff+=DestIDDest1;//目标ID
            EraseBuff+=OverTimeDest;//超时时间
            EraseBuff+=(char)U_FILE_RESERVER;//保留
            EraseBuff+=AreaDest;//操作区
            EraseBuff+=(char)0x00;//保留
            EraseBuff+=(char)0x00;//保留
            qDebug() << EraseBuff.toHex();
            config_Btn = EraseFileBtnPD;//按键按下
            emit sendsignal(EraseBuff);
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

//时间更新
void ConfigPage::updateTime()
{
    dateEdit->setDateTime(QDateTime::currentDateTime());
}
//更新时间数据
/****************************************************
串口通信 上位机->接收器 命令字89
时间设置信息内容
0~4:目标ID
(1)、当ID为0xFFFFFFFFFF群发
(2)、当ID为指定设备ID时，1对1发送
5:消息分类
bit7~4:0-日历 1-通知
bit3~0:消息编号，每发布一次消息，编号加加，饱和卷绕
6:消息长度
7~12:
年月日时分秒：6字节 2017-08-01 14：40：30-> 17 08 01 14 40 30
******************************************************/
void ConfigPage::setTimebuf()
{
    QByteArray msgbuff;
    QByteArray timebuff;
    QString datasrc;
    uint8_t msg_info;
    msgbuff+=U_CMD_MSG_PUSH;//命令
    if(false == msgAllRadioBtn->isChecked()&& false == msgDestRadioBtn->isChecked())
    {
        emit sendMsgBox("请选择消息方式");
        return;
    }
    if(false == msgTypeCalRadioBtn->isChecked())
    {
        emit sendMsgBox("请选择消息类别为时间");
        return;
    }
    if(msgAllRadioBtn->isChecked())//群发
    {
        msgbuff+=QByteArray::fromHex(MSG_DESTID_ALL);//目标ID
    }
    else
    {
        if(TargetIDLineEdt->text().length() < (TagID_LEN*2))
        {
            emit sendMsgBox("腕带参数框填写正确的目标ID");
            return;
        }
        QString DestIDSrc = TargetIDLineEdt->text();
        QByteArray DestIDDest = QByteArray::fromHex(DestIDSrc.toLatin1());//目标ID
        msgbuff+= DestIDDest;
    }
    msg_info = (msg_calendar<<U_MSG_TYPE_Pos)&U_MSG_TYPE_Msk;//消息分类
    MSG_Store.MSG2_Seq++;//消息序号
    if(MSG_Store.MSG2_Seq > U_MSG_SEQ_MAX)
        MSG_Store.MSG2_Seq = 1;
    msg_info |= (MSG_Store.MSG2_Seq<<U_MSG_SEQ_Pos)&U_MSG_SEQ_Msk;//消息序号
    //时间内容
    datasrc = dateEdit->text();
    timebuff = QByteArray::fromHex(datasrc.toLatin1());
    timebuff.remove(0,1);
    msgbuff+=msg_info;//消息分类、消息编号
    msgbuff+=MSG2_FIX_LEN;//长度，固定6
    msgbuff+=timebuff;//时间
    config_Btn = settimeBtnPD;//按键按下
    emit sendsignal(msgbuff);
}
/****************************************************
串口通信 上位机->接收器
消息命令89
信息内容
0~4:目标ID
(1)、当ID为0xFFFFFFFFFF群发
(2)、当ID为指定设备ID时，1对1发送
5:消息分类
bit7~4:0-日历 1-通知
bit3~0:消息编号，每发布一次消息，编号加加，饱和卷绕
6:消息长度
7~x:消息内容
******************************************************/
#define GBK 1
void ConfigPage::msgSend()
{
    QByteArray MsgBuff;//消息缓存
    uint8_t msg_info;
    QString MsgSrc = messageTedt->toPlainText();
#if GBK
    QByteArray MsgDest = this->U2GBK(MsgSrc);
#else
    QByteArray MsgDest = this->QString2Unicode(MsgSrc);
#endif
    if(false == msgAllRadioBtn->isChecked()&& false == msgDestRadioBtn->isChecked())
    {
        emit sendMsgBox("请选择消息方式");
        return;
    }
    if(false == msgTypeNewsRadioBtn->isChecked())
    {
        emit sendMsgBox("请选择消息类别为通知");
        return;
    }
    MsgBuff+=U_CMD_MSG_PUSH;//消息命令
    if(msgAllRadioBtn->isChecked())//群发
    {
        MsgBuff+=QByteArray::fromHex(MSG_DESTID_ALL);//目标ID
    }
    else
    {
        if(TargetIDLineEdt->text().length() < (TagID_LEN*2))
        {
            emit sendMsgBox("腕带参数框填写正确的目标ID");
            return;
        }
        QString DestIDSrc = TargetIDLineEdt->text();
        QByteArray DestIDDest = QByteArray::fromHex(DestIDSrc.toLatin1());//目标ID
        MsgBuff+= DestIDDest;
    }
    msg_info = (msg_news<<U_MSG_TYPE_Pos)&U_MSG_TYPE_Msk;//消息分类
    MSG_Store.MSG1_Seq++;//消息序号
    if(MSG_Store.MSG1_Seq > U_MSG_SEQ_MAX)
        MSG_Store.MSG1_Seq = 1;
    msg_info |= (MSG_Store.MSG1_Seq<<U_MSG_SEQ_Pos)&U_MSG_SEQ_Msk;//消息序号
    MsgBuff+=msg_info;//消息分类、消息序号
    char MsgLen = MsgDest.length();
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
    if(DestIDSrc.length()<(TagID_LEN*2))
    {
        emit sendMsgBox("腕带参数框填写正确的目标ID");
        return;
    }
    else
    {
        QByteArray DeviceTestBuf;
        DeviceTestBuf += (char)U_CMD_DEVICE_TEST;
        QByteArray DestIDDec = QByteArray::fromHex(DestIDSrc.toLatin1());//目标ID
        DeviceTestBuf+=DestIDDec;
        DeviceTestBuf+= (char)0x00;
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
    device_model->setHorizontalHeaderItem(4,new QStandardItem(QObject::tr("数据")));//传感值
    device_model->setHorizontalHeaderItem(5,new QStandardItem(QObject::tr("门口边界")));//边界管理器ID
    device_model->setHorizontalHeaderItem(6,new QStandardItem(QObject::tr("普通边界")));//边界管理器ID
    device_model->setHorizontalHeaderItem(7,new QStandardItem(QObject::tr("版本")));
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
    device_model->setHorizontalHeaderItem(2,new QStandardItem(QObject::tr("State")));
    device_model->setHorizontalHeaderItem(3,new QStandardItem(QObject::tr("RSSI")));
    device_model->setHorizontalHeaderItem(4,new QStandardItem(QObject::tr("数据")));//传感值
    device_model->setHorizontalHeaderItem(5,new QStandardItem(QObject::tr("门口边界")));//边界管理器ID
    device_model->setHorizontalHeaderItem(6,new QStandardItem(QObject::tr("普通边界")));//边界管理器ID
    device_model->setHorizontalHeaderItem(7,new QStandardItem(QObject::tr("版本")));
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
    device_model->setHorizontalHeaderItem(4,new QStandardItem(QObject::tr("数据")));//传感值
    device_model->setHorizontalHeaderItem(5,new QStandardItem(QObject::tr("门口边界")));//边界管理器ID
    device_model->setHorizontalHeaderItem(6,new QStandardItem(QObject::tr("普通边界")));//边界管理器ID
    device_model->setHorizontalHeaderItem(7,new QStandardItem(QObject::tr("版本")));
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
    device_model->setHorizontalHeaderItem(4,new QStandardItem(QObject::tr("数据")));//传感值
    device_model->setHorizontalHeaderItem(5,new QStandardItem(QObject::tr("门口边界")));//边界管理器ID
    device_model->setHorizontalHeaderItem(6,new QStandardItem(QObject::tr("普通边界")));//边界管理器ID
    device_model->setHorizontalHeaderItem(7,new QStandardItem(QObject::tr("版本")));
    qDebug() <<"关闭自动上报"<< AutoReportBuf.toHex();
    emit sendsignal(AutoReportBuf);
}



//消息最大长度
void ConfigPage::msgMaxLength()
{
    QString textContent = messageTedt->toPlainText();
    int length = textContent.count();
    int maxLength = 110; // 最大字符数
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


