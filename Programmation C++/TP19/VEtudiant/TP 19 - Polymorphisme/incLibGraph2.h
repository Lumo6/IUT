/*!
 * \file "incLibGraph2.h"
 * 
 * \version 2016
 *
 * \brief Fichier d'inclusion de la bibliothèque LibGraph2.
 *
 * Ce fichier permet de centraliser l'inclusion de la bibliothèque LibGraph2 
 * pour s'assurer que le niveau utilisé de la bibliothèque est bien le même 
 * quelques soient les fichiers sources.
 *
 */
#pragma once
/*!\brief Défini le niveau d'utilisation de LibGraph2 au niveau 3
 */
#define LIBGRAPH2_LEVEL 4
#include <LibGraph2.h>

//!\brief Largeur des imagettes représentant les parties de gâteaux
const int gc_nImgWidth = 83;
//!\brief Hauteur des imagettes représentant les parties de gâteaux
const int gc_nImgHeight = 66;
//!\brief Distance à respecter verticallement entre deux étages (0 -> les étages sont confondus).
const int gc_nImgYOffset = 25;
//!\brief Durée max d'une partie en millisecondes
const DWORD gc_dwMaxTime = 15000;
