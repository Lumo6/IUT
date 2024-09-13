/*
    This file is part of LittleTestFramework.

    LittleTestFramework is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    LittleTestFramework is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with LittleTestFramework. If not, see <http://www.gnu.org/licenses/>.
*/
/*!
 * \file  "Test.h"
 *
 * \brief Déclaration des fonctions du framework de test. 
 *
 * \author Benjamin ALBOUY-KISSI
 * \date 2009-2020
 * \version 1.2
 */
#pragma once

/*!
 * \if TestHelp
 * \mainpage
 * \tableofcontents
 * \section secTitre Utilisation
 * 
\code{.cpp}
#include "test.h"
void main()
{
  BEGIN_TESTS
    int a = 2;
    int b = 3;
    NOTICE("Début des tests"<<std::endl<<std::endl);
    TEST("Vérification de la valeur de a", a, 2);
    TEST("Vérification de l'inégalité entre a et b", a==b, false);
    TEST("Ce test doit échouer", a==b, true);
  END_TESTS
}
\endcode
 * \see BEGIN_TESTS | NOTICE | TEST | END_TESTS
 * 
 * \section secAutre Utilisation avancée
 * D'autres macros sont définies pour permettre d'écrire des tests qui compilent et s'exécutent (en échouant) même si la classe ou la fonction testée n'est pas encore implémentée :
 *
 * \subsection secConstr Conctruction d'objet
 * La macro \ref CONSTRUCT_VERIF_IMP permet de créer des objets. Si les classes des objets ne sont pas encore définie, alors le test échoue. Exemple :
 *
\code{.cpp}
  CONSTRUCT_VERIF_IMP(CMaClasse, monObjet); // <=> CMaClasse monObjet;
  CONSTRUCT_VERIF_IMP(CMaClasse, monObjet(param1)); // <=> CMaClasse monObjet(param1);
  CONSTRUCT_VERIF_IMP(CMaClasse, *pMonObjet = new CMaClasse(param1)); // <=> CMaClasse *pMonObjet = new CMaClasse(param1);
\endcode
 * 
 * \subsection secImp Vérification d'implémentation
 * La macro \ref TEST_IMP permet de tester si un symbole est implémenté. Le symbole pet être une classe, une fonction, une variable globale, etc... Exemple :
 * 
\code{.cpp}
  TEST_IMP(CMaClasse); 
  TEST_IMP(CMaClasse::MonMembre);
  TEST_IMP(MaFonction);
\endcode
 *
 * \subsection secTestImp Tests avec vérification d'implémentation
 * Les macros \ref TEST_VERIF_IMP_1 à \ref TEST_VERIF_IMP_3 permettent de réaliser un test si un à trois symboles sont effectivement implémentés.
 *
\code{.cpp}
  CONSTRUCT_VERIF_IMP(CMaClasse, monObjet); // <=> CMaClasse monObjet;
  TEST_VERIF_IMP_1(CMaClasse::GetX, "Vérification de la valeur de x", monObjet.GetX(), 0);
  TEST_VERIF_IMP_2(CMaClasse::GetAlpha, CMaClasse::GetBeta, "Vérification de la valeur de (alpha, beta)", monObjet.GetAplha()==0 && monObjet.GetBeta()==0, true);
\endcode
 * \endif
 */

#include <iostream>
#ifndef FOREGROUND_BLUE 
#define FOREGROUND_BLUE      0x0001 //!< text color contains blue.
#endif
#ifndef FOREGROUND_GREEN 
#define FOREGROUND_GREEN     0x0002 //!< text color contains green.
#endif
#ifndef FOREGROUND_RED 
#define FOREGROUND_RED       0x0004 //!< text color contains red.
#endif
#ifndef FOREGROUND_INTENSITY 
#define FOREGROUND_INTENSITY 0x0008 //!< text color is intensified.
#endif
#ifndef BACKGROUND_BLUE 
#define BACKGROUND_BLUE      0x0010 //!< background color contains blue.
#endif
#ifndef BACKGROUND_GREEN 
#define BACKGROUND_GREEN     0x0020 //!< background color contains green.
#endif
#ifndef BACKGROUND_RED 
#define BACKGROUND_RED       0x0040 //!< background color contains red.
#endif
#ifndef BACKGROUND_INTENSITY 
#define BACKGROUND_INTENSITY 0x0080 //!< background color is intensified.
#endif

