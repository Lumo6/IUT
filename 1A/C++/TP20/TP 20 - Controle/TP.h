/// 
/// \file  "TP.h"
/// 
/// \brief Déclaration de la classe CTP. 
/// 
/// 
#pragma once
#include "vecteur2D.h"
#include "Wall.h"
#include "MechClock.h"
#include "AutoClock.h"
#include "gui.h"
#include <memory>

/// 
/// \brief
/// Classe "métier" du TP.
/// 
/// Cette classe concentre toutes les actions du programme nécessaires pour le 
/// fonctionnement du programme. Les méthodes publiques sont les points d'entrées 
/// événementiels qui sont appelés par le programme principal en réponse des 
/// interactions de l'utilisateur.
/// 
/// La classe CTP est déclarée dans le fichier TP.h.
/// \code
/// #include "TP.h"
/// \endcode
/// 
/// 
class CTP
{
  CWall m_wall;                             ///< \brief Le mur
  std::shared_ptr<CClock> m_pSelectedClock; ///< \brief L'horloge sélectionnée sur le mur
  std::shared_ptr<CGUI> m_pGUI;             ///< \brief L'objet de dessin

private:
  CPoint2D AbsToRelPixelPos(const CPoint2D& AbsPixelPos) const;
  bool ValidateUTCOffsetString(const std::string& strUTCOffset, std::chrono::minutes& durUTCOffset);

public:
  CTP(std::shared_ptr<CGUI> pGui);

  void Afficher() const;
  std::shared_ptr<CClock> CreateMechClock();
  std::shared_ptr<CClock> CreateAutoClock();
  void SelectClock(const CPoint2D& AbsPixelPos);
  bool HangClock(std::shared_ptr<CClock> pClock, const CPoint2D& AbsPixelPos);
  void TightenSpring();
  void Tick();
  /// \brief Met en surbrillance la case sous la position AbsPixelPos
  /// \param AbsPixelPos Position de la souris par raport au coin suppérieur gauche de la fenêtre
  /// \remark Si aucune case ne se trouve sous la position AbsPixelPos, alors aucune case n'est mise en surbrillance.
  void HighLightCase(const CPoint2D& AbsPixelPos){m_wall.HighLight(AbsToRelPixelPos(AbsPixelPos));}
};

