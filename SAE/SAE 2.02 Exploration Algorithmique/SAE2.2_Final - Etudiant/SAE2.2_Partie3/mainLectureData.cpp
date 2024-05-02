#include <iostream> // std::cout
#include "SAE_Datas_Heat.h"
#include "Traitement.h"

int main() {

    // Création de l'objet SAE_Datas_Heat
    SAE_Datas_Heat myStations;
    std::cout << "Etude sur " << myStations.nbMonths() << " mois " << "\n" << "\n";
    ListeStation lB = myStations.getListeStation();

    AfficherTout(lB);

    AfficherStatsStationAnnee(lB, 7761, 1995);
    AfficherStatsStationAnnee(lB, 7761, 2004);

    std::cout << MoyTempNAnneesStation(lB, 7761, 2004, 6)<<std::endl;

    std::vector<std::pair<float, float>> tab = DiffTempStationNAnnees(lB, 2004, 6);

    for (auto& pair : tab)
        std::cout << "station : " << pair.first << " temp : " << pair.second<<std::endl;

    

    for (int i = 1992; i < 2021; i++) {
        std::cout << std::endl << MoyTempAnneeStation(lB, i).first << "     " << MoyTempAnneeStation(lB, i).second;
    }

    std::cout << std::endl<< std::endl << AnneeMinTempNAnnee(lB, 1992, 20).first << "     " << AnneeMinTempNAnnee(lB, 1992, 20).second;

    return 0;
}

