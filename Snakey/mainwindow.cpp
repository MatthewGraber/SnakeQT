#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&SnakeScene);

    srand(time(0));

    // Brushes and pens
    headPen.setColor(Qt::GlobalColor::cyan);
    headBrush.setColor(Qt::GlobalColor::cyan);
    headBrush.setStyle(Qt::BrushStyle::SolidPattern);
    tailPen.setColor(Qt::GlobalColor::blue);
    tailBrush.setColor(Qt::GlobalColor::blue);
    tailBrush.setStyle(Qt::BrushStyle::SolidPattern);
    applePen.setColor(Qt::GlobalColor::red);
    appleBrush.setColor(Qt::GlobalColor::red);
    appleBrush.setStyle(Qt::BrushStyle::SolidPattern);


    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    // Put the head in the center

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_startBtn_clicked()
{
    tail = std::vector<QRectF>();
    tailSpaces1 = std::vector<std::vector<int>>();

    ui->graphicsView->setFixedHeight(602);
    timer->start(500);
    ui->startBtn->setVisible(false);

    SetApplePosition();
}

void MainWindow::update()  {

    // Update snake position
    if (direction == 0) {
        nextSpace1[1]--;
    }
    else if (direction == 1) {
        nextSpace1[0]++;
    }
    else if (direction == 2) {
        nextSpace1[1]++;
    }
    else {
        nextSpace1[0]--;
    }

    // Check for hitting edge
    if (nextSpace1[0] > 14 || nextSpace1[0] < 0 || nextSpace1[1] > 14 || nextSpace1[1] < 0) {
        EndGame();
    }

    // Update apple position
    if (std::equal(nextSpace1, nextSpace1 + 2, appleSpace)) {
        SetApplePosition();
        std::vector<int> newTail = {headSpace1[0], headSpace1[1]};
        tailSpaces1.push_back(newTail);

        QRectF next;
        tail.push_back(next);
    }
    else if(tailSpaces1.size() > 0) {

        if (tailSpaces1.size() > 1) {
            for (int i = 1; i < tailSpaces1.size(); i++) {
                tailSpaces1[i-1][0] = tailSpaces1[i][0];
                tailSpaces1[i-1][1] = tailSpaces1[i][1];
            }
        }
        tailSpaces1.back()[0] = headSpace1[0];
        tailSpaces1.back()[1] = headSpace1[1];
    }

    // Check to see if we ate ourself
    for (int i = 0; i < tailSpaces1.size(); i++) {
        if (nextSpace1[0] == tailSpaces1[i][0] && nextSpace1[1] == tailSpaces1[i][1]) {
            EndGame();
        }
    }

    headSpace1[0] = nextSpace1[0];
    headSpace1[1] = nextSpace1[1];

    ui->tailLen->display((int) tailSpaces1.size());
    DrawScene();
    // headSpace1[0] = 3;
}

void MainWindow::DrawScene() {
    SnakeScene.clear();
    border.setCoords(0, 0, 599, 599);
    SnakeScene.addRect(border);

    // Draw the head
    head.setCoords(headSpace1[0]*squareSize, headSpace1[1]*squareSize, (headSpace1[0]+1)*squareSize, (headSpace1[1]+1)*squareSize);
    SnakeScene.addRect(head, headPen, headBrush);

    // Draw the tail
    for (int i = 0; i < tailSpaces1.size(); i++) {
        tail[i].setCoords(tailSpaces1[i][0]*squareSize, tailSpaces1[i][1]*squareSize, (tailSpaces1[i][0] + 1)*squareSize, (tailSpaces1[i][1] + 1)*squareSize);
        std::cout << "Tail segment " << i << " X coord " << tailSpaces1[i][0] << "\n";
        std::cout << "Tail segment " << i << " Y coord " << tailSpaces1[i][1] << "\n";
        //QRectF seg(tailSpaces1[i][0]*squareSize, tailSpaces1[i][1]*squareSize, (tailSpaces1[i][0] + 1)*squareSize, (tailSpaces1[i][1] + 1)*squareSize);
        SnakeScene.addRect(tail[i], tailPen, tailBrush);
    }

    apple.setCoords(appleSpace[0]*squareSize, appleSpace[1]*squareSize, (appleSpace[0]+1)*squareSize, (appleSpace[1]+1)*squareSize);
    SnakeScene.addRect(apple, applePen, appleBrush);
}


void MainWindow::keyPressEvent(QKeyEvent * event)
{
    // NOTE: We can't reverse
    // Go up!
    if( event->key() == Qt::Key_W)
    {
        direction = 0;
    }
    else if (event->key() == Qt::Key_D) {
        direction = 1;
    }
    else if (event->key() == Qt::Key_S) {
        direction = 2;
    }
    else if (event->key() == Qt::Key_A) {
        direction = 3;
    }
}

void MainWindow::SetApplePosition() {
    appleSpace[0] = rand()%14;
    appleSpace[1] = rand()%14;

    if (std::equal(nextSpace1, nextSpace1 + 2, appleSpace)) {
        SetApplePosition();
    }
    else {
        for (int i = 0; i < tailSpaces1.size(); i++) {
            if (tailSpaces1[i][0] == appleSpace[0] && tailSpaces1[i][1] == appleSpace[1]) {
                SetApplePosition();
                break;
            }
        }
    }
}

void MainWindow::EndGame() {
    timer->stop();
}
