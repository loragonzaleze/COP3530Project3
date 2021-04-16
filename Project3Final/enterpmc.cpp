#include "enterpmc.h"
#include "ui_enterpmc.h"
#include <iostream>
#include "finaloutput.h"
using namespace std;

enterPMC::enterPMC(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::enterPMC)
{
    ui->setupUi(this);
}

enterPMC::~enterPMC()
{
    delete ui;
}


void enterPMC::on_textP_returnPressed()
{
    QString qs;
    qs = ui->textP->text();
    string strP;
    strP = qs.toUtf8().constData();
    p = stof(strP);
    ui->textP->clear();
    ui->textP->setText(qs);
    ui->textP->setClearButtonEnabled(false);
}

void enterPMC::on_textM_returnPressed()
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

void enterPMC::on_textC_returnPressed()
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

void enterPMC::on_pushButton_clicked()
{
    cout << "Price: " << p << " " << "Slope: " << m << " " << "constant" << c << endl;
    finOutput = new finalOutput(this);
    finOutput->show();
    this->hide();
}
