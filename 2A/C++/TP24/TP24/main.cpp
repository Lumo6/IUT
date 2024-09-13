#include "TP.h"
#include "QController.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QController controller;

    return a.exec();
}
