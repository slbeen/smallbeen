#ifndef WQTIMERCTRL_H
#define WQTIMERCTRL_H

#include <QWidget>
#include <QTimer>
#include <QDateTime>


namespace Ui {
class WQTimerCtrl;
}

class WQTimerCtrl : public QWidget
{
    Q_OBJECT

public:
    explicit WQTimerCtrl(QWidget *parent = nullptr);
    ~WQTimerCtrl();
    /**
     * @brief initUI 初始化界面
     */
    void initUI();

    /**
     * @brief initUI 初始化连接
     */
    void initConnect();

    /**
     * @brief setBaseTime 设置界面时间
     * @param startTime 开始时间
     * @param endTime   结束时间
     */
    void setBaseTime(QDateTime startTime, QDateTime endTime);

    /**
     * @brief setIsEditTime 设置dateTimeEdit是否使用
     * @param flag : true 可以使用 : false 不可以使用
     */
    void setIsEditTime(bool flag);

    /**
     * @brief setIsGoFront 设置快进or快退
     * @param flag  : true 快进 : false 快退
     */
    void setIsGoFront(bool flag);

private slots:
    /**
     * @brief slotTimeOut 定时器槽函数
     */
    void slotTimeOut();

    /**
     * @brief slotBtnClicked 按钮槽函数
     */
    void slotBtnClicked();

    /**
     * @brief slotEditingFinished dateTimeEdit完成编辑槽函数
     */
    void slotEditingFinished();

private:
    Ui::WQTimerCtrl *ui;

    QTimer *m_pTimer = nullptr;     //定时器

    QDateTime m_startTime;          //开始时间
    QDateTime m_endTime;            //结束时间

    bool m_isGoFront;               //快进or后退
};

#endif // WQTIMERCTRL_H
