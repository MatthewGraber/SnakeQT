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
#include <QLCDNumber>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Snake {
public:
    int headSpace[2] = {7, 7};
    int nextSpace[2] = {7, 7};
    std::vector<std::vector<int>> tailSpaces;

    // 0 = UP, 1 = RIGHT, 2 = DOWN, 3 = LEFT
    int direction = 0;
    bool alive = true;

    QLCDNumber *score;

    QBrush headBrush;
    QBrush tailBrush;

    QPen headPen;
    QPen tailPen;

    QRectF head;
    std::vector<QRectF> tail;

    void Init();
    void Reset();
    void FindNext();
    void UpdatePos();
    void Grow();
    void DrawSelf();
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
   // void on_startBtn_clicked();
    void update();

protected:
    //bool eventFilter(QObject *obj, QEvent *event) override;

private:
    void DrawScene();
    void SetApplePosition();

    void StartGame();
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

    // MENU OPTIONS

    int period = 500;
    bool twoPlayer = true;

    // END MENU OPTIONS

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

    Snake Alex;
    Snake Don;

    QTimer *timer;
    QTimer *beginGame;
};
#endif // MAINWINDOW_H
