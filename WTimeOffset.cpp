#include "WTimeOffset.h"
#include "ui_WTimeOffset.h"

WTimeOffset::WTimeOffset(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WTimeOffset)
{
    ui->setupUi(this);
    ui->horizontalSlider->setRange(0, 24 * 60 * 60 - 1);
    setWindowTitle(QStringLiteral("设置时间偏移"));
}

WTimeOffset::~WTimeOffset()
{
    delete ui;
}

void WTimeOffset::setDateTime(QDateTime startTime)
{
    ui->dateTimeEdit->setDateTime(startTime);
    ui->dateTimeEdit_2->setDateTime(startTime);
    ui->dateEdit->setDate(startTime.date());
}

QDateTime WTimeOffset::getStartTime()
{
    return ui->dateTimeEdit_2->dateTime();
}

void WTimeOffset::on_timeEdit_editingFinished()
{
    int res = 0;
    res = (ui->timeEdit->time().hour() * 60 * 60 +
           ui->timeEdit->time().minute() * 60 +
           ui->timeEdit->time().second());

    ui->horizontalSlider->setValue(res);
}

void WTimeOffset::on_pushButton_2_clicked()
{
    accept();
}

void WTimeOffset::on_pushButton_3_clicked()
{
    reject();
}

void WTimeOffset::on_pushButton_clicked()
{
    QDateTime dateTime = ui->dateTimeEdit->dateTime();


    if(ui->checkBox->isChecked())
    {
        dateTime.setDate(ui->dateEdit->date());
    }
    qint64 iDateTime = dateTime.toMSecsSinceEpoch();

    qint64 res = (ui->timeEdit->time().hour() * 60 * 60 +
           ui->timeEdit->time().minute() * 60 +
           ui->timeEdit->time().second()) * 1000;

    iDateTime = iDateTime + res;

    ui->dateTimeEdit_2->setDateTime(QDateTime::fromMSecsSinceEpoch(iDateTime));
}

void WTimeOffset::on_horizontalSlider_valueChanged(int value)
{
    QString hour = QString::number(value / 60 / 60);
    QString minute = QString::number(value / 60 % 60);
    QString secord = QString::number(value % 60);

    ui->timeEdit->setTime(QTime::fromString(hour + minute + secord, "HHmmss"));
}
