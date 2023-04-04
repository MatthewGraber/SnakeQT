#include "death.h"
#include "ui_death.h"

Death::Death(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Death)
{
    ui->setupUi(this);
}

Death::~Death()
{
    delete ui;
}

void Death::on_pushButton_clicked()
{
    this->close();
}

