/*!
 *
 * \brief Déclaration des fonctions de gestion des menus. 
 *
 * \author Benjamin ALBOUY-KISSI
 * \date 2009-2015
 * \version 1.1
 */
#ifndef MENUS_H
#define MENUS_H

#include "matrice.h"

//! \brief Gère les menus. 
char menu(char* texte);
//! \brief Gestion du menu principal. 
void MenuPrincipal(const int nNbMatrices, CMatrice* pMat);
//! \brief Gestion du menu opérations. 
void MenuOperations(const int nNbMatrices, CMatrice* pMat);
//! \brief Gestion du menu vérifications. 
void MenuVerifications(const int nNbMatrices, CMatrice* pMat);

#endif //MENUS_H