/*!
 * \internal
 * Enumération des couleurs de texte console.
 */
enum class Color
{
  DarkForegroundBlue      = FOREGROUND_BLUE,
  DarkForegroundGreen     = FOREGROUND_GREEN,
  DarkForegroundRed       = FOREGROUND_RED,
  DarkForegroundCyan      = FOREGROUND_BLUE | FOREGROUND_GREEN,
  DarkForegroundYellow    = FOREGROUND_GREEN | FOREGROUND_RED,
  DarkForegroundMagenta   = FOREGROUND_RED | FOREGROUND_BLUE,
  DarkForegroundWhite     = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
  LightForegroundBlue     = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
  LightForegroundGreen    = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
  LightForegroundRed      = FOREGROUND_INTENSITY | FOREGROUND_RED,
  LightForegroundCyan     = FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN,
  LightForegroundYellow   = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED,
  LightForegroundMagenta  = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
  LightForegroundWhite    = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
  DarkBackgroundBlue      = BACKGROUND_BLUE,
  DarkBackgroundGreen     = BACKGROUND_GREEN,
  DarkBackgroundRed       = BACKGROUND_RED,
  DarkBackgroundCyan      = BACKGROUND_BLUE | BACKGROUND_GREEN,
  DarkBackgroundYellow    = BACKGROUND_GREEN | BACKGROUND_RED,
  DarkBackgroundMagenta   = BACKGROUND_RED | BACKGROUND_BLUE,
  DarkBackgroundWhite     = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
  LightBackgroundBlue     = BACKGROUND_INTENSITY | BACKGROUND_BLUE,
  LightBackgroundGreen    = BACKGROUND_INTENSITY | BACKGROUND_GREEN,
  LightBackgroundRed      = BACKGROUND_INTENSITY | BACKGROUND_RED,
  LightBackgroundCyan     = BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN,
  LightBackgroundYellow   = BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_RED,
  LightBackgroundMagenta  = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE,
  LightBackgroundWhite    = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
  RestoreDefaultColor     = 0
};

/*!
 * \internal
 * Opérateur de sortie vers flux permettant de changer la couleur de sortie console.
 */
inline std::ostream& operator<<(std::ostream& out, Color color)
{
#ifndef NO_VT100_SUPPORT
  switch (color)
  {
  case Color::DarkForegroundBlue:
    out << "\x1B[34m";
    break;
  case Color::DarkForegroundGreen:
    out << "\x1B[32m";
    break;
  case Color::DarkForegroundRed:
    out << "\x1B[31m";
    break;
  case Color::DarkForegroundCyan:
    out << "\x1B[36m";
    break;
  case Color::DarkForegroundYellow:
    out << "\x1B[33m";
    break;
  case Color::DarkForegroundMagenta:
    out << "\x1B[35m";
    break;
  case Color::DarkForegroundWhite:
    out << "\x1B[37m";
    break;
  case Color::LightForegroundBlue:
    out << "\x1B[1;34m";
    break;
  case Color::LightForegroundGreen:
    out << "\x1B[1;32m";
    break;
  case Color::LightForegroundRed:
    out << "\x1B[1;31m";
    break;
  case Color::LightForegroundCyan:
    out << "\x1B[1;36m";
    break;
  case Color::LightForegroundYellow:
    out << "\x1B[1;33m";
    break;
  case Color::LightForegroundMagenta:
    out << "\x1B[1;35m";
    break;
  case Color::LightForegroundWhite:
    out << "\x1B[1;37m";
    break;
  case Color::DarkBackgroundBlue:
    out << "\x1B[44m";
    break;
  case Color::DarkBackgroundGreen:
    out << "\x1B[42m";
    break;
  case Color::DarkBackgroundRed:
    out << "\x1B[41m";
    break;
  case Color::DarkBackgroundCyan:
    out << "\x1B[46m";
    break;
  case Color::DarkBackgroundYellow:
    out << "\x1B[43m";
    break;
  case Color::DarkBackgroundMagenta:
    out << "\x1B[45m";
    break;
  case Color::DarkBackgroundWhite:
    out << "\x1B[47m";
    break;
  case Color::LightBackgroundBlue:
    out << "\x1B[1;44m";
    break;
  case Color::LightBackgroundGreen:
    out << "\x1B[1;42m";
    break;
  case Color::LightBackgroundRed:
    out << "\x1B[1;41m";
    break;
  case Color::LightBackgroundCyan:
    out << "\x1B[1;46m";
    break;
  case Color::LightBackgroundYellow:
    out << "\x1B[1;43m";
    break;
  case Color::LightBackgroundMagenta:
    out << "\x1B[1;45m";
    break;
  case Color::LightBackgroundWhite:
    out << "\x1B[1;47m";
    break;
  case Color::RestoreDefaultColor:
    out << "\x1B[0m";
    break;
  default:
    break;
  }
#endif
  return out;
}

