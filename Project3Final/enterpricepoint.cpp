#include "enterpricepoint.h"
#include "ui_enterpricepoint.h"
#include "finaloutput.h"
#include <iostream>
using namespace std;

enterPricePoint::enterPricePoint(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::enterPricePoint)
{
    ui->setupUi(this);
}

enterPricePoint::~enterPricePoint()
{
    delete ui;
}

void enterPricePoint::on_pushButton_clicked()
{
    cout << "Price: " << p <<  endl;
    finOutput = new finalOutput(this);
    finOutput->show();
    this->hide();
}

void enterPricePoint::on_lineEdit_2_returnPressed()
{
    QString qs;
    qs = ui->lineEdit_2->text();
    string strP;
    strP = qs.toUtf8().constData();
    p = stof(strP);
    ui->lineEdit_2->clear();
    ui->lineEdit_2->setText(qs);
    ui->lineEdit_2->setClearButtonEnabled(false);
}
