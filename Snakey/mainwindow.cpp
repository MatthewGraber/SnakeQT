#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&SnakeScene);

    srand(time(0));

    // QObject::installEventFilter();

    // twoPlayer = false;

    // Brushes and pens
    // Alex
    QColor alexHead;
    alexHead.setRgbF(153, 0, 204);
    Alex.headPen.setColor(alexHead);
    Alex.headBrush.setColor(alexHead);
    Alex.headBrush.setStyle(Qt::BrushStyle::SolidPattern);
    QColor alexTail;
    alexHead.setRgbF(0, 51, 204);
    Alex.tailPen.setColor(alexTail);
    Alex.tailBrush.setColor(alexTail);
    Alex.tailBrush.setStyle(Qt::BrushStyle::SolidPattern);

    // Don
    Don.headPen.setColor(Qt::GlobalColor::cyan);
    Don.headBrush.setColor(Qt::GlobalColor::cyan);
    Don.headBrush.setStyle(Qt::BrushStyle::SolidPattern);
    Don.tailPen.setColor(Qt::GlobalColor::blue);
    Don.tailBrush.setColor(Qt::GlobalColor::blue);
    Don.tailBrush.setStyle(Qt::BrushStyle::SolidPattern);

    // Apple
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
//    tail = std::vector<QRectF>();
//    tailSpaces1 = std::vector<std::vector<int>>();
    qInfo() << "Begining game";
    if (twoPlayer) {
        Alex.headSpace[0] = 3;
        Alex.headSpace[1] = 7;

        Don.headSpace[0] = 10;
        Don.headSpace[1] = 7;
    }
    else {
        Alex.headSpace[0] = 7;
        Alex.headSpace[1] = 7;
    }
    Alex.Reset();
    Don.Reset();

    qInfo() << "Reset Snakes";

    ui->graphicsView->setFixedHeight(604);
    timer->start(period);

    qInfo() << "Started timer";

    ui->startBtn->setVisible(false);

    SetApplePosition();
}


void Snake::Reset() {
    tail = std::vector<QRectF>();
    tailSpaces = std::vector<std::vector<int>>();
    direction = 0;
    alive = true;
    nextSpace[0] = headSpace[0];
    nextSpace[1] = headSpace[1];
}


void Snake::FindNext() {
    // Update snake position
    if (direction == 0) {
        nextSpace[1]--;
    }
    else if (direction == 1) {
        nextSpace[0]++;
    }
    else if (direction == 2) {
        nextSpace[1]++;
    }
    else {
        nextSpace[0]--;
    }

    // Check for hitting edge
    if (nextSpace[0] > 14 || nextSpace[0] < 0 || nextSpace[1] > 14 || nextSpace[1] < 0) {
        alive = false;
        return;
    }
}


void MainWindow::update()  {

//    // Update snake position
//    if (direction == 0) {
//        nextSpace1[1]--;
//    }
//    else if (direction == 1) {
//        nextSpace1[0]++;
//    }
//    else if (direction == 2) {
//        nextSpace1[1]++;
//    }
//    else {
//        nextSpace1[0]--;
//    }

//    // Check for hitting edge
//    if (nextSpace1[0] > 14 || nextSpace1[0] < 0 || nextSpace1[1] > 14 || nextSpace1[1] < 0) {
//        EndGame();
//        return;
//    }

    qInfo() << "Finding next";
    Alex.FindNext();
    if (twoPlayer)
        Don.FindNext();

    qInfo() << "Checking to see if headspaces are equal";
    if (std::equal(Alex.headSpace, Alex.headSpace + 2, Don.headSpace) && twoPlayer) {
        qInfo() << "Heads equal! Ending game";
        Don.alive = false;
        Alex.alive = false;
        EndGame();
        // return; // TODO: Return?
    }
    else {
        qInfo() << "Not equal";
        // Update First player
        if (std::equal(Alex.nextSpace, Alex.nextSpace + 2, appleSpace)) {
            Alex.Grow();
            SetApplePosition();
        }
        else {
            qInfo() << "Updating pos";
            Alex.UpdatePos();
        }

        // Update second player
        if (twoPlayer) {
            if (std::equal(Don.nextSpace, Don.nextSpace + 2, appleSpace)) {
                Don.Grow();
                SetApplePosition();
            }
            else {
                qInfo() << "Updating pos";
                Don.UpdatePos();
            }
        }
    }

//    // Update apple position
//    else if (std::equal(nextSpace1, nextSpace1 + 2, appleSpace)) {
//        std::vector<int> newTail = {headSpace1[0], headSpace1[1]};
//        tailSpaces1.push_back(newTail);

//        QRectF next;
//        tail.push_back(next);
//        SetApplePosition();
//    }
//    else if(tailSpaces1.size() > 0) {

//        if (tailSpaces1.size() > 1) {
//            for (int i = 1; i < tailSpaces1.size(); i++) {
//                tailSpaces1[i-1][0] = tailSpaces1[i][0];
//                tailSpaces1[i-1][1] = tailSpaces1[i][1];
//            }
//        }
//        tailSpaces1.back()[0] = headSpace1[0];
//        tailSpaces1.back()[1] = headSpace1[1];
//    }

//    // Check to see if we ate ourself
//    for (int i = 0; i < tailSpaces1.size(); i++) {
//        if (nextSpace1[0] == tailSpaces1[i][0] && nextSpace1[1] == tailSpaces1[i][1]) {
//            EndGame();

//        }
//    }

//    headSpace1[0] = nextSpace1[0];
//    headSpace1[1] = nextSpace1[1];

//    ui->tailLen->display((int) tailSpaces1.size());
    qInfo() << "Drawing scene";
    DrawScene();

    if (!(Alex.alive && Don.alive)) {
        EndGame();
    }
    // headSpace1[0] = 3;
}

