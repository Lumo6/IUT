#include "DoubleApprox.h"
#include <cmath>
//Pour éviter les problèmes, ce fichier doit être enregistré au format UTF-8
//Grâce à ce commentaire qui contient des caractères accentués, c'est le cas.


bool CDoubleApprox::operator==(CDoubleApprox d)
{
	if (fabs(this->m_dVal - d.m_dVal) <= pow(10, -10))
		return true;
	else
		return false;
}

bool CDoubleApprox::operator!=(CDoubleApprox d)
{
	if (fabs(this->m_dVal - d.m_dVal) >= pow(10, -10))
		return true;
	else
		return false;
}

bool CDoubleApprox::operator>(CDoubleApprox d)
{
	if (this->m_dVal > d.m_dVal )
		return true;
	else 
		return false;
}

bool CDoubleApprox::operator<(CDoubleApprox d)
{
	if (this->m_dVal < d.m_dVal-pow(10,-10) )
		return true;
	else
		return false;
}

bool CDoubleApprox::operator<=(CDoubleApprox d)
{
	if (this->m_dVal <= d.m_dVal )
		return true;
	else
		return false;
}

bool CDoubleApprox::operator>=(CDoubleApprox d)
{
	if (this->m_dVal+ pow(10, -10) >= d.m_dVal)
		return true;
	else
		return false;
}

CDoubleApprox CDoubleApprox::operator-()
{
	CDoubleApprox temp{-this->m_dVal};
	return CDoubleApprox(temp);
}

CDoubleApprox CDoubleApprox::operator+()
{
	return CDoubleApprox(*this);
}

CDoubleApprox CDoubleApprox::operator*(CDoubleApprox d)
{
	return CDoubleApprox(this->m_dVal*d.m_dVal);
}

CDoubleApprox CDoubleApprox::operator+(CDoubleApprox d)
{
	return CDoubleApprox(this->m_dVal + d.m_dVal);
}

CDoubleApprox CDoubleApprox::operator-(CDoubleApprox d)
{
	return CDoubleApprox(this->m_dVal - d.m_dVal);
}

CDoubleApprox CDoubleApprox::operator/(CDoubleApprox d)
{
	if (d.m_dVal != 0)
		return CDoubleApprox(this->m_dVal / d.m_dVal);
	else
		return CDoubleApprox{0};
}

CDoubleApprox& CDoubleApprox::operator*=(CDoubleApprox d)
{
	this->m_dVal *= d.m_dVal;
	return(*this);
}

CDoubleApprox& CDoubleApprox::operator+=(CDoubleApprox d)
{
	this->m_dVal += d.m_dVal;
	return(*this);
}

CDoubleApprox& CDoubleApprox::operator-=(CDoubleApprox d)
{
	this->m_dVal -= d.m_dVal;
	return(*this);
}

CDoubleApprox& CDoubleApprox::operator/=(CDoubleApprox d)
{
	if (d.m_dVal != 0)
		this->m_dVal /= d.m_dVal;
	else
		this->m_dVal = 0;
	return(*this);
}

double CDoubleApprox::to_double() const
{
	return double(m_dVal);
}

double CDoubleApprox::GetDouble()
{
	return this->m_dVal;
}

CDoubleApprox operator+(double r, CDoubleApprox d)
{
	return CDoubleApprox(r)+d;
}

CDoubleApprox operator-(double r, CDoubleApprox d)
{
	return CDoubleApprox(r)-d;
}

CDoubleApprox operator*(double r, CDoubleApprox d)
{
	return CDoubleApprox(r)*d;
}

CDoubleApprox operator/(double r, CDoubleApprox d)
{
	return CDoubleApprox(r)/d;
}

bool operator==(double r, CDoubleApprox d)
{
	return CDoubleApprox(r) == d;
}

bool operator!=(double r, CDoubleApprox d)
{
	return CDoubleApprox(r) != d;
}

bool operator>(double r, CDoubleApprox d)
{
	return CDoubleApprox(r) > d;
}

bool operator<(double r, CDoubleApprox d)
{
	return CDoubleApprox(r) < d;
}

bool operator<=(double r, CDoubleApprox d)
{
	return CDoubleApprox(r) <= d;
}

bool operator>=(double r, CDoubleApprox d)
{
	return CDoubleApprox(r) >= d;
}

double& operator*=(double& r, CDoubleApprox d)
{
	return r *= d.to_double();
}

double& operator+=(double& r, CDoubleApprox d)
{
	return r += d.to_double();
}

double& operator-=(double& r, CDoubleApprox d)
{
	return r -= d.to_double();
}

double& operator/=(double& r, CDoubleApprox d)
{
	return r /= d.to_double();
}
