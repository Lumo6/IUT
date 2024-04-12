/*!
 *
 * \brief Définition des fonctions principales du programme.
 *
 * \author Benjamin ALBOUY-KISSI
 * \date 2009-2017
 * \version 1.1
 */

#include "fonctions.h"
#include "utils.h"
#include <iostream>

/*!
 * \fn  void CreerMatrice(CMatrice& mat)
 *
 * \author  Benjamin Albouy Kissi
 * \date  23/11/2009
 *
 * \param [in,out]  mat La matrice à créer.
 *
 * Cette fonction demande à l'utilisateur la taille de la matrice, crée la matrice puis initialise
 * les valeurs de la matrice.
 */
void CreerMatrice(CMatrice& mat)
{
  int lig, col;
  std::cout << "Entrez le nombre de lignes de la matrice : ";
  lig = SaisirEntier(1, 10);
  std::cout << "Entrez le nombre de colonnes de la matrice : ";
  col = SaisirEntier(1, 10);
  mat = CMatrice(lig, col);
  for (int i = 0; i < lig; ++i)
  {
    std::cout << "Entrez les valeurs des éléments de la ligne " << i + 1 << " séparées par des espaces\n";
    for (int j = 0; j < col; ++j)
      std::cin >> mat(i, j);
  }
}

/*!
 * \fn  void AfficherMatrice(const CMatrice& mat)
 *
 * \author  Benjamin Albouy Kissi
 * \date  23/11/2009
 *
 * \param mat La matrice à afficher.
 */
void AfficherMatrice(const CMatrice& mat)
{
  std::cout << "La matrice est : \n" << mat << '\n';
}

/*!
 * \fn  void AjouterMatrice(CMatrice& matA, const CMatrice& matB, const CMatrice& matC)
 *
 * \author  Benjamin Albouy Kissi
 * \date  23/11/2009
 *
 * \param [out] matA  La matrice A.
 * \param       matB  La matrice B.
 * \param       matC  La matrice C.
 *
 * Effectue le calcul \p matA = \p matB + \p matC
 */
void AjouterMatrice(CMatrice& matA, const CMatrice& matB, const CMatrice& matC)
{
  matA = matB + matC;
  std::cout << matB << "\n + \n" << matC << "\n = \n" << matA;
}

/*!
 * \fn  void AjouterMatrice2(CMatrice& matA, const CMatrice& matB)
 *
 * \author  Benjamin Albouy Kissi
 * \date  23/11/2009
 *
 * \param [in,out]  matA  La matrice A.
 * \param           matB  La matrice B.
 *
 * Effectue le calcul \p matA += \p matB
 */
void AjouterMatrice2(CMatrice& matA, const CMatrice& matB)
{
  std::cout << "A avant l'opération = \n" << matA << '\n';
  matA += matB;
  std::cout << "B = \n" << matB << '\n';
  std::cout << "A = \n" << matA << '\n';
}

/*!
 * \fn  void SoustraireMatrice(CMatrice& matA, const CMatrice& matB, const CMatrice& matC)
 *
 * \author  Benjamin Albouy Kissi
 * \date  23/11/2009
 *
 * \param [out] matA  La matrice A.
 * \param       matB  La matrice B.
 * \param       matC  La matrice C.
 *
 * Effectue le calcul \p matA = \p matB - \p matC
 */
void SoustraireMatrice(CMatrice& matA, const CMatrice& matB, const CMatrice& matC)
{
  matA = matB - matC;
  std::cout << matB << "\n - \n" << matC << "\n = \n" << matA;
}

/*!
 * \fn  void SoustraireMatrice2(CMatrice& matA, const CMatrice& matB)
 *
 * \author  Benjamin Albouy Kissi
 * \date  23/11/2009
 *
 * \param [in,out]  matA  La matrice A.
 * \param           matB  La matrice B.
 *
 * Effectue le calcul \p matA -= \p matB
 */
void SoustraireMatrice2(CMatrice& matA, const CMatrice& matB)
{
  std::cout << "A avant l'opération = \n" << matA << '\n';
  matA += matB;
  std::cout << "B = \n" << matB << '\n';
  std::cout << "A = \n" << matA << '\n';
}

/*!
 * \fn  void MultiplierMatrice(CMatrice& matA, const CMatrice& matB, const CMatrice& matC)
 *
 * \author  Benjamin Albouy Kissi
 * \date  23/11/2009
 *
 * \param [out] matA  La matrice A.
 * \param       matB  La matrice B.
 * \param       matC  La matrice C.
 *
 * Effectue le calcul \p matA = \p matB * \p matC
 */
void MultiplierMatrice(CMatrice& matA, const CMatrice& matB, const CMatrice& matC)
{
  matA = matB * matC;
  std::cout << matB << "\n * \n" << matC << "\n = \n" << matA;
}

/*!
 * \fn  void EgaliteMatrice(const CMatrice&matA, const CMatrice&matB)
 *
 * \param matA  La matrice A.
 * \param matB  La matrice B.
 *
 * Affiche le résultat du test \p matA == \p matB.
 */
void EgaliteMatrice(const CMatrice& matA, const CMatrice& matB)
{
  if (matA == matB)
    std::cout << "Les matrices \n" << matA << "\n et \n" << matB << "\nsont égales\n";
  else
    std::cout << "Les matrices \n" << matA << "\n et \n" << matB << "\nne sont pas égales\n";
}

/*!
 * \fn  void DifferenceMatrice(const CMatrice&matA, const CMatrice&matB)
 *
 * \param matA  La matrice A.
 * \param matB  La matrice B.
 *
 * Affiche le résultat du test \p matA != \p matB.
 */
void DifferenceMatrice(const CMatrice& matA, const CMatrice& matB)
{
  if (matA != matB)
    std::cout << "Les matrices \n" << matA << "\n et \n" << matB << "\nsont différentes\n";
  else
    std::cout << "Les matrices \n" << matA << "\n et \n" << matB << "\nne sont pas différentes\n";
}

