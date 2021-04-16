#ifndef ENTERPRICEPOINT_H
#define ENTERPRICEPOINT_H
#pragma once

#include <sys/types.h>
#include <QMainWindow>
#include "finaloutput.h"

namespace Ui {
class enterPricePoint;
}

class enterPricePoint : public QMainWindow
{
    Q_OBJECT

public:
    explicit enterPricePoint(QWidget *parent = nullptr);
    ~enterPricePoint();

private slots:
    void on_pushButton_clicked();

    void on_lineEdit_2_returnPressed();

private:
    Ui::enterPricePoint *ui;
    finalOutput *finOutput;
    float p;
};

#endif // ENTERPRICEPOINT_H
