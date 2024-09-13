#pragma once
#include <iostream>
#include <string>

class etudiant {
private:
	std::string nom="SansNom";
	std::string prenom="SansPrenom";
public:
	etudiant(std::string,std::string);
	//etudiant(std::string);
	etudiant() = default;
	void SetNom(std::string N) {
		nom = N;
	}
	void SetPrenom(std::string P) {
		prenom = P;
	}
	std::string GetNom() {
		return nom;
	}
	std::string GetPrenom() {
		return prenom;
	}
};