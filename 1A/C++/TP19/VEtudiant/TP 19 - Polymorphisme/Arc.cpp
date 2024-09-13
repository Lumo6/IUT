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
    LibGraph2::ILibGraph2* libgraph = LibGraph2::GetLibGraph2();
    CForme::Afficher();
    libgraph->drawArc(GetBounds(), m_startAngle, m_sweepAngle);
}
