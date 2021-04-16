#ifndef TIMETAKEN_H
#define TIMETAKEN_H
#pragma once

#include <QMainWindow>
#include "secondwindow.h"

namespace Ui {
class timeTaken;
}

class timeTaken : public QMainWindow
{
    Q_OBJECT

public:
    explicit timeTaken(QWidget *parent = nullptr);
    ~timeTaken();

private slots:
    void on_pushButton_clicked();

private:
    Ui::timeTaken *ui;
    SecondWindow *secWindow;
};

#endif // TIMETAKEN_H
