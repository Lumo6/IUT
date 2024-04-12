#include "fonctions.h"
#include <iostream>

int main()
{
    std::string csvout = "Comparaison.csv";
    std::ofstream csv(csvout);
    if (!csv.is_open()) {
        std::cerr << "Il y à un problème d'ouverture du fichier : " << csvout << ".\n";
    }

    //Creation de 3 tableaux pour pouvoir appeler les fonctions et avoir le nom des fonctions de tri.

    std::vector<tabfonc> tabinit = { initTabAleat,initTabPresqueTri,initTabPresqueTriDeb,initTabPresqueTriDebFin,initTabPresqueTriFin};
    std::vector<tabtri> tabfonctri = { TriParSelection,TriABulles,TriABullesOpt,TriPeigne,TriRapide,triCocktail,triInsertion,triPairImpair,triShell};
    std::vector<std::string> tabnomfonc = { "Selection","Bulles","BullesOpt","Peigne","Rapide","Cocktail","Insertion","PairImpair","Shell"};

    //Ecriture de l'entete dans le fichier csv grace aux nom des fonctions de tri.

    csv << "\"N\"";
    for (size_t i = 0; i < tabfonctri.size(); i++) {
        csv << ";Aleat "<<tabnomfonc[i]<<";PresqueTri "<<tabnomfonc[i]<<";PresqueTriDeb "<<tabnomfonc[i]<<";PresqueTriDebFin "<<tabnomfonc[i]<<";PresqueTriFin" << tabnomfonc[i];
    }
    csv << "\n";

    //Randomisation de la taille des tableaux

    size_t N = rand() % 100 + 2;

    std::vector<int> tabaleat = tabinit[0](N); // Permet de garder le tableau aléatoire de base car il sera trié après le passage dans une fonction.

    
    //Boucle permettant de tester les algorithme avec plusieurs N différent (ici 5).

    for (size_t i = 0; i < 5; i++) {
        
        //creation de 2 vecteur : 1 permettra de stocker le nombre d'itération de chaque algorithme de tri, l'autre contient tout les tableaux initialisés.

        std::vector<std::array<std::string, 6>> NbrIt;
        std::vector<std::vector<int>> tabtab;
        
        //Création d'un tableau stockant les nombres de comparaisons et boucle permettant d'utiliser toutes les fonctions contenu dans le tableau tabfonctri

        std::array<std::string, 6> tabtemp;
        for (size_t i = 0; i < tabfonctri.size(); i++) {
            tabtab.clear(); //Reset du tableau pour le reinitialiser
            for (size_t j = 0; j < tabinit.size(); j++) {
                tabtab.push_back(tabinit[j](N));
            }
            //Lance la fonction actuel (grace à i) pour chaque tableaux
            for (size_t j = 0; j < tabinit.size(); j++) {
                tabtemp[j] = std::to_string(tabfonctri[i](tabtab[j]));
            }
            //Vérifie pour chaque tableaux si il est trié ou non.
            NbrIt.push_back(tabtemp);
            for (size_t j = 0; j < tabtab.size(); j++) {
                verifTri(tabtab[j]);
            }
            
        }

        //Création du fichier csv ligne par ligne
        csv << N << ";";
        for (size_t i = 0; i < NbrIt.size(); i++) {
            for (size_t j = 0; j < NbrIt[i].size(); j++) {
                csv << NbrIt[i][j];
                if (j != NbrIt[i].size() - 1) {
                    csv << ";";
                }
            }
        }

        csv << "\n";

        //Randomisation du N entre 2 et 100.

        N = rand() % 99 + 2;   
    }
}