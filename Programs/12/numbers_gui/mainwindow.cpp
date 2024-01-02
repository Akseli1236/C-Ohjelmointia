#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "gameboard.hh"
#include <QGraphicsScene>
#include <vector>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QTextBrowser>
#include <QTimer>

const Coords UP = {0, -1};
const Coords LEFT = {-1, 0};
const Coords DOWN = {0, 1};
const Coords RIGHT = {1, 0};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , seed_(0)
    , goal_(2048)
    , tempValueGoal_(2048)
    , language_("englanti")
    , sec_(0)
    , min_(0)
    , hour_(0)
    , score_(0)

{
    ui->setupUi(this);
    board_ = new GameBoard;
    board_->init_empty();
    board_->fill(seed_);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    disableButtons();

    //asetetaan haluttuja ominaisuuksia tekstikentille
    ui->seedLabel->setStyleSheet("font-weight: bold;");
    ui->targetValueLabel->setStyleSheet("font-weight: bold;");
    ui->controlsLabel->setStyleSheet("font-weight: bold; font-size: 21px;");
    ui->ajastin->setAlignment(Qt::AlignCenter);
    ui->ajastin->setStyleSheet("font-size: 30px;");
    ui->ajastin->setText("00:00:00");


    timer = new QTimer(this);
    ui->pushButton->setEnabled(false);
    connect(timer, &QTimer::timeout, this, &MainWindow::timerFunction);


    drawStart();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete board_;
}

void MainWindow::drawStart()
{
    button = new QPushButton("Start",this);
    button->setGeometry(50,200,125,50);
    ui->button_quit->setGeometry(50,250,125,50);
    ui->button_quit->setText("Quit");

    connect(button, &QPushButton::clicked,
            this, &MainWindow::reset);
}

void MainWindow::drawBoard()
{
    Coords tempCoords = {};
    for (int x = 0; x < SIZE; x++){
        for (int y = 0; y < SIZE; y++){
            tempCoords = {x,y};

            NumberTile* tuloste = board_->get_item(tempCoords);
            const QString text = QString::number(tuloste->value());
            QLabel* numeberTileLabel = new QLabel();

            numeberTileLabel->setText(text);
            numeberTileLabel->setGeometry((x)*50,(y+1)*50,45,45);
            numeberTileLabel->setStyleSheet(COLORS.at(tuloste->value()));
            numeberTileLabel->setAlignment(Qt::AlignCenter);

            scene->addWidget(numeberTileLabel);
            labelsByCoords[tempCoords] = numeberTileLabel;
        }
    }
    connect(button, &QPushButton::clicked,
            this, &MainWindow::resetBoard);
    timerReset();
    enableButtons();


}

void MainWindow::disableButtons()
{

    ui->right->setEnabled(false);
    ui->left->setEnabled(false);
    ui->up->setEnabled(false);
    ui->down->setEnabled(false);

}

void MainWindow::enableButtons()
{
    ui->right->setEnabled(true);
    ui->left->setEnabled(true);
    ui->up->setEnabled(true);
    ui->down->setEnabled(true);
}

void MainWindow::resetBoard()
{
    delete board_;
    board_ = new GameBoard;
    board_->init_empty();
    board_->fill(seed_);

    drawBoard();

}

void MainWindow::reset()
{
    this->setStyleSheet("background-color: orange;");
    ui->pushButton->setEnabled(true);

    //Pitää huolen siitä, että kesken pelin ei voi vaihtaa goal_ arvoa
    goal_ = tempValueGoal_;
    scene->clear();
    labelsByCoords.clear();

    gameStarted = true;
    score_ = 0;
    ui->score->display(score_);

    //Tarkastetaan kieli, jotta voidaan vaihtaa sana oikealle kielelle
    if (language_ == "englanti"){
        button->setText("Restart");
        ui->pushButton->setText("Pause");
    }else{
        button->setText("Aloita uudelleen");
        ui->pushButton->setText("Pysäytä");
    }
    drawBoard();

}
void MainWindow::updateBoard()
{
    Coords tempCoords = {};
    for (int x = 0; x < SIZE; x++){
        for (int y = 0; y < SIZE; y++){
            tempCoords = {x,y};

            NumberTile* tuloste = board_->get_item(tempCoords);
            const QString tileValue = QString::number(tuloste->value());

            //Vain 2048 arvoon asti on värejä, joten siitä eteenpäin kaikilla
            //numeroilla on sama väri
            if (COLORS.find(tuloste->value()) != COLORS.end()){
                labelsByCoords[tempCoords]->setStyleSheet(COLORS.at(tuloste->value()));
            }else{
                labelsByCoords[tempCoords]->setStyleSheet("background-color: green");
            }

            //Laskee pelin pisteet
            score_ += tuloste->value()*2;
            ui->score->display(score_);


            labelsByCoords[tempCoords]->setText(tileValue);

        }
   }

}

