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

void CEllispse::Afficher() const
{
	LibGraph2::ILibGraph2* libgraph = LibGraph2::GetLibGraph2();
	CForme::Afficher();
	libgraph->drawEllipse(GetBounds());
}
