#include "supplycurveeqn.h"
#include "ui_supplycurveeqn.h"
#include <iostream>
#include "finaloutput.h"
using namespace std;

supplyCurveEqn::supplyCurveEqn(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::supplyCurveEqn)
{
    ui->setupUi(this);
}

supplyCurveEqn::~supplyCurveEqn()
{
    delete ui;
}

void supplyCurveEqn::on_textM_returnPressed()
{
    QString qs;
    qs = ui->textM->text();
    string strM;
    strM = qs.toUtf8().constData();
    m = stof(strM);
    ui->textM->clear();
    ui->textM->setText(qs);
    ui->textM->setClearButtonEnabled(false);
}

void supplyCurveEqn::on_textC_returnPressed()
{
    QString qs;
    qs = ui->textC->text();
    string strC;
    strC = qs.toUtf8().constData();
    c = stof(strC);
    ui->textC->clear();
    ui->textC->setText(qs);
    ui->textC->setClearButtonEnabled(false);
}

void supplyCurveEqn::on_pushButton_clicked()
{
    cout << "slope: " << m << "constant" << c << endl;
    finOutput = new finalOutput(this);
    finOutput->show();
    this->hide();
}
