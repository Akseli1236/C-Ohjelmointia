#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "gradecounter.hh"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , n_(0)
    , g_(0)
    , p_(0)
    , e_(0)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_spinBoxN_valueChanged(int arg1)
{
    n_= arg1;

}


void MainWindow::on_spinBoxG_valueChanged(int arg1)
{
    g_= arg1;

}


void MainWindow::on_spinBoxP_valueChanged(int arg1)
{
    p_= arg1;

}


void MainWindow::on_spinBoxE_valueChanged(int arg1)
{
    e_= arg1;
}


void MainWindow::on_countPushButton_clicked()
{
    int a = count_final_grade(n_,g_,p_,e_);
    ui->textBrowser->clear();
    ui->textBrowser->append("Total grade: " + QString::number(a));

}

