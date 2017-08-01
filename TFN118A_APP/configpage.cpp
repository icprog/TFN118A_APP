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
     pwrCombo->addItem(tr("0dBm"));
     pwrCombo->addItem(tr("-30dBm"));
     pwrCombo->addItem(tr("-20dBm"));
     pwrCombo->addItem(tr("-16dBm"));
     pwrCombo->addItem(tr("-12dBm"));
     pwrCombo->addItem(tr("-8dBm"));
     pwrCombo->addItem(tr("-4dBm"));
     pwrCombo->addItem(tr("4dBm"));
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
     alarmCombo->addItem(tr("4s"));
     alarmCombo->addItem(tr("1s"));
     alarmCombo->addItem(tr("2s"));
     alarmCombo->addItem(tr("3s"));

     alarmCombo->addItem(tr("5s"));
     alarmCombo->addItem(tr("6s"));


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
     QTextEdit *messageTedt = new QTextEdit;
     messageTedt->setText("小朋友，你们好！");
     messageTedt->setMaximumHeight(50);
     messageTedt->setMaximumWidth(160);
     QPushButton *messageBtn = new QPushButton("发送消息");
     QGridLayout *messageLayout = new QGridLayout;
     messageLayout->addWidget(messageTedt,0,0,1,2);
     messageLayout->addWidget(messageBtn,1,0,1,2);
     messageGroup->setLayout(messageLayout);
     //文件操作
     QGroupBox *fileGroup = new QGroupBox("文件操作");
     fileGroup->setMaximumHeight(240);
     fileGroup->setMaximumWidth(180);
     //QButtonGroup无布局管理，需要layout布局管理
     QButtonGroup *WRBtnGroup = new QButtonGroup;
     readRadioBtn = new QRadioButton("读操作");
     writeRadioBtn = new QRadioButton("写操作");
     WRBtnGroup->addButton(readRadioBtn,0);
     WRBtnGroup->addButton(writeRadioBtn,1);
     WRBtnGroup->setExclusive(true);//按钮互斥

     QLabel *TargetIDLabel1 = new QLabel("目标ID:");
     TargetIDLineEdt1 = new QLineEdit;
     TargetIDLineEdt1->setMaxLength(8);

     QLabel *modeLabel = new QLabel("模式:");
     QComboBox *modeCombo = new QComboBox;
     modeCombo->addItem("参数区");
     modeCombo->addItem("保留区");
     modeCombo->addItem("用户区1");
     modeCombo->addItem("用户区2");

     QLabel *offsetLabel = new QLabel("偏移:");
     QComboBox *offsetCombo = new QComboBox;
     QStringList offsetList = (QStringList() << "0" << "1" << "2" << "3" << "4" << "5" << "6"
                               << "7" << "8" << "9" << "10" << "11" << "12" << "12" << "14"
                               << "15" << "16");
     offsetCombo->addItems(offsetList);

     QLabel *lenthLabel = new QLabel("长度:");
     QComboBox *lenthCombo = new QComboBox;
     QStringList lenthList = (QStringList() << "16" << "1" << "2" << "3" << "4" << "5" << "6"
                               << "7" << "8" << "9" << "10" << "11" << "12" << "12" << "14"
                               << "15" << "0");
     lenthCombo->addItems(lenthList);

     QLabel *dataLabel = new QLabel("数据:");
     QTextEdit *dataTedt = new QTextEdit;
     dataTedt->setText("01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16");
     dataTedt->setMaximumHeight(50);
     dataTedt->setMaximumWidth(160);

     QGridLayout *fileLayout = new QGridLayout;
     fileLayout->addWidget(readRadioBtn,0,0);
     fileLayout->addWidget(writeRadioBtn,0,1);
     fileLayout->addWidget(TargetIDLabel1, 1,0);
     fileLayout->addWidget(TargetIDLineEdt1, 1,1);
     fileLayout->addWidget(modeLabel,2,0);
     fileLayout->addWidget(modeCombo,2,1);
     fileLayout->addWidget(offsetLabel,3,0);
     fileLayout->addWidget(offsetCombo,3,1);
     fileLayout->addWidget(lenthLabel,4,0);
     fileLayout->addWidget(lenthCombo,4,1);
     fileLayout->addWidget(dataLabel,5,0);
     fileLayout->addWidget(dataTedt,6,0,1,2);
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
     QPushButton *testBtn = new QPushButton("整机测试");
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
    QStringList searchTimeList = (QStringList() << "2s" << "1s" << "3s" << "4s" << "5s" << "6s"
                              << "7s");
    searchTimeCombox->addItems(searchTimeList);

    lpfilterCombox = new QCheckBox("低电过滤");
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
    rssiCombox->setDisabled(true);

    QPushButton *searchTagBtn = new QPushButton("查询标签");
    QPushButton *searchReaderBtn = new QPushButton("查询读写器");

    QGridLayout *searchDeviceLayout = new QGridLayout;
    searchDeviceLayout->addWidget(searchDevicelabel,0,0);
    searchDeviceLayout->addWidget(searchTimeCombox,0,1);
    searchDeviceLayout->addWidget(lpfilterCombox,1,0,1,2);
    searchDeviceLayout->addWidget(rssiCheckBox,2,0);
    searchDeviceLayout->addWidget(rssiCombox,2,1);
    searchDeviceLayout->addWidget(searchTagBtn,3,0);
    searchDeviceLayout->addWidget(searchReaderBtn,3,1);

    searchDeviceGroup->setLayout(searchDeviceLayout);

    //自动上报
    QGroupBox *autoreportGroup = new QGroupBox("自动上报");
    QLabel *leaveTimeLabel = new QLabel("离开时间:");
    QComboBox *leaveTimeCombox = new QComboBox;
    QStringList leaveTimeList = (QStringList() << "3s" << "1s" << "2s" << "4s" << "5s" << "6s"
                              << "7s" << "8s" << "9s" << "10s");
    leaveTimeCombox->addItems(leaveTimeList);

    QLabel *reportTimeLabel = new QLabel("上报间隔:");
    QComboBox *reportTimeCombox = new QComboBox;
    QStringList reportTimeList = (QStringList() << "3s" << "1s" << "2s" << "4s" << "5s" << "6s"
                              << "7s");
    reportTimeCombox->addItems(reportTimeList);

    QCheckBox *lpfilterAutoCombox = new QCheckBox("低电过滤");
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
    rssiAutoCombox->setDisabled(true);
    QPushButton *AutoReportOpenBtn = new QPushButton("打开自动上报");
    QPushButton *AutoReportCloseBtn = new QPushButton("关闭自动上报");

    QGridLayout *autoreportLayout = new QGridLayout;
    autoreportLayout->addWidget(leaveTimeLabel,0,0);
    autoreportLayout->addWidget(leaveTimeCombox,0,1);
    autoreportLayout->addWidget(reportTimeLabel,2,0);
    autoreportLayout->addWidget(reportTimeCombox,2,1);
    autoreportLayout->addWidget(lpfilterAutoCombox,3,0);
    autoreportLayout->addWidget(rssiAutoCheckBox,4,0);
    autoreportLayout->addWidget(rssiAutoCombox,4,1);
    autoreportLayout->addWidget(AutoReportOpenBtn,5,0);
    autoreportLayout->addWidget(AutoReportCloseBtn,5,1);
    autoreportGroup->setLayout(autoreportLayout);


    //设备信息
    QTextEdit *infoDevice = new QTextEdit;
    QGridLayout *extensionLayout = new QGridLayout;
    extensionLayout->addWidget(searchDeviceGroup,0,0,1,1);
    extensionLayout->addWidget(autoreportGroup,0,1,1,1);
    extensionLayout->addWidget(infoDevice,1,0,1,2);


    //扩展窗口
    connect(radioBtn, &QAbstractButton::toggled, extension, &QWidget::setVisible);

    QVBoxLayout *extensionMainLayout = new QVBoxLayout;
    extensionMainLayout->setMargin(0);
    extensionMainLayout->addLayout(extensionLayout);
    extension->setLayout(extensionMainLayout);
    extension->setMaximumHeight(400);
    extension->setMaximumWidth(600);
    extension->hide();
    event_init();
    //
}

