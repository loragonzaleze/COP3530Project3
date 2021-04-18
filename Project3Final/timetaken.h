#ifndef TIMETAKEN_H
#define TIMETAKEN_H
#pragma once

#include <QMainWindow>
#include "secondwindow.h"
#include "avltree.h"
#include "hashmap.h"
#include "b_plus_tree.h"
using namespace std;

namespace Ui {
class timeTaken;
}

class timeTaken : public QMainWindow
{
    Q_OBJECT

public:
    void setAVLTime(float time);
    void setHashMapTime(float time);
    void setBTreeTime(float time);
    explicit timeTaken(QWidget *parent = nullptr);
    timeTaken(QWidget *parent, AVLTree avl, HashMap hashmap, B_Plus_Tree btree);
    ~timeTaken();

private slots:
    void on_pushButton_clicked();

private:
    AVLTree avl;
    HashMap hashmap;
    B_Plus_Tree btree;

    QString avlPrint;
    QString hashMapPrint;
    QString BTreePrint;
    Ui::timeTaken *ui;
    SecondWindow *secWindow;
};

#endif // TIMETAKEN_H
