#pragma once
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <LibGraph2.h>
#include "Bouton.h"

class Donnee {
private:
	std::vector<std::pair<std::pair<unsigned int, unsigned int>,float>> infos;
public:
	Donnee() { RecupDonnee(); };
	void RecupDonnee();
	std::vector<std::pair<std::pair<unsigned int, unsigned int>, float>> GetInfos() { return infos; };
	std::vector<std::pair<unsigned int, float>> GetMoyenneAnnee();
	std::vector<std::pair<unsigned int, float>> GetAnnee(unsigned int);
};