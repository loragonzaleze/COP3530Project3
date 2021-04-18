#include "enterpmc.h"
#include "ui_enterpmc.h"
#include <iostream>
#include "finaloutputpmc.h"
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
enterPMC::enterPMC(QWidget *parent, AVLTree avl, HashMap hashmap, B_Plus_Tree btree):
    QMainWindow(parent),
    ui(new Ui::enterPMC)
{
    ui->setupUi(this);
    this->avl = avl;
    this->hashmap = hashmap;
    this->btree = btree;
}

void enterPMC::on_textP_returnPressed()
{
    QString qs;
    pFilled = true;
    qs = ui->textP->text();
    string strP;
    strP = qs.toUtf8().constData();
    p = stof(strP);
    ui->textP->clear();
    ui->textP->setText(qs);
    ui->textP->setClearButtonEnabled(false);
    ui->textP->clearFocus();
}

void enterPMC::on_textM_returnPressed()
{
    QString qs;
    mFilled = true;
    qs = ui->textM->text();
    string strM;
    strM = qs.toUtf8().constData();
    m = stof(strM);
    ui->textM->clear();
    ui->textM->setText(qs);
    ui->textM->setClearButtonEnabled(false);
    ui->textM->clearFocus();
}

void enterPMC::on_textC_returnPressed()
{
    QString qs;
    cFilled = true;
    qs = ui->textC->text();
    string strC;
    strC = qs.toUtf8().constData();
    c = stof(strC);
    ui->textC->clear();
    ui->textC->setText(qs);
    ui->textC->setClearButtonEnabled(false);
    ui->textC->clearFocus();
}

void enterPMC::on_pushButton_clicked()
{
    if(mFilled && cFilled && pFilled)
        openNew();
}
void enterPMC::openNew()
{
    pFilled = false;
    mFilled = false;
    cFilled = false;
    this->hide();
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::microseconds;

    auto t1AVL = high_resolution_clock::now();
    int avlStatus = avl.PrintMarketStatus(m,c,p);
    auto t2AVL = high_resolution_clock::now();

    duration<float, std::micro> ms_floatAVL = t2AVL - t1AVL;

    auto t1HM = high_resolution_clock::now();
    int hashStatus = hashmap.PrintMarketStatus(m,c,p);
    auto t2HM = high_resolution_clock::now();
    duration<float, std::micro> ms_floatHM = t2HM - t1HM;

    auto t1BT = high_resolution_clock::now();
    int BTreeStatus = btree.PrintMarketStatus(m,c,p);
    auto t2BT = high_resolution_clock::now();
    duration<float, std::micro> ms_floatBT = t2BT - t1BT;

    finOutput = new finaloutputPMC(this, avl, hashmap, btree);
    finOutput->setStatusAvl(avlStatus);
    finOutput->setStatusHashMap(hashStatus);
    finOutput->setStatusBTree(BTreeStatus);
    finOutput->setAvlFTime(ms_floatAVL.count());
    finOutput->setBTreeFTime(ms_floatBT.count());
    finOutput->setHashMapFTime(ms_floatHM.count());
    finOutput->show();
    finOutput->update();
}
