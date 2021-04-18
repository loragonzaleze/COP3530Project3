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
supplyCurveEqn::supplyCurveEqn(QWidget *parent, AVLTree avl, HashMap hashmap, B_Plus_Tree btree):
    QMainWindow(parent),
    ui(new Ui::supplyCurveEqn)
{
    ui->setupUi(this);
    this->avl = avl;
    this->hashmap = hashmap;
    this->btree = btree;
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
    ui->textM->clearFocus();
    mFilled = true;
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
    ui->textC->clearFocus();
    cFilled = true;
}

void supplyCurveEqn::on_pushButton_clicked()
{
    if(mFilled && cFilled)
        openNew();
}
void supplyCurveEqn::openNew()
{
    cFilled = false;
    mFilled = false;
    this->hide();
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::microseconds;

    auto t1AVL = high_resolution_clock::now();
    float pAvl = 0;
    int qAvl = 0;
    avl.FindEquilibriumPricePoint(m, c, pAvl, qAvl);
    auto t2AVL = high_resolution_clock::now();

    duration<float, std::micro> ms_floatAVL = t2AVL - t1AVL;

    auto t1HM = high_resolution_clock::now();
    float pHM = 0;
    int qHM = 0;
    hashmap.FindEquilibriumPricePoint(m, c, pHM, qHM);
    auto t2HM = high_resolution_clock::now();
    duration<float, std::micro> ms_floatHM = t2HM - t1HM;

    auto t1BT = high_resolution_clock::now();
    float pBT = 0;
    int qBT= 0;
    btree.FindEquilibriumPricePoint(m, c, pBT, qBT);
    auto t2BT = high_resolution_clock::now();
    duration<float, std::micro> ms_floatBT = t2BT - t1BT;

    finOutput = new finalOutput(this, avl, hashmap, btree);
    finOutput->setAvlFTime(ms_floatAVL.count());
    finOutput->setHashMapFTime(ms_floatHM.count());
    finOutput->setBTreeFTime(ms_floatBT.count());
    finOutput->setAvlOutput(pAvl, qAvl, "mc");
    finOutput->setHashMapOutput(pHM, qHM, "mc");
    finOutput->setBTreeOutput(pBT, qBT, "mc");

    finOutput->show();
    finOutput->update();
}
