#include "ListeStation.h"

#include <iostream>



// Cette fonction est un peu a modifier par rapport a la partie 1 car il y a un tableau maintenant en plus
void ListeStation::ajoute_cellule_en_tete(const std::shared_ptr<CelluleStation> cel) {
	if (_pListDeb == nullptr) {
		std::shared_ptr<CelluleStation> cel1 = std::make_shared< CelluleStation>(cel->_ID);
		cel1->tab_arbres = cel->tab_arbres;
		_pListFin = cel1;
		_pListDeb = cel1;
	}
	else {
		std::shared_ptr<CelluleStation> cel1 = std::make_shared< CelluleStation>(cel->_ID);
		cel1->tab_arbres = cel->tab_arbres;
		cel1->_pSuiv = _pListDeb;
		_pListDeb->_pPred = cel1;
		_pListDeb = cel1;
	}
}

void ListeStation::affiche_liste() const {
	std::shared_ptr<CelluleStation> p = _pListDeb;
	while (p != nullptr) {
		std::cout << p->_ID << " ";
		p = p->_pSuiv;
	}
	std::cout << std::endl;
}

void ListeStation::affiche_liste_endroit() const {
	std::shared_ptr<CelluleStation> p = _pListFin;
	while (p != nullptr) {
		std::cout << p->_ID << " ";
		p = p->_pPred;
	}
	std::cout << std::endl;
}




int ListeStation::nbelem() const {
	std::shared_ptr<CelluleStation> p = _pListDeb;
	int nb = 0;
	while (p != nullptr) {
		nb += 1;
		p = p->_pSuiv;
	}
	return nb;
}


// renvoie le ptr vers cellule avec cle. Si cle absente renvoie null
std::shared_ptr<CelluleStation> ListeStation::recherche_ptr(int cle)const {

	std::shared_ptr<CelluleStation> p = _pListDeb;
	while (p != nullptr) {
		if (p->_ID == cle)
			return p;
		p = p->_pSuiv;
	}
	return nullptr;
}


void ListeStation::supprime_cellule(int cle) {
	std::shared_ptr<CelluleStation> p = recherche_ptr(cle);;

	if (p->_pPred != nullptr) {
		if (p->_pSuiv != nullptr) { // cas trouve et pas en tete ou en queue de liste
			p->_pPred->_pSuiv = p->_pSuiv;
			p->_pSuiv->_pPred = p->_pPred;
		}
		else // Suppression en queue de liste
		{
			p->_pPred->_pSuiv = nullptr;
			_pListFin = p->_pPred;
		}
	}
	else {

		if (p->_pSuiv != nullptr) { // suppression en tete de liste
			p->_pSuiv->_pPred = nullptr;
			_pListDeb = p->_pSuiv;
		}
		else
		{
			_pListDeb = nullptr;
			_pListFin = nullptr;
		}
	}
}


void ListeStation::liberer_liste() {
	std::shared_ptr<CelluleStation> p = _pListDeb;
	std::shared_ptr<CelluleStation> p2 = _pListFin;
	while (p2->_pPred != nullptr) {
		p2 = p2->_pPred;
		if (p2 != nullptr) {
			p2->_pSuiv->_pPred = nullptr;
		}
	}
	while (_pListDeb != nullptr) {
		std::shared_ptr<CelluleStation> p = _pListDeb;
		_pListDeb = _pListDeb->_pSuiv;
	}
}