void Snake::Grow() {
    std::vector<int> newTail = {headSpace[0], headSpace[1]};
    tailSpaces.push_back(newTail);

    QRectF next;
    tail.push_back(next);

    headSpace[0] = nextSpace[0];
    headSpace[1] = nextSpace[1];
}


void Snake::UpdatePos() {
    // Update apple position
    if (tailSpaces.size() > 0) {
        if (tailSpaces.size() > 1) {
            for (int i = 1; i < tailSpaces.size(); i++) {
                tailSpaces[i-1][0] = tailSpaces[i][0];
                tailSpaces[i-1][1] = tailSpaces[i][1];
            }
        }
        tailSpaces.back()[0] = headSpace[0];
        tailSpaces.back()[1] = headSpace[1];

        // Check to see if we ate ourself
        for (int i = 0; i < tailSpaces.size(); i++) {
            if (nextSpace[0] == tailSpaces[i][0] && nextSpace[1] == tailSpaces[i][1]) {
                alive = false;
            }
        }
    }

    headSpace[0] = nextSpace[0];
    headSpace[1] = nextSpace[1];

}


void MainWindow::DrawScene() {
    SnakeScene.clear();
    border.setCoords(0, 0, 601, 601);
    SnakeScene.addRect(border);

    // Draw the head
    Alex.head.setCoords(Alex.headSpace[0]*squareSize, Alex.headSpace[1]*squareSize, (Alex.headSpace[0]+1)*squareSize, (Alex.headSpace[1]+1)*squareSize);
    SnakeScene.addRect(Alex.head, Alex.headPen, Alex.headBrush);

    // Draw the tail
    for (int i = 0; i < Alex.tailSpaces.size(); i++) {
        Alex.tail[i].setCoords(Alex.tailSpaces[i][0]*squareSize, Alex.tailSpaces[i][1]*squareSize, (Alex.tailSpaces[i][0] + 1)*squareSize, (Alex.tailSpaces[i][1] + 1)*squareSize);
        SnakeScene.addRect(Alex.tail[i], Alex.tailPen, Alex.tailBrush);
    }

    if (twoPlayer) {
        // Draw the head
        Don.head.setCoords(Don.headSpace[0]*squareSize, Don.headSpace[1]*squareSize, (Don.headSpace[0]+1)*squareSize, (Don.headSpace[1]+1)*squareSize);
        SnakeScene.addRect(Don.head, Don.headPen, Don.headBrush);

        // Draw the tail
        for (int i = 0; i < Don.tailSpaces.size(); i++) {
            Don.tail[i].setCoords(Don.tailSpaces[i][0]*squareSize, Don.tailSpaces[i][1]*squareSize, (Don.tailSpaces[i][0] + 1)*squareSize, (Don.tailSpaces[i][1] + 1)*squareSize);
            SnakeScene.addRect(Don.tail[i], Don.tailPen, Don.tailBrush);
        }
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
        Alex.direction = 0;
        //direction = 0;
    }
    else if (event->key() == Qt::Key_D) {
        Alex.direction = 1;
        //direction = 1;
    }
    else if (event->key() == Qt::Key_S) {
        Alex.direction = 2;
        //direction = 2;
    }
    else if (event->key() == Qt::Key_A) {
        Alex.direction = 3;
        //direction = 3;
    }
    else if (event->key() == Qt::Key_I) {
        if (twoPlayer)
            Don.direction = 0;
        else
            Alex.direction = 0;
        //direction = 3;
    }
    else if (event->key() == Qt::Key_L) {
        if (twoPlayer)
            Don.direction = 1;
        else
            Alex.direction = 1;
        //direction = 3;
    }
    else if (event->key() == Qt::Key_K) {
        if (twoPlayer)
            Don.direction = 2;
        else
            Alex.direction = 2;
        //direction = 3;
    }
    else if (event->key() == Qt::Key_J) {
        if (twoPlayer)
            Don.direction = 3;
        else
            Alex.direction = 3;
        //direction = 3;
    }

}

void MainWindow::SetApplePosition() {
    appleSpace[0] = rand()%15;
    appleSpace[1] = rand()%15;
    qInfo() << "Setting apple pos";

    if (std::equal(Alex.headSpace, Alex.headSpace + 2, appleSpace)) {
        SetApplePosition();
    }
    else if (std::equal(Don.headSpace, Don.headSpace + 2, appleSpace) && twoPlayer) {
        SetApplePosition();
    }
    else {
//        for (int i = 0; i < tailSpaces1.size(); i++) {
//            if (tailSpaces1[i][0] == appleSpace[0] && tailSpaces1[i][1] == appleSpace[1]) {
//                SetApplePosition();
//                break;
//            }
//        }
        for (int i = 0; i < Alex.tailSpaces.size(); i++) {
            if (Alex.tailSpaces[i][0] == appleSpace[0] && Alex.tailSpaces[i][1] == appleSpace[1]) {
                SetApplePosition();
                break;
            }
        }
        if (twoPlayer) {
            for (int i = 0; i < Don.tailSpaces.size(); i++) {
                if (Don.tailSpaces[i][0] == appleSpace[0] && Don.tailSpaces[i][1] == appleSpace[1]) {
                    SetApplePosition();
                    break;
                }
            }
        }
    }
}

void MainWindow::EndGame() {
    timer->stop();
}
