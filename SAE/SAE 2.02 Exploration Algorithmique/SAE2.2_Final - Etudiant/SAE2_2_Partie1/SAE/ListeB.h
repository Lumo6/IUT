#pragma once
#include <memory>
#include "CelluleB.h"

class ListeB {
private:
	std::shared_ptr<CelluleB> _pListDeb = nullptr;
	std::shared_ptr<CelluleB> _pListFin = nullptr;
public:
	std::shared_ptr<CelluleB> acces_tete() { return _pListDeb; }; // Complexite O(1)
	std::shared_ptr<CelluleB> acces_queue() { return _pListFin; }; // Complexite O(1)

	void ajoute_cellule_en_tete(const std::shared_ptr<CelluleB> cel); // attention 2 cas // Complexite O(1)
	void ajoute_cellule_en_queue(const std::shared_ptr<CelluleB> cel); // Complexite O(n)  (n : nombre d'elements)
	void affiche_liste()const; // Complexite O(n)  (n : nombre d'elements)
	void affiche_liste_endroit()const; //parcours depuis la queue // Complexite O(n)  (n : nombre d'elements)
	void liberer_liste(); // Complexite O(n)  (n : nombre d'elements)
	int nbelem() const; // Complexite O(n^2)  (n : nombre d'elements)
	std::shared_ptr<CelluleB> recherche_ptr(int cle)const; // Complexite O(n)  (n : nombre d'elements)
	void supprime_cellule(int cle); // Complexite O(n)  (n : nombre d'elements)

};