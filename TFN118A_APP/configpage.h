#ifndef CONFIGPAGE_H
#define CONFIGPAGE_H

#include <QWidget>
#include <QtWidgets>
#include "packet.h"
typedef enum
{
    idleBtn=0,
    settimeBtnPD=1,
    setparaBtnPD,
    WriteFileBtnPD,
    ReadFileBtnPD,
    EraseFileBtnPD,
    MsgBtnPD,
    SesrchTagPD,
    AutoReportPD,
    DeviceTestPD
}Btn_Typedef;

class ConfigPage : public QWidget
{
    Q_OBJECT
public:
    explicit ConfigPage(QWidget *parent = 0);
    QWidget *extension;
    QPushButton *radioBtn;
    void createExtension();
    void event_init();
    void ShowReadFileData(QByteArray Data_Src);//显示读取的数据
    void ClearReadFileData();//清空数据
    QTableView *infoDevice;//设备信息
    QStandardItemModel *device_model;
//    QByteArray databuf;

    Btn_Typedef config_Btn = idleBtn;
private:
    QPushButton *getTimeBtn;//获取时间按钮
    QPushButton *setTimeBtn;//设置时间按钮
    QPushButton *setParaBtn;//参数设置按钮
    QComboBox *pwrCombo;//参数-发射功率
    QComboBox *wModeCombo;//参数-工作模式
    QComboBox *P_SendPeriodCombo;//参数-发射周期
    QComboBox *alarmCombo;//参数-报警时间
    QComboBox *P_EventClearMothodCombo;//参数-事件清除方式
    QComboBox *P_BaseRssiThrCombo;//参数-低频激活信号强度门限
    QLineEdit *P_SensorParaLineEdt;//参数-传感参数
    QLineEdit *TargetIDLineEdt;//目标ID

    QDateTimeEdit *dateEdit;
    //消息
    QTextEdit *messageTedt;//消息内容
    QPushButton *messageBtn;//消息下发按钮
    QRadioButton *msgTypeCalRadioBtn;//日历消息
    QRadioButton *msgTypeNewsRadioBtn;//文字消息
    QRadioButton *msgAllRadioBtn;//群发
    QRadioButton *msgDestRadioBtn;//指定发送
    MSG_Store_Typedef MSG_Store;//消息序号
    //文件操作
    QRadioButton *readRadioBtn;//读操作
    QRadioButton *writeRadioBtn;//写操作
    QRadioButton *eraseRadioBtn;//擦除
    QLineEdit *TargetIDLineEdt1;//目标ID1
    QCheckBox *readCheckBox = new QCheckBox("读操作");
    QCheckBox *writeCheckBox = new QCheckBox("写操作");
    QComboBox *OverTime;//命令超时时间
    QComboBox *modeCombo;//操作区选择，参数区->保留区->用户区1、2
    QComboBox *offsetCombo;//偏移
    QComboBox *lenthCombo;//长度
    QTextEdit *dataTedt;//数据内容
    QPushButton *WRFileBtn;//文件操作按钮
    QByteArray U2GBK(QString unic);//unicode->gbk
    QByteArray QString2Unicode(QString src);//string->unicode
    QPushButton *testBtn;//整机测试
    //扩展窗口-射频处理
    QPushButton *searchTagBtn;//查询标签
    QPushButton *searchReaderBtn;//查询读写器
    QComboBox *searchTimeCombox;//查询时间
    QCheckBox *lpfilterCheckBox;//查询低电滤波
    QCheckBox *rssiCheckBox;//查询rssi滤波
    QComboBox *rssiCombox;//查询rssi值

    //自动上报
    QPushButton *AutoReportOpenBtn;
    QPushButton *AutoReportCloseBtn;
    QComboBox *reportTimeCombox;//上报时间
    QComboBox *leaveTimeCombox;//离开时间
    QCheckBox *rssiAutoCheckBox;//rssi
    QComboBox *rssiAutoCombox;//rssi
    QCheckBox *lpfilterAutoCheckBox;//低电过滤
signals:
    void sendsignal(QByteArray);
    void sendMsgBox(QString);
public slots:
    void updateTime();
    void setTimebuf();//更新时间BUFF
    void setParaBuf();//更新参数buff
    void WriteReadFile();//写文件操作
    void msgMaxLength();
    void msgSend();//消息下发
    void SearchTag();//查询标签
    void SearchReader();//查询读写器
    void AutoReportOpen();
    void AutoReportClose();
    void DeviceTest();//整机测试
};

#endif // CONFIGPAGE_H
