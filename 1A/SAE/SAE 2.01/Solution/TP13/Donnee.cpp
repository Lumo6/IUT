#include "Donnee.h"


void Donnee::RecupDonnee()
{
    std::ifstream fichierIn("aigoual_Mensuel.csv");
    std::string ligne;

    //Récupère les données pour avoir la température pour chaque mois de chaque années du fichier
    while (std::getline(fichierIn, ligne))
    {
        std::pair<std::pair<unsigned int, unsigned int>, float> tempdates;
        std::istringstream ligneStream(ligne);
        std::string info;
        for (size_t i = 0; i < 2; i++) {
            if (std::getline(ligneStream, info, ';'))
            {
                if (i == 0) {
                    tempdates.first.first = stoi(info.substr(0,4));
                    tempdates.first.second = stoi(info.substr(4, 2));
                }
                else {
                    tempdates.second = stof(info);
                }
                
            }
        }
        std::getline(ligneStream, info);
        infos.push_back(tempdates);
        
    }
    fichierIn.close();
   
}

std::vector<std::pair<unsigned int, float>> Donnee::GetMoyenneAnnee()
{
    //Retourne la moyenne des température d'une année et l'année
    std::vector<std::pair<unsigned int, float>> tempannee;

    unsigned int annee = infos[0].first.first;
    int cpt = 0;
    while (cpt < infos.size()) {
        unsigned int currentYear = infos[cpt].first.first;
        float sumTemp = 0.0f;
        int countTemp = 0;

        while (cpt < infos.size() && currentYear == infos[cpt].first.first) {
            sumTemp += infos[cpt].second;
            ++countTemp;
            ++cpt;
        }

        if (countTemp > 0) {
            float moyenne = sumTemp / static_cast<float>(countTemp);
            tempannee.push_back(std::make_pair(currentYear, moyenne));
        }
    }

    return tempannee;
}

std::vector<std::pair<unsigned int, float>> Donnee::GetAnnee(unsigned int anne)
{
    //Retourne tout les mois d'une année choisis avec leurs température
    std::vector<std::pair<unsigned int, float>> tab;
    for (auto& ele : infos) {
        if (anne == ele.first.first) {
            tab.push_back(std::pair(ele.first.second, ele.second));
        }
    }
    return tab;
}