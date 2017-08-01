#include "dialog.h"
#include <QtWidgets>



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
    QPushButton *helpButton = new QPushButton(tr("帮助"));
    QPushButton *closeButton = new QPushButton(tr("关闭"));
    //关闭按钮事件
    connect(closeButton, &QAbstractButton::clicked, this, &QWidget::close);
    //创建页列表
    createIcons();
    contentsWidget->setCurrentRow(0);
    //创建串口类
    my_serial = new serial;
    QLabel *ReaderLabel = new QLabel("读写器ID:");
    ReaderLabel->setMinimumWidth(60);
    ReaderLabel->setMaximumWidth(60);
    ReaderIDLineEdt = new QLineEdit;
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

    //configdialog 数据更新
    connect(configpage,&ConfigPage::sendsignal,this,&Dialog::SendData);
}

Dialog::~Dialog()
{

}

void Dialog::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (!current)
        current = previous;
    pagesWidget->setCurrentIndex(contentsWidget->row(current));
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

void Dialog::SendData(QByteArray data)
{
    qDebug()<<"主界面";
    QByteArray send_data;
    if(configpage->config_Btn.settimeBtn)
    {
        configpage->config_Btn.settimeBtn = 0;
        m_packet->packet_append(&send_data,&data);
        my_serial->sendData(send_data);
        qDebug() << "时间设置";

    }
    else if(configpage->config_Btn.sendparaBtn)
    {
        configpage->config_Btn.sendparaBtn = 0;
        my_serial->sendData(data);
        qDebug() << "参数设置";
    }
}
