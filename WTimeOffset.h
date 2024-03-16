#ifndef WTIMEOFFSET_H
#define WTIMEOFFSET_H

#include <QDialog>

namespace Ui {
class WTimeOffset;
}

class WTimeOffset : public QDialog
{
    Q_OBJECT

public:
    explicit WTimeOffset(QWidget *parent = nullptr);
    ~WTimeOffset();

    void setDateTime(QDateTime startTime);

    QDateTime getStartTime();
private slots:
    void on_timeEdit_editingFinished();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_horizontalSlider_valueChanged(int value);

private:
    Ui::WTimeOffset *ui;
};

#endif // WTIMEOFFSET_H
