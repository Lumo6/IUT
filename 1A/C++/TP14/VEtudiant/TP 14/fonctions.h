/*!
 *
 * \brief Déclaration des fonctions principales du programme. 
 *
 * \author Benjamin ALBOUY-KISSI
 * \date 2009-2015
 * \version 1.1
 */
#ifndef FONCTIONS_H
#define FONCTIONS_H

#include "matrice.h"

//! \brief Cree une matrice. 
void CreerMatrice(CMatrice& mat);
//! \brief Affiche une matrice. 
void AfficherMatrice(const CMatrice& mat);
//! \brief Ajoute deux matrices dans une troisième. 
void AjouterMatrice(CMatrice& matA, const CMatrice& matB, const CMatrice& matC);
//! \brief Ajoute deux matrices dans la première de l'opération. 
void AjouterMatrice2(CMatrice& matA, const CMatrice& matB);
//! \brief Soustrait deux matrices dans une troisième. 
void SoustraireMatrice(CMatrice& matA, const CMatrice& matB, const CMatrice& matC);
//! \brief Soustrait deux matrices dans la première de l'opération. 
void SoustraireMatrice2(CMatrice& matA, const CMatrice& matB);
//! \brief Multiplie deux matrices dans une troisième. 
void MultiplierMatrice(CMatrice& matA, const CMatrice& matB, const CMatrice& matC);
//! \brief Vérifie l'égalité entre deux matrices. 
void EgaliteMatrice(const CMatrice& matA, const CMatrice& matB);
//! \brief Vérifie l'inégalité entre deux matrices. 
void DifferenceMatrice(const CMatrice& matA, const CMatrice& matB);

#endif //FONCTIONS_H
