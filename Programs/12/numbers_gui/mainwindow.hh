
/* COMP.CS.110 Ohjelmointi 2: Rakenteet / Programming 2: Structures
* Project3: 2048 peli
 *Tämä tiedosto luo graafisen käyttöliittymän pohjakoodin avulla
 *Tässä tidostossa määritellään kaikki tarvittavat osat joita
 *käyttöliittymä tarvitsee toimiakseen. Yleisesti tästä tiedostosta
 *löytyy myös metodit joita tarvitaan käyttöliittymän toimintaan
 *Sekä muita tarvittavia tietoja, kuten mikä väri on kullakin yksittäisellä
 *numerolaatalla, kun sillä on tietty arvo.
 *
 *
  Ohjelman kirjoittaja ( Täytä omilla tiedoillasi )
* Nimi: Akseli Ahonen
* Opiskelijanumero: 150313812
* Käyttäjätunnus: tbakah ( Git-repositorion hakemistonimi. )
* E-Mail: akseli.ahonen@tuni.fi
*
* Huomioita ohjelmasta ja sen toteutuksesta:
*
*
* */

#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QGraphicsScene>
#include <QLineEdit>
#include <map>

using Coords = std::pair<int, int>;

//Värit tietyille numeroille
const std::map<int, QString> COLORS = {{0,"background-color:rgb(255,201,101)"}
                                       ,{2, "background-color:rgb(255,102,0)"}
                                       ,{4, "background-color:orange"}
                                       ,{8, "background-color:rgb(255,246,66)"}
                                       ,{16, "background-color:rgb(191,253,53)"}
                                       ,{32, "background-color:rgb(85,202,65)"}
                                       ,{64, "background-color:aqua"}
                                       ,{128, "background-color:rgb(65,186,202)"}
                                       ,{256, "background-color:blue"}
                                       ,{512, "background-color:purple"}
                                       ,{1024, "background-color:rgb(202,65,192)"}
                                       ,{2048,"background-color:red"}};

class GameBoard;

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //constructori
    MainWindow(QWidget *parent = nullptr);
    //deconstrucotri
    ~MainWindow();

    //Piirtää kaiken muun paitsi itse numerolaattoja
    void drawStart();

    //Piirtää numerolaat
    void drawBoard();

    //Päivittää pelialustan
    void updateBoard();

    //Siirtää laattoja haluttuun suuntaan.
    //Saa parametrina koordinaati.
    void move(Coords coords);

    //Määrittää mitä ajastin näyttää
    void timerFunction();

    //Nollaa ajastimen
    void timerReset();

private slots:


    //Siemenluvun kysyminen
    void on_lineEdit_textChanged(const QString &arg1);

    //Tavoiteluvun kysyminen
    void on_lineEdit_2_textChanged(const QString &arg1);


    //Liikutetaan laattoja ylös, oikealle, alas ja vasemmalle
    void on_up_clicked();
    void on_right_clicked();
    void on_left_clicked();
    void on_down_clicked();

    //Muuttaa pelin tekstin englanniksi
    void on_actionEnglish_triggered();

    //Muuttaa pelin tekstin suomeksi
    void on_actionSuomi_triggered();

    //Avaa menusta ohjeen pelin säännöistä
    void on_actionHelp_triggered();

    //Pause/continue nappi eli aloittaa ja lopettaa ajastimen´
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;
    QPushButton* button;
    QLabel* label_ = nullptr;
    QLineEdit text;
    QTimer* timer;

    GameBoard* board_;
    //Tänne varastoidaan numerolaattojen arvotS
    std::map<std::pair<int,int>, QLabel*> labelsByCoords = {};

    int seed_; //siemenluku
    int goal_; //tavoiteluku
    int tempValueGoal_; //Autta siinä, että kesken pelin tavoite ei vaihdu
    QString language_; //kertoo mikä kieli on valittuna

    int sec_;
    int min_;
    int hour_;
    int score_;

    bool gameStarted = false; //kertoo onko peli alkanut
    bool timerOn = false; //kertoo onko ajastin päällä

    //Laittaa siirtymisnapit pois päältä
    void disableButtons();
    //Laittaa siirtymisnapit päälle
    void enableButtons();

    //Poistaa pelilaudan ja luo uuden, jotta ei synny muistiongelmia.
    void resetBoard();

    //Resetoi kaikki tarvittavat komponentit, jotta peli voidaan aloittaa alusta
    void reset();


};
#endif // MAINWINDOW_HH
