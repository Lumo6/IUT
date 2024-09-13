#pragma once
#include <list>
#include "Employer.h"
#include "Etudiant.h"
#include "Personne.h"
#include <memory>
class Annuaire {
private:
	std::list<std::shared_ptr<Employe>> listemp;
	std::list< std::shared_ptr<Etudiant>> listetu;
public:
	void SetListEmploye(std::list<std::shared_ptr<Employe>>  n) { listemp = n; };
	std::list<std::shared_ptr<Employe>> GetListEmploye() { return listemp; };
	void AddEmploye(std::shared_ptr<Employe> n) { listemp.push_back(n); };
	void DelEmploye(std::shared_ptr<Employe> n) { listemp.remove(n); };

	void SetListEtu(std::list< std::shared_ptr<Etudiant>> n) { listetu = n; };
	std::list< std::shared_ptr<Etudiant>> GetListEtu() { return listetu; };
	void AddEtudiant(std::shared_ptr<Etudiant> n) { listetu.push_back(n); };
	void DelEmploye(std::shared_ptr<Etudiant> n) { listetu.remove(n); };

	std::list<std::shared_ptr<Employe>> RechercheEmploye(std::string, std::string);
	std::list< std::shared_ptr<Etudiant>> RechercheEtudiant(std::string, std::string);
};