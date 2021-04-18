#include "enterpricepoint.h"
#include "ui_enterpricepoint.h"
#include "finaloutput.h"
#include "mainwindow.h"
#include <iostream>
using namespace std;

enterPricePoint::enterPricePoint(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::enterPricePoint)
{
    ui->setupUi(this);
}
enterPricePoint::enterPricePoint(QWidget *parent, AVLTree avl, HashMap hashmap, B_Plus_Tree btree):
    QMainWindow(parent),
    ui(new Ui::enterPricePoint)
{
    ui->setupUi(this);
    this->avl = avl;
    this->hashmap = hashmap;
    this->btree = btree;
}
enterPricePoint::~enterPricePoint()
{
    delete ui;
}

void enterPricePoint::on_pushButton_clicked()
{
    openNew(p);
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
    ui->lineEdit_2->clearFocus();
}
void enterPricePoint::openNew(float price)
{
    this->hide();
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::microseconds;

    auto t1AVL = high_resolution_clock::now();
    int avlQuantity = avl.FindQuantityDemanded(price);
    auto t2AVL = high_resolution_clock::now();

    duration<float, std::micro> ms_floatAVL = t2AVL - t1AVL;

    auto t1HM = high_resolution_clock::now();
    int hashQuantity = hashmap.FindQuantityDemanded(price);
    auto t2HM = high_resolution_clock::now();
    duration<float, std::micro> ms_floatHM = t2HM - t1HM;

    auto t1BT = high_resolution_clock::now();
    int BTreeQuantity = btree.FindQuantityDemanded(price);
    auto t2BT = high_resolution_clock::now();
    duration<float, std::micro> ms_floatBT = t2BT - t1BT;

    finOutput = new finalOutput(this, avl, hashmap, btree);
    finOutput->setAvlFTime(ms_floatAVL.count());
    finOutput->setHashMapFTime(ms_floatHM.count());
    finOutput->setBTreeFTime(ms_floatBT.count());
    finOutput->setAvlOutput(-1, avlQuantity, "p");
    finOutput->setHashMapOutput(-1, hashQuantity, "p");
    finOutput->setBTreeOutput(-1, BTreeQuantity, "p");

    finOutput->show();
    finOutput->update();
}
