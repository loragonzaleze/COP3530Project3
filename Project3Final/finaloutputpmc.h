#ifndef FINALOUTPUTPMC_H
#define FINALOUTPUTPMC_H

#include <QMainWindow>
#include "avltree.h"
#include "b_plus_tree.h"
#include "hashmap.h"
namespace Ui {
class finaloutputPMC;
}

class finaloutputPMC : public QMainWindow
{
    Q_OBJECT

public:
    explicit finaloutputPMC(QWidget *parent = nullptr);
    finaloutputPMC(QWidget *parent, AVLTree avl, HashMap hashmap, B_Plus_Tree btree);
    ~finaloutputPMC();
    void setStatusAvl(int val);
    void setStatusBTree(int val);
    void setStatusHashMap(int val);
    void setAvlFTime(float time);
    void setBTreeFTime(float time);
    void setHashMapFTime(float time);


private slots:
    void on_pushButton_clicked();

private:
    Ui::finaloutputPMC *ui;
    AVLTree avl;
    HashMap hashmap;
    B_Plus_Tree btree;
};

#endif // FINALOUTPUTPMC_H
