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
  //! Son epaisseur. 
  float m_fThickness = 1.0f;
  //! Son style de tracé. 
  LibGraph2::pen_DashStyles m_eStyle = LibGraph2::pen_DashStyles::Solid;

  void ComputeBounds();

public:
  void Afficher() const;
  void SetP1(const LibGraph2::CPoint& pt);
  void SetP2(const LibGraph2::CPoint& pt);
  //!\brief Retourne la boîte englobante de la forme
  const LibGraph2::CRectangle& GetBounds() const {return m_rectBounds;}

  //!\brief Retourne sa couleur
  LibGraph2::ARGB           GetColor()     const { return m_colColor; }
  //!\brief Retourne son epaisseur
  float                     GetThickness() const { return m_fThickness; }
  //!\brief Retourne son style de trait
  LibGraph2::pen_DashStyles GetStyle()     const { return m_eStyle; }

  //!\brief Définit sa couleur
  //!\param color Nouvelle couleur
  void SetColor(LibGraph2::ARGB color)           { m_colColor = color; }
  //!\brief Définit son epaisseur
  //!\param thickness Nouvelle épaisseur
  void SetThickness(float thickness)             { m_fThickness = thickness; }
  //!\brief Définit son style de trait
  //!\param style Nouveau style
  void SetStyle(LibGraph2::pen_DashStyles style) { m_eStyle = style; }
};

#endif FORME_H
