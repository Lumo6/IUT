/*!
 *
 * \brief Définition des fonctions utilitaires.
 *
 * \author Benjamin ALBOUY-KISSI
 * \date 2009-2017
 * \version 1.1
 */

#include "utils.h"
#include <iostream>

 /*!
  * \fn  int SaisirEntier(int min, int max)
  *
  * \author  Benjamin Albouy Kissi
  * \date  23/11/2009
  *
  * \param min Le minimum admis pour l'entier.
  * \param max Le maximum admis pour l'entier.
  *
  * \return la valeur de l'entier.
  *
  * Cette valeur demande la saisie d'un entier entre deux valeurs. Tant que l'entier entré n'est pas
  * correct, la fonction demande une nouvelle valeur.
  */
int SaisirEntier(int min, int max)
{
  int n;
  std::cin >> n;
  while (n<min || n>max)
  {
    std::cout << "Veuiller entrer une valeur entre " << min << " et " << max << " : ";
    std::cin >> n;
  }
  return n;
}
