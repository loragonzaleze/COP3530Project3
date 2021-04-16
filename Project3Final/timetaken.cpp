#include "timetaken.h"
#include "ui_timetaken.h"
#include "secondwindow.h"

timeTaken::timeTaken(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::timeTaken)
{
    ui->setupUi(this);
}

timeTaken::~timeTaken()
{
    delete ui;
}

void timeTaken::on_pushButton_clicked()
{
    secWindow = new SecondWindow(this);
    secWindow->show();
    this->hide();
}
