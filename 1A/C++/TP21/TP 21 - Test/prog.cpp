/*!
* \file  "prog.cpp"
*
* \brief Programme principal. 
*
*/

/*!
 * \mainpage TP 09 – Exercice 1	Modification de la classe CMatrice
 *
 * \tableofcontents
 * 
 * \section sec1 Travail à réaliser
 *
 * <ul>
 *   <li>Copiez les contenus des fichiers Matrice.h et Matrice.cpp du TP 2 dans leurs homologues de ce TP. </li>
 *   <li>En utilisant la technique des templates, modifiez la classe CMatrice de sorte que les éléments stockés soient d’un type générique.</li>
 *   <ul>
 *     <li>Que devient le fichier Matrice.cpp ?</li>
 *   </ul>
 *   <li>Exécutez le programme de test de façon à ce qu'il passe tous les tests...</li>
 *   <ul>
 *     <li>Vous devrez dans un premier temps faire en sorte qu'il compile en ajoutant à la classe CMatrice les membres adéquats.</li>
 *     <li>Adaptez le template CMatrice au besoin.</li>
 *   </ul>
 * </ul>
 */
#include "StdAfx.h"
#include "matrice.h"
#include "test.h"

#include <iostream>
#include <sstream>
#include <complex>


/*!
* \brief Main entry-point for this application. 
*
*/
int main(void)
{
#ifdef _WIN32
  SetConsoleOutputCP(65001);
#endif
  BEGIN_TESTS
  //Construction par défaut
  CMatrice<double> mat1;
  TEST("Vérification du constructeur par défaut", mat1.GetNbRows() == 0 && mat1.GetNbCols() == 0, true);

  //Construction avec deux paramètres
  CMatrice<double> mat2{ 3, 4 };
  TEST("Vérification du constructeur avec deux paramètres", mat2.GetNbRows() == 3 && mat2.GetNbCols() == 4, true);

  //Opérateur ()
  //Définition des données
  for (int i = 0; i < 3; ++i)
    for (int j = 0; j < 4; ++j)
      TEST("Vérification de l'opérateur (i,j) en écriture à la position " << i << "," << j, mat2(i, j) = i * 4 + j, i * 4 + j);
  //Validation
  for (int i = 0; i < 3; ++i)
    for (int j = 0; j < 4; ++j)
      TEST("Vérification de la définition des données pour (" << i << "," << j << ") = " << i * 4 + j, mat2(i, j), i * 4 + j);

  //Opérateur ==
  CMatrice<double> mat3{ 3, 4 };
  CMatrice<double> mat4{ 3, 4 };
  //Définition des données
  for (int i = 0; i<3; ++i)
    for (int j = 0; j<4; ++j)
    {
      TEST("mat3(" << i << "," << j << ") = " << i * 4 + j, mat3(i, j) = i * 4 + j, i * 4 + j);
      TEST("mat4(" << i << "," << j << ") = " << i * 4 + j + 1, mat4(i, j) = i * 4 + j + 1, i * 4 + j + 1);
    }
  TEST("Vérification de l'égalité entre mat2 et mat3", mat2 == mat3, true);
  TEST("Vérification de la non égalité entre mat2 et mat4", mat2 == mat4, false);

  //Opérateur !=
  TEST("Vérification de la non inégalité entre mat2 et mat3", mat2 != mat3, false);
  TEST("Vérification de l'inégalité entre mat2 et mat4", mat2 != mat4, true);

  //Méthode d'initialisation Zeros
  CMatrice<double> mat5{ mat4 };
  mat5.Zeros();
  for (int i = 0; i < 3; ++i)
    for (int j = 0; j < 4; ++j)
      TEST("Vérification que l'élément de mat5 (" << i << "," << j << ") soit 0", mat5(i, j), 0);
  TEST("Vérifie que la méthode Zeros() retourne bien une référence de l'objet courrant", &(mat5.Zeros()), &mat5);

  //Méthode d'initialisation Identity()
  mat5 = mat4;
  mat5.Identity();
  for (int i = 0; i < 3; ++i)
    for (int j = 0; j < 4; ++j)
      TEST("Vérification que l'élément de mat5 (" << i << "," << j << ") soit " << (i == j ? 1 : 0), mat5(i, j), (i == j ? 1 : 0));
  TEST("Vérifie que la méthode Identity() retourne bien une référence de l'objet courrant", &(mat5.Identity()), &mat5);

  //Opérateur - unaire
  mat3 = -mat4;
  for (int i = 0; i < 3; ++i)
    for (int j = 0; j < 4; ++j)
      TEST("Vérification que l'élément de mat3 (" << i << "," << j << ") soit " << -(i * 4 + j + 1), mat3(i, j), -(i * 4 + j + 1));

  //Opérateur -= 
  mat3 -= mat4;
  for (int i = 0; i < 3; ++i)
    for (int j = 0; j < 4; ++j)
      TEST("Vérification que l'élément de mat3 (" << i << "," << j << ") soit " << -2 * (i * 4 + j + 1), mat3(i, j), -2 * (i * 4 + j + 1));

  //Opérateur - binaire
  mat3 = mat3 - mat4;
  for (int i = 0; i < 3; ++i)
    for (int j = 0; j < 4; ++j)
      TEST("Vérification que l'élément de mat3 (" << i << "," << j << ") soit " << -3 * (i * 4 + j + 1), mat3(i, j), -3 * (i * 4 + j + 1));

  //Opérateur += 
  mat3 += mat4;
  for (int i = 0; i < 3; ++i)
    for (int j = 0; j < 4; ++j)
      TEST("Vérification que l'élément de mat3 (" << i << "," << j << ") soit " << -2 * (i * 4 + j + 1), mat3(i, j), -2 * (i * 4 + j + 1));

  //Opérateur + binaire
  mat3 = mat3 + mat4;
  for (int i = 0; i < 3; ++i)
    for (int j = 0; j < 4; ++j)
      TEST("Vérification que l'élément de mat3 (" << i << "," << j << ") soit " << -(i * 4 + j + 1), mat3(i, j), -(i * 4 + j + 1));

  //Opérateur * binaire
  CMatrice<double> mat9{ 2, 3 };
  CMatrice<double> mat10{ 3, 2 };
  CMatrice<double> mat11{ 2, 2 };
  mat9(0, 0) = 1;   mat9(0, 1) = 2;   mat9(0, 2) = 3;
  mat9(1, 0) = 4;   mat9(1, 1) = 5;   mat9(1, 2) = 6;

  mat10(0, 0) = 1;  mat10(0, 1) = 2;
  mat10(1, 0) = 3;  mat10(1, 1) = 4;
  mat10(2, 0) = 5;  mat10(2, 1) = 6;

  mat11(0, 0) = 22; mat11(0, 1) = 28;
  mat11(1, 0) = 49; mat11(1, 1) = 64;
  CMatrice<double> mat12;
  mat12 = mat9 * mat10;
  TEST("Vérification du produit matriciel", mat12, mat11);

  //Opérateur << de sortie vers flux
  {
    std::ostringstream os;
    os << mat11;
    std::string txt = "    22    28\n"
      "    49    64";
    TEST("Vérification de la sortie vers flux", os.str(), txt);
  }

  CMatrice<std::complex<double>> matComplexe{ 3, 4 };
  for (int i = 0; i<3; ++i)
    for (int j = 0; j<4; ++j)
    {
      matComplexe(i, j) = std::complex<double>{i * 4.0 + j, -i * 4.0 - j};
    }

  TEST("Vérification de la conversion implicite des matrices : ", matComplexe = mat4, decltype(matComplexe)(mat4));

  END_TESTS


  return 0;
}

