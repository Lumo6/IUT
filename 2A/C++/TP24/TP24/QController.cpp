#include "QController.h"

QController::QController(QObject *parent)
	: QObject(parent)
{
	tp = new TP();

	QObject::connect(tp, &TP::NoMoreTime, this, &QController::end);
	QObject::connect(this, &QController::restart, tp, &TP::reset);

	tp->show();
}

QController::~QController()
{}
