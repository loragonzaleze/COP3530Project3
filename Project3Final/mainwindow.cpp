#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "secondwindow.h"
#include "timetaken.h"
#include "avltree.h"
#include <QPixmap>
#include <QMessageBox>
#include <iostream>
#include <fstream>
#include "hashmap.h"

using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix(":/img/C:/Users/Bruce Maddux/Desktop/COP3530/graphbackground.JPG");
    ui->label_pic->setPixmap(pix);

}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::GetDataFromFile(string filePath, vector<float> &prices)
{
    ifstream inFile;
    inFile.open(filePath);
    string input;
    while(inFile >> input)
    {
        int x = stof(input);
        prices.push_back(x);
    }
}


void MainWindow::on_lineEdit_2_returnPressed()
{
    QString qs;
    qs = ui->lineEdit_2->text();
    csvFile = qs.toUtf8().constData();
    openNew();
}
string MainWindow::getCSV()
{
    return csvFile;
}


void MainWindow::on_comboBox_textActivated(const QString &arg1)
{
    string s = arg1.toUtf8().constData();
    csvFile = s;
    if(csvFile == "Invisible Ink Printer")
        csvFile = "C:/Users/Bruce Maddux/Desktop/COP3530/Data Sets/Invisible_Ink_Printer.csv";
    if(csvFile == "A Plain Old Smartphone")
        csvFile = "C:/Users/Bruce Maddux/Desktop/COP3530/Data Sets/A_Plain_Old_Smartphone.csv";
    if(csvFile == "Flying Car")
        csvFile = "C:/Users/Bruce Maddux/Desktop/COP3530/Data Sets/Flying_Car.csv";
    if(csvFile == "Success Guide for COP3530")
        csvFile = "C:/Users/Bruce Maddux/Desktop/COP3530/Data Sets/Success_Guide_For_COP3530.csv";
    openNew();
}
void MainWindow::openNew()
{
    this->hide();
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;
    GetDataFromFile(csvFile, prices);
    auto t1AVL = high_resolution_clock::now();
    for(unsigned long long i =0; i < prices.size(); i++)
    {
        avl.LoadDataSet(prices[i]);
    }

    auto t2AVL = high_resolution_clock::now();

    duration<float, std::milli> ms_floatAVL = t2AVL - t1AVL;

    auto t1HM = high_resolution_clock::now();
    for(unsigned long long i = 0; i < prices.size(); i++)
    {
        hashmap.LoadDataSet(prices[i]);
    }

    auto t2HM = high_resolution_clock::now();
    duration<float, std::milli> ms_floatHM = t2HM - t1HM;

    sort(prices.begin(), prices.end());
    auto t1BT = high_resolution_clock::now();
    for(unsigned long long i = 0; i < prices.size(); i++)
    {
        btree.LoadDataSet(prices[i]);
    }
    auto t2BT = high_resolution_clock::now();

    duration<float, std::milli> ms_floatBT = t2BT - t1BT;

    time = new timeTaken(this, avl, hashmap, btree);
    time->setHashMapTime(ms_floatHM.count());
    time->setBTreeTime(ms_floatBT.count());
    time->setAVLTime(ms_floatAVL.count());

    time->show();
    time->update();

}
