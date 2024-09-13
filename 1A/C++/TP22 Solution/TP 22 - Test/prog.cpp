/*!
* \file  "prog.cpp"
*
* \brief Programme principal. 
*
 * \author Benjamin ALBOUY-KISSI
 * \date 2016
*/

/*!
 * \mainpage TP 22 – Exercice 1	Modification de la classe CMatrice
 *
 * \tableofcontents
 * 
 * \section sec0 Objectifs du TP
 * 
 * L’objectif du TP est de reprendre la classe matrice du TP précédent et de gérer les erreurs potentielles.
 * 
 * \section sec1 Exercice 1 Génération d’une erreur
 * 
 * <ul>
 *   <li>Dans le programme principal, créez une matrice \c matA de taille 2x3 et une matrice \c matB de taille 3x2. Initialisez leurs valeurs.</li>
 *   <li>Créez une troisième matrice \c matC et copiez le code suivant :</li>
 * \code
matC = matA + matB;
cout << "Affichage des matrices :\n"
        "matA = \n"
     << matA << "\n"
        "matB = \n"
     << matB << "\n"
        "matC = \n"
     << matC << "\n";
\endcode
 *   <li>Compilez et exécutez votre programme.</li>
 *   <ul>
 *     <li>Que se passe-t-il ?</li>
 *     <li>Déterminez pourquoi le programme se termine sans afficher les matrices.</li>
 *   </ul>
 * </ul>
 *
 * \section sec2 Exercice 2 Création d’une classe d’erreur
 * 
 * Les erreurs possibles dans la classe matrice sont les suivantes :
 *
 * <table>
 *   <tr><th>Fonction membre</th><th>Erreur</th></tr>
 *   <tr><td>CMatrice::operator()(size_t, size_t) const</td><td>Les indices sont hors de la plage</td></tr>
 *   <tr><td>CMatrice::operator()(size_t, size_t)</td><td>Les indices sont hors de la plage</td></tr>
 *   <tr><td>CMatrice::operator*(const CMatrice& mat) const</td><td>Les tailles ne sont pas compatibles</td></tr>
 *   <tr><td>CMatrice::operator+=(const CMatrice& mat)</td><td>Les tailles ne sont pas compatibles</td></tr>
 *   <tr><td>CMatrice::operator-=(const CMatrice& mat)</td><td>Les tailles ne sont pas compatibles</td></tr>
 * </table>
 *
 * Pour ces deux types d’erreur, nous pouvons leur attribuer un code d’erreur. Ce code d’erreur peut être stocké dans une classe puis 
 * interprété par une méthode de cette classe pour afficher le message d’erreur.
 *
 * <ul>
 *   <li>Créez une classe CErreurMatrice qui a pour attributs :</li>
 *   <ul>
 *     <li>Un entier qui sera le code d’erreur.</li>
 *     <li>Une chaîne de caractères qui identifiera la fonction qui a généré l’erreur.</li>
 *     <li>Un constructeur avec deux paramètres qui initialisera les deux attributs.</li>
 *     <li>Un accesseur public pour chacun des attributs.</li>
 *   </ul>
 *   <li>Définissez l’opérateur de sortie vers flux permettant d’afficher le message d’erreur correspondant au code d’erreur d’un objet 
 *   CErreurMatrice.</li>
 *   <li>Testez cette classe dans un programme principal.</li>
 * </ul>
 * 
 * \section sec3 Exercice 3 Utilisation de la classe d’erreur
 *
 * <ul>
 *   <li>Par le mécanisme des exceptions, utilisez la classe CErreurMatrice dans la classe matrice pour signaler les erreurs au programme principal.</li>
 *   <li>Modifiez le programme principal de \ref sec1 "l’exercice 1" en conséquence pour que la gestion soit complète. Le programme doit dans tous les cas 
 *   afficher les matrices \c matA, \c matB et \c matC. Si une erreur survient, elle doit simplement être affichée à l’utilisateur via le flux d’erreur.</li>
 * </ul>
 * 
 * \section sec4 Exercice 4 Test complet
 * <ul>
 *   <li>Ecrivez un programme principal permettant de tester toutes les erreurs possibles de la classe CMatrice.</li>
 * </ul>
 */
#include "StdAfx.h"
#include "matrice.h"
#include "ErreurMatrice.h"
#include "test.h"

#include <conio.h>
#include <iostream>


/*!
* \brief Main entry-point for this application. 
*
*/
int main(void)
{
#ifdef WIN32
  SetConsoleOutputCP(CP_UTF8);
#endif 
  BEGIN_TESTS
    //!\todo Complétez le programme principal ici.
    //Solution
    //Cette solution n'est pas complète !
    CMatrice<double> matA(2,3), matB(3,2), matC;
    matA(0,0) = 1; matA(0,1) = 2; matA(0,2) = 3; 
    matA(1,0) = 4; matA(1,1) = 5; matA(1,2) = 6; 

    matB(0,0) = 7; matB(0,1) = 8;
    matB(1,0) = 9; matB(1,1) = 10;
    matB(2,0) = 11; matB(2,1) = 12;

    try
    {
      matC = matA+matB;
      TEST("Ce test ne doit pas être exécuté", true, false)
    }
    catch(CErreurMatrice& em)
    {
      TEST("L'erreur \"" << em << "\" a été rencontrée", true, true)
    }

    std::cout << "Affichage des matrices :\n"
                 "matA = \n"
              << matA << "\n"
                 "matB = \n"
              << matB << "\n"
                 "matC = \n"
              << matC << "\n";
    //Fin Solution
  END_TESTS

}

