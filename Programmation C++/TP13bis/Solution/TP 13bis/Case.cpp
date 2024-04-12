/*!
 * \file "case.cpp"
 * Définition de la classe CCase
 * 
 * Copyright (c) 2015 by Benjamin ALBOUY-KISSI
 *
 * \todo Définissez la classe CCase dans le fichier Case.cpp
 */
//Solution
#include "Case.h"
#include <LibGraph2.h>

using namespace LibGraph2;

/*!
 * \param pCase
 * Case se trouvant à droite de la case courante.
 * 
 * \note 1. La case passée en paramètre se voit affecter la case courante comme case de gauche.
 * \note 2. La définition de la case de droite ne peut se faire que si aucune case n'est déjà affectée à droite.
 *
 * \see
 * CCase::setTopCase | CCase::setLeftCase | CCase::setBottomCase
 */
void CCase::setRightCase(CCase* pCase)
{
  if (!m_pRightCase && pCase && !pCase->m_pLeftCase)
  {
    m_pRightCase = pCase;
    pCase->m_pLeftCase = this;
  }
}

/*!
 * \param pCase
 * Case se trouvant en haut de la case courante.
 * 
 * \note 1. La case passée en paramètre se voit affecter la case courante comme case du bas.
 * \note 2. La définition de la case du haut ne peut se faire que si aucune case n'est déjà affectée en haut.
 *
 * \see
 * CCase::setRightCase | CCase::setLeftCase | CCase::setBottomCase
 */
void CCase::setTopCase(CCase* pCase)
{
  if (!m_pTopCase && pCase && !pCase->m_pBottomCase)
  {
    m_pTopCase = pCase;
    pCase->m_pBottomCase = this;
  }
}

/*!
 * \param pCase
 * Case se trouvant à gauche de la case courante.
 * 
 * \note 1. La case passée en paramètre se voit affecter la case courante comme case de droite.
 * \note 2. La définition de la case de gauche ne peut se faire que si aucune case n'est déjà affectée à gauche.
 *
 * \see
 * CCase::setTopCase | CCase::setRightCase | CCase::setBottomCase
 */
void CCase::setLeftCase(CCase* pCase)
{
  if (!m_pLeftCase && pCase && !pCase->m_pRightCase)
  {
    m_pLeftCase = pCase;
    pCase->m_pRightCase = this;
  }
}

/*!
 * \param pCase
 * Case se trouvant en bas de la case courante.
 * 
 * \note 1. La case passée en paramètre se voit affecter la case courante comme case du haut.
 * \note 2. La définition de la case du bas ne peut se faire que si aucune case n'est déjà affectée en bas.
 *
 * \see
 * CCase::setTopCase | CCase::setLeftCase | CCase::setRightCase
 */
void CCase::setBottomCase(CCase* pCase)
{
  if (!m_pBottomCase && pCase && !pCase->m_pTopCase)
  {
    m_pBottomCase = pCase;
    pCase->m_pTopCase = this;
  }
}

//Fin Solution