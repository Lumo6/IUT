/*!
 * \file  "BitMap.h"
 *
 * \brief Définition de la classe CBitMap. 
 *
 */
#include "StdAfx.h"
#include <cassert>
#include "BitMap.h"
#include <fstream>

using namespace LibGraph2;
using namespace std;

/*!
 * \brief
 * Constructeur depuis un fichier.
 * 
 * Initialise une image depuis un fichier PPM
 *
 * \param strFileName Nom de ficheir à charger
 *
 * \see CBitMap::LoadImagePPM()
 */
CBitMap::CBitMap(const LibGraph2::CString& strFileName)
{
  LoadImagePPM(strFileName);
}

/*!
 * \brief
 * Alloue la mémoire pour l'image avec les dimensions passées en paramètres.
 * 
 * \param width
 * Largeur de l'image.
 * 
 * \param height
 * Hauteur de l'image.
 * 
 * \remarks
 * L'image doit être vide avant d'appeler cette fonction.
 * 
 * \see
 * CBitMap::Free()
 */
void CBitMap::Alloc(int width, int height)
{
  m_vPixels.resize(width * height);
  m_nWidth = width;
  m_nHeight = height;
}

/*!
 * \brief
 * Charge une image depuis un fichier.
 * 
 * \param strFileName
 * Nom du fichier image à charger.
 * 
 * Les formats pris en charges sont : PPM, PGM, PBM et PNM.
 * 
 * \remarks
 * Le format internet doit être de type P6 (format binaire couleur RGB)
 * 
 * \see
 * Separate items with the '|' character.
 */
void CBitMap::LoadImagePPM(const CString& strFileName)
{
  ILibGraph2* pLibgraph = GetLibGraph2();
  ifstream file(strFileName, ios_base::binary | ios_base::in);
  char strMagic[3];
  file.get(strMagic, 3);
  if(strMagic[0] != 'P' || strMagic[1] != '6')
  {
    pLibgraph->guiMessageBox("Erreur", "Le fichier n'a pas un format valide", msgbtn_types::MsgBtnOK, msgicon_types::MsgIcnExclamation);
    return;
  }
  int nMax;
  int nLargeur, nHauteur;
  file>>nLargeur>>nHauteur>>nMax;
  if(nMax > 255)
  {
    pLibgraph->guiMessageBox("Erreur", "Le fichier n'a pas un format valide", msgbtn_types::MsgBtnOK, msgicon_types::MsgIcnExclamation);
    return;
  }
  if(nHauteur*nLargeur > m_nWidth*m_nHeight)
  {
    Alloc(nLargeur, nHauteur);
  }
  else
  {
    m_nWidth = nLargeur;
    m_nHeight = nHauteur;
  }
  ARGB *pCurPixel = m_vPixels.data();
  char cIgnore;
  file.read(&cIgnore,1);
  for(int i=0; i<nHauteur; ++i)
    for(int j=0; j<nLargeur; ++j)
    {
      unsigned char r,g,b;
      file.read((char*)&r,1);
      file.read((char*)&g,1);
      file.read((char*)&b,1);
      *(pCurPixel++)=MakeARGB(255,r,g,b);
    }

  file.close();
}

/*!
 * \brief
 * Affiche l'image.
 * 
 * \param pos
 * Position du coin supérieur gauche de l'image.
 */
void CBitMap::Draw(const LibGraph2::CPoint& pos) const
{
  ILibGraph2* pLibgraph = GetLibGraph2();
  const ARGB* pCurPixel = m_vPixels.data();
  for(int i=0; i<m_nHeight; ++i)
    for(int j=0; j<m_nWidth; ++j)
      pLibgraph->setPixel(CPoint((float)j-m_nWidth/2,(float)i-m_nHeight/2)+pos,*(pCurPixel++));
}

/*!
 * \brief
 * Applique une déformation à l'image.
 * 
 * \param mat
 * Matrice de transformation à appliquer. Doit être de taille 3x3.
 * 
 * \todo 
 * Complétez le code de la fonction CBitMap::Transform() de façon à ce que le
 * calcul se fasse avec des matrices de double. Dans un premier temps, déclarez
 * le paramètre correct.
 */
