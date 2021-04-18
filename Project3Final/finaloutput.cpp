#include "ui_finaloutput.h"
#include "finaloutput.h"
#include "secondwindow.h"
#include "mainwindow.h"
#include <sstream>
using namespace std;

finalOutput::finalOutput(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::finalOutput)
{
    ui->setupUi(this);
}
 finalOutput::finalOutput(QWidget *parent, AVLTree avl, HashMap hashmap, B_Plus_Tree btree):
     QMainWindow(parent),
     ui(new Ui::finalOutput)
 {
     ui->setupUi(this);
     this->avl = avl;
     this->hashmap = hashmap;
     this->btree = btree;
 }
finalOutput::~finalOutput()
{
    delete ui;
}

void finalOutput::on_pushButton_clicked()
{
    SecondWindow *secWindow = new SecondWindow(this, avl, hashmap, btree);
    secWindow->show();
    this->hide();
}
void finalOutput::setAvlFTime(float time)
{
    ostringstream ss;
    ss << time;
    std::string s(ss.str());
    QString avlPrint = QString::fromStdString(s);
    ui->avlFTime->setText(avlPrint + " µs");
}
void finalOutput::setHashMapFTime(float time)
{
    ostringstream ss;
    ss << time;
    std::string s(ss.str());
    QString hashMapPrint = QString::fromStdString(s);
    ui->HashMapFTime->setText(hashMapPrint + " µs");
}
void finalOutput::setBTreeFTime(float time)
{
    ostringstream ss;
    ss << time;
    std::string s(ss.str());
    QString BTreePrint = QString::fromStdString(s);
    ui->BTreeFTime->setText(BTreePrint + " µs");
}
void finalOutput::setAvlOutput(float output, int quantity, string type)
{
    if(type == "p")
    {
        ostringstream ss;
        ss << quantity;
        std::string s(ss.str());
        QString x = QString::fromStdString(s);
        ui->avlTreeOutput->setText(x);
        ui->avlHeader->setText("Quantity Demanded:");
        ui->avlTreeQuantity->hide();
        ui->avlHeaderLow->hide();
    }
    if(type == "mc")
    {
        ostringstream ss;
        ss << output;
        std::string s(ss.str());
        QString x = QString::fromStdString(s);
        ui->avlTreeOutput->setText(x);
        ui->avlHeader->setText("Equilibrium Price Point:");

        ostringstream ss2;
        ss2 << output;
        std::string s2(ss2.str());
        QString x2 = QString::fromStdString(s2);
        ui->avlTreeQuantity->setText(x);
        ui->avlTreeQuantity->show();
        ui->avlHeaderLow->setText("Equilibrium Quanity:");
        ui->avlHeaderLow->show();
    }
}
void finalOutput::setBTreeOutput(float output, int quantity, string type)
{
    if(type == "p")
    {
        ostringstream ss;
        ss << quantity;
        std::string s(ss.str());
        QString x = QString::fromStdString(s);
        ui->BTreeOutput->setText(x);
        ui->BTreeHeader->setText("Quantity Demanded:");
        ui->BTreeQuantity->hide();
        ui->BTreeHeaderLow->hide();
    }
    if(type == "mc")
    {
        ostringstream ss;
        ss << output;
        std::string s(ss.str());
        QString x = QString::fromStdString(s);
        ui->BTreeOutput->setText(x);
        ui->BTreeHeader->setText("Equilibrium Price Point:");

        ostringstream ss2;
        ss2 << output;
        std::string s2(ss2.str());
        QString x2 = QString::fromStdString(s2);
        ui->BTreeQuantity->setText(x);
        ui->BTreeQuantity->show();
        ui->BTreeHeaderLow->setText("Equilibrium Quanity:");
        ui->BTreeHeaderLow->show();
    }
}
void finalOutput::setHashMapOutput(float output, int quantity, string type)
{
    if(type == "p")
    {
        ostringstream ss;
        ss << quantity;
        std::string s(ss.str());
        QString x = QString::fromStdString(s);
        ui->hashMapOutput->setText(x);
        ui->hashMapHeader->setText("Quantity Demanded:");
        ui->hashMapQuantity->hide();
        ui->hashHeaderLow->hide();
    }
    if(type == "mc")
    {
        ostringstream ss;
        ss << output;
        std::string s(ss.str());
        QString x = QString::fromStdString(s);
        ui->hashMapOutput->setText(x);
        ui->hashMapHeader->setText("Equilibrium Price Point:");

        ostringstream ss2;
        ss2 << output;
        std::string s2(ss2.str());
        QString x2 = QString::fromStdString(s2);
        ui->hashMapQuantity->setText(x);
        ui->hashMapQuantity->show();
        ui->hashHeaderLow->setText("Equilibrium Quanity:");
        ui->hashHeaderLow->show();
    }
}
