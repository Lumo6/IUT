#pragma once
#include <memory>
#include "Cellule.h"

class Liste {
private :
	std::shared_ptr<Cellule> _pList=nullptr;
public :
	std::shared_ptr<Cellule> acces_plist() { return _pList; };

	void ajoute_cellule_en_tete(const std::shared_ptr<Cellule> cel); // Complexite O(1)
	void affiche_liste()const;  // Complexite O(n)  (n : nombre d'elements)

	void ajoute_cellule_en_queue(const std::shared_ptr<Cellule> cel); // Complexite O(n)  (n : nombre d'elements)
	int nbelem() const; // Complexite O(n^2)  (n : nombre d'elements)

	//recherche du pointeur vers la Cellule contenant cle 
	std::shared_ptr<Cellule> recherche_ptr(int cle)const; // Complexite O(n)  (n : nombre d'elements)

	//recherche du pointeur vers la Cellule avant la Cellule contenant cle (utile pour la suppression pour chainage)
	std::shared_ptr<Cellule> recherche_ptr_avant_cle(int cle)const; // Complexite O(n)  (n : nombre d'elements)
	void supprime_cellule(int cle); // Complexite O(n)  (n : nombre d'elements)

	void liberer_liste();  //vide la liste // Complexite O(n)  (n : nombre d'elements)

};
