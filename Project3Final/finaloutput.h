#ifndef FINALOUTPUT_H
#define FINALOUTPUT_H
#pragma once

#include <QMainWindow>

namespace Ui {
class finalOutput;
}

class finalOutput : public QMainWindow
{
    Q_OBJECT

public:
    explicit finalOutput(QWidget *parent = nullptr);
    ~finalOutput();

private slots:
    void on_pushButton_clicked();

private:
    Ui::finalOutput *ui;
   // SecondWindow *secWindow;
};

#endif // FINALOUTPUT_H
