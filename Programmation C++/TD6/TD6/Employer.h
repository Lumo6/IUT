#pragma once
#include <string>
#include "Personne.h"
class Employe : public Personne {
private:
	statuts statut;
	size_t bureau;
public:
	statuts GetStatut() { return statut; };
	size_t GetBureau() { return bureau; };
	void SetStatus(statuts n) { statut = n; };
	void SetBureau(size_t n) { bureau = n; };
};

enum class statuts {
	secr�tariat,
	servicetech,
	serviceinf,
	enseignant,
	enseignantcherch,
	intervenantext
};