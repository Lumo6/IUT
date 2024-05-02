#include "Traitement.h"
#include <iomanip>
#include <fstream>

//exemple de fonction pour l exploitation de la structure arborescente
float somme_deltaT(Arbre ab) {

    if (ab.get_rac() == nullptr) return 0;
    else {
        Arbre arbregauche(ab.get_rac()->_pFilsG);
        Arbre arbredroit(ab.get_rac()->_pFilsD);

        return ab.get_rac()->_deltaT + somme_deltaT(arbregauche) + somme_deltaT(arbredroit); // parcours prefixe
    }
}

/* 
Fonction permettant d'afficher toutes les temp et sigma par mois pour chaque station pour chaque années
*/
void AfficherTout(ListeStation& lB)
{
    std::shared_ptr<CelluleStation> pS;
    std::shared_ptr<CelluleArbre> pA;

    for (pS = lB.acces_tete(); pS != nullptr; pS = pS->_pSuiv) {
        for (pA = pS->tab_arbres[0].get_rac(); pA != nullptr; pA = pA->_pFilsD) {
            AfficherStatsStationAnnee(lB, pS->_ID, pA->_annee);
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}

/*
Affiche les statisiques d'une station pour une année
*/
void AfficherStatsStationAnnee(ListeStation& lB, int id, int annee)
{
    std::shared_ptr<CelluleStation> pS = lB.recherche_ptr(id);
    std::shared_ptr<CelluleArbre> pA;

    std::cout << "Station Annee Mois Temperature Sigma" << std::endl;

    if (pS != nullptr) {
        for (size_t i = 0; i < pS->tab_arbres.size(); i++) {
            std::shared_ptr<CelluleArbre> pA = pS->tab_arbres[i].get_rac();
            while (pA != nullptr) {
                if (pA->_annee == annee) {
                    std::cout << std::setw(6) << pS->_ID << std::setw(7) << pA->_annee << std::setw(4) << i + 1 << std::setw(11) << pA->_tempMois << std::setw(8) << pA->_tSigmaMois << std::endl;
                }
                pA = pA->_pFilsD;
            }
        }
    }
}

/*
Donne la Température du mois d'une celluleA.
*/
float GetTemp(std::shared_ptr<CelluleArbre> celluleA)
{
    return celluleA->_tempMois;
}

/*
Donne le Sigma du mois d'une celluleA.
*/
float GetSig(std::shared_ptr<CelluleArbre> celluleA) {
    return celluleA->_tSigmaMois;
}

/*
Renvoit la moyenne des températures de n années depuis une année donnée.
*/
float MoyTempNAnneesStation(ListeStation& lB, int id, int annee_depart, size_t nb)
{
    size_t annee_fin = annee_depart + nb;
    if (annee_fin > 2021) {
        std::cout << "Dommage, pas assez de données !" << std::endl;
        return 0.0;
    }

    std::shared_ptr<CelluleStation> station = lB.recherche_ptr(id);
    if (station == nullptr) {
        std::cout << "Pas de station existante avec l'id : " << id << std::endl;
        return 0.0;
    }

    float moy = 0;

    std::shared_ptr<CelluleArbre> pA = station->tab_arbres[0].get_rac();
    while (pA->_annee != annee_depart) {
        pA = pA->_pFilsD;
    }

    for (int annee = annee_depart; annee < annee_fin; annee++) {
        for (size_t mois = 0; mois < station->tab_arbres.size(); mois++) {
            pA = station->tab_arbres[mois].get_rac();
            while (pA != nullptr) {
                if (pA->_annee == annee) {
                    moy += pA->_tempMois;
                }
                pA = pA->_pFilsD;
            }
        }
    }

    moy /= (nb * 12);

    return moy;
}

/*
Renvoit la différence de température d'une station entre 2 années
*/
float DiffTemp2AnneeStation(ListeStation& lB, int id, int annee_1, int annee_2)
{
    return (MoyTempNAnneesStation(lB, id, annee_1, 1) - MoyTempNAnneesStation(lB, id, annee_2, 1));
}


/*
Renvoit un vecteur contennant la différence de température d'une station sur N années
*/
std::vector<std::pair<float, float>> MoyTempStationNAnnees(ListeStation& lB, int annee_1, size_t n)
{
    std::vector<std::pair<float, float>> vec;
    std::pair<float, float> pair;

    std::shared_ptr<CelluleStation> station = lB.acces_tete();
    while (station != nullptr) {
        pair.first = station->_ID;
        pair.second = MoyTempNAnneesStation(lB, station->_ID, annee_1, n);
        vec.push_back(pair);
        station = station->_pSuiv;
    }
    return vec;
}

/*
Renvoit un vecteur contennant la différence de température d'une station sur N années
*/
std::pair<int, float> MaxDiffTempStationNAnnees(ListeStation& lB, int annee, size_t n) {

    std::vector<std::pair<float, float>> vec = MoyTempStationNAnnees(lB, annee, n);

    std::pair<int, float> pair_max;
    for (auto& pair : vec) {
        if (pair_max.second < pair.second)
            pair_max = pair;
    }

    return pair_max;
}

/*
Renvoit une pair contennant la différence maximale de température d'une station sur N années
*/
std::pair<int, float> MinDiffTempStationNAnnees(ListeStation& lB, int annee, size_t n) {

    std::vector<std::pair<float, float>> vec = MoyTempStationNAnnees(lB, annee, n);

    std::pair<int, float> pair_max = vec[0];
    for (auto& pair : vec) {
        if (pair_max.second > pair.second)
            pair_max = pair;
    }

    return pair_max;
}

/*
Renvoit une pair contennant la différence minimum de température d'une station sur N années
*/
std::pair<int, float> AnneeMinTempNAnnee(ListeStation& lB, int annee, size_t n) {
    std::pair<int, float> ann_min = MoyTempAnneeStation(lB, annee);
    std::pair<int, float> temp;
    for (int i = 1; i < n; i++) {
        temp = MoyTempAnneeStation(lB, annee + i);
        if (temp.second < ann_min.second)
            ann_min = temp;

    }
    return ann_min;
}

/*
Renvoit une pair contennant la température minimum d'une station sur N années
*/
std::pair<int, float> AnneeMaxTempNAnnee(ListeStation& lB, int annee, size_t n) {
    std::pair<int, float> ann_max = MoyTempAnneeStation(lB, annee);
    std::pair<int, float> temp;
    for (size_t i = 1; i < n; i++) {
        temp = MoyTempAnneeStation(lB, annee + i);
        if (temp.second > ann_max.second)
            ann_max = temp;

    }
    return ann_max;
}

/*
Renvoit une pair contennant la température maximum d'une station sur N années
*/
std::pair<int, float> MoyTempAnneeStation(ListeStation& lB, int annee) {
    
    std::pair<int, float> pair_moy;
    float moy = 0.0;
    
    std::shared_ptr<CelluleStation> S = lB.acces_tete();
    while (S != nullptr) {
        moy += MoyTempNAnneesStation(lB, S->_ID,annee, 1);
        S = S->_pSuiv;
    }

    pair_moy.first = annee;
    pair_moy.second = moy/lB.nbelem();

    return pair_moy;
}

/*
Affiche toutes les Stats des stations par saisons
*/
void AfficheStatsStationSaison(ListeStation& listeStations, int id, int annee) {
    std::shared_ptr<CelluleStation> pStation = listeStations.recherche_ptr(id);
    std::string saison;



    if (pStation != nullptr) {
        std::cout << std::setw(6) << "Station" << std::setw(7) << "Annee" << std::setw(10) << "Saison" << std::setw(10) << "Temperature" << std::setw(10) << "Sigma" << std::endl;

        for (int i = 0; i < 4; i++) {
            std::shared_ptr<CelluleArbre> pA = pStation->tab_arbres[(i * 3)].get_rac();
            std::shared_ptr<CelluleArbre> pA2 = pStation->tab_arbres[(i * 3) + 1].get_rac();
            std::shared_ptr<CelluleArbre> pA3 = pStation->tab_arbres[(i * 3) + 2].get_rac();


            while (pA != nullptr && pA2 != nullptr && pA3 != nullptr) {
                if (pA->_annee == annee) {
                    switch (i) {
                    case 0:
                        saison = "Printemps";
                        break;
                    case 1:
                        saison = "Ete";
                        break;
                    case 2:
                        saison = "Automne";
                        break;
                    case 3:
                        saison = "Hiver";
                        break;
                    }
                    float moyenneSigma = 0;
                    float moyenneTemp = (pA->_tempMois + pA2->_tempMois + pA3->_tempMois) / 3;
                    if (pA->_annee != 1992)
                        moyenneSigma = (pA->_tSigmaMois + pA2->_tSigmaMois + pA3->_tSigmaMois) / 3;

                    std::cout << std::setw(6) << pStation->_ID << std::setw(7) << pA->_annee << std::setw(10) << saison << std::setw(11) << moyenneTemp << std::setw(11) << moyenneSigma << std::endl;
                }
                pA = pA->_pFilsD;
                pA2 = pA2->_pFilsD;
                pA3 = pA3->_pFilsD;
            }
        }
    }
}

/*
Renvoit toutes les Stats des stations par saisons
*/
std::vector<SeasonStats> GetStatsStationSaison(ListeStation& listeStations, int id, int annee) {
    std::vector<SeasonStats> stats;
    std::shared_ptr<CelluleStation> pStation = listeStations.recherche_ptr(id);
    std::string saison;


    if (pStation != nullptr) {

        for (int i = 0; i < 4; i++) {
            std::shared_ptr<CelluleArbre> pA = pStation->tab_arbres[(i * 3)].get_rac();
            std::shared_ptr<CelluleArbre> pA2 = pStation->tab_arbres[(i * 3) + 1].get_rac();
            std::shared_ptr<CelluleArbre> pA3 = pStation->tab_arbres[(i * 3) + 2].get_rac();



            while (pA != nullptr && pA2 != nullptr && pA3 != nullptr) {
                if (pA->_annee == annee) {
                    switch (i) {
                    case 0:
                        saison = "Printemps";
                        break;
                    case 1:
                        saison = "Ete";
                        break;
                    case 2:
                        saison = "Automne";
                        break;
                    case 3:
                        saison = "Hiver";
                        break;
                    }
                    float moyenneSigma = 0;
                    float moyenneTemp = (pA->_tempMois + pA2->_tempMois + pA3->_tempMois) / 3;
                    if (pA->_annee != 1992)
                        moyenneSigma = (pA->_tSigmaMois + pA2->_tSigmaMois + pA3->_tSigmaMois) / 3;
                    stats.push_back(SeasonStats(pStation->_ID, pA->_annee, saison, moyenneTemp, moyenneSigma));
                }
                pA = pA->_pFilsD;
                pA2 = pA2->_pFilsD;
                pA3 = pA3->_pFilsD;
            }
        }
    }

    return stats;
}

/*
Faire un fichier CSV dans lequel est stocker les moyennes des temperatures des annees
*/
std::ofstream& MoyTempAnneeCSV(std::ofstream& out, ListeStation& lB) {
    std::shared_ptr<CelluleStation> station = lB.acces_queue();
    std::shared_ptr<CelluleArbre> arbre = station->tab_arbres[0].get_rac();
    std::pair<int, float> at;

    std::locale customLocale(std::locale(), new DotAsDecimalSeparator);
    out.imbue(customLocale);


    while (arbre) {
        at = MoyTempAnneeStation(lB, arbre->_annee);
        out << at.first << ";" << at.second << std::endl;
        arbre = arbre->_pFilsD;
    }

    return out;
}


/*
Faire un fichier CSV dans lequel est stocker les différences des temperatures d'une station pour chaque annees
*/
std::ofstream& MoyTempStationCSV(std::ofstream& out, ListeStation& lB, int id) {
    std::shared_ptr<CelluleStation> station = lB.recherche_ptr(id);
    std::shared_ptr<CelluleArbre> arbre = station->tab_arbres[0].get_rac();

    std::locale customLocale(std::locale(), new DotAsDecimalSeparator);
    out.imbue(customLocale);

    out << "Station;" << station->_ID << std::endl;
    while (arbre) {
        float temp = MoyTempNAnneesStation(lB, station->_ID, arbre->_annee, 1);
        out << arbre->_annee << ";" << temp << std::endl;
        arbre = arbre->_pFilsD;
    }

    return out;
}

/*
Faire un fichier CSV dans lequel est stocker les différences des temperatures d'une station pour chaque annees
*/
std::ofstream& DifTempPourTouteStationCSV(std::ofstream& out, ListeStation& lB, int annee_1, size_t n) {
    std::vector<std::pair<float, float>> tab = MoyTempStationNAnnees(lB, annee_1, n);

    std::locale customLocale(std::locale(), new DotAsDecimalSeparator);
    out.imbue(customLocale);

    for (auto& pair : tab)
        out << pair.first << ";" << pair.second << std::endl;

    return out;
}