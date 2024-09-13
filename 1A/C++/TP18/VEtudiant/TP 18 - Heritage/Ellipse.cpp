/*!
 * \file  "Ellipse.cpp"
 *
 * \brief Implements the ellipse class. 
 *
 *
 * \todo Définir dans ce fichier les fonctions membres de la classe CEllipse
 */
#include "StdAfx.h"
#include "Ellipse.h"
#include "incLibGraph2.h"

void CEllipse::Afficher() const
{
	CForme::Afficher();
	LibGraph2::GetLibGraph2Exp()->drawEllipse(GetBounds());
}
