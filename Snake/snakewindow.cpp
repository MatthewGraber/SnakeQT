#include "snakewindow.h"
#include "./ui_snakewindow.h"

SnakeWindow::SnakeWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SnakeWindow)
{
    ui->setupUi(this);

//    for (int i = 0; i < 15; i++) {
//        for (int j = 0; j < 15; j++) {
//            spaces[i][j] = 0;
//        }
//    }
    srand(time(0));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    // Put the head in the center
    spaces[8][8] = 1;
}

SnakeWindow::~SnakeWindow()
{
    delete ui;
}

void SnakeWindow::update() {

}
