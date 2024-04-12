#pragma once
#include <string>

class Personne {
protected:
	std::string nom;
	std::string prenom;
	std::string email;
public:
	Personne(std::string, std::string, std::string);
	std::string GetNom() { return nom; };
	std::string GetPrenom() { return prenom; };
	std::string GetEmail() { return email; };
	void SetNom(std::string n) { nom = n; };
	void SetPrenom(std::string n) {prenom = n;};
	void SetEmail(std::string n) { email = n; };
};