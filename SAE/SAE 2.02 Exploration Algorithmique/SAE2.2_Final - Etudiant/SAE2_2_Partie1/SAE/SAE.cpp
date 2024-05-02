// SAE.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "Cellule.h"
#include "Liste.h"
#include "CelluleB.h"
#include "ListeB.h"
#include "CelluleA.h"
#include "Arbre.h"

#include <vector>
#include <string>
#include <array>
#include <memory>

int main()
{
   
  
    // Ecrivez vos tests dans le prog principal que l'on presentera proprement
    // ceux qui suivent sont juste la pour vous montrer comment cela marche
    std::shared_ptr<Cellule> cel = std::make_shared< Cellule>();
    std::shared_ptr<Cellule> cel2 = std::make_shared< Cellule>(5);
    std::shared_ptr<Cellule> cel3 = std::make_shared< Cellule>(1);
    std::shared_ptr<Cellule> cel4 = std::make_shared< Cellule>(9);
    std::shared_ptr<Cellule> cel5 = std::make_shared< Cellule>(8);
    std::shared_ptr<Cellule> cel6 = std::make_shared< Cellule>(3);
  

    Liste l;
    l.ajoute_cellule_en_tete(cel);
    l.ajoute_cellule_en_tete(cel2);
    l.ajoute_cellule_en_tete(cel3); 
    l.ajoute_cellule_en_tete(cel4);
    l.ajoute_cellule_en_tete(cel5);
    l.ajoute_cellule_en_tete(cel6);
   
    l.affiche_liste();
    std::cout << "il y a  " << l.nbelem() << " elements \n";
    l.ajoute_cellule_en_queue(cel3);
    l.supprime_cellule(1);
    l.affiche_liste();
    l.liberer_liste();
    std::cout << "Hello World2!\n";
    l.affiche_liste();

    std::shared_ptr<CelluleB> cel7 = std::make_shared< CelluleB>();
    std::shared_ptr<CelluleB> cel8 = std::make_shared< CelluleB>(5);
    std::shared_ptr<CelluleB> cel9 = std::make_shared< CelluleB>(1);
    std::shared_ptr<CelluleB> cel10 = std::make_shared< CelluleB>(9);
    std::shared_ptr<CelluleB> cel11 = std::make_shared< CelluleB>(8);
    std::shared_ptr<CelluleB> cel12 = std::make_shared< CelluleB>(3);


    ListeB l2;
    l2.ajoute_cellule_en_tete(cel7);
    l2.ajoute_cellule_en_tete(cel8);
    l2.ajoute_cellule_en_tete(cel9);
    l2.ajoute_cellule_en_tete(cel10);
    l2.ajoute_cellule_en_tete(cel11);
    l2.ajoute_cellule_en_tete(cel12);

    l2.affiche_liste();
    std::cout << "il y a  " << l2.nbelem() << " elements \n";
    l2.ajoute_cellule_en_queue(cel9);
    l2.supprime_cellule(1);
    l2.affiche_liste();
    l2.liberer_liste();
    std::cout << "Hello World2!\n";
    l2.affiche_liste();

    std::shared_ptr<CelluleA> cel13 = std::make_shared< CelluleA>(6);
    std::shared_ptr<CelluleA> cel14 = std::make_shared< CelluleA>(5);
    std::shared_ptr<CelluleA> cel15 = std::make_shared< CelluleA>(1);
    std::shared_ptr<CelluleA> cel16 = std::make_shared< CelluleA>(9);
    std::shared_ptr<CelluleA> cel17 = std::make_shared< CelluleA>(8);
    std::shared_ptr<CelluleA> cel18 = std::make_shared< CelluleA>(3);
    std::shared_ptr<CelluleA> cel19 = std::make_shared< CelluleA>(10);

    Arbre A;
    A.ajoute_cellule(cel13);
    A.ajoute_cellule(cel14);
    A.ajoute_cellule(cel15);
    A.ajoute_cellule(cel16);
    A.ajoute_cellule(cel17);
    A.ajoute_cellule(cel18);

    A.affiche_arbre_infixe();
    std::cout << "\n";
    A.affiche_arbre_prefixe();
    std::cout << "\n";
    A.affiche_arbre_postfixe();
    std::cout << "\n";
    std::cout << "il y a  " << A.nbelem() << " elements et "<<A.nbfeuille()<<" feuilles.\n";
    A.ajoute_cellule(cel19);
    std::cout << "il y a  " << A.nbelem() << " elements et " << A.nbfeuille() << " feuilles.\n";
    A.supprime_cellule(1);
    std::cout << "il y a  " << A.nbelem() << " elements et " << A.nbfeuille() << " feuilles.\n";
    A.affiche_arbre_infixe();
    A.liberer_arbre();
    std::cout << "\nHello World2!\n";
    A.affiche_arbre_infixe();

    return 0;

}
