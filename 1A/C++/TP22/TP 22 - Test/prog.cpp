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
    CMatrice<double> mat(2, 3);
    for (size_t i = 0; i < mat.GetNbRows(); ++i)
    {
        for (size_t j = 0; j < mat.GetNbCols(); ++j)
        {
            mat(i, j) = i * mat.GetNbCols() + j + 1.0;
        }
    }
    try
    {
        double val = mat(2, 3);
    }
    catch (const CErreurMatrice& e)
    {
        std::cout << "Erreur : ";
        std::cout << e;
        std::cout << std::endl;
    }
    CMatrice<double> mat2(2, 3);
    for (size_t i = 0; i < mat2.GetNbRows(); ++i)
    {
        for (size_t j = 0; j < mat2.GetNbCols(); ++j)
        {
            mat2(i, j) = i * mat2.GetNbCols() + j + 1.0;
        }
    }
    try
    {
        mat2(2, 3) = 10;
    }
    catch (const CErreurMatrice& e)
    {
        std::cout << "Erreur : ";
        std::cout << e;
        std::cout << std::endl;
    }
    CMatrice<double> mat5(2, 3);
    CMatrice<double> mat6(3, 2);
    for (size_t i = 0; i < mat5.GetNbRows(); ++i)
    {
        for (size_t j = 0; j < mat5.GetNbCols(); ++j)
        {
            mat5(i, j) = i * mat5.GetNbCols() + j + 1.0;
        }
    }
    for (size_t i = 0; i < mat6.GetNbRows(); ++i)
    {
        for (size_t j = 0; j < mat6.GetNbCols(); ++j)
        {
            mat6(i, j) = i * mat6.GetNbCols() + j + 1.0;
        }
    }
    try
    {
        mat5 += mat6;
    }
    catch (const CErreurMatrice& e)
    {
        std::cout << "Erreur : ";
        std::cout << e;
        std::cout << std::endl;
    }

    try
    {
        CMatrice<double> mat7(3, 4);
        CMatrice<double> mat8(4, 3);
        mat7 -= mat8;
    }
    catch (const CErreurMatrice& e)
    {
        std::cout << "Erreur : ";
        std::cout << e;
        std::cout << std::endl;
    }

    try
    {
        CMatrice<double> mat1(4, 8);
        CMatrice<double> mat2(3, 2);
        mat1(0, 0) = 1;   mat1(0, 1) = 2;   mat1(0, 2) = 3;
        mat1(1, 0) = 4;   mat1(1, 1) = 5;   mat1(1, 2) = 6;

        mat2(0, 0) = 1;  mat2(0, 1) = 2;
        mat2(1, 0) = 3;  mat2(1, 1) = 4;
        mat2(2, 0) = 5;  mat2(2, 1) = 6;

        CMatrice<double> result1(2, 2);
        result1(0, 0) = 22; result1(0, 1) = 28;
        result1(1, 0) = 49; result1(1, 1) = 64;

        TEST("Code générant une erreur : ", mat1 * mat2, result1);
    }
    catch (const CErreurMatrice& e)
    {
        TEST("L'erreur suivante est détectée :\"" << e <<"\"", true, true);
    }

    END_TESTS

}