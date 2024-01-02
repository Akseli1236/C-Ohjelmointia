#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <string>
#include <fstream>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , found(1)

{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_findPushButton_clicked()
{

    if (found == 2){
        ui->textBrowser->setText("File found");
    }else if (found == 1){
        if (word == 1){
            ui->textBrowser->setText("Word found");
        }else{
            ui->textBrowser->setText("Word not found");
        }

    }else{
        ui->textBrowser->setText("File not found");
    }
}

void MainWindow::on_fileLineEdit_editingFinished()
{
    QFile file(ui->fileLineEdit->text());
    if (not file.open(QIODevice::ReadOnly)){
        found = 0;
    }else{
        found = 1;
        if (file.size() == 0){
            found = 2;
        }

    }

    file.close();

}


void MainWindow::on_keyLineEdit_editingFinished()
{
    QFile file(ui->fileLineEdit->text());
    if (not file.open(QIODevice::ReadOnly)){
        found = 0;
    }else{
        found = 1;
        if (file.size() == 0){
            found = 2;
        }
    }

    QTextStream stream(&file);
    QString data = stream.readAll();
    int pos = data.indexOf(ui->keyLineEdit->text().remove('"'));
    std::string lapha = data.toStdString();
    QString mam = data;
    QString mam2 = ui->keyLineEdit->text().remove('"');
    mam2 = mam2.toLower();
    mam = mam.toLower();
    int pos2 = mam.indexOf(mam2);
    std::string s = "";

    for (auto & k: lapha){
        s.push_back(tolower(k));
    }
    std::string syote = "";
    for (auto & k : ui->keyLineEdit->text().toStdString()){
        if (k == ' '){
            break;
        }
        syote.push_back(tolower(k));
    }
    std::string::iterator it;
    it = std::find (syote.begin(), syote.end(), ui->keyLineEdit->text().remove('"'));


    if (ui->matchCheckBox->isChecked()){
        if (pos >= 0){
            word = 1;
        }else{
            word = 0;
        }

    }else{
        if (mam2.isEmpty()){
            word = 0;
        }
        else if (pos2 >= 0){
            word = 1;
        }else{
            word = 0;
        }
    }
    file.close();
}

