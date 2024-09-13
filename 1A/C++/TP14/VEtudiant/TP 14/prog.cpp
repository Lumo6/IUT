#include "matrice.h"
#include "test.h"

#include <conio.h>
#include <sstream>
#include <iostream>
#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32

int main(void)
{
#ifdef _WIN32
  SetConsoleOutputCP(CP_UTF8);
#endif // _WIN32

  BEGIN_TESTS

      TEST_IMP(CMatrice);
  CONSTRUCT_VERIF_IMP(CMatrice, mat1);
  TEST_VERIF_IMP_2(CMatrice::GetNbRows, CMatrice::GetNbCols, "Vérification du constructeur par défaut", mat1.GetNbRows() == 0 && mat1.GetNbCols() == 0, true);

  CONSTRUCT_VERIF_IMP(CMatrice, mat2(3, 4));
  std::cout << mat2.GetNbRows() << mat2.GetNbCols() << std::endl;
  TEST_VERIF_IMP_2(CMatrice::GetNbRows, CMatrice::GetNbCols, "Vérification du constructeur avec deux paramètres", mat2.GetNbRows() == 3 && mat2.GetNbCols() == 4, true);



  for (int i = 0; i < 3; ++i)
      for (int j = 0; j < 4; ++j)
          TEST_VERIF_IMP_1(CMatrice::operator(), "Vérification de l'opérateur (i,j) en écriture à la position " << i << "," << j, mat2(i, j) = i * 6 + j, i * 6 + j);
  for (int i = 0; i < 3; ++i)
      for (int j = 0; j < 4; ++j)
          TEST_VERIF_IMP_1(CMatrice::operator(), "Vérification de la définition des données pour (" << i << "," << j << ") = " << i * 6 + j, mat2(i, j), i * 6 + j);

  CONSTRUCT_VERIF_IMP(CMatrice, mat3(3, 4));
  CONSTRUCT_VERIF_IMP(CMatrice, mat4(3, 4));
  for (int i = 0; i < 3; ++i)
      for (int j = 0; j < 4; ++j)
      {
          TEST_VERIF_IMP_1(CMatrice::operator(), "mat3(" << i << "," << j << ") = " << i * 4 + j, mat3(i, j) = i * 6 + j, i * 6 + j);
          TEST_VERIF_IMP_1(CMatrice::operator(), "mat4(" << i << "," << j << ") = " << i * 4 + j + 1, mat4(i, j) = i * 6 + j + 6, i * 6 + j + 6);
      }
  TEST_VERIF_IMP_1(CMatrice::operator==, "Vérification de l'égalité entre mat2 et mat3", mat2 == mat3, true);
  TEST_VERIF_IMP_1(CMatrice::operator==, "Vérification de la non égalité entre mat2 et mat4", mat2 == mat4, false);

  CONSTRUCT_VERIF_IMP(CMatrice, mat5 = mat3);
  TEST_VERIF_IMP_1(CMatrice::operator==, "Vérification de l'égalité entre mat3 et mat5", mat3 == mat5, true);

  CONSTRUCT_VERIF_IMP(CMatrice, mat7(4, 3));
  for (int i = 0; i < 4; ++i)
      for (int j = 0; j < 3; ++j)
          TEST_VERIF_IMP_1(CMatrice::operator(), "mat7(" << i << "," << j << ") = " << i * 3 + j, mat7(i, j) = i * 3 + j, i * 3 + j);
  TEST_VERIF_IMP_2(CMatrice, CMatrice::operator==, "Affectation de mat7 à mat5", mat5 = mat7, mat7);
  TEST_VERIF_IMP_1(CMatrice::operator==, "Vérification de l'égalité entre mat7 et mat5", mat7 == mat5, true);

  VERIF_IMP_1(CMatrice::Zeros, mat7.Zeros());
  for (int i = 0; i < 4; ++i)
      for (int j = 0; j < 3; ++j)
          TEST_VERIF_IMP_1(CMatrice::operator(), "Vérification que l'élément de mat7 (" << i << "," << j << ") soit 0", mat7(i, j), 0);
  TEST_VERIF_IMP_1(CMatrice::Zeros, "Vérifie que la méthode Zeros() retourne bien une référence de l'objet courrant", &(mat7.Zeros()), &mat7);

  VERIF_IMP_1(CMatrice::Identity, mat7.Identity());
  for (int i = 0; i < 4; ++i)
      for (int j = 0; j < 3; ++j)
          TEST_VERIF_IMP_1(CMatrice::operator(), "Vérification que l'élément de mat8 (" << i << "," << j << ") soit " << (i == j ? 1 : 0), mat7(i, j), (i == j ? 1 : 0));
  TEST_VERIF_IMP_1(CMatrice::Identity, "Vérifie que la méthode Identity() retourne bien une référence de l'objet courrant", &(mat7.Identity()), &mat7);

  VERIF_IMP_1(CMatrice::operator-, mat7 = -mat4);
  for (int i = 0; i < 3; ++i)
      for (int j = 0; j < 4; ++j)
          TEST_VERIF_IMP_1(CMatrice::operator(), "Vérification que l'élément de mat7 (" << i << "," << j << ") soit " << -(i * 6 + j + 6), mat7(i, j), -(i * 6 + j + 6));

  VERIF_IMP_1(CMatrice::operator-=, mat7 -= mat4);
  for (int i = 0; i < 3; ++i)
      for (int j = 0; j < 4; ++j)
          TEST_VERIF_IMP_1(CMatrice::operator(), "Vérification que l'élément de mat7 (" << i << "," << j << ") soit " << -2 * (i * 6 + j + 6), mat7(i, j), -2 * (i * 6 + j + 6));

  VERIF_IMP_1(CMatrice::operator-, mat7 = mat7 - mat4);
  for (int i = 0; i < 3; ++i)
      for (int j = 0; j < 4; ++j)
          TEST_VERIF_IMP_1(CMatrice::operator(), "Vérification que l'élément de mat7 (" << i << "," << j << ") soit " << -3 * (i * 6 + j + 6), mat7(i, j), -3 * (i * 6 + j + 6));

  VERIF_IMP_1(CMatrice::operator+=, mat7 += mat4);
  for (int i = 0; i < 3; ++i)
      for (int j = 0; j < 4; ++j)
          TEST_VERIF_IMP_1(CMatrice::operator(), "Vérification que l'élément de mat7 (" << i << "," << j << ") soit " << -2 * (i * 6 + j + 6), mat7(i, j), -2 * (i * 6 + j + 6));

  VERIF_IMP_1(CMatrice::operator+, mat7 = mat7 + mat4);
  for (int i = 0; i < 3; ++i)
      for (int j = 0; j < 4; ++j)
          TEST_VERIF_IMP_1(CMatrice::operator(), "Vérification que l'élément de mat7 (" << i << "," << j << ") soit " << -(i * 6 + j + 6), mat7(i, j), -(i * 6 + j + 6));

  CONSTRUCT_VERIF_IMP(CMatrice, mat9(2, 3));
  CONSTRUCT_VERIF_IMP(CMatrice, mat10(3, 2));
  CONSTRUCT_VERIF_IMP(CMatrice, mat11(2, 2));
  VERIF_IMP_1(CMatrice::operator(), mat9(0, 0) = 1); VERIF_IMP_1(CMatrice::operator(), mat9(0, 1) = 2); VERIF_IMP_1(CMatrice::operator(), mat9(0, 2) = 3);
  VERIF_IMP_1(CMatrice::operator(), mat9(1, 0) = 4); VERIF_IMP_1(CMatrice::operator(), mat9(1, 1) = 5); VERIF_IMP_1(CMatrice::operator(), mat9(1, 2) = 6);

  VERIF_IMP_1(CMatrice::operator(), mat10(0, 0) = 1); VERIF_IMP_1(CMatrice::operator(), mat10(0, 1) = 2);
  VERIF_IMP_1(CMatrice::operator(), mat10(1, 0) = 3); VERIF_IMP_1(CMatrice::operator(), mat10(1, 1) = 4);
  VERIF_IMP_1(CMatrice::operator(), mat10(2, 0) = 5); VERIF_IMP_1(CMatrice::operator(), mat10(2, 1) = 6);

  VERIF_IMP_1(CMatrice::operator(), mat11(0, 0) = 22); VERIF_IMP_1(CMatrice::operator(), mat11(0, 1) = 28);
  VERIF_IMP_1(CMatrice::operator(), mat11(1, 0) = 49); VERIF_IMP_1(CMatrice::operator(), mat11(1, 1) = 64);
  CONSTRUCT_VERIF_IMP(CMatrice, mat12);
  VERIF_IMP_1(CMatrice::operator*, mat12 = mat9 * mat10);
  TEST_VERIF_IMP_1(CMatrice::operator==, "Vérification du produit matriciel", mat12, mat11);
  
  VERIF_IMP_1(mat11, {
      std::ostringstream os;
      os << mat11;
      std::string txt = "    22    28\n"
                        "    49    64";
      TEST("Vérification de la sortie vers flux", os.str(), txt);
  })

  END_TESTS
  return 0;
}

