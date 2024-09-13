#include "TP.h"
#include "QController.h"

TP::TP(QWidget *parent)
    : QWidget(parent)
{
    remaining_time = 6;
    ui.setupUi(this);
    but = new QPushButton(this);
    tim = new QTimer(this);

    QHBoxLayout* lay = new QHBoxLayout(this);
    lay->addWidget(but);
    setLayout(lay);

    QObject::connect(but, &QPushButton::clicked, this, &TP::click);
    QObject::connect(tim, &QTimer::timeout, this, &TP::tic);
    QObject::connect(this, &TP::NoMoreTime, this, &TP::end);
    tic();
    tim->start(1000);
}

TP::~TP()
{
}

