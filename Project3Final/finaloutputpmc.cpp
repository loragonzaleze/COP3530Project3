#include "finaloutputpmc.h"
#include "ui_finaloutputpmc.h"
#include <sstream>
#include "secondwindow.h"
finaloutputPMC::finaloutputPMC(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::finaloutputPMC)
{
    ui->setupUi(this);
}

finaloutputPMC::~finaloutputPMC()
{
    delete ui;
}
finaloutputPMC::finaloutputPMC(QWidget *parent, AVLTree avl, HashMap hashmap, B_Plus_Tree btree) :
     QMainWindow(parent),
ui(new Ui::finaloutputPMC)
{
    ui->setupUi(this);
    this->avl = avl;
    this->hashmap = hashmap;
    this->btree = btree;
}
void finaloutputPMC::setAvlFTime(float time)
{
    ostringstream ss;
    ss << time;
    std::string s(ss.str());
    QString avlPrint = QString::fromStdString(s);
    ui->avlFTime->setText(avlPrint + " µs");
}
void finaloutputPMC::setHashMapFTime(float time)
{
    ostringstream ss;
    ss << time;
    std::string s(ss.str());
    QString hashMapPrint = QString::fromStdString(s);
    ui->HashMapFTime->setText(hashMapPrint + " µs");
}
void finaloutputPMC::setBTreeFTime(float time)
{
    ostringstream ss;
    ss << time;
    std::string s(ss.str());
    QString BTreePrint = QString::fromStdString(s);
    ui->BTreeFTime->setText(BTreePrint + " µs");
}
void finaloutputPMC::setStatusAvl(int val)
{

    if(val == 0)
    {
        ui->statusLabelAvl->setText("The market would be in an equilibrium.");
    }
    if(val > 0)
    {
        ostringstream ss;
        ss << val;
        std::string s(ss.str());
        QString x = QString::fromStdString(s);
        ui->statusLabelAvl->setText("There would be a surplus of " + x +" items being produced.");
    }
    if(val < 0)
    {
        val *= -1;
        ostringstream ss;
        ss << val;
        std::string s(ss.str());
        QString x = QString::fromStdString(s);
        ui->statusLabelAvl->setText("There would be a shortage of " + x +" items.");
    }
}
void finaloutputPMC::setStatusBTree(int val)
{

    if(val == 0)
    {
        ui->statusLabelBTree->setText("The market would be in an equilibrium.");
    }
    if(val > 0)
    {
        ostringstream ss;
        ss << val;
        std::string s(ss.str());
        QString x = QString::fromStdString(s);
        ui->statusLabelBTree->setText("There would be a surplus of " + x +" items being produced.");
    }
    if(val < 0)
    {
        val *= -1;
        ostringstream ss;
        ss << val;
        std::string s(ss.str());
        QString x = QString::fromStdString(s);
        ui->statusLabelBTree->setText("There would be a shortage of " + x +" items.");
    }
}
void finaloutputPMC::setStatusHashMap(int val)
{

    if(val == 0)
    {
        ui->statusLabelHashMap->setText("The market would be in an equilibrium.");
    }
    if(val > 0)
    {
        ostringstream ss;
        ss << val;
        std::string s(ss.str());
        QString x = QString::fromStdString(s);
        ui->statusLabelHashMap->setText("There would be a surplus of " + x +" items being produced.");
    }
    if(val < 0)
    {
        val *= -1;
        ostringstream ss;
        ss << val;
        std::string s(ss.str());
        QString x = QString::fromStdString(s);
        ui->statusLabelHashMap->setText("There would be a shortage of " + x +" items.");
    }
}



void finaloutputPMC::on_pushButton_clicked()
{
    SecondWindow *secWindow = new SecondWindow(this, avl, hashmap, btree);
    secWindow->show();
    this->hide();
}
