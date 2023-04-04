#include "menuwindow.h"
#include "difficulty_select.h"
#include "exiting.h"
#include "ui_menuwindow.h"
#include <QtMultimedia/QMediaPlayer>

bool player_cnt;
MenuWindow::MenuWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MenuWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Main Menu");
    //Main Menu Music
    //QMediaPlayer* music = new QMediaPlayer();
    //music->setSource(QUrl::fromLocalFile("qrc:/music/s033.wav"));
    //music->play();
}

MenuWindow::~MenuWindow()
{
    delete ui;
}

void MenuWindow::on_pushButton_clicked()
{
    Difficulty_Select *w = new Difficulty_Select();
    player_cnt = false;
    w->show();
}


void MenuWindow::on_Exit_Button_clicked()
{
    Exiting *e = new Exiting();
    e->show();
}


void MenuWindow::on_Two_Player_Game_clicked()
{
    Difficulty_Select *w = new Difficulty_Select();
    player_cnt = true;
    w->show();
}

