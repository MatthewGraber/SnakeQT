#include "menuwindow.h"
#include "difficulty_select.h"
#include "exiting.h"
#include "ui_menuwindow.h"

MenuWindow::MenuWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MenuWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Main Menu");
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

