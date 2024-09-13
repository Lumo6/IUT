/*!
 * \file  "TP.h"
 *
 * \brief Déclaration de la classe CTP. 
 *
 */
#pragma once
#include "BitMap.h"

/*!
 * \brief
 * Classe de gestion du TP.
 * 
 * Cette classe est instanciée une seule fois pour répresenter toutes les actions du TP.
 * 
 * \todo 
 * Ajouter à la classe CTP 3 matrices membres privés. Ces matrices 3x3 doivent travailler sur des \c double.\n
 * Une matrice \c m_matRot pour la matrice de rotation.\n
 * Une matrice \c m_matScale pour la matrice de mise à l'échelle.\n
 * Une matrice \c m_matTear pour la matrice de déchirement.\n
 */
class CTP
{
  //!\brief Image originale
  CBitMap m_bmp;
  //!\brief Image transformée
  CBitMap m_bmpTrans;

  CMatrice<double> m_matRot = CMatrice<double>(3, 3);;
  CMatrice<double> m_matScale = CMatrice<double>(3, 3);;
  CMatrice<double> m_matTear = CMatrice<double>(3, 3);;

  //!\brief Angle de rotation
  double m_dAngleRad;

  void ComputeTransform();

public:
  CTP(void);

  bool OpenPPMFile();
  void IncreaseAngle();
  void DecreaseAngle();
  void IncreaseScaleX();
  void DecreaseScaleX();
  void IncreaseScaleY();
  void DecreaseScaleY();
  void IncreaseTearX();
  void DecreaseTearX();
  void IncreaseTearY();
  void DecreaseTearY();

  void Draw();
};

