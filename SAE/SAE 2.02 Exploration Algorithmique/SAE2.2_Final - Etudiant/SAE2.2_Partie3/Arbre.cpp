#include "Arbre.h"
#include <iostream>

void Arbre::ajoute_cellule(const std::shared_ptr<CelluleArbre> cel) {

	std::shared_ptr<CelluleArbre> ptcel1 = std::make_shared<CelluleArbre>(cel->_deltaT, cel->_annee, cel->_tempMois, cel->_tSigmaMois);
	std::shared_ptr<CelluleArbre> p = _pArbre;
	bool nontrouve = true;
	if (p == nullptr) { nontrouve = false; _pArbre = ptcel1; }
	while (nontrouve) {
		if (ptcel1->_annee < p->_annee) {
			if (p->_pFilsG == nullptr) {
				nontrouve = false; p->_pFilsG = ptcel1;
			}
			else p = p->_pFilsG;
		}
		else {
			if (p->_pFilsD == nullptr) {
				nontrouve = false; p->_pFilsD = ptcel1;
			}
			else p = p->_pFilsD;

		}
	}
}



void Arbre::affiche_arbre_prefixe()const {
	if (_pArbre) {
		Arbre arbregauche(this->_pArbre->_pFilsG);
		Arbre arbredroit(this->_pArbre->_pFilsD);

		std::cout << _pArbre->_deltaT << " ";
		arbregauche.affiche_arbre_prefixe();
		arbredroit.affiche_arbre_prefixe();
	}
}


void Arbre::affiche_arbre_infixe()const {
	if (_pArbre) {
		Arbre arbregauche(this->_pArbre->_pFilsG);
		Arbre arbredroit(this->_pArbre->_pFilsD);

		arbregauche.affiche_arbre_infixe();
		std::cout << _pArbre->_deltaT << " ";
		arbredroit.affiche_arbre_infixe();
	}
}



void Arbre::affiche_arbre_postfixe()const {
	if (_pArbre) {
		Arbre arbregauche(this->_pArbre->_pFilsG);
		Arbre arbredroit(this->_pArbre->_pFilsD);

		arbregauche.affiche_arbre_postfixe();
		arbredroit.affiche_arbre_postfixe();
		std::cout << _pArbre->_deltaT << " ";

	}
}




float Arbre::max()const {
	if (!_pArbre) {
		std::cerr << "L'arbre est vide." << std::endl;
		return 0;
	}

	std::shared_ptr<CelluleArbre> p = _pArbre;
	while (p->_pFilsD) {
		p = p->_pFilsD;
	}
	return p->_deltaT;
}

float Arbre::min()const {
	if (!_pArbre) {
		std::cerr << "L'arbre est vide." << std::endl;
		return 0;
	}

	std::shared_ptr<CelluleArbre> p = _pArbre;
	while (p->_pFilsG) {
		p = p->_pFilsG;
	}
	return p->_deltaT;
}

int Arbre::hauteur()const {
	if (!_pArbre) {
		return -1;
	}

	int MaxD = Arbre(_pArbre->_pFilsD).hauteur();
	int MaxG = Arbre(_pArbre->_pFilsG).hauteur();

	if (MaxD < MaxG) {
		return MaxG + 1;
	}
	else
	{
		return MaxD + 1;
	}
}


int Arbre::nbelem() const {
	if (!_pArbre) {
		return 0;
	}

	int nbElementsGauche = Arbre(_pArbre->_pFilsG).nbelem();
	int nbElementsDroit = Arbre(_pArbre->_pFilsD).nbelem();

	return nbElementsGauche + nbElementsDroit + 1;
}


int Arbre::nbfeuille()const {
	int nbFD = 0;
	int nbFG = 0;
	if (!_pArbre) {
		return 0;
	}

	if (!_pArbre->_pFilsG && !_pArbre->_pFilsD) {
		return 1;
	}

	nbFD += Arbre(_pArbre->_pFilsD).nbfeuille();
	nbFG += Arbre(_pArbre->_pFilsG).nbfeuille();


	return nbFG + nbFD;
}


