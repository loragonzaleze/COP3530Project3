#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma once

#include <QMainWindow>
#include "secondwindow.h"
#include "timetaken.h"
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_lineEdit_2_returnPressed();

    string getCSV();



    void on_comboBox_textActivated(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QString currentFile = "";
    timeTaken *time;
    string csvFile;
};
#endif // MAINWINDOW_H
