#include <math.h>
#include "angle.h"
#include <sstream>
#include <string>
//Pour éviter les problèmes, ce fichier doit être enregistré au format UTF-8
//Grâce à ce commentaire qui contient des caractères accentués, c'est le cas.

CAngle::CAngle(double d)
{
	SetRad(d);
}

double CAngle::Rad() const
{
	return m_daAngle.to_double()*pi;
}

void CAngle::SetRad(double d)
{
	d = fmod(d + pi, 2.0 * pi); 
	if (d < 0) d += 2.0 * pi;
	d -= pi;
	d /= pi;
	m_daAngle = d;
}

double CAngle::Deg() const
{
	return m_daAngle.to_double()*180;
}

void CAngle::SetDeg(double d)
{
	SetRad(d * pi / 180.0);
}

double CAngle::Grad() const
{
	return m_daAngle.to_double()*200;
}

void CAngle::SetGrad(double d)
{
	SetRad(d * pi / 200.0);;
}

bool CAngle::operator==(CAngle a)
{
	return this->m_daAngle==a.m_daAngle;
}

bool CAngle::operator!=(CAngle a)
{
	return this->m_daAngle != a.m_daAngle;
}

CAngle CAngle::operator+(CAngle a)
{
	return CAngle(m_daAngle.to_double() + a.m_daAngle.to_double());
}

CAngle CAngle::operator-(CAngle a)
{
	return CAngle(m_daAngle.to_double() - a.m_daAngle.to_double());
}

double CAngle::GetAngle()
{
	return m_daAngle.to_double();
}

bool operator==(double d, CAngle a)
{
	return CAngle(d) == a;
}

bool operator!=(double d, CAngle a)
{
	return CAngle(d) != a;
}

CAngle operator+(double d, CAngle a)
{
	return CAngle{d+a.GetAngle()};
}

CAngle operator-(double d, CAngle a)
{
	return CAngle{ d - (a.GetAngle()*180/pi) };
}

std::ostream& operator<<(std::ostream& out,const CAngle& a)
{
	out << a.Rad() << " (" << a.Deg() << "° / " << a.Grad() << " grad)";
	return out;
}
