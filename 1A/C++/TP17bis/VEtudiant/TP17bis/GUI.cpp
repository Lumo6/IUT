#include "GUI.h"

void CGUI::drawOneCell(const CCell& cell, double dAnim, size_t i, size_t j) const
{
  m_pLibgraph2->setPen(LibGraph2::MakeARGB(0, 0, 0, 0), 0.0f);
  if (cell.IsDying())
  {
    m_pLibgraph2->setSolidBrush(LibGraph2::MakeARGB(static_cast<BYTE>(255 * (1.0 - dAnim)), 0, 0, 0));
  }
  else if (cell.IsNascent())
  {
    m_pLibgraph2->setSolidBrush(LibGraph2::MakeARGB(static_cast<BYTE>(255 * dAnim), 0, 0, 0));
  }
  else
  {
    m_pLibgraph2->setSolidBrush(LibGraph2::MakeARGB(255, 0, 0, 0));
  }

  m_pLibgraph2->drawRectangle({
    LibGraph2::CPoint(j * m_szCellSize.m_fWidth, i * m_szCellSize.m_fHeight),
    m_szCellSize });
}

/*!
 * L'affichage consiste principalement à dessiner des rectangles noirs pour les cellules vivantes.
 * 
 * Pour rendre l'animation plus "fluide", entre chaque pas d'animation, les états transitoires des 
 * cellules (Nascent et Dying) sont affichés avec transition douce vers l'état suivant. Les transitions
 * sont Nascent -> Adult (la cellule apparait en fondu) et Dying -> Dead (la cellule disparait en fondu)
 * 
 * Si l'application est en mode "Initialisation", aucune animation de transition n'est affichée.
 * 
 * \todo Complétez cette fonction pour afficher toutes les cellules de la boite de Petri. 
 * - **Note 1** : La boîte de Petri est accessible via la donnée membre m_PetriDish. 
 * - **Note 2** : Vous devrez également ajouter à la classe CPetriDish un accesseur vers les cellules. 
 * Par exemple, vous pourriez lui ajouter l'opérateur operator() prenant en paramètre la position 
 * (i,j) de la cellule à retourner.
 * - **Note 3** : N'oubliez pas qu'il existe la méthode CGUI::drawOneCell qui fait tout le travail d'affichage
 * pour une cellule passée en paramètre. UTILISEZ-LA !
 */
void CGUI::DrawIt() 
{
  double dAnim = 1.0;
  if (!m_bInitMode)
  {
    dAnim = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - m_lastTick).count()
      / static_cast<double>(m_StepDuration.count());
    if (dAnim >= 1.0)
    {
      m_lastTick = std::chrono::high_resolution_clock::now();
      dAnim = 0.0;
      m_PetriDish.Update();
    }
    m_pLibgraph2->askForRefresh();
  }
  for (size_t i = 0; i < m_PetriDish.Size(); i++)
  {
    for (size_t j = 0; j < m_PetriDish.Size(); j++)
    {
        auto cellp = m_PetriDish(i, j);
        if (cellp) {
            auto cell = *cellp;
            drawOneCell(cell, dAnim, i, j);
        }
    }
  }
}

/*!
 * En mode "Initialisation", les coordonnées de la souris sont utilisées pour détecter la cellule cliquée.
 * Si la cellule est vivante, elle est tuée, sinon elle est créée.
 * 
 * \param ptMouse Coordonnées de la souris
 */
void CGUI::MousePressed(const LibGraph2::CPoint& ptMouse)
{
  if (!m_bInitMode)
    return;
  unsigned int i, j;
  i = static_cast<unsigned int>(ptMouse.m_fY / m_szCellSize.m_fHeight);
  j = static_cast<unsigned int>(ptMouse.m_fX / m_szCellSize.m_fWidth);
  if (m_PetriDish.IsAlive(i, j))
    m_PetriDish.ForceDead(i, j);
  else
    m_PetriDish.ForceAlive(i, j);
  m_pLibgraph2->askForRefresh();
}

/*!
 * Change le mode de l'application. Si la simulation est lancée, l'application quitte le mode 
 * "Initialisation". Inversement, si la simulation est arrêtée, l'application entre dans le mode
 * "Initialisation".
 * 
 * \param bStart \c true (par défaut) pour lancer la simulation, \c false pour l'arrêter
 */
void CGUI::Simulation(bool bStart)
{
  m_bInitMode = !bStart;
  m_lastTick = std::chrono::high_resolution_clock::now();
  m_pLibgraph2->askForRefresh();
}
