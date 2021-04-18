#ifndef ENTERPRICEPOINT_H
#define ENTERPRICEPOINT_H
#pragma once

#include <sys/types.h>
#include <QMainWindow>
#include "finaloutput.h"
#include "avltree.h"
#include "hashmap.h"
#include "b_plus_tree.h"

namespace Ui {
class enterPricePoint;
}

class enterPricePoint : public QMainWindow
{
    Q_OBJECT

public:
    explicit enterPricePoint(QWidget *parent = nullptr);
    ~enterPricePoint();
    enterPricePoint(QWidget *parent, AVLTree avl, HashMap hashmap, B_Plus_Tree btree);

private slots:
    void on_pushButton_clicked();
    void on_lineEdit_2_returnPressed();

private:
    AVLTree avl;
    HashMap hashmap;
    B_Plus_Tree btree;
    void openNew(float price);
    Ui::enterPricePoint *ui;
    finalOutput *finOutput;
    float p;
};

#endif // ENTERPRICEPOINT_H
