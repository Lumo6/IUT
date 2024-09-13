/// 
/// \file  "gui.h"
/// 
/// \brief Déclaration de la classe CGUI.
/// 
/// 
#pragma once
#include "incLibGraph2.h"
#include "vecteur2D.h"

class CAutoClock;
class CMechClock;

/// \brief Classe de gestion de l'interface graphique
/// 
/// Cette classe regroupe toutes les fonctionnalités d'interaction avec l'utilisateur. Elle est
/// basée sur LibGraph2 pour cela.
/// 
class CGUI
{
  /// \brief Pointeur vers l'objet principal LibGraph2 
  LibGraph2::ILibGraph2* m_pLibGraph;
  /// \brief Fonction utilitaire de conversion de CPoint2D en LibGraph2::CPoint 
  LibGraph2::CPoint toLibGraph2Point(const CPoint2D& pt2D) const { return LibGraph2::CPoint(static_cast<float>(pt2D.X()), static_cast<float>(pt2D.Y())); }
  /// \brief Fonction utilitaire de conversion de CSize2D en LibGraph2::CSize 
  LibGraph2::CSize toLibGraph2Size(const CSize2D& sz2D) const { return LibGraph2::CSize(static_cast<float>(sz2D.X()), static_cast<float>(sz2D.Y())); }
  /// \brief Fonction utilitaire de conversion de LibGraph2::CSize en CSize2D 
  CSize2D toSize2D(const LibGraph2::CSize& lg2Sz) const { return CSize2D(lg2Sz.m_fWidth, lg2Sz.m_fHeight); }

public:
  /// \brief Constante définissant la position relative du coin supérieur gauche du mur dans la fenêtre.
  const CPoint2D mc_ptWholeWallRelPos = CPoint2D{ 0.0, 106.0 };
  /// \brief Constante définissant la taille totale de l'image du mur.
  const CSize2D mc_szWholeWallSize = CSize2D{ 1280.0, 720.0-106.0 };
  /// \brief Constante définissant la taille du mur au sein de l'image du mur.
  const CSize2D mc_szWall = CSize2D{ 1280.0, 720.0 - 106.0 };
  /// \brief Constante définissant la position du mur au sein de l'image du mur.
  const CSize2D mc_ptWallRelPos = CSize2D{ 0.0, 0.0 };
  /// \brief Constante définissant la taille de la représentation graphique d'une horloge.
  const CSize2D mc_ClockSize = CSize2D{ 96.0, 96.0 };

public:
  /// \brief Constructeur
  CGUI() { m_pLibGraph = LibGraph2::GetLibGraph2(); }

  /// \brief Retourne la taille de la fenêtre graphique
  /// \return Un objet CSize2D représentant la taille de la fenêtre graphique
  CSize2D getWndSize()const{ return toSize2D(m_pLibGraph->getSize()); }

  void drawAutoClock(const CPoint2D& ptPos, const CAutoClock& clock) const;
  void drawMechClock(const CPoint2D& ptPos, const CMechClock& clock) const;

  void drawWall(const CPoint2D& ptPos)const;
  void drawHighlight(const CPoint2D& ptPos, const CSize2D& szSize)const;

  void drawString(const std::string& strText) const;

  bool askForValue(std::string& value, const std::string& title, const std::string& prompt) const;

  void showExclamation(const std::string& title, const std::string& prompt) const;
};

