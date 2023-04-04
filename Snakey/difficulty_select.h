#ifndef DIFFICULTY_SELECT_H
#define DIFFICULTY_SELECT_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class Difficulty_Select;
}

class Difficulty_Select : public QDialog
{
    Q_OBJECT

public:
    explicit Difficulty_Select(QWidget *parent = nullptr);
    ~Difficulty_Select();

private slots:
    void on_Spicy_Button_clicked();

    void on_Mid_Button_clicked();

    void on_Sweet_Button_clicked();

private:
    Ui::Difficulty_Select *ui;
};

#endif // DIFFICULTY_SELECT_H
