#include "Traitement.h"
#include <iomanip>

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
    std::shared_ptr<CelluleStation> pStation;
    std::shared_ptr<CelluleArbre> pArbre;

    for (pStation = lB.acces_tete(); pStation != nullptr; pStation = pStation->_pSuiv) {
        for (pArbre = pStation->tab_arbres[0].get_rac(); pArbre != nullptr; pArbre = pArbre->_pFilsD) {
            AfficherStatsStationAnnee(lB, pStation->_ID, pArbre->_annee);
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}

/*
* Cette fonction permet d'afficher toutes les statistiques d'une station pour une année donnée
* Elle prend en paramètre une ListeStation en référence, un id de station et une année
*/
void AfficherStatsStationAnnee(ListeStation& lB, int id, int annee)
{
    std::shared_ptr<CelluleStation> pStation = lB.recherche_ptr(id);
    std::shared_ptr<CelluleArbre> pArbre;

    std::cout << "Station Annee Mois Temperature Sigma" << std::endl;

    if (pStation != nullptr) {
        for (size_t i = 0; i < pStation->tab_arbres.size(); i++) {
            std::shared_ptr<CelluleArbre> pArbre = pStation->tab_arbres[i].get_rac();
            while (pArbre != nullptr) {
                if (pArbre->_annee == annee) {
                    std::cout << std::setw(6) << pStation->_ID << std::setw(7) << pArbre->_annee << std::setw(4) << i + 1 << std::setw(11) << pArbre->_tempMois << std::setw(8) << pArbre->_tSigmaMois << std::endl;
                }
                pArbre = pArbre->_pFilsD;
            }
        }
    }
}

/*
* Cette fonction renvoie la température du mois de la celluleA mis en paramètre
* Elle renvoie un int
*/
float GetTemp(std::shared_ptr<CelluleArbre> celluleA)
{
    return celluleA->_tempMois;
}

/*
* Cette fonction renvoie le sigma du mois de la celluleA mis en paramètre
* Elle renvoie un float
*/
float GetSig(std::shared_ptr<CelluleArbre> celluleA) {
    return celluleA->_tSigmaMois;
}

/*
* Cette fonction permet de calculer la température moyenne de n années en partant d'une certaine année
* Elle prend en paramètre une ListeStation en référence, un id de station, un int qui est l'année de départ et un size_t qui est le nombre d'année souhaité
* Elle renvoie un float
*/
float MoyTempNAnneesStation(ListeStation& lB, int id, int annee_depart, size_t nb_annee)
{
    size_t annee_fin = annee_depart + nb_annee;
    if (annee_fin > 2021) {
        std::cout << "Impossible ! Pas assez de données !" << std::endl;
        return 0.0;
    }

    std::shared_ptr<CelluleStation> station = lB.recherche_ptr(id);
    if (station == nullptr) {
        std::cout << "Station introuvable avec l'ID : " << id << std::endl;
        return 0.0;
    }

    float moy = 0;

    std::shared_ptr<CelluleArbre> pArbre = station->tab_arbres[0].get_rac();
    while (pArbre->_annee != annee_depart) {
        pArbre = pArbre->_pFilsD;
    }

    for (int annee = annee_depart; annee < annee_fin; annee++) {
        for (size_t mois = 0; mois < station->tab_arbres.size(); mois++) {
            pArbre = station->tab_arbres[mois].get_rac();
            while (pArbre != nullptr) {
                if (pArbre->_annee == annee) {
                    moy += pArbre->_tempMois;
                }
                pArbre = pArbre->_pFilsD;
            }
        }
    }

    moy /= (nb_annee * 12);

    return moy;
}

/*
* Cette fonction permet de faire la différence de température d'une station entre 2 années
* Elle prend en paramètre une ListeStation& en référence, un int qui est l'id de la station, un int qui est l'année 1 et un int qui est l'année 2
* Elle renvoie un float
*/
float DiffTemp2AnneeStation(ListeStation& lB, int id, int annee_1, int annee_2)
{
    return (MoyTempNAnneesStation(lB, id, annee_1, 1) - MoyTempNAnneesStation(lB, id, annee_2, 1));
}

std::vector<std::pair<float, float>> DiffTempStationNAnnees(ListeStation& lB, int annee_1, size_t n)
{
    std::vector<std::pair<float, float>> tab;
    std::pair<float, float> pair;

    std::shared_ptr<CelluleStation> station = lB.acces_tete();
    while (station != nullptr) {
        pair.first = station->_ID;
        pair.second = MoyTempNAnneesStation(lB, station->_ID, annee_1, n);
        tab.push_back(pair);
        station = station->_pSuiv;
    }
    return tab;
}

std::pair<int, float> MaxDiffTempStationNAnnees(ListeStation& lB, int annee, size_t n) {

    std::vector<std::pair<float, float>> tab = DiffTempStationNAnnees(lB, annee, n);

    std::pair<int, float> pair_max;
    for (auto& pair : tab) {
        if (pair_max.second < pair.second)
            pair_max = pair;
    }

    return pair_max;
}

std::pair<int, float> MinDiffTempStationNAnnees(ListeStation& lB, int annee, size_t n) {

    std::vector<std::pair<float, float>> tab = DiffTempStationNAnnees(lB, annee, n);

    std::pair<int, float> pair_max = tab[0];
    for (auto& pair : tab) {
        if (pair_max.second > pair.second)
            pair_max = pair;
    }

    return pair_max;
}

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

std::pair<int, float> AnneeMinTempNAnnee(ListeStation& lB, int annee, size_t n) {
    std::pair<int, float> ann_min = MoyTempAnneeStation(lB, annee);
    std::pair<int, float> temp;
    for (size_t i = 1; i < n; i++) {
        temp = MoyTempAnneeStation(lB, annee + i);
        if (temp.second < ann_min.second)
            ann_min = temp;
        
    }
    return ann_min;
}

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