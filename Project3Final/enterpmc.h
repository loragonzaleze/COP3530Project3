#ifndef ENTERPMC_H
#define ENTERPMC_H
#pragma once

#include <QMainWindow>
#include "finaloutput.h"

namespace Ui {
class enterPMC;
}

class enterPMC : public QMainWindow
{
    Q_OBJECT

public:
    explicit enterPMC(QWidget *parent = nullptr);
    ~enterPMC();

private slots:

    void on_textP_returnPressed();

    void on_textM_returnPressed();

    void on_textC_returnPressed();

    void on_pushButton_clicked();

private:
    Ui::enterPMC *ui;
    float p;
    float m;
    float c;
    finalOutput *finOutput;
};

#endif // ENTERPMC_H
