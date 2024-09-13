/*!
 *
 * \brief Programme principal. 
 *
 * \author Benjamin ALBOUY-KISSI
 * \date 2009-2017
 * \version 1.1
 */

#include "matrice.h"
#include "menus.h"

#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32
#include <iostream>
#include <string>

/*!
 *
 * \mainpage
 * \tableofcontents
 *
 * Ce programme est un programme de test de la classe CMatrice. Référez-vous à 
 * la classe CMatrice pour la documentation principale et au fichier 
 * test.h pour la documentation des fonctions de test.
 *
 */

/*!
 * \fn  void main(void)
 *
 * \brief Main entry-point for this application. 
 *
 * \author  Benjamin Albouy Kissi
 * \date  23/11/2009
 */
int main(void)
{
#ifdef _WIN32
  SetConsoleOutputCP(CP_UTF8);
#endif // _WIN32

  // Nombre max de matrices. 
  const int nNbMatrices = 3;
  // Tableau de matrices. 
  CMatrice pMat[nNbMatrices];

  std::cout<<R"welcome(Bienvenue dans ce TP
Ce TP a été créé par Benjamin ALBOUY-KISSI le 23/11/2009
Révision du programme principal : version 1.2

Appuyez sur Entrée pour afficher le menu principal)welcome";

  std::string strIgnore;
  std::getline(std::cin, strIgnore);

  MenuPrincipal(nNbMatrices, pMat);

  system("cls");
  std::cout << "Aurevoir et à bientôt !\n";
  return 0;
}

