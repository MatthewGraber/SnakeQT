#ifndef DEATH_H
#define DEATH_H

#include <QDialog>

namespace Ui {
class Death;
}

class Death : public QDialog
{
    Q_OBJECT

public:
    explicit Death(QWidget *parent = nullptr);
    ~Death();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Death *ui;
};

#endif // DEATH_H
