#pragma once

#include <QObject>
#include "TP.h"

class QController  : public QObject
{
	Q_OBJECT
signals:
	void restart();
public:
	QController(QObject *parent = nullptr);
	~QController();
	TP* tp;
public slots:
	void end(bool clicked) {
		QMessageBox::StandardButton ans = QMessageBox::question(nullptr,
			"Résultat",
			QString("Vous avez %1.\nVoulez vous rejouer ?")
			.arg(clicked ? "gagné" : "perdu"));
		if (ans == QMessageBox::Yes)
		{
			emit restart();
		}
		else
		{
			delete tp;
		}
	};
};
