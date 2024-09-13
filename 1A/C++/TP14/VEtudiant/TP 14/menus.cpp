/*!
 *
 * \brief Implémentation des fonctions de gestion des menus.
 *
 * \author Benjamin ALBOUY-KISSI
 * \date 2009-2017
 * \version 1.1
 */
#include "menus.h"
#include "fonctions.h"
#include "utils.h"
#include <conio.h>
#include <iostream>

 /*!
  * \fn  char menu(char* texte)
  *
  * \author  Benjamin Albouy Kissi
  * \date  23/11/2009
  *
  * \param [in]  texte Le texte du menu à afficher.
  *
  * \return Le caractère appuyé.
  */
char menu(char* texte)
{
  char choix;
  std::cout
    << "\n -= Menu =-\n\n"
    << texte
    << "\n\nVotre choix : ";

  std::cin >> choix;
  system("cls");
  return choix;
}

/*!
 * \fn  void MenuPrincipal()
 *
 * \author  Benjamin Albouy Kissi
 * \date  23/11/2009
 */
void MenuPrincipal(const int nNbMatrices, CMatrice* pMat)
{
  char cMenuPrincipal[] = R"menu(
c : Créer une matrice
a : Afficher une matrice
o : Opérations sur les matrices
v : Vérifications des matrices

q : Quitter)menu";
  char choix;

  while ((choix = menu(cMenuPrincipal)) != 'q')
  {
    switch (choix)
    {
    case 'c':
    {
      int n;
      std::cout << "Entrez le numéro de la matrice que vous voulez créer (entre 1 et " << nNbMatrices << ") : ";
      n = SaisirEntier(1, nNbMatrices);
      CreerMatrice(pMat[n - 1]);
    }
    break;
    case 'a':
    {
      int n;
      std::cout << "Entrez le numéro de la matrice que vous voulez afficher (entre 1 et " << nNbMatrices << ") : ";
      n = SaisirEntier(1, nNbMatrices);
      AfficherMatrice(pMat[n - 1]);
    }
    break;
    case 'o':
      MenuOperations(nNbMatrices, pMat);
      break;
    case 'v':
      MenuVerifications(nNbMatrices, pMat);
      break;
    case 'q':
      break;
    default:
      std::cout << "Ce choix est impossible !\n";
    }
  }
}

/*!
 * \fn  void MenuOperations(const int nNbMatrices, CMatrice* pMat)
 *
 * \author  Benjamin Albouy Kissi
 * \date  23/11/2009
 *
 * \param nNbMatrices     Le nombre de matrices.
 * \param [in,out]  pMat  Le tableau de matrices.
 */
