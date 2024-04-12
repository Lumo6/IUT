#pragma once

#ifdef _WIN32
#define NOMINMAX
#include <Windows.h>
#endif

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Cmonth {
private:
	short year;
	short month;
	short day;
public:
	Cmonth(short);
	short getNum();
	short getNbdays();
	std::string toString();
};

class CYear {
private:
	short year;
	bool leap;
public: 
	CYear(unsigned short);
	short getNum();
	bool isLeap();
	std::string toString();
};

class CDate {
private:
	short day = 1;
	Cmonth InfMonth = 01;
	CYear InfYear = 1970;
public:
	CDate(short, short, short);
	short getday();
	Cmonth getmonth();
	CYear getyear();
	std::string toString();
};

class etudiant
{
private:
	std::string nom = "Sans nom";
	std::string prenom = "";
	CDate date;
public:
	void Affichertexte();
	bool verifnom(std::string);
	etudiant(std::string nom,
		std::string prenom,
		CDate date);
	std::string getnom();
};