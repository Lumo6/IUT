/*!
 * \file  "Forme.h"
 *
 * \brief Declares the forme class. 
 *
 */
#ifndef FORME_H
#define FORME_H

#include "incLibGraph2.h"

/*!
 * \brief Une forme. 
 *
 * \todo Rendez cette classe polymorphe pour permettre l'affichage correct des 
 * objets de types dérivés par la manipulation d'un pointeur de type CForme
 *
 */
class CForme
{
private:
  //! Sa boîte englobante
  LibGraph2::CRectangle m_rectBounds;

  //! Son point d'origine 
  LibGraph2::CPoint m_ptP1;
  //! Son point d'arrivée 
  LibGraph2::CPoint m_ptP2;

  //! Sa couleur. 
  LibGraph2::ARGB m_colColor = 0xFF000000;
  //! Sa couleur de remplissage. 
  LibGraph2::ARGB m_colFillColor = 0xFFFF0000;
  //! Son epaisseur. 
  float m_fThickness = 1.0f;
  //! Son style de tracé. 
  LibGraph2::pen_DashStyles m_eStyle = LibGraph2::pen_DashStyles::Solid;

  void ComputeBounds();

public:
  virtual void Afficher() const;
  void SetP1(const LibGraph2::CPoint& pt);
  void SetP2(const LibGraph2::CPoint& pt);
  //!\brief Retourne la boîte englobante de la forme
  const LibGraph2::CRectangle& GetBounds() const {return m_rectBounds;}

  //!\brief Retourne sa couleur
  LibGraph2::ARGB           GetColor()     const { return m_colColor; }
  //!\brief Retourne sa couleur de remplissage
  LibGraph2::ARGB           GetFillColor() const { return m_colFillColor; }
  //!\brief Retourne son epaisseur
  float                     GetThickness() const { return m_fThickness; }
  //!\brief Retourne son style de trait
  LibGraph2::pen_DashStyles GetStyle()     const { return m_eStyle; }

  //!\brief Définit sa couleur
  //!\param color Nouvelle couleur
  void SetColor(LibGraph2::ARGB color) { m_colColor = color; }
  //!\brief Définit sa couleur de remplissage
  //!\param color Nouvelle couleur de remplissage
  void SetFillColor(LibGraph2::ARGB color) { m_colFillColor = color; }
  //!\brief Définit son epaisseur
  //!\param thickness Nouvelle épaisseur
  void SetThickness(float thickness) { m_fThickness = thickness; }
  //!\brief Définit son style de trait
  //!\param style Nouveau style
  void SetStyle(LibGraph2::pen_DashStyles style) { m_eStyle = style; }

};

#endif FORME_H