/*! \internal
 * \brief Macro d'aides pour ce fichier
 * \endinternal
 * \brief Ne pas utiliser ! Pour usage interne du Framework.
 */
#define HELP_VERIF_IMP(symbole) \
  __if_not_exists(symbole) { \
    nNbFailedTests++; \
    std::cout<<"Test ligne "<<__LINE__<<" : "; \
    std::cout<<Color::LightForegroundRed<<"Echec - Le symbole \"" #symbole "\" n'est pas implémenté."<<std::endl; \
    std::cout<<Color::RestoreDefaultColor; \
  } \

/*!
 * \brief Affiche une notification au cours des tests
 * 
 * \param text
 * Texte à afficher dans la notification.
 * 
 * Affiche la notification "text" en cyan brillant dans la console à l'aide de l'objet \c cout. 
 *
 */
#define NOTICE(text) \
  std::cout<<Color::LightForegroundCyan<<text<<Color::RestoreDefaultColor<<'\n';

#ifdef _MSC_VER
/*!
 * \brief Macro de vérification de prérequis d'implémentation
 *
 * \param symbole
 * Symbole dont l'implémentation est requise.
 *
 * \param operation
 * Opération à réaliser.
 *
 * Vérifie que le "symbole" soit implémenté puis, si oui, réalise l'opération demandée.
 *
 * \see BEGIN_TESTS | END_TESTS | TEST_IMP(symbole)
 */
#define VERIF_IMP_1(symbole, operation) \
  HELP_VERIF_IMP(symbole) \
  __if_exists(symbole){ operation; }

/*!
 * \brief Macro de vérification de prérequis d'implémentation
 *
 * \param symbole1
 * Symbole dont l'implémentation est requise.
 *
 * \param symbole2
 * Symbole dont l'implémentation est requise.
 *
 * \param operation
 * Opération à réaliser.
 *
 * Vérifie que les "symbole1" et "symbole2" soient implémentés puis, si oui, réalise l'opération demandée.
 *
 * \see BEGIN_TESTS | END_TESTS | TEST_IMP(symbole)
 */
#define VERIF_IMP_2(symbole1, symbole2, operation) \
  HELP_VERIF_IMP(symbole1) \
  HELP_VERIF_IMP(symbole2) \
  __if_exists(symbole1){ \
    __if_exists(symbole2){ \
      operation; \
    } \
  }

/*!
 * \brief Macro de vérification de prérequis d'implémentation
 *
 * \param symbole1
 * Symbole dont l'implémentation est requise.
 *
 * \param symbole2
 * Symbole dont l'implémentation est requise.
 *
 * \param symbole3
 * Symbole dont l'implémentation est requise.
 *
 * \param operation
 * Opération à réaliser.
 *
 * Vérifie que les "symbole1", "symbole2" et "symbole3" soient implémentés puis, si oui, réalise l'opération demandée.
 *
 * \see BEGIN_TESTS | END_TESTS | TEST_IMP(symbole)
 */