void MenuOperations(const int nNbMatrices, CMatrice* pMat)
{
  char cMenuOperation[] = R"menu(
a : Ajouter deux matrices dans une troisième matrice (opérateur +)
s : Soustraire deux matrices dans une troisième matrice (opérateur -)
m : Multiplier deux matrices dans une troisième matrice (opérateur *)

z : Ajouter deux matrices dans la première matrice de l'opération (opérateur +=)
d : Soustraire deux matrices dans la première matrice de l'opération (opérateur -=)

r : Retour)menu";
  char choix;
  while ((choix = menu(cMenuOperation)) != 'r')
  {
    switch (choix)
    {
    case 'a': //Ajouter deux matrices dans une troisième matrice (opérateur +)
    {
      int a, b, c;
      std::cout << "Cette action effectuera l'opération A = B+C\n";
      std::cout << "Entrez le numéro de la matrice pour A (entre 1 et " << nNbMatrices << ") : ";
      a = SaisirEntier(1, nNbMatrices);
      std::cout << "Entrez le numéro de la matrice pour B (entre 1 et " << nNbMatrices << ") : ";
      b = SaisirEntier(1, nNbMatrices);
      std::cout << "Entrez le numéro de la matrice pour C (entre 1 et " << nNbMatrices << ") : ";
      c = SaisirEntier(1, nNbMatrices);
      AjouterMatrice(pMat[a - 1], pMat[b - 1], pMat[c - 1]);
    }
    break;
    case 's': //Soustraire deux matrices dans une troisième matrice (opérateur -)
    {
      int a, b, c;
      std::cout << "Cette action effectuera l'opération A = B-C\n";
      std::cout << "Entrez le numéro de la matrice pour A (entre 1 et " << nNbMatrices << ") : ";
      a = SaisirEntier(1, nNbMatrices);
      std::cout << "Entrez le numéro de la matrice pour B (entre 1 et " << nNbMatrices << ") : ";
      b = SaisirEntier(1, nNbMatrices);
      std::cout << "Entrez le numéro de la matrice pour C (entre 1 et " << nNbMatrices << ") : ";
      c = SaisirEntier(1, nNbMatrices);
      SoustraireMatrice(pMat[a - 1], pMat[b - 1], pMat[c - 1]);
    }
    break;
    case 'm': //Multiplier deux matrices dans une troisième matrice (opérateur *)
    {
      int a, b, c;
      std::cout << "Cette action effectuera l'opération A = B*C\n";
      std::cout << "Entrez le numéro de la matrice pour A (entre 1 et " << nNbMatrices << ") : ";
      a = SaisirEntier(1, nNbMatrices);
      std::cout << "Entrez le numéro de la matrice pour B (entre 1 et " << nNbMatrices << ") : ";
      b = SaisirEntier(1, nNbMatrices);
      std::cout << "Entrez le numéro de la matrice pour C (entre 1 et " << nNbMatrices << ") : ";
      c = SaisirEntier(1, nNbMatrices);
      MultiplierMatrice(pMat[a - 1], pMat[b - 1], pMat[c - 1]);
    }
    break;
    case 'z': //Ajouter deux matrices dans la première matrice de l'opération (opérateur +=)
    {
      int a, b;
      std::cout << "Cette action effectuera l'opération A += B\n";
      std::cout << "Entrez le numéro de la matrice pour A (entre 1 et " << nNbMatrices << ") : ";
      a = SaisirEntier(1, nNbMatrices);
      std::cout << "Entrez le numéro de la matrice pour B (entre 1 et " << nNbMatrices << ") : ";
      b = SaisirEntier(1, nNbMatrices);
      AjouterMatrice2(pMat[a - 1], pMat[b - 1]);
    }
    break;
    case 'd': //Soustraire deux matrices dans la première matrice de l'opération (opérateur -=)
    {
      int a, b;
      std::cout << "Cette action effectuera l'opération A -= B\n";
      std::cout << "Entrez le numéro de la matrice pour A (entre 1 et " << nNbMatrices << ") : ";
      a = SaisirEntier(1, nNbMatrices);
      std::cout << "Entrez le numéro de la matrice pour B (entre 1 et " << nNbMatrices << ") : ";
      b = SaisirEntier(1, nNbMatrices);
      SoustraireMatrice2(pMat[a - 1], pMat[b - 1]);
    }
    break;
    case 'r': //Retour
      break;
    default:
      std::cout << "Ce choix est impossible !\n";
    }
  }
}

/*!
 * \fn  void MenuVerifications(const int nNbMatrices, CMatrice* pMat)
 *
 * \author  Benjamin Albouy Kissi
 * \date  23/11/2009
 *
 * \param nNbMatrices     Le nombre de matrices.
 * \param [in,out]  pMat  Le tableau de matrices.
 */
void MenuVerifications(const int nNbMatrices, CMatrice* pMat)
{
  char cMenuVerification[] = R"menu(
e : Vérifier l'égalité entre deux matrices (opérateur ==)
n : Vérifier l'inégalité entre deux matrices (opérateur !=)
r : Retour)menu";
  char choix;
  while ((choix = menu(cMenuVerification)) != 'r')
  {
    switch (choix)
    {
    case 'e': //Vérifier l'égalité entre deux matrices (opérateur ==)
    {
      int a, b;
      std::cout << "Cette action vérifiera A == B\n";
      std::cout << "Entrez le numéro de la matrice pour A (entre 1 et " << nNbMatrices << ") : ";
      a = SaisirEntier(1, nNbMatrices);
      std::cout << "Entrez le numéro de la matrice pour B (entre 1 et " << nNbMatrices << ") : ";
      b = SaisirEntier(1, nNbMatrices);
      EgaliteMatrice(pMat[a - 1], pMat[b - 1]);
    }
    break;
    case 'n': //Vérifier l'inégalité entre deux matrices (opérateur !=)
    {
      int a, b;
      std::cout << "Cette action vérifiera A != B\n";
      std::cout << "Entrez le numéro de la matrice pour A (entre 1 et " << nNbMatrices << ") : ";
      a = SaisirEntier(1, nNbMatrices);
      std::cout << "Entrez le numéro de la matrice pour B (entre 1 et " << nNbMatrices << ") : ";
      b = SaisirEntier(1, nNbMatrices);
      DifferenceMatrice(pMat[a - 1], pMat[b - 1]);
    }
    break;
    case 'r': //Retour
      break;
    default:
      std::cout << "Ce choix est impossible !\n";
    }
  }
}
