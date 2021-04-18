#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma once

#include <QMainWindow>
#include "secondwindow.h"
#include "timetaken.h"
#include "avltree.h"
#include <vector>
#include "hashmap.h"
#include "b_plus_tree.h"
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    string getCSV();
    AVLTree avl;
    HashMap hashmap;
    B_Plus_Tree btree;

private slots:

    void on_lineEdit_2_returnPressed();


    void on_comboBox_textActivated(const QString &arg1);

private:
    void openNew();
    void GetDataFromFile(string filePath, vector<float> &prices);
    vector<float> prices;
    Ui::MainWindow *ui;
    QString currentFile = "";
    timeTaken *time;
    string csvFile;
};
#endif // MAINWINDOW_H
