#include "Liste.h"
#include <iostream>



void Liste::ajoute_cellule_en_tete(const std::shared_ptr<Cellule> cel) {
	std::shared_ptr<Cellule> cel1 = std::make_shared< Cellule>(cel->_info);
	cel1->_pSuiv=_pList;
	_pList = cel1;
	

}

void Liste::affiche_liste() const{
	std::shared_ptr<Cellule> p = _pList;
	while (p != nullptr) {
		std::cout << p->_info << " ";
		p = p->_pSuiv;
	}
	std::cout << std::endl;
}


void Liste::ajoute_cellule_en_queue(const std::shared_ptr<Cellule> cel) {
	std::shared_ptr<Cellule> p = _pList;
	while (p->_pSuiv != nullptr) {
		p = p->_pSuiv;
	}
	p->_pSuiv = cel;
}

int Liste::nbelem() const {
	std::shared_ptr<Cellule> p = _pList;
	int nb = 0;
	while (p != nullptr) {
		nb += 1;
		p = p->_pSuiv;
	}
	return nb;
}


// renvoie le ptr vers cellule avec cle, nullptr si cle absente
std::shared_ptr<Cellule> Liste::recherche_ptr(int cle)const {
	std::shared_ptr<Cellule> p = _pList;
	if (!_pList) return nullptr;  //liste vide
	else {
		while (p != nullptr && p->_info != cle) {
			p = p->_pSuiv;
		}
		if (p)
			return p;
		else return nullptr;
	}
}



// renvoie le ptr vers cellule avant la cellule avec cle. Si cle en 1ere cellule ou absente renvoie nullptr
std::shared_ptr<Cellule> Liste::recherche_ptr_avant_cle(int cle)const {
	std::shared_ptr<Cellule> pred = _pList;
	if (pred == nullptr || pred->_info == cle) return nullptr;
	while ( pred->_pSuiv!=nullptr && pred->_pSuiv->_info!=cle) {
		pred = pred->_pSuiv;
	}
	if (pred->_pSuiv && pred->_pSuiv->_info == cle)
		return pred;
	else return nullptr;
}


void Liste::supprime_cellule(int cle) {
	std::shared_ptr<Cellule> pred = recherche_ptr_avant_cle(cle);
	std::shared_ptr<Cellule> p;

	if (pred != nullptr) { // cas trouve et pas en tete de liste
		p = pred->_pSuiv;  // p pointe vers la cellule contenant cle donc p->_pSuiv existe
		pred->_pSuiv = p->_pSuiv;
	}
	else{

		if (_pList && _pList->_info==cle) { // suppression en tete de liste
			p = _pList;
			_pList = nullptr;
		}
		
	}

}


void Liste::liberer_liste() {
	std::shared_ptr<Cellule> p = _pList;
	while (_pList != nullptr) {
		std::shared_ptr<Cellule> p = _pList;
		_pList = _pList->_pSuiv;
	}
}