#ifndef CONFIGPAGE_H
#define CONFIGPAGE_H

#include <QWidget>
#include <QtWidgets>
typedef struct
{
    uint8_t settimeBtn;
    uint8_t sendparaBtn;
}config_Btn_Typedef;
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
    config_Btn_Typedef config_Btn;
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
    //文件操作
    QRadioButton *readRadioBtn;//读操作
    QRadioButton *writeRadioBtn;//写操作
    QLineEdit *TargetIDLineEdt1;//目标ID1
    QCheckBox *readCheckBox = new QCheckBox("读操作");
    QCheckBox *writeCheckBox = new QCheckBox("写操作");
    void updateTime();
    void setTimebuf();//更新时间BUFF
    void setParaBuf();//更新参数buff
    void listTag();
signals:
    void sendsignal(QByteArray);
public slots:
};

#endif // CONFIGPAGE_H
