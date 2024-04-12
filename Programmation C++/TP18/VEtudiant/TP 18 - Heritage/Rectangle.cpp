/*!
 * \file  Rectangle.cpp
 *
 * \brief Implements the rectangle class. 
 *
 *
 * \todo Définir dans ce fichier les fonctions membres de la classe CRect
 */
#include "StdAfx.h"
#include "Rectangle.h"
#include "incLibGraph2.h"

void CRect::Afficher() const
{
	CForme::Afficher();
	LibGraph2::GetLibGraph2Exp()->drawRectangle(GetBounds());
}