void MainWindow::move(Coords coords)
{
    if (board_->is_full()){
        QLabel* loseLabel = new QLabel();
        if (language_ == "englanti"){
            loseLabel->setText("You Lost! \n No more spaces left");
        }else{
            loseLabel->setText("Hävisit! \n Ei vapaita ruutuja");
        }
        loseLabel->setGeometry(30,100,135,50);
        loseLabel->setAlignment(Qt::AlignCenter);

        //Vaihdetaan tastaväriä
        this->setStyleSheet("background-color:red");
        disableButtons();


        scene->addWidget(loseLabel);
        timer->stop();

    }
    else if (board_->move(coords,goal_)){
        QLabel* winLabel = new QLabel();
        if (language_ == "englanti"){
            winLabel->setText("You Win! \n Goal value Reached");
        }else{
            winLabel->setText("Voitit!\n Tavoiteluku saavutettu");
        }
        winLabel->setGeometry(30,100,150,50);
        winLabel->setAlignment(Qt::AlignCenter);

        //Vaihdetaan tastaväriä
        this->setStyleSheet("background-color:green");
        disableButtons();

        scene->addWidget(winLabel);
        timer->stop();

    }else{
        board_->new_value(false);
    }

    updateBoard();

}

void MainWindow::timerFunction()
{
    sec_ = sec_ + 1;
    if (sec_ == 60){
        sec_ = 0;
        min_ = min_ + 1;
    }
    if (min_ == 60){
        min_ = 0;
        hour_ = hour_ + 1;
    }
    if (min_ < 10 or sec_ < 10){
        if (min_ < 10 and sec_ < 10){
            ui->ajastin->setText("0"+QString::number(hour_)+":0"
                                + QString::number(min_)+":0"+QString::number(sec_));
        }else if (min_ < 10)
            ui->ajastin->setText("0"+QString::number(hour_)+":0"
                                 + QString::number(min_)+":"+QString::number(sec_));
        else{
            ui->ajastin->setText("0"+QString::number(hour_)+":"
                                 + QString::number(min_)+":0"+QString::number(sec_));
        }
    }


}

void MainWindow::timerReset()
{
    sec_ = 0;
    min_ = 0;
    hour_ = 0;

    timer->start(1000);
    timerOn = true;
    ui->ajastin->setText("00:00:00");


}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    seed_ = arg1.toInt();
}


void MainWindow::on_lineEdit_2_textChanged(const QString &arg1)
{

    float help = arg1.toInt();
    while (help > 1){
        help = help / 2;
    }
    if (help == 1){
        tempValueGoal_ = arg1.toInt();
    }else{
        tempValueGoal_ = 2048;
    }

}

void MainWindow::on_up_clicked()
{
    move(UP);
}


void MainWindow::on_right_clicked()
{
    move(RIGHT);
}


void MainWindow::on_down_clicked()
{
    move(DOWN);
}


void MainWindow::on_left_clicked()
{
    move(LEFT);
}


void MainWindow::on_actionEnglish_triggered()
{
    ui->menuOptions->setTitle("Options");
    ui->menuChange_language->setTitle("Change language");
    language_ = "englanti";

    if (not gameStarted){
        button->setText("Start");
    }else{
        button->setText("Restart");
    }

    if (timerOn){
        ui->pushButton->setText("Pause");
    }else{
        ui->pushButton->setText("Continue");
    }
    //Asetetaan tekstit oikeaan paikaan
    //ja annetaan niille oikean ominaisuudet
    ui->seedLabel->setGeometry(90,4,100,50);
    ui->targetValueLabel->setGeometry(60,109,120,20);
    ui->button_quit->setText("Quit");
    ui->seedLabel->setText("Seed");
    ui->targetValueLabel->setText("Target number");
    ui->controlsLabel->setText("Controls");
}


void MainWindow::on_actionSuomi_triggered()
{
    ui->menuOptions->setTitle("Asetukset");
    ui->menuChange_language->setTitle("Vaihda kieli");
    language_ = "suomi";

    if (not gameStarted){
        button->setText("Aloita");
    }else{
        button->setText("Aloita uudelleen");
    }

    if (timerOn){
        ui->pushButton->setText("Pysäytä");
    }else{
        ui->pushButton->setText("Jatka");
    }
    //Asetetaan tekstit oikeaan paikaan
    //ja annetaan niille oikean ominaisuudet
    ui->seedLabel->setGeometry(68,5,100,50);
    ui->targetValueLabel->setGeometry(72,110,100,20);
    ui->button_quit->setText("Lopeta");
    ui->seedLabel->setText("Siemenluku");
    ui->targetValueLabel->setText("Tavoiteluku");
    ui->controlsLabel->setText("Kontrollit");

}


void MainWindow::on_actionHelp_triggered()
{
    //Luetaan tiedostosta ohjeet ja näytetään
    //ne uudessa ikkunasa
    QWidget *helpWdg = new QWidget;
    QFile file("//home//tbakah//1//student//12//numbers_gui//ohjeet.txt");
    QTextBrowser *rules = new QTextBrowser(helpWdg);
    rules->resize(550,550);
    file.open(QIODevice::ReadOnly);

    QTextStream in(&file);
    rules->setText(in.readAll());
    helpWdg->resize(550,550);
    helpWdg->show();
}


void MainWindow::on_pushButton_clicked()
{
    if (timerOn){
        timer->stop();
        disableButtons();
        timerOn = false;

        if (language_ == "englanti"){
            ui->pushButton->setText("Continue");
        }else{
            ui->pushButton->setText("Jatka");
        }

    }else{
        timer->start(1000);
        enableButtons();

        if (language_ == "englanti"){
            ui->pushButton->setText("Pause");
        }else{
            ui->pushButton->setText("Pysäytä");
        }
        timerOn = true;
    }
}

