#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>
#define cout qDebug() << "[" << __FILE__ << ":" << __LINE__ << "]"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(QStringLiteral("时间控制器"));


    m_WQTimerCtrl = new WQTimerCtrl(this);

    ui->verticalLayout->addWidget(m_WQTimerCtrl);
}

MainWindow::~MainWindow()
{
    delete ui;
}
