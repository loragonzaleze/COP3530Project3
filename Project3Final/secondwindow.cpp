#include "secondwindow.h"
#include "ui_secondwindow.h"
#include "enterpricepoint.h"
#include "supplycurveeqn.h"
#include "enterpmc.h"

SecondWindow::SecondWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SecondWindow)
{
    ui->setupUi(this);
}

SecondWindow::~SecondWindow()
{
    delete ui;
}


void SecondWindow::on_exit_clicked()
{
    this->close();
}

void SecondWindow::on_load_clicked()
{
    p = new enterPricePoint(this);
    p->show();
    this->hide();
}

void SecondWindow::on_printStatus_clicked()
{
    pmc = new enterPMC(this);
    pmc->show();
    this->hide();
}

void SecondWindow::on_findPricePoint_clicked()
{
    mc = new supplyCurveEqn(this);
    mc->show();
    this->hide();
}