void ConfigPage::event_init()
{
    connect(getTimeBtn,&QPushButton::clicked,this,&ConfigPage::updateTime);//获取时间
    connect(setTimeBtn,&QPushButton::clicked,this,&ConfigPage::setTimebuf);//设置时间
    connect(setParaBtn,&QPushButton::clicked,this,&ConfigPage::setParaBuf);//设置参数
    connect(rssiCheckBox,&QCheckBox::clicked,rssiCombox,&QComboBox::setEnabled);//选择
}
//时间更新
void ConfigPage::updateTime()
{
    dateEdit->setDateTime(QDateTime::currentDateTime());
}
//更新时间数据
void ConfigPage::setTimebuf()
{
    QByteArray timebuff;
    timebuff.resize(10);
    QString str= dateEdit->text();
    qDebug() << str;
    timebuff = str.toLatin1();
    config_Btn.settimeBtn = 1;//按键按下
    emit sendsignal(timebuff);
}
//更新参数buff
#define TAGP_PWR_IDX 1
#define TAGP_PWR_Pos									4
#define TAGP_WORKMODE_IDX 2
#define TAGP_WORKMODE_Pos								0
#define TAGP_WORKMODE_Msk								0x0f
#define TAGP_WORKMODE_MAX_VALUE							0x01
#define TAGP_KEYALARM_IDX								4
void ConfigPage::setParaBuf()
{

    char txpower,workmode;
    QByteArray parabuff;
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
    parabuff[TAGP_KEYALARM_IDX] = tag_alarmtime.at(0).toLatin1()-0x30;
    parabuff[TAGP_PWR_IDX] = txpower;
    parabuff[TAGP_WORKMODE_IDX] =workmode;
    qDebug() << "获取参数值:" << parabuff.toHex();
    config_Btn.sendparaBtn = 1;//按k键按下
    emit sendsignal(parabuff);
}
//查询标签
void ConfigPage::listTag()
{
   //time
   QString str_search_time =  searchTimeCombox->currentText();
   str_search_time.chop(1);//移除最后一位
   char serch_time = str_search_time.toInt();
   //rssi


//   str_search_time = str_search_time
}


