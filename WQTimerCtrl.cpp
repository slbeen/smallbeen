#include "WQTimerCtrl.h"
#include "ui_WQTimerCtrl.h"
#include "WTimeOffset.h"
#include <QMessageBox>
#include <QDebug>
#define cout qDebug() << "[" << __FILE__ << ":" << __LINE__ << "]"
WQTimerCtrl::WQTimerCtrl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WQTimerCtrl)
{
    ui->setupUi(this);

    initUI();
    initConnect();
}

WQTimerCtrl::~WQTimerCtrl()
{
    delete ui;
}

void WQTimerCtrl::initUI()
{
    ui->horizontalSlider->setRange(0, 24 * 60 * 60 - 1);
    ui->horizontalSlider->setValue(0);

    m_pTimer = new QTimer(this);
    m_pTimer->setInterval(1000);
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(slotTimeOut()));


    QDateTime startTime = QDateTime::currentDateTime();
    setBaseTime(startTime.addDays(-30), startTime);

    setIsEditTime(true);

    setIsGoFront(true);
}

void WQTimerCtrl::initConnect()
{
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(slotBtnClicked()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(slotBtnClicked()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(slotBtnClicked()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(slotBtnClicked()));

    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(slotBtnClicked()));

    connect(ui->dateTimeEdit, SIGNAL(editingFinished()), this, SLOT(slotEditingFinished()));
    connect(ui->dateTimeEdit_2, SIGNAL(editingFinished()), this, SLOT(slotEditingFinished()));

}

void WQTimerCtrl::setBaseTime(QDateTime startTime, QDateTime endTime)
{
    m_startTime = startTime;
    m_endTime = endTime;

    ui->dateTimeEdit->setDateTime(m_startTime);
    ui->dateTimeEdit_2->setDateTime(m_endTime);
}

void WQTimerCtrl::setIsEditTime(bool flag)
{
    ui->dateTimeEdit->setEnabled(flag);
    ui->dateTimeEdit_2->setEnabled(flag);
}

void WQTimerCtrl::setIsGoFront(bool flag)
{
    m_isGoFront = flag;
}

void WQTimerCtrl::slotBtnClicked()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    QString str = btn->text();
    if(str.compare(QStringLiteral("开始")) == 0)
    {
        btn->setText(QStringLiteral("暂停"));
        m_pTimer->start();
    }
    else if(str.compare(QStringLiteral("暂停")) == 0)
    {
        btn->setText(QStringLiteral("开始"));
        m_pTimer->stop();
    }
    else if(str.compare(QStringLiteral("结束")) == 0)
    {
        ui->pushButton->setText(QStringLiteral("开始"));
        ui->horizontalSlider->setValue(0);
        m_pTimer->stop();
        m_pTimer->setInterval(1000);
        ui->dateTimeEdit->setDateTime(m_startTime);
    }
    else if(str.compare(QStringLiteral("快进")) == 0)
    {
        QString str = ui->label_3->text();
        int n = str.right(str.size() - 1).toInt();
        n *= 2;
        if(n == 16) n = 1;
        int per = 1000;
        if(n == 2)
        {
            per = 500;
        }
        else if(n == 4)
        {
            per = 250;
        }
        else if(n == 8)
        {
            per = 125;
        }
        ui->label_3->setText(QStringLiteral("X%1").arg(QString::number(n)));
        setIsGoFront(true);
        m_pTimer->setInterval(per);
        m_pTimer->start();
        ui->pushButton->setText(QStringLiteral("暂停"));
    }
    else if(str.compare(QStringLiteral("快退")) == 0)
    {
        QString str = ui->label_4->text();
        int n = str.right(str.size() - 1).toInt();
        n *= 2;
        if(n == 16) n = 1;
        int per = 1000;
        if(n == 2)
        {
            per = 500;
        }
        else if(n == 4)
        {
            per = 250;
        }
        else if(n == 8)
        {
            per = 125;
        }
        ui->label_4->setText(QStringLiteral("X%1").arg(QString::number(n)));
        setIsGoFront(false);
        m_pTimer->setInterval(per);
        m_pTimer->start();
        ui->pushButton->setText(QStringLiteral("暂停"));
    }
    else if(str.compare(QStringLiteral("设置偏移")) == 0)
    {
        WTimeOffset wTimeOffset;
        wTimeOffset.setDateTime(ui->dateTimeEdit->dateTime());
        if(wTimeOffset.exec() == QDialog::Accepted)
        {
            QDateTime newStartTime = wTimeOffset.getStartTime();
            qint64 inewStartTime = newStartTime.toMSecsSinceEpoch();

            QDateTime oldStartTime = ui->dateTimeEdit->dateTime();
            qint64 ioldStartTime = oldStartTime.toMSecsSinceEpoch();

            qint64 itmpTime = inewStartTime - ioldStartTime;

            QDateTime oldEndTime = ui->dateTimeEdit_2->dateTime();
            cout << oldEndTime;
            qint64 ioldEndTime = oldEndTime.toMSecsSinceEpoch() ;
            qint64 inewEndTime = ioldEndTime + itmpTime;

            cout << wTimeOffset.getStartTime();
            cout << QDateTime::fromMSecsSinceEpoch(inewEndTime);
            ui->dateTimeEdit->setDateTime(wTimeOffset.getStartTime());
            ui->dateTimeEdit_2->setDateTime(QDateTime::fromMSecsSinceEpoch(inewEndTime));
        }
    }
}

void WQTimerCtrl::slotTimeOut()
{
    //改变时间进度条
    int msec = ui->horizontalSlider->value();
    ui->horizontalSlider->setValue(msec + 1);
    if(msec == ui->horizontalSlider->maximum())
    {
        ui->horizontalSlider->setValue(0);
    }
    QDateTime dateTime = ui->dateTimeEdit->dateTime();

    if(m_isGoFront)
        dateTime = dateTime.addSecs(1);
    else
        dateTime = dateTime.addSecs(-1);

    ui->dateTimeEdit->setDateTime(dateTime);
}

void WQTimerCtrl::slotEditingFinished()
{
    QDateTimeEdit* timeEdit = qobject_cast<QDateTimeEdit*>(sender());
    if(!timeEdit) return ;
    if(timeEdit == ui->dateTimeEdit)
    {
        if(timeEdit->dateTime() < m_endTime)
        {
            m_startTime = timeEdit->dateTime();
        }
        else
        {
            QMessageBox::information(this,
                                     QStringLiteral("提示"),
                                     QStringLiteral("开始时间必须小于结束时间！"),
                                     QMessageBox::Yes);

            timeEdit->setDateTime(m_startTime);
        }
    }
    else if(timeEdit == ui->dateTimeEdit_2)
    {
        if(m_startTime < timeEdit->dateTime())
        {
            m_endTime = timeEdit->dateTime();
        }
        else
        {
            QMessageBox::information(this,
                                     QStringLiteral("提示"),
                                     QStringLiteral("结束时间必须大于开始时间！"),
                                     QMessageBox::Yes);

            timeEdit->setDateTime(m_endTime);
        }
    }
}