bool Arbre::non_degenere()const {
	if (_pArbre == nullptr) return false;
	else {
		// l'arbre est non degenere si au moins 1 noeud possede 2 fils
		if (_pArbre->_pFilsG != nullptr && _pArbre->_pFilsD != nullptr) return true;
		else {
			if (_pArbre->_pFilsG == nullptr) {
				Arbre arbredroit(this->_pArbre->_pFilsD);
				return arbredroit.non_degenere();
			}
			else { //_pArbre->_pFilsD == nullptr
				Arbre arbregauche(this->_pArbre->_pFilsG);
				return arbregauche.non_degenere();
			}
		}
	}
}


//On exploite dans la recherche le fait que l arbre soit un ABR
// Renvoie le pointeur sur la cellule contenant cle, nullptr si pas trouve
// Fonction importante
std::shared_ptr<CelluleArbre> Arbre::recherche_ptr(int cle)const {
	std::shared_ptr<CelluleArbre> p = _pArbre;
	bool nontrouve = true;
	if (p == nullptr) { nontrouve = false; p = nullptr; }
	while (nontrouve) {
		if (cle < p->_annee) {
			if (p->_pFilsG == nullptr) {
				nontrouve = false; p = nullptr;
			}
			else p = p->_pFilsG;
		}
		else {
			if (p->_pFilsD == nullptr) {
				nontrouve = false; p = nullptr;
			}
			else p = p->_pFilsD;
		}
	}
	return p;

}




void Arbre::supprime_cellule(int cle) {

	std::shared_ptr<CelluleArbre> p = _pArbre;
	std::shared_ptr<CelluleArbre> psauve = _pArbre;
	std::shared_ptr<CelluleArbre> pred = _pArbre;
	bool nontrouve = true;
	if (p != nullptr && p->_deltaT == cle) { //suppression en tete
		pred = p->_pFilsG; // pour rattachement
		if (p->_pFilsD != nullptr) {
			p = p->_pFilsD;
			while (p && p->_pFilsG)
				p = p->_pFilsG;
			p->_pFilsG = pred;
			_pArbre = _pArbre->_pFilsD;
		}
		else _pArbre = pred; // pas de sous arbre droit
		return;
	}

	bool filsdroit = true;;
	while (p != nullptr && nontrouve) {
		if (cle < p->_deltaT) {
			pred = p;
			filsdroit = false;
			p = p->_pFilsG;
		}
		else
			if (cle > p->_deltaT) {
				pred = p;
				filsdroit = true;
				p = p->_pFilsD;
			}
			else nontrouve = false;  // on a trouve
	}

	if (p && p->_pFilsG == nullptr && p->_pFilsD == nullptr) {  // si feuille
		if (filsdroit)
			pred->_pFilsD = nullptr;

		else pred->_pFilsG = nullptr;
	}
	else { //si pas feuille
		psauve = p;

		if (p && p->_pFilsD != nullptr) {
			p = p->_pFilsD;
			while (p && p->_pFilsG)
				p = p->_pFilsG;
			p->_pFilsG = psauve->_pFilsG;
			if (filsdroit)
				pred->_pFilsD = psauve->_pFilsD;
			else
				pred->_pFilsG = psauve->_pFilsD;
		}
		else
			if (pred && psauve)
				if (filsdroit)
					pred->_pFilsD = psauve->_pFilsG;
				else
					pred->_pFilsG = psauve->_pFilsG; // pas de sous arbre droit

	}
}




void Arbre::liberer_arbre() {
	if (_pArbre) {
		Arbre arbregauche(this->_pArbre->_pFilsG);
		Arbre arbredroit(this->_pArbre->_pFilsD);

		arbregauche.liberer_arbre();
		arbredroit.liberer_arbre();
		_pArbre = nullptr;
	}
}