#define VERIF_IMP_3(symbole1, symbole2, symbole3, operation) \
  HELP_VERIF_IMP(symbole1) \
  HELP_VERIF_IMP(symbole2) \
  HELP_VERIF_IMP(symbole3) \
  __if_exists(symbole1){ \
    __if_exists(symbole2){ \
      __if_exists(symbole3){ \
        operation; \
      } \
    } \
  }

/*!
 * \brief Macro de vérification d'implémentation d'un symbole
 * 
 * \param symbole
 * Symbole dont la présence doit être vérifiée.
 * 
 * Teste que le "symbole" est bien défini. En cas d'échec, incrémente la variable 
 * \c nNbFailedTests, en cas de succès, incrémente la variable \c nNbSucceededTests.
 *
 * \remark
 * Les variables \c nNbSucceededTests et \c nNbFailedTests sont déclarées et initialisées par la 
 * macro BEGIN_TESTS. La macro TEST ne peut être utilisée qu'entre les macros BEGIN_TESTS et 
 * END_TESTS.
 *
 * \see BEGIN_TESTS | END_TESTS | VERIF_IMP_1(symbole, operation)
 */
#define TEST_IMP(symbole) \
  std::cout<<"Test ligne "<<__LINE__<<" : "; \
  __if_exists(symbole) { nNbSucceededTests++; std::cout<<Color::LightForegroundGreen<<"Ok"; } \
  __if_not_exists(symbole) { nNbFailedTests++; std::cout<<Color::LightForegroundRed<<"Echec"; } \
  std::cout<<Color::RestoreDefaultColor<<" : Vérification de l'implémentation du symbole " #symbole<<std::endl; 
#endif //MSVC

 /*!
  * \brief Macro de test
  *
  * \param text
  * Texte d'explication du test. Est affiché en début de ligne de test.
  *
  * \param operation
  * Opération à tester.
  *
  * \param resultat
  * Résultat attendu de l'opération.
  *
  * Teste que l'"operation" obtient bien le bon "resultat". En cas d'échec, incrémente la variable
  * \c nNbFailedTests, en cas de succès, incrémente la variable \c nNbSucceededTests.
  *
  * \remark
  * Les variables \c nNbSucceededTests et \c nNbFailedTests sont déclarées et initialisées par la
  * macro BEGIN_TESTS. La macro TEST ne peut être utilisée qu'entre les macros BEGIN_TESTS et
  * END_TESTS.
  *
  * \see BEGIN_TESTS | END_TESTS
  */
#define TEST(text, operation, resultat) \
{\
  std::cout<<"Test ligne "<<__LINE__<<" : "; \
  std::cout<<(((operation) == resultat) ? (nNbSucceededTests++, std::cout<<Color::LightForegroundGreen, "Ok") : (nNbFailedTests++, std::cout<<Color::LightForegroundRed, "Echec")); \
  std::cout<<Color::RestoreDefaultColor<<" : "<<text<<" : "<<"Teste que \"" #operation "\" soit égal à \"" #resultat "\""<<std::endl; \
}

/*!
 * \brief Macro de test d'exceptions
 *
 * \param text
 * Texte d'explication du test. Est affiché en début de ligne de test.
 *
 * \param operation
 * Opération à tester qui doit lancer une exception.
 *
 * \param type_exception
 * Type d'exception à recevoir. Paramètre de catch, par exemple <CODE>std::runtime_error&</CODE>.
 *
 * Teste que l'"operation" lance bien une exception du type attendu. En cas d'échec, incrémente la variable
 * \c nNbFailedTests, en cas de succès, incrémente la variable \c nNbSucceededTests.
 *
 * \remark
 * Les variables \c nNbSucceededTests et \c nNbFailedTests sont déclarées et initialisées par la
 * macro BEGIN_TESTS. La macro TEST ne peut être utilisée qu'entre les macros BEGIN_TESTS et
 * END_TESTS.
 *
 * \see BEGIN_TESTS | END_TESTS
 */
