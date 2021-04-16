#ifndef SUPPLYCURVEEQN_H
#define SUPPLYCURVEEQN_H
#pragma once

#include <sys/types.h>
#include <QMainWindow>
#include "finaloutput.h"

namespace Ui {
class supplyCurveEqn;
}

class supplyCurveEqn : public QMainWindow
{
    Q_OBJECT

public:
    explicit supplyCurveEqn(QWidget *parent = nullptr);
    ~supplyCurveEqn();

private slots:
    void on_textM_returnPressed();

    void on_textC_returnPressed();

    void on_pushButton_clicked();

private:
    Ui::supplyCurveEqn *ui;
    float m;
    float c;
    finalOutput *finOutput;
};

#endif // SUPPLYCURVEEQN_H
