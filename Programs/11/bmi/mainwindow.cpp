#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <math.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , weigth_(0)
    , heigth_(0)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_weightLineEdit_textChanged(const QString &arg1)
{
    weigth_ = arg1.toInt();
}


void MainWindow::on_heightLineEdit_textChanged(const QString &arg1)
{
    heigth_ = arg1.toInt();
}


void MainWindow::on_countButton_clicked()
{
    if (heigth_ == 0 || weigth_ == 0){
        ui->infoTextBrowser->setText("");
        ui->resultLabel->setText("Cannot count");
    }else{
        float kraa = heigth_ / 100.0;
        float bmi = weigth_ / (kraa*kraa);
        ui->resultLabel->setText(QString::number(bmi));

        if (bmi > 25){
            ui->infoTextBrowser->setText("You are overweight.");
        }else if (bmi > 18.5){
            ui->infoTextBrowser->setText("Your weight is normal.");
        }else{
            ui->infoTextBrowser->setText("You are underweight.");
        }
    }


}