#define TEST_EXCEPTION(text, operation, type_exception) \
{\
  std::cout<<"Test ligne "<<__LINE__<<" : "; \
  try {\
    operation;\
    nNbFailedTests++;\
    std::cout << Color::LightForegroundRed << "Echec - Pas d'exception"; \
  }\
  catch (type_exception) {\
    nNbSucceededTests++;\
    std::cout << Color::LightForegroundGreen << "Ok";\
  }\
  catch (...) {\
    nNbFailedTests++;\
    std::cout << Color::LightForegroundRed << "Echec - Mauvaise Exception"; \
  }\
  std::cout << Color::RestoreDefaultColor << " : " << text << " : " << "Teste que \"" #operation "\" lance une exception de type \"" #type_exception "\"\n"; \
}

#ifdef _MSC_VER
/*!
 * \brief Macro de test avec vérification de prérequis d'implémentation
 * 
 * \param symbole1
 * Symbole dont l'implémentation est requise.
 * 
 * \param text
 * Texte d'explication du test. Est affiché en début de ligne de test.
 * 
 * \param operation
 * Opération à tester.
 * 
 * \param resultat
 * Résultat attendu de l'opération.
 *
 * Teste que le "symbole" est implémenté puis applique le test demandé à l'aide de la macro TEST(text, operation, resultat)
 *
 * \see BEGIN_TESTS | END_TESTS | TEST(text, operation, resultat)
 */
#define TEST_VERIF_IMP_1(symbole1, text, operation, resultat) \
{\
  HELP_VERIF_IMP(symbole1) \
  __if_exists(symbole1){ TEST(text,operation,resultat) } \
}

/*!
 * \brief Macro de test avec vérification de prérequis d'implémentation
 * 
 * \param symbole1
 * Symbole dont l'implémentation est requise.
 * \param symbole2
 * Symbole dont l'implémentation est requise.
 * 
 * \param text
 * Texte d'explication du test. Est affiché en début de ligne de test.
 * 
 * \param operation
 * Opération à tester.
 * 
 * \param resultat
 * Résultat attendu de l'opération.
 *
 * Teste que les symboles sont implémentés puis applique le test demandé à l'aide de la macro TEST(text, operation, resultat)
 *
 * \see BEGIN_TESTS | END_TESTS | TEST(text, operation, resultat)
 */
#define TEST_VERIF_IMP_2(symbole1, symbole2, text, operation, resultat) \
{\
  HELP_VERIF_IMP(symbole1) \
  HELP_VERIF_IMP(symbole2) \
  __if_exists(symbole1){ \
    __if_exists(symbole2){ \
      TEST(text,operation,resultat) \
    } \
  } \
}

/*!
 * \brief Macro de test avec vérification de prérequis d'implémentation
 * 
 * \param symbole1
 * Symbole dont l'implémentation est requise.
 * \param symbole2
 * Symbole dont l'implémentation est requise.
 * \param symbole3
 * Symbole dont l'implémentation est requise.
 * 
 * \param text
 * Texte d'explication du test. Est affiché en début de ligne de test.
 * 
 * \param operation
 * Opération à tester.
 * 
 * \param resultat
 * Résultat attendu de l'opération.
 *
 * Teste que les symboles sont implémentés puis applique le test demandé à l'aide de la macro TEST(text, operation, resultat)
 *
 * \see BEGIN_TESTS | END_TESTS | TEST(text, operation, resultat)
 */
#define TEST_VERIF_IMP_3(symbole1, symbole2, symbole3, text, operation, resultat) \
{\
  HELP_VERIF_IMP(symbole1) \
  HELP_VERIF_IMP(symbole2) \
  HELP_VERIF_IMP(symbole3) \
  __if_exists(symbole1){ \
    __if_exists(symbole2){ \
      __if_exists(symbole3){ \
        TEST(text,operation,resultat) \
      } \
    } \
  } \
}

/*!
 * \brief Macro de construction d'objet avec vérification de prérequis d'implémentation
 *
 * \param classname
 * Nom de la classe à instancier.
 *
 * \param objname
 * Nom de l'objet instancié.
 *
 * Vérifie que la classe \c classname est implémentée puis l'instancie par l'objet \c objname.
 *
 * \see BEGIN_TESTS | END_TESTS | TEST(text, operation, resultat)
 */
