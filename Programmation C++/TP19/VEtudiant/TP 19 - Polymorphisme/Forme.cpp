/*!
 * \file  "Forme.cpp"
 *
 * \brief Implements the forme class. 
 *
 */
#include "StdAfx.h"
#include "Forme.h"
#include "incLibGraph2.h"

/*!
 * \brief Prépare l'affichage de cette forme. 
 */
void CForme::Afficher() const 
{
  LibGraph2::GetLibGraph2()->setPen(m_colColor, m_fThickness, m_eStyle);
  LibGraph2::GetLibGraph2()->setSolidBrush(m_colFillColor);
}

/*!
 * \brief Définit la position du coin haut-gauche de cet objet. 
 */
void CForme::SetP1(const LibGraph2::CPoint& pt) 
{
  m_ptP1 = pt;
  ComputeBounds();
}

/*!
 * \brief Définit la position du coin bas-droit de cet objet. 
 */
void CForme::SetP2(const LibGraph2::CPoint& pt) 
{
  m_ptP2 = pt;
  ComputeBounds();
}

/*!
 * \brief Calcule la boîte englobante à partir de m_ptP1 et m_ptP2. 
 */
void CForme::ComputeBounds()
{
  LibGraph2::CPoint ptTopLeft(min(m_ptP1.m_fX, m_ptP2.m_fX), min(m_ptP1.m_fY, m_ptP2.m_fY));
  LibGraph2::CSize szSize(abs(m_ptP1.m_fX - m_ptP2.m_fX), abs(m_ptP1.m_fY - m_ptP2.m_fY));
  m_rectBounds = LibGraph2::CRectangle(ptTopLeft, szSize);
}
