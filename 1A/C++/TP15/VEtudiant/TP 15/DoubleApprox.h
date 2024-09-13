//Pour éviter les problèmes, ce fichier doit être enregistré au format UTF-8
//Grâce à ce commentaire qui contient des caractères accentués, c'est le cas.
#pragma once
class CDoubleApprox {
private:
	double m_dVal;
public:
	CDoubleApprox(double d) { m_dVal = d; };
	bool operator==(CDoubleApprox);
	bool operator!=(CDoubleApprox);
	bool operator>(CDoubleApprox);
	bool operator<(CDoubleApprox);
	bool operator<=(CDoubleApprox);
	bool operator>=(CDoubleApprox);
	CDoubleApprox operator-();
	CDoubleApprox operator+();
	CDoubleApprox operator*(CDoubleApprox);
	CDoubleApprox operator+(CDoubleApprox);
	CDoubleApprox operator-(CDoubleApprox);
	CDoubleApprox operator/(CDoubleApprox);
	CDoubleApprox& operator*=(CDoubleApprox);
	CDoubleApprox& operator+=(CDoubleApprox);
	CDoubleApprox& operator-=(CDoubleApprox);
	CDoubleApprox& operator/=(CDoubleApprox);
	double to_double() const;
	double GetDouble();
};

CDoubleApprox operator+(double, CDoubleApprox);
CDoubleApprox operator-(double, CDoubleApprox);
CDoubleApprox operator*(double, CDoubleApprox);
CDoubleApprox operator/(double, CDoubleApprox);
bool operator==(double, CDoubleApprox);
bool operator!=(double, CDoubleApprox);
bool operator>(double, CDoubleApprox);
bool operator<(double, CDoubleApprox);
bool operator<=(double, CDoubleApprox);
bool operator>=(double, CDoubleApprox);
double& operator*=(double&,CDoubleApprox);
double& operator+=(double&,CDoubleApprox);
double& operator-=(double&,CDoubleApprox);
double& operator/=(double&,CDoubleApprox);

inline CDoubleApprox operator ""_da(long double val) { return CDoubleApprox((double)val); }
inline CDoubleApprox operator ""_da(unsigned long long val) { return CDoubleApprox((double)val); }