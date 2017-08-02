#ifndef CONFIGPAGE_H
#define CONFIGPAGE_H

#include <QWidget>
#include <QtWidgets>

typedef enum
{
    idleBtn=0,
    settimeBtnPD=1,
    setparaBtnPD,
    WriteFileBtnPD,
    ReadFileBtnPD,
    MsgBtnPD
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
//    QByteArray databuf;

    Btn_Typedef config_Btn = idleBtn;
private:
    QPushButton *getTimeBtn;//获取时间按钮
    QPushButton *setTimeBtn;//设置时间按钮
    QPushButton *setParaBtn;//参数设置按钮
    QComboBox *pwrCombo;//参数-发射功率
    QComboBox *wModeCombo;//参数-工作模式
    QComboBox *alarmCombo;//参数-报警时间
    QLineEdit *TargetIDLineEdt;//目标ID
    QDateTimeEdit *dateEdit;
    QComboBox *searchTimeCombox;//查询时间
    QCheckBox *lpfilterCombox;//查询低电滤波
    QCheckBox *rssiCheckBox;//查询rssi滤波
    QComboBox *rssiCombox;//查询rssi值
    QCheckBox *rssiAutoCheckBox;//rssi
    QComboBox *rssiAutoCombox;//rssi
    //消息
    QTextEdit *messageTedt;//消息内容
    QPushButton *messageBtn;//消息下发按钮
    //文件操作
    QRadioButton *readRadioBtn;//读操作
    QRadioButton *writeRadioBtn;//写操作
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

signals:
    void sendsignal(QByteArray);
public slots:
    void updateTime();
    void setTimebuf();//更新时间BUFF
    void setParaBuf();//更新参数buff
    void listTag();
    void WriteReadFile();//写文件操作
    void msgMaxLength();
    void msgSend();//消息下发

};

#endif // CONFIGPAGE_H
