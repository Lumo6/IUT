#pragma once
#include "Personne.h"
class Etudiant : public Personne {
private:
	size_t semestre;
	size_t td_gr;
	size_t tp_gr;
public:
	size_t GetSemestre() { return semestre; };
	size_t GetTD() { return td_gr; };
	size_t GetTP() { return tp_gr; };
	void SetSemestre(size_t n) { semestre = n; };
	void SetTD(size_t n) { td_gr = n; };
	void SetTP(size_t n) { tp_gr = n; };
};