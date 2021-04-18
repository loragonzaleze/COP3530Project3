#ifndef ENTERPMC_H
#define ENTERPMC_H
#pragma once

#include <QMainWindow>
#include "finaloutputpmc.h"
#include "avltree.h"
#include "hashmap.h"
#include "b_plus_tree.h"

namespace Ui {
class enterPMC;
}

class enterPMC : public QMainWindow
{
    Q_OBJECT

public:
    explicit enterPMC(QWidget *parent = nullptr);
    ~enterPMC();
    enterPMC(QWidget *parent, AVLTree avl, HashMap hashmap, B_Plus_Tree btree);

private slots:

    void on_textP_returnPressed();

    void on_textM_returnPressed();

    void on_textC_returnPressed();

    void on_pushButton_clicked();

    void openNew();

private:
    AVLTree avl;
    HashMap hashmap;
    B_Plus_Tree btree;
    Ui::enterPMC *ui;
    float p;
    float m;
    float c;
    bool pFilled = false;
    bool mFilled = false;
    bool cFilled = false;
    finaloutputPMC *finOutput;
};

#endif // ENTERPMC_H
