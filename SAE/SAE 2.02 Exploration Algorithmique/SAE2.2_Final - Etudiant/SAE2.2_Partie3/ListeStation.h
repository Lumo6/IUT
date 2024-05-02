#pragma once
#include <memory>
#include "CelluleStation.h"

class ListeStation {
private:
	std::shared_ptr<CelluleStation> _pListDeb = nullptr;
	std::shared_ptr<CelluleStation> _pListFin = nullptr;
public:
	std::shared_ptr<CelluleStation> acces_tete() const{ return _pListDeb; }; // Complexite O(1)
	std::shared_ptr<CelluleStation> acces_queue() const { return _pListFin; }; // Complexite O(1)

	void ajoute_cellule_en_tete(const std::shared_ptr<CelluleStation> cel); // attention 2 cas // Complexite O(1)
	void affiche_liste()const; // Complexite O(n)  (n : nombre d'elements)
	void affiche_liste_endroit()const; //parcours depuis la queue // Complexite O(n)  (n : nombre d'elements)
	void liberer_liste(); // Complexite O(n)  (n : nombre d'elements)
	int nbelem() const; // Complexite O(n^2)  (n : nombre d'elements)
	std::shared_ptr<CelluleStation> recherche_ptr(int cle)const; // Complexite O(n)  (n : nombre d'elements)
	void supprime_cellule(int cle); // Complexite O(n)  (n : nombre d'elements)

};