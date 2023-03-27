#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QGraphicsScene>
#include <random>
#include <QTimer>
#include <QBrush>
#include <QPen>
#include <QKeyEvent>
#include <vector>
#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_startBtn_clicked();
    void update();



private:
    void DrawScene();
    void SetApplePosition();

    void EndGame();
    void keyPressEvent(QKeyEvent *);

    Ui::MainWindow *ui;
    QGraphicsScene SnakeScene;

    int headSpace1[2] = {7, 7};
    int nextSpace1[2] = {7, 7};
    int appleSpace[2];
    std::vector<std::vector<int>> tailSpaces1;

    const int squareSize = 40;
    const int gridSize = 15;

    QBrush headBrush;
    QBrush tailBrush;
    QBrush appleBrush;

    QPen headPen;
    QPen tailPen;
    QPen applePen;

    QRectF border;
    QRectF head;
    QRectF apple;
    std::vector<QRectF> tail;

    // 0 = UP, 1 = RIGHT, 2 = DOWN, 3 = LEFT
    int direction = 0;

    QTimer *timer;
    QTimer *beginGame;
};
#endif // MAINWINDOW_H
