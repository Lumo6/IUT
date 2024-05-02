#include <iostream> // std::cout
#include <cstdlib>
#include "SAE_Datas_Heat.h"
#include "Traitement.h"
#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32





int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif // _WIN32
    // Création de l'objet SAE_Datas_Heat
    SAE_Datas_Heat myStations;
    std::cout << "Etude sur " << myStations.nbMonths() << " mois " << "\n" << "\n";
    ListeStation lB = myStations.getListeStation();
    bool programme = true;
    char entree;
    char svt;
    while (programme) {

        std::cout << "Choisissez une action : \n"
            << "a : Afficher toutes les Stats d'une station pour un an\n"
            << "b : Affichez toutes les Stats des stations par saisons\n"
            << "c : Tout afficher\n"
            << "d : Récupérer la moyenne de température par année pour une station\n"
            << "e : Différence de température entre deux années pour station\n"
            << "f : Récupérer la différence de température de toutes les stations sur N années\n"
            << "g : Récupérer la différence maximale de température des stations sur N années\n"
            << "h : Récupérer la différence minimum de température des stations sur N années\n"
            << "i : Récupérer la température minimum sur N années\n"
            << "j : Récupérer la température maximum sur N années\n"
            << "k : Récupérer la moyenne des température de toutes les stations pour un année.\n"
            << "l : Faire un fichier CSV dans lequel est stocker les moyennes des temperatures des annees\n"
            << "m : Faire un fichier CSV dans lequel est stocker les moyennes des temperatures d'une station pour chaque annees\n"
            << "n : Faire un fichier CSV dans lequel est stocker les différences des temperatures d'une station pour chaque annees\n"
            << "q : Quitter\n\n"
            << "Voici la liste des stations : ";
            lB.affiche_liste();
            std::cout << "\nL'étude est faite de 1992 à 2020. Veuillez entrer uniquement des valeurs entre ces dates.";
        std::cin >> entree;
        if (entree > 64 && entree < 91) {
            entree += 32;
        }
        switch (entree) {
        case 'a': {
            int id = 0;
            int annee = 0;
            std::cout << "Entrer l'id de la station et l'annee voulu" << std::endl;
            std::cin >> id >> annee;
            AfficherStatsStationAnnee(lB, id, annee);
            std::cout << "Entrer sur une touche pour retourner au menu" << std::endl;
            std::cin >> svt;
            std::system("cls");
            break;
        }
        case 'b': {
            int id = 0;
            int annee = 0;
            std::cout << "Entrer l'id de la station et l'annee voulu" << std::endl;
            std::cin >> id >> annee;
            AfficheStatsStationSaison(lB,id,annee);
            std::cout << "Entrer sur une touche pour retourner au menu" << std::endl;
            std::cin >> svt;
            std::system("cls");
            break;
        }
        case 'c': {
            AfficherTout(lB);
            std::cout << "Entrer sur une touche pour retourner au menu" << std::endl;
            std::cin >> svt;
            std::system("cls");
            break;
        }
        case 'd': {
            int id = 0;
            int annee = 0;
            int nb = 0;
            std::cout << "Entrer l'id de la station et l'annee et le nombre d'annee voulues" << std::endl;
            std::cin >> id >> annee >> nb;
            std::cout << MoyTempNAnneesStation(lB, id, annee, nb) << std::endl;
            std::cout << "Entrer sur une touche pour retourner au menu" << std::endl;
            std::cin >> svt;
            std::system("cls");
            break;
            
        }
        case 'e': {
            int id = 0;
            int annee1 = 0;
            int annee2 = 0;
            std::cout << "Entrer l'id de la station et les 2 annees voulues." << std::endl;
            std::cin >> id >> annee1 >> annee2;
            std::cout << DiffTemp2AnneeStation(lB, id, annee1, annee2) << std::endl;
            std::cout << "Entrer sur une touche pour retourner au menu" << std::endl;
            std::cin >> svt;
            std::system("cls");
            break;
            
        }
        case 'f': {
            int annee = 0;
            int nb = 0;
            std::cout << "Entrer l'annee et le nombre d'annee voulues" << std::endl;
            std::cin >> annee >> nb;
            std::vector<std::pair<float, float>> tab = MoyTempStationNAnnees(lB, annee, nb);

            for (auto& pair : tab)
                std::cout << "Station : " << pair.first << " Température : " << pair.second << std::endl;
            std::cout << "Entrer sur une touche pour retourner au menu" << std::endl;
            std::cin >> svt;
            std::system("cls");
            break;
            
        }
        case 'g': {
            int annee = 0;
            int nb = 0;
            std::cout << "Entrer l'annee et le nombre d'annee voulues" << std::endl;
            std::cin >> annee >> nb;
            std::pair<int, float> vec = MaxDiffTempStationNAnnees(lB, annee, nb);
            std::cout << "Station : " << vec.first << " Température : " << vec.second << std::endl;
            std::cout << "Entrer sur une touche pour retourner au menu" << std::endl;
            std::cin >> svt;
            std::system("cls");
            break;
            
        }
        case 'h': {
            int annee = 0;
            int nb = 0;
            std::cout << "Entrer l'annee et le nombre d'annee voulues" << std::endl;
            std::cin >> annee >> nb;
            std::pair<int, float> vec = MinDiffTempStationNAnnees(lB, annee, nb);
            std::cout << "Station : " << vec.first << " Température : " << vec.second << std::endl;
            std::cout << "Entrer sur une touche pour retourner au menu" << std::endl;
            std::cin >> svt;
            std::system("cls");
            break;
        }
        case 'i': {
            int annee = 0;
            int nb = 0;
            std::cout << "Entrer l'annee et le nombre d'annee voulues" << std::endl;
            std::cin >> annee >> nb;
            std::cout << "Annee : " << AnneeMinTempNAnnee(lB, annee, nb).first << "Température Min :    " << AnneeMinTempNAnnee(lB, annee, nb).second << std::endl;
            std::cout << "Entrer sur une touche pour retourner au menu" << std::endl;
            std::cin >> svt;
            std::system("cls");
            break;
        }
        case 'j': {
            int annee = 0;
            int nb = 0;
            std::cout << "Entrer l'annee et le nombre d'annee voulues" << std::endl;
            std::cin >> annee >> nb;
            std::cout << "Annee : " << AnneeMaxTempNAnnee(lB, annee, nb).first << "Température Max :     " << AnneeMaxTempNAnnee(lB, annee, nb).second << std::endl;
            std::cout << "Entrer sur une touche pour retourner au menu" << std::endl;
            std::cin >> svt;
            std::system("cls");
            break;
        }
        case'k': {
            int annee = 0;
            std::cout << "Entrer l'annee voulu." << std::endl;
            std::cin >> annee;
            std::cout << "Annee : " << MoyTempAnneeStation(lB,annee).first << "Température :     " << MoyTempAnneeStation(lB, annee).second << std::endl;
            std::cout << "Entrer sur une touche pour retourner au menu" << std::endl;
            std::cin >> svt;
            std::system("cls");
            break;
        }
        case'l': {
            std::ofstream out("MoyTempAnnee.csv");
            MoyTempAnneeCSV(out, lB);
            std::cout << "Entrer sur une touche pour retourner au menu" << std::endl;
            std::cin >> svt;
            std::system("cls");
            break;
        }
        case'm': {
            int id = 0;
            std::cout << "Entrer l'id voulu" << std::endl;
            std::cin >> id;
            std::ofstream out("MoyTempStation" + std::to_string(id) + ".csv");
            MoyTempStationCSV(out, lB, id);
            std::cout << "Entrer sur une touche pour retourner au menu" << std::endl;
            std::cin >> svt;
            std::system("cls");
            break;
        }
        case'n': {
            int annee = 0;
            int nb = 0;
            std::cout << "Entrer  l'annee et le nombre d'annee voulues" << std::endl;
            std::cin >> annee >> nb;
            std::ofstream out("DifTempPourTouteStation" + std::to_string(annee)+"à"+ std::to_string(annee+nb) + ".csv");
            DifTempPourTouteStationCSV(out,lB, annee,nb);
            std::cout << "Entrer sur une touche pour retourner au menu" << std::endl;
            std::cin >> svt;
            std::system("cls");
            break;
        }
        case'q': {
            programme = false;
            break;
        }
        }
    }
    return 0;
}