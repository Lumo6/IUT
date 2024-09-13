#pragma once

#include <QtWidgets/QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QTimer>
#include "ui_TP.h"

class TP : public QWidget
{
    Q_OBJECT
signals:
    void NoMoreTime(bool);

public:
    TP(QWidget *parent = nullptr);
    ~TP();
    bool clicked = false;
private:
    Ui::TPClass ui;
    int remaining_time;
    QPushButton* but;
    QTimer* tim;
    

private slots:
    void click() {
        clicked = true;
    };
    void tic() {
        remaining_time--;
        if (remaining_time == 0)
            emit NoMoreTime(clicked);
        but->setText(QString("Cliquez-moi d'ici %1 secondes").arg(remaining_time));
    };
    void end() {
        tim->stop();
        but->setEnabled(false);
    };
public slots:
    void reset() {
        clicked = false;
        remaining_time = 6;
        tim->start(1000);
        but->setEnabled(true);
    };
};
