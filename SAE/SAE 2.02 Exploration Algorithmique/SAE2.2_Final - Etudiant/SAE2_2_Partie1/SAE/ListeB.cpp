#include "ListeB.h"
#include <iostream>


// attention 2 cas
void ListeB::ajoute_cellule_en_tete(const std::shared_ptr<CelluleB> cel) {
	if (_pListDeb == nullptr) {
		std::shared_ptr<CelluleB> cel1 = std::make_shared< CelluleB>(cel->_info);
		_pListFin = cel1;
		_pListDeb = cel1;
	}
	else {
		std::shared_ptr<CelluleB> cel1 = std::make_shared< CelluleB>(cel->_info);
		cel1->_pSuiv = _pListDeb;
		_pListDeb->_pPred = cel1;
		_pListDeb = cel1;
	}
}

void ListeB::ajoute_cellule_en_queue(const std::shared_ptr<CelluleB> cel) {
	std::shared_ptr<CelluleB> cel1 = std::make_shared< CelluleB>(cel->_info);
	_pListFin->_pSuiv = cel1;
	cel1->_pPred = _pListFin;
	_pListFin = cel1;

}

void ListeB::affiche_liste() const {
	std::shared_ptr<CelluleB> p = _pListDeb;
	while (p != nullptr) {
		std::cout << p->_info << " ";
		p = p->_pSuiv;
	}
	std::cout << std::endl;
}

void ListeB::affiche_liste_endroit() const {
	std::shared_ptr<CelluleB> p = _pListFin;
	while (p != nullptr) {
		std::cout << p->_info << " ";
		p = p->_pPred;
	}
	std::cout << std::endl;
}

int ListeB::nbelem() const {
	std::shared_ptr<CelluleB> p = _pListDeb;
	int nb = 0;
	while (p != nullptr) {
		nb += 1;
		p = p->_pSuiv;
	}
	return nb;
}


// renvoie le ptr vers cellule avec cle. Si cle absente renvoie null
std::shared_ptr<CelluleB> ListeB::recherche_ptr(int cle)const {
	std::shared_ptr<CelluleB> p = _pListDeb;
	if (!_pListDeb) return nullptr;  //liste vide
	else {
		while (p != nullptr && p->_info != cle) {
			p = p->_pSuiv;
		}
		if (p)
			return p;
		else return nullptr;
	}
}


void ListeB::supprime_cellule(int cle) {
	std::shared_ptr<CelluleB> p = recherche_ptr(cle);;

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


void ListeB::liberer_liste() {
	std::shared_ptr<CelluleB> p = _pListDeb;
	std::shared_ptr<CelluleB> p2 = _pListFin;
	while (p2->_pPred != nullptr) {
		p2 = p2->_pPred;
		if (p2 != nullptr) {
			p2->_pSuiv->_pPred = nullptr;
		}
	}
	while (_pListDeb != nullptr) {
		std::shared_ptr<CelluleB> p = _pListDeb;
		_pListDeb = _pListDeb->_pSuiv;
	}
}