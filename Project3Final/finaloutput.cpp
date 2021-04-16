#include "finaloutput.h"
#include "ui_finaloutput.h"
#include "secondwindow.h"
 finalOutput::finalOutput(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::finalOutput)
{
    ui->setupUi(this);
}

finalOutput::~finalOutput()
{
    delete ui;
}

void finalOutput::on_pushButton_clicked()
{
    SecondWindow *secWindow = new SecondWindow;
    secWindow->show();
    this->hide();
}
