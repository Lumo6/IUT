/*!
 * \file  "Arc.cpp"
 *
 * \brief Implements the arc class. 
 *
 *
 * \todo Définir dans ce fichier les fonctions membres de la classe CArc
 */

#include "StdAfx.h"
#include "Arc.h"
#include "incLibGraph2.h"

void CArc::Afficher() const
{
	CForme::Afficher();
	LibGraph2::GetLibGraph2Exp()->drawArc(GetBounds(),m_angDebut,m_angBal);
}

void CArc::SetAngBal(float n)
{
	m_angBal = n;
}
