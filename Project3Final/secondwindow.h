#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H
#pragma once

#include <sys/types.h>
#include <QMainWindow>
#include "enterpricepoint.h"
#include "supplycurveeqn.h"
#include "enterpmc.h"
#include "avltree.h"
#include "hashmap.h"
#include "b_plus_tree.h"

namespace Ui {
class SecondWindow;
}

class SecondWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SecondWindow(QWidget *parent = nullptr);
    ~SecondWindow();
    SecondWindow(QWidget *parent, AVLTree avl, HashMap hashmap, B_Plus_Tree btree);


private slots:

    void on_exit_clicked();

    void on_load_clicked();

    void on_printStatus_clicked();

    void on_findPricePoint_clicked();

private:
    Ui::SecondWindow *ui;
    AVLTree avl;
    HashMap hashmap;
    B_Plus_Tree btree;
    enterPricePoint *p;
    enterPMC *pmc;
    supplyCurveEqn *mc;

};

#endif // SECONDWINDOW_H
