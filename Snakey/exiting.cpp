#include "exiting.h"
#include "ui_exiting.h"

Exiting::Exiting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Exiting)
{
    ui->setupUi(this);
    this->setWindowTitle("Exit?");
}

Exiting::~Exiting()
{
    delete ui;
}

void Exiting::on_pushButton_clicked()
{
    exit(0);
}
void Exiting::on_pushButton_2_clicked()
{
    this->close();
}

