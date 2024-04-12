#include <iostream>
#include "CMarbleBag.h"
int main()
{
    size_t Win = 0; //Si cette valeur est à 1, Francesca a gagné la manche, si elle est à 2, il y a eu égalité, si elle est à 3, Sergio a gagné la manche.
    CMarbleBag Francesca;
    CMarbleBag Sergio;

    //Boucle tant qu'aucun des 2 sacs sont vides.
    while (Sergio.GetSac().size() != 0 && Francesca.GetSac().size() != 0) {
        
        //Création des 2 sacs de billes
        std::shared_ptr<CMarble> MarbleS = std::make_shared<CMarble>(); 
        std::shared_ptr<CMarble> MarbleF = std::make_shared<CMarble>();

        //Affiche les valeurs des 2 sacs.
        std::cout << "Sac de Sergio : \nValeur de prestige : " << Sergio.ValPrestige() << "\nNombre de billes : " << Sergio.NbMarble()<<"\n";
        std::cout << "Sac de Francesca : \nValeur de prestige : " << Francesca.ValPrestige() << "\nNombre de billes : " << Francesca.NbMarble() << "\n\n";
        
        //Selectionne 1 billes aléatoirement dans chaque sacs et affiche ses valeurs.
        MarbleS = Sergio.RandomMarble();
        MarbleF = Francesca.RandomMarble();
        std::cout << "Bille de Sergio : \nPoids : " << MarbleS->GetPoids() << "\n";
        std::cout << "Bille de Francesca : \nPoids : " << MarbleF->GetPoids() << "\n\n";

        //Recherche du vainqueur de la manche
        if (MarbleS->GetPoids() < MarbleF->GetPoids()) {
            std::cout << "Francesca a gagné la manche !\n";
            Win = 1;
        }
        else {
            if (MarbleS->GetPoids() > MarbleF->GetPoids()) {
                std::cout << "Sergio a gagné la manche !\n";
                Win = 3;
            }
            else {
                std::cout << "Il y a exaequo !\n";
                Win = 2;
            }
        }

        //Arrengement des billes en fonction du resultat de la manche.
        if (Win == 1) {
            Francesca.AddMarble(MarbleS);
            Sergio.RemoveMarble(MarbleS);
        }
        else if (Win == 3) {
            Sergio.AddMarble(MarbleF);
            Francesca.RemoveMarble(MarbleF);
        }
    }

    //Verifie qui a un sac vide et affiche le vainqueur de la partie.
    if (Sergio.GetSac().size() == 0) {
        std::cout << "Francesca a gagné la partie !";
    }
    else {
        std::cout << "Sergio a gagné la partie !";
    }
}

