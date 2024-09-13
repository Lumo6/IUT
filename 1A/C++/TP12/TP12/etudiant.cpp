#include "etudiant.h"

void etudiant::Affichertexte()
{
	std::cout << "Nom : " << nom <<std::endl<< "Prénom : " << prenom << std::endl << "Date de naissance : " << date.toString() <<std::endl;
}

etudiant::etudiant(std::string nom = "Sans Nom", std::string prenom = "", CDate date = {1,01,1970}) :nom(nom), prenom(prenom), date(date)
{
}

std::string etudiant::getnom()
{
	return nom;
}

bool etudiant::verifnom(std::string Vnom)
{
	if (nom == Vnom) {
		return true;
	}
	else {
		return false;
	}
}

Cmonth::Cmonth(short nb)
{	
	if (nb > 12) {
		month = 12;
	}
	else if (nb < 1) {
		month = 1;
	}
	else month = nb;
}

short Cmonth::getNum()
{
	return month;
}

short Cmonth::getNbdays()
{
	switch (getNum()) {
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12: {
		return 31;
		break;
	}
	case 2: {
		return 29;
		break;
	}
	default: {
		return 30;
		break;
	}
	}
}

std::string Cmonth::toString()
{
	std::string mois;
	switch (month) {
	case 1: {
		return "janvier";
		break;
	}
	case 2: {
		return "février";
		break;
	}
	case 3: {
		return "mars";
		break;
	}
	case 4: {
		return "avril";
		break;
	}
	case 5: {
		return "mai";
		break;
	}
	case 6: {
		return "juin";
		break;
	}
	case 7: {
		return "juillet";
		break;
	}
	case 8: {
		return "août";
		break;
	}
	case 9: {
		return "septembre";
		break;
	}
	case 10: {
		return "octobre";
		break;
	}
	case 11: {
		return "novembre";
		break;
	}
	default :{
		return "decembre";
		break;
	}
	}
}

CYear::CYear(unsigned short annee):year(annee)
{
	leap = ((year & 3) == 0) && (((year % 100) != 0) || ((year % 400) == 0));
}

short CYear::getNum()
{
	return year;
}

bool CYear::isLeap()
{
	return leap;
}

std::string CYear::toString()
{
	return std::to_string(year);
}

CDate::CDate(short j , short m , short a):InfMonth(m),InfYear(a)
{
	if (InfYear.isLeap()) {
		if (j < 1) {
			day = 1;
		}
		else if (j > InfMonth.getNbdays()) {
			day = InfMonth.getNbdays();
		}
		else {
			day = j;
		}
	}
	else {
		if (InfMonth.getNum() == 2) {
			if (j < 1) {
				day = 1;
			}
			else if (j > InfMonth.getNbdays()-1) {
				day = InfMonth.getNbdays()-1;
			}
			else {
				day = j;
			}
		}
		else {
			if (j < 1) {
				day = 1;
			}
			else if (j > InfMonth.getNbdays()) {
				day = InfMonth.getNbdays();
			}
			else {
				day = j;
			}
		}
	}
}

short CDate::getday()
{
	return InfMonth.getNbdays();
}

Cmonth CDate::getmonth()
{
	return InfMonth;
}

CYear CDate::getyear()
{
	return InfYear;
}

std::string CDate::toString()
{
	return std::to_string(day) + '/' + InfMonth.toString() + '/' + InfYear.toString();
}
