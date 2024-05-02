#pragma once

#include <iostream>

#include "CelluleStation.h"
#include "ListeStation.h"
#include "CelluleArbre.h"
#include "Arbre.h"
#include <vector>

float somme_deltaT(Arbre ab);

void AfficherTout(ListeStation& lB); // Compl�xit� O(n�)
void AfficherStatsStationAnnee(ListeStation& lB, int id, int annee); // Compl�xit� O(n�)

float GetTemp(std::shared_ptr<CelluleArbre> celluleA); // Compl�xit� O(1)
float GetSig(std::shared_ptr<CelluleArbre> celluleA); // Compl�xit� O(1)

float MoyTempNAnneesStation(ListeStation& lB, int id, int annee_depart, size_t nb_annee); // Compl�xit� O(n�)

float DiffTemp2AnneeStation(ListeStation& lB, int id, int annee_1, int annee_2); // Compl�xit� O(n�)

std::vector<std::pair<float, float>> DiffTempStationNAnnees(ListeStation& lB, int annee_1, size_t n); // Compl�xit� O(n�)

std::pair<int, float> MaxDiffTempStationNAnnees(ListeStation& lB, int annee, size_t n);// Compl�xit� O(n�)

std::pair<int, float> MinDiffTempStationNAnnees(ListeStation& lB, int annee, size_t n);

std::pair<int, float> MoyTempAnneeStation(ListeStation& lB, int annee);// Compl�xit� O(n�)

std::pair<int, float> AnneeMinTempNAnnee(ListeStation& lB, int annee, size_t n);// Compl�xit� O(n�)

std::pair<int, float> AnneeMaxTempNAnnee(ListeStation& lB, int annee, size_t n);// Compl�xit� O(n�)

