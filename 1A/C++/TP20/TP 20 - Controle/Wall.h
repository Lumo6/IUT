/// 
/// \file  "Wall.h"
/// 
/// \brief Déclaration de la classe CWall. 
/// 
/// 
#pragma once
#include "Clock.h"
#include "gui.h"
#include <array>
#include <memory>

/// 
/// \brief
/// Classe représentant un mur.
/// 
/// Cette classe gère un mur sur lequel sont suspendues des horloges. Les horloges peuvent
/// être de différentes sortes (électroniques ou mécaniques). Un mur est affiché
/// graphiquement avec les horloges qu'il supporte.
/// 
/// La classe CWall est déclarée dans le fichier Wall.h.
/// \code
/// #include "Wall.h"
/// \endcode
/// 
/// 
class CWall
{
public:
  /// \brief Constante définissant le nombre de colonnes d'horloges possibles sur le mur
  static const size_t sc_nNbCol = 10;
  /// \brief Constante définissant le nombre de lignes d'horloges possibles sur le mur
  static const size_t sc_nNbLig = 4;
  /// \brief Constante définissant le nombre d'horloges possibles sur le mur
  static const size_t sc_nNbCases = sc_nNbCol * sc_nNbLig;

private:
  /// \brief Passe à true lorsqu'une horloge mécanique cesse de fonctionner
  bool m_bGameOver = false;
  /// \brief tableau de pointeur vers les horloges suspendues sur le mur
  std::array<std::shared_ptr<CClock>, sc_nNbCases> m_Clocks;  

  /// \brief Indice de la case à afficher en surbrillance ou -1 si aucune.
  int m_nHighLightCase = -1;

  /// \brief Objet de type CGUI utilisé pour réaliser l'affichage des différentes informations
  std::shared_ptr<CGUI> m_pGUI;

  int GetCaseAt(const CPoint2D& RelPixelPos) const;

public:
  CWall(std::shared_ptr<CGUI> pGUI);
  void Afficher(const CPoint2D& AbsPixelPos)const;
  std::shared_ptr<CClock> GetClock(const CPoint2D& RelPixelPos);
  bool HangClock(const CPoint2D& RelPixelPos, std::shared_ptr<CClock> pClock);
  void HighLight(const CPoint2D& RelPixelPos);
  void Tick();
};

