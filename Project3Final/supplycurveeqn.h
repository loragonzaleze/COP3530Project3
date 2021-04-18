#ifndef SUPPLYCURVEEQN_H
#define SUPPLYCURVEEQN_H
#pragma once

#include <sys/types.h>
#include <QMainWindow>
#include "finaloutput.h"
#include "avltree.h"
#include "hashmap.h"

namespace Ui {
class supplyCurveEqn;
}

class supplyCurveEqn : public QMainWindow
{
    Q_OBJECT

public:
    explicit supplyCurveEqn(QWidget *parent = nullptr);
    ~supplyCurveEqn();
    supplyCurveEqn(QWidget *parent, AVLTree avl, HashMap hashmap, B_Plus_Tree btree);

private slots:
    void on_textM_returnPressed();

    void on_textC_returnPressed();

    void on_pushButton_clicked();

private:
    void openNew();
    bool cFilled = false;
    bool mFilled = false;
    AVLTree avl;
    HashMap hashmap;
    B_Plus_Tree btree;
    Ui::supplyCurveEqn *ui;
    float m;
    float c;
    finalOutput *finOutput;
};

#endif // SUPPLYCURVEEQN_H
