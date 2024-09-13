#pragma once
#include "incLibGraph2.h"
#include "PetriDish.h"
#include <chrono>
using namespace std::chrono_literals;

/*!
 * \brief Gère l'interface graphique de l'application.
 * 
 * L'interface possède deux modes :
 * - Le mode "Initialisation"
 * C'est le mode par défaut, lorsque la simulation ne s'exécute pas. Dans ce mode, l'utilisateur peut
 * cliquer dans la fenêtre pour faire naitre ou mourir des cellules
 * - Le mode "Simulation"
 * Dans ce mode, l'application exécute la simulation. Les interactions avec la souris sont désactivées.
 */
class CGUI
{
  const LibGraph2::CSize m_szCellSize{ 10.0f, 10.0f };
  CPetriDish& m_PetriDish;
  LibGraph2::ILibGraph2* m_pLibgraph2;
  bool m_bInitMode = true;
  std::chrono::milliseconds m_StepDuration{ 400 };
  std::chrono::high_resolution_clock::time_point m_lastTick;

  void drawOneCell(const CCell& cell, double dAnim, size_t i, size_t j) const;

public:
  /*!
   * Construit la GUI en l'attachant à une boîte de Petri.
   * 
   * \param PetriDish Une référence vers la boîte de Petri à utiliser
   */
  CGUI(CPetriDish& PetriDish) :
    m_PetriDish{ PetriDish }
  {
    m_pLibgraph2 = LibGraph2::GetLibGraph2();
    m_pLibgraph2->show(LibGraph2::CSize{ m_szCellSize.m_fWidth * m_PetriDish.Size() , m_szCellSize.m_fHeight * m_PetriDish.Size() });
  }

  //!\brief Affiche l'interface
  void DrawIt();

  //!\brief Fonction appelée lorsque la souris est enfoncée
  void MousePressed(const LibGraph2::CPoint& ptMouse);

  //!\brief Démarre ou arrête la simulation
  void Simulation(bool bStart = true);

  //!\brief Retourne la durée du pas de simulation
  std::chrono::milliseconds StepDuration() const { return m_StepDuration; }
  //!\brief Définit la durée du pas de simulation
  void SetStepDuration(std::chrono::milliseconds newDuration) { m_StepDuration = std::max(newDuration, 50ms); }

};

