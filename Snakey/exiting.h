#ifndef EXITING_H
#define EXITING_H

#include <QDialog>

namespace Ui {
class Exiting;
}

class Exiting : public QDialog
{
    Q_OBJECT

public:
    explicit Exiting(QWidget *parent = nullptr);
    ~Exiting();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Exiting *ui;
};

#endif // EXITING_H
