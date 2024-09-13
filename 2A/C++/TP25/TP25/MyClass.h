#pragma once

#include <QtWidgets/QWidget>
#include "ui_MyClass.h"

class MyClass : public QWidget
{
    Q_OBJECT

public:
    MyClass(QWidget *parent = nullptr);
    ~MyClass();

private:
    Ui::MyClassClass ui;
};
