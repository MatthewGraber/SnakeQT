#include "difficulty_select.h"
#include "ui_difficulty_select.h"
int var;
Difficulty_Select::Difficulty_Select(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Difficulty_Select)
{
    ui->setupUi(this);
}

Difficulty_Select::~Difficulty_Select()
{
    delete ui;
}

void Difficulty_Select::on_Spicy_Button_clicked()
{
    var = 75;
    MainWindow *p = new MainWindow();
    p->show();
    this->close();
}


void Difficulty_Select::on_Mid_Button_clicked()
{
    var = 150;
    MainWindow *p = new MainWindow();
    p->show();
    this->close();
}


void Difficulty_Select::on_Sweet_Button_clicked()
{
    var = 350;
    MainWindow *p = new MainWindow();
    p->show();
    this->close();
}