#define CONSTRUCT_VERIF_IMP(classname, objname) \
  HELP_VERIF_IMP(classname) \
  __if_exists(classname) { classname objname ; }

/*!
 * \brief Macro de destruction d'objet pointé avec vérification de prérequis d'implémentation
 *
 * \param ptrname
 * Nom du pointeur à supprimer.
 *
 * Vérifie que la variable \c ptrname existe puis la détruit à l'aide de l'opérateur \c delete.
 *
 * \see BEGIN_TESTS | END_TESTS | TEST(text, operation, resultat)
 */
#define DELETE_VERIF_IMP(ptrname) \
  HELP_VERIF_IMP(ptrname) \
  __if_exists(ptrname) { delete ptrname ; }

#endif //_MSC_VER
/*!
 * \def BEGIN_TESTS
 * \brief Démarrage des tests
 * 
 * Doit être utilisée avant de commencer les tests à l'aide de la macro \c TEST .
 *
 * \see TEST | END_TESTS
 */
#if defined(_DEBUG) && defined(_MSC_VER)
#define BEGIN_TESTS \
  { \
    _CrtMemState mem1, mem2, memdiff; \
    _CrtMemCheckpoint(&mem1); \
    { \
      int nNbFailedTests = 0; \
      int nNbSucceededTests = 0; \
      try {
#else
#define BEGIN_TESTS \
  { \
    int nNbFailedTests = 0; \
    int nNbSucceededTests = 0; \
    try { 
#endif //def _DEBUG

/*!
 * \def END_TESTS
 * \brief Termine les tests
 * 
 * Doit être utilisée à la fin de la liste de tests. La macro affiche un récapitulatif sur le nombre de tests effectués et le nombre de tests échoués.
 *
 * \remark 
 * En mode DEBUG, cette macro vérifie qu'il n'y a pas eu de fuites mémoire depuis l'utilisation de BEGIN_TESTS. 
 *
 * \see TEST | BEGIN_TESTS
 */
#if defined(_DEBUG) && defined(_MSC_VER)
#define END_TESTS \
      } catch(...) { \
        nNbFailedTests++; \
        std::cout<<std::endl<<Color::LightForegroundRed<<"Une exception non gérée a été rencontrée"<<Color::RestoreDefaultColor<<std::endl; \
      } \
      std::cout<<std::endl; \
      std::cout<<"Nombre de tests réalisés : "<<nNbSucceededTests+nNbFailedTests<<std::endl; \
      std::cout<<(nNbFailedTests > 0 ? Color::LightForegroundRed : Color::LightForegroundGreen)<<"Nombre de tests échoués : "<<nNbFailedTests<<std::endl; \
    } \
    _CrtMemCheckpoint(&mem2); \
    if(_CrtMemDifference(&memdiff, &mem1, &mem2)) \
    { \
      _CrtMemDumpAllObjectsSince(&mem1); \
      std::cout<<Color::LightForegroundRed<<"Des fuites mémoires ont été détectées, vérifiez vos allocations et désallocations !"<<std::endl; \
    } \
    else \
      std::cout<<Color::LightForegroundGreen<<"Aucune fuite mémoire détectée."<<std::endl; \
    std::cout<<Color::RestoreDefaultColor; \
  }
#else
#define END_TESTS \
    } catch(...) { \
      nNbFailedTests++; \
      std::cout<<std::endl<<Color::LightForegroundRed<<"Une exception non gérée a été rencontrée"<<Color::RestoreDefaultColor<<std::endl; \
    } \
    std::cout<<std::endl; \
    std::cout<<"Nombre de tests réalisés : "<<nNbSucceededTests+nNbFailedTests<<std::endl; \
    std::cout<<(nNbFailedTests > 0 ? Color::LightForegroundRed : Color::LightForegroundGreen)<<"Nombre de tests échoués : "<<nNbFailedTests<<std::endl; \
  } \
  std::cout<<Color::LightForegroundYellow<<"Détection des fuites mémoires impossible en mode Release."<<Color::RestoreDefaultColor<<std::endl;
#endif //def _DEBUG

