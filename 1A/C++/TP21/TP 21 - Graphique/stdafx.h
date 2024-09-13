/*!
 * \file "StdAfx.h"
 * 
 * \version 2012
 *
 * \brief Fichier de gestion des en-têtes précompilées.
 *
 * fichier Include pour les fichiers Include système standard, ou les fichiers 
 * Include spécifiques aux projets qui sont utilisés fréquemment, et sont 
 * rarement modifiés
 *
 */

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclure les en-têtes Windows rarement utilisés
// Fichiers d'en-tête Windows :
#include <windows.h>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifdef _DEBUG
   #ifndef DBG_NEW
      #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
      #define new DBG_NEW
   #endif
#endif  // _DEBUG
// Fichiers d'en-tête C RunTime
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: faites référence ici aux en-têtes supplémentaires nécessaires au programme
