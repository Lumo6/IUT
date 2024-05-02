#pragma once

#include <memory>
#include "CelluleArbre.h"

class Arbre {
private:
	std::shared_ptr<CelluleArbre> _pArbre = nullptr;
public:
	Arbre() {
		_pArbre = nullptr;
	};

	Arbre(std::shared_ptr<CelluleArbre> ptr) {
		_pArbre = ptr;
	};

	std::shared_ptr<CelluleArbre> get_rac() { return _pArbre; }

	void ajoute_cellule(const std::shared_ptr<CelluleArbre> cel); // Complexite O(log(n))  (n : nombre d'elements)
	void affiche_arbre_prefixe()const; // Complexite O(n*log(n))  (n : nombre d'elements)
	void affiche_arbre_infixe()const; // Complexite O(n*log(n))  (n : nombre d'elements)
	void affiche_arbre_postfixe()const; // Complexite O(n*log(n))  (n : nombre d'elements)
	void liberer_arbre(); // Complexite O(n*log(n))  (n : nombre d'elements)
	int nbelem() const; // Complexite O(log(n))  (n : nombre d'elements)
	float max()const; // Complexite O(log(n))  (n : nombre d'elements)
	float min()const; // Complexite O(log(n))  (n : nombre d'elements)
	int hauteur()const; // Complexite O(log(n))  (n : nombre d'elements)
	int nbfeuille()const; // Complexite O(log(n))  (n : nombre d'elements)
	bool non_degenere()const; // Complexite O(n*log(n))  (n : nombre d'elements)
	std::shared_ptr<CelluleArbre> recherche_ptr(int cle)const; // Complexite O(log(n))  (n : nombre d'elements)
	void supprime_cellule(int cle); // Complexite O(log(n))  (n : nombre d'elements)

};