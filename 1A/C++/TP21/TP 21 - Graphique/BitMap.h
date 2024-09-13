/*!
 * \file  "BitMap.h"
 *
 * \brief Déclaration de la classe CBitMap. 
 *
 */
#pragma once
#include "incLibGraph2.h"
#include "..\TP 21 - Test\Matrice.h"
#include <vector>

/*!
 * \brief
 * Gère une image sous forme de tableau de pixels.
 * 
 */
class CBitMap
{
  //!\brief Tableau de pixels organisé ligne par ligne du haut vers le bas et de gauche à droite.
  std::vector<LibGraph2::ARGB> m_vPixels;
  //!\brief Largeur de l'image
  int m_nWidth = 0;
  //!\brief Hauteur de l'image
  int m_nHeight = 0;
  void LoadImagePPM(const LibGraph2::CString& strFileName);
  void Alloc(int width, int height);

public:
  CBitMap() = default;
  CBitMap(const LibGraph2::CString& strFileName);

  //!\brief Accesseur de la largeur de l'image
  int GetWidth() const { return m_nWidth; }
  //!\brief Accesseur de la hauteur de l'image
  int GetHeight() const { return m_nHeight; }

  void Draw(const LibGraph2::CPoint& pos) const;

  void Transform(CMatrice<double>&
    );
};

