#ifndef SNAKEWINDOW_H
#define SNAKEWINDOW_H

#include <QWidget>
#include <QGraphicsScene>
#include <random>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class SnakeWindow; }
QT_END_NAMESPACE

class SnakeWindow : public QWidget
{
    Q_OBJECT

public:
    SnakeWindow(QWidget *parent = nullptr);
    ~SnakeWindow();

private slots:
    void update();

private:
    void DrawScene();

    Ui::SnakeWindow *ui;
    QGraphicsScene SnakeScene;

    // 0 = empty, 1 = snakehead, 2 = snakeTail, 3 = apple
    int spaces[15][15];
    const int squareSize = 40;

    QRectF head;
    QRectF apple;
    std::vector<QRectF> tail;

    QTimer *timer;
};
#endif // SNAKEWINDOW_H
