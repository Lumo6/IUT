//Pour éviter les problèmes, ce fichier doit être enregistré au format UTF-8
//Grâce à ce commentaire qui contient des caractères accentués, c'est le cas
#pragma once
#include <cmath>
#include <iostream>
#include "DoubleApprox.h"
const long double pi = 4*std::atanl(1);

class CAngle {
private:
	double arrondi(double angle) const;
	CDoubleApprox m_daAngle=0;
public:
	CAngle() = default;
	CAngle(double d);
	double Rad() const;
	void SetRad(double);
	double Deg() const;
	void SetDeg(double);
	double Grad() const;
	void SetGrad(double);
	bool operator==(CAngle);
	bool operator!=(CAngle);
	CAngle operator+(CAngle);
	CAngle operator-(CAngle);
	double GetAngle();
};

bool operator==(double,CAngle);
bool operator!=(double,CAngle);
CAngle operator+(double,CAngle);
CAngle operator-(double, CAngle);
std::ostream& operator<<(std::ostream&, const CAngle&);
