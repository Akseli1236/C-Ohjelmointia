#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
   , sec_(0)
   , min_(0)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(myfunction()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::myfunction()
{
    sec_ = sec_ + 1;
    if (sec_ == 60){
        sec_ = 0;
        min_ = min_ + 1;
        ui->lcdNumberMin->display(min_);
    }
    ui->lcdNumberSec->display(sec_);


}

void MainWindow::on_startButton_clicked()
{
    timer->start(1000);
}


void MainWindow::on_stopButton_clicked()
{
    timer->stop();
}


void MainWindow::on_resetButton_clicked()
{
    timer->stop();
    sec_ = 0;
    min_ = 0;
    ui->lcdNumberMin->display(min_);
    ui->lcdNumberSec->display(sec_);


}

