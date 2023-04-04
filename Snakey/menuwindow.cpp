#include "menuwindow.h"
#include "difficulty_select.h"
#include "exiting.h"
#include "ui_menuwindow.h"
#include <QtMultimedia/QMediaPlayer>



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
    w->show();
}


void MenuWindow::on_Exit_Button_clicked()
{
    Exiting *e = new Exiting();
    e->show();
}

