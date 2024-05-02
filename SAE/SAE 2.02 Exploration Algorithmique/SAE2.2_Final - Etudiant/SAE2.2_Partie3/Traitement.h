#pragma once

#include <iostream>

#include "CelluleStation.h"
#include "ListeStation.h"
#include "CelluleArbre.h"
#include "Arbre.h"
#include <vector>

float somme_deltaT(Arbre ab);

void AfficherTout(ListeStation& lB); // Compléxité O(n²)
void AfficherStatsStationAnnee(ListeStation& lB, int id, int annee); // Compléxité O(n²)

float GetTemp(std::shared_ptr<CelluleArbre> celluleA); // Compléxité O(1)
float GetSig(std::shared_ptr<CelluleArbre> celluleA); // Compléxité O(1)

float MoyTempNAnneesStation(ListeStation& lB, int id, int annee_depart, size_t nb_annee); // Compléxité O(n²)

float DiffTemp2AnneeStation(ListeStation& lB, int id, int annee_1, int annee_2); // Compléxité O(n²)

std::vector<std::pair<float, float>> DiffTempStationNAnnees(ListeStation& lB, int annee_1, size_t n); // Compléxité O(n²)

std::pair<int, float> MaxDiffTempStationNAnnees(ListeStation& lB, int annee, size_t n);// Compléxité O(n²)

std::pair<int, float> MinDiffTempStationNAnnees(ListeStation& lB, int annee, size_t n);

std::pair<int, float> MoyTempAnneeStation(ListeStation& lB, int annee);// Compléxité O(n²)

std::pair<int, float> AnneeMinTempNAnnee(ListeStation& lB, int annee, size_t n);// Compléxité O(n²)

std::pair<int, float> AnneeMaxTempNAnnee(ListeStation& lB, int annee, size_t n);// Compléxité O(n²)