void CBitMap::Transform(CMatrice<double>& mat
  )
{
  //!\todo Décommentez la ligne suivante dès que vous avez ajouté le paramètre
  assert(mat.GetNbCols() == 3 && mat.GetNbRows() == 3);

  //Calcule la matrice inverse
  //!\todo Instancier une matrice matinv de taille 3x3, puis décommentez le code suivant
  CMatrice matinv = CMatrice<double>(3, 3);
  double a,b,c,d,e,f,g,h,i;
  a = mat(0,0);  b = mat(0,1);  c = mat(0,2);
  d = mat(1,0);  e = mat(1,1);  f = mat(1,2);
  g = mat(2,0);  h = mat(2,1);  i = mat(2,2);
  double det = a*e*i + b*f*g + c*d*h - c*e*g - f*h*a - i*b*d;
  matinv(0,0) = e*i-f*h; matinv(0,1) = c*h-b*i; matinv(0,2) = b*f-c*e;
  matinv(1,0) = f*g-d*i; matinv(1,1) = a*i-c*g; matinv(1,2) = c*d-a*f;
  matinv(2,0) = d*h-e*g; matinv(2,1) = b*g-a*h; matinv(2,2) = a*e-b*d;

  //Calcule les transformés des 4 coins pour connaitre la taille de la nouvelle image
  //!\todo Instancier une matrice pt de taille 3x1, puis décommentez le code suivant
  CMatrice pt = CMatrice<double>(3, 1);
  CPoint topleft;
  CPoint bottomright;
  
  //Coin supérieur gauche
  pt(0, 0) = 0; pt(1, 0) = 0; pt(2, 0) = 1;
  pt = mat * pt;
  topleft.m_fX = (float)(pt(0, 0) / pt(2, 0));
  topleft.m_fY = (float)(pt(1, 0) / pt(2, 0));
  bottomright.m_fX = (float)(pt(0, 0) / pt(2, 0));
  bottomright.m_fY = (float)(pt(1, 0) / pt(2, 0));
  //Coin supérieur droit
  pt(0, 0) = m_nWidth - 1; pt(1, 0) = 0; pt(2, 0) = 1;
  pt = mat * pt;
  topleft.m_fX = min((float)(pt(0, 0) / pt(2, 0)), topleft.m_fX);
  topleft.m_fY = min((float)(pt(1, 0) / pt(2, 0)), topleft.m_fY);
  bottomright.m_fX = max((float)(pt(0, 0) / pt(2, 0)), bottomright.m_fX);
  bottomright.m_fY = max((float)(pt(1, 0) / pt(2, 0)), bottomright.m_fY);
  //Coin inférieur gauche
  pt(0, 0) = 0; pt(1, 0) = m_nHeight - 1; pt(2, 0) = 1;
  pt = mat * pt;
  topleft.m_fX = min((float)(pt(0, 0) / pt(2, 0)), topleft.m_fX);
  topleft.m_fY = min((float)(pt(1, 0) / pt(2, 0)), topleft.m_fY);
  bottomright.m_fX = max((float)(pt(0, 0) / pt(2, 0)), bottomright.m_fX);
  bottomright.m_fY = max((float)(pt(1, 0) / pt(2, 0)), bottomright.m_fY);
  //Coin inférieur droit
  pt(0, 0) = m_nWidth - 1; pt(1, 0) = m_nHeight - 1; pt(2, 0) = 1;
  pt = mat * pt;
  topleft.m_fX = min((float)(pt(0, 0) / pt(2, 0)), topleft.m_fX);
  topleft.m_fY = min((float)(pt(1, 0) / pt(2, 0)), topleft.m_fY);
  bottomright.m_fX = max((float)(pt(0, 0) / pt(2, 0)), bottomright.m_fX);
  bottomright.m_fY = max((float)(pt(1, 0) / pt(2, 0)), bottomright.m_fY);

  //Alloue la mémoire pour la nouvelle image à la nouvelle taille
  int nWidth = (int)(bottomright.m_fX - topleft.m_fX + 0.5f);
  int nHeight = (int)(bottomright.m_fY - topleft.m_fY + 0.5f);
  std::vector<ARGB> vPixels(nWidth * nHeight);

  //Transforme l'image
  ARGB* pCurPixel = vPixels.data();
  for(int i=0; i<nHeight; ++i)
    for(int j=0; j<nWidth; ++j)
    {
      //!\todo Décommentez le code suivant
      //pt(0,0) = j+topleft.m_fX; pt(1,0) = i+topleft.m_fY; pt(2,0) = 1;
      //pt = matinv*pt;
      //int itrans = (int)(pt(1,0)/pt(2,0)+0.5);
      //int jtrans = (int)(pt(0,0)/pt(2,0)+0.5);
      //if(itrans >= 0 && itrans < m_nHeight && jtrans >= 0 && jtrans < m_nWidth)
      //  *pCurPixel = m_vPixels[itrans*m_nWidth + jtrans];
      //else
      //  *pCurPixel = 0; //Noir transparent si en dehors de l'image initiale

      //pCurPixel++;
    }
  m_vPixels = std::move(vPixels);
  m_nWidth = nWidth;
  m_nHeight = nHeight;
}
