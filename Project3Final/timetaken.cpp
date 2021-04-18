#include "timetaken.h"
#include "ui_timetaken.h"
#include "secondwindow.h"
#include <sstream>
timeTaken::timeTaken(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::timeTaken)
{
    ui->setupUi(this);
}
timeTaken::timeTaken(QWidget *parent, AVLTree avl, HashMap hashmap, B_Plus_Tree btree):
    QMainWindow(parent),
    ui(new Ui::timeTaken)
{
    ui->setupUi(this);
    this->avl = avl;
    this->hashmap = hashmap;
    this->btree = btree;
}
timeTaken::~timeTaken()
{
    delete ui;
}
void timeTaken::setAVLTime(float time)
{
    ostringstream ss;
    ss << time;
    std::string s(ss.str());
    avlPrint = QString::fromStdString(s);
    ui->avlTime->setText(avlPrint + " ms");
}
void timeTaken::setHashMapTime(float time)
{
    ostringstream ss;
    ss << time;
    std::string s(ss.str());
    hashMapPrint = QString::fromStdString(s);
    ui->hashMapTime->setText(hashMapPrint + " ms");
}
void timeTaken::setBTreeTime(float time)
{
    ostringstream ss;
    ss << time;
    std::string s(ss.str());
    BTreePrint = QString::fromStdString(s);
    ui->BTreeTime->setText(BTreePrint + " ms");
}
void timeTaken::on_pushButton_clicked()
{
    secWindow = new SecondWindow(this, avl, hashmap, btree);
    secWindow->show();
    this->hide();
}
