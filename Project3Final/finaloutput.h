#ifndef FINALOUTPUT_H
#define FINALOUTPUT_H
#pragma once

#include <QMainWindow>
#include "avltree.h"
#include "hashmap.h"
#include "b_plus_tree.h"

namespace Ui {
class finalOutput;
}

class finalOutput : public QMainWindow
{
    Q_OBJECT

public:
    explicit finalOutput(QWidget *parent = nullptr);
    ~finalOutput();
    finalOutput(QWidget *parent, AVLTree avl, HashMap hashmap, B_Plus_Tree btree);
    void setAvlFTime(float time);
    void setHashMapFTime(float time);
    void setBTreeFTime(float time);
    void setAvlOutput(float output, int quantity, string type);
    void setBTreeOutput(float output, int quantity, string type);
    void setHashMapOutput(float output, int quantity, string type);
private slots:
    void on_pushButton_clicked();

private:
    Ui::finalOutput *ui;
    AVLTree avl;
    B_Plus_Tree btree;
    HashMap hashmap;
};

#endif // FINALOUTPUT_H
