#pragma once

#include <iostream>

#include "CelluleStation.h"
#include "ListeStation.h"
#include "CelluleArbre.h"
#include "Arbre.h"
#include <vector>

float somme_deltaT(Arbre ab);

void AfficherTout(ListeStation& ); // Compléxité O(n)
void AfficherStatsStationAnnee(ListeStation& , int , int ); // Compléxité O(n)

float GetTemp(std::shared_ptr<CelluleArbre> celluleA); // Compléxité O(1)
float GetSig(std::shared_ptr<CelluleArbre> celluleA); // Compléxité O(1)

float MoyTempNAnneesStation(ListeStation& ,int, int, size_t ); // Compléxité O(n)

float DiffTemp2AnneeStation(ListeStation& , int , int , int ); // Compléxité O(n)

std::vector<std::pair<float, float>> MoyTempStationNAnnees(ListeStation& , int , size_t ); // Compléxité O(n)

std::pair<int, float> MaxDiffTempStationNAnnees(ListeStation& , int , size_t);// Compléxité O(n)

std::pair<int, float> MinDiffTempStationNAnnees(ListeStation& , int , size_t );// Compléxité O(n)

std::pair<int, float> AnneeMinTempNAnnee(ListeStation&, int, size_t);// Compléxité O(n)

std::pair<int, float> AnneeMaxTempNAnnee(ListeStation&, int, size_t);// Compléxité O(n)

std::pair<int, float> MoyTempAnneeStation(ListeStation& , int annee);// Compléxité O(n)

struct SeasonStats {

    int stationID;
    int annee;
    std::string saison;
    float moyenneTemperature;
    float moyenneSigma;

    SeasonStats(int id, int an, std::string sai, float temp, float sigma) {
        stationID = id;
        annee = an;
        saison = sai;
        moyenneTemperature = temp;
        moyenneSigma = sigma;
    }

};
void AfficheStatsStationSaison(ListeStation& listeStations, int id, int annee);
std::vector<SeasonStats> GetStatsStationSaison(ListeStation& listeStations, int id, int annee);

struct DotAsDecimalSeparator : std::numpunct<char> {
    char do_decimal_point() const { return ','; }
};

std::ofstream& MoyTempAnneeCSV(std::ofstream& out, ListeStation& lB);

std::ofstream& MoyTempStationCSV(std::ofstream& out, ListeStation& lB, int id);

std::ofstream& DifTempPourTouteStationCSV(std::ofstream& out, ListeStation& lB, int annee_1, size_t n);
