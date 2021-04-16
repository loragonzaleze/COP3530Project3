#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "secondwindow.h"
#include "timetaken.h"
#include <QPixmap>
#include <QMessageBox>
#include <iostream>

using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix("E:/Users/bruce/Desktop/COP3530/linechart.gif");
    ui->label_pic->setPixmap(pix);
}
MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_lineEdit_2_returnPressed()
{
    time = new timeTaken(this);
    time->show();
    QString qs;
    qs = ui->lineEdit_2->text();
    csvFile = qs.toUtf8().constData();
    this->hide();
}
string MainWindow::getCSV()
{
    return csvFile;
}


void MainWindow::on_comboBox_textActivated(const QString &arg1)
{
    time = new timeTaken(this);
    time->show();
    string s = arg1.toUtf8().constData();
    this->hide();
}
