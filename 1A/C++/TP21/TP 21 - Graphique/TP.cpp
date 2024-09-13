/*!
 * \file  "TP.cpp"
 *
 * \brief Définition de la classe CTP. 
 *
 */
#include "StdAfx.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <sstream>
#include "TP.h"
#include "incLibGraph2.h"

using namespace LibGraph2;
using namespace std;

/*!
 * \brief
 * Constructeur par défaut.
 */
CTP::CTP(void)
  : m_dAngleRad(0)
{
    m_matRot.Identity();
    m_matScale.Identity();
    m_matTear.Identity();

  //!\todo Initialiser les 3 matrices à la matrice identité
}


/*!
 * \brief
 * Calcule l'image tranformée.
 */
void CTP::ComputeTransform()
{
  //!\todo Créer une matrice étant égale à \c "m_matTear*m_matScale*m_matRot"
    CMatrice<double> Mat = m_matTear * m_matScale * m_matRot;
  m_bmpTrans = m_bmp;
  //!\todo Passer la matrice créée à l'appel de la fonction \c Transform ci-dessous.
  m_bmpTrans.Transform(Mat
    );
}

/*!
 * \brief
 * Appelée pour ouvrir un fichier image.
 * 
 * \returns
 * \c true si l'ouverture a été réalisée, \c false si l'utilisateur a choisi d'annuler.
 */
bool CTP::OpenPPMFile()
{
  CString strFileName;
  vector<CString> vstrFileTypes = { "Portable Pixmap|*.ppm;*.pgm;*.pbm;*.pnm", "Tous les fichiers|*.*" };

  ILibGraph2* pLibgraph = GetLibGraph2();

  if (!pLibgraph->guiGetFileName(strFileName, true, vstrFileTypes))
    return false;

  m_bmp = CBitMap(strFileName);
  ComputeTransform();
  return true;
}

/*!
 * \brief
 * Incrémente l'angle de 1 degré.
 */
void CTP::IncreaseAngle()
{
  m_dAngleRad += M_PI/180.0;
  if(m_dAngleRad >= M_PI)
    m_dAngleRad -= 2.0*M_PI;
  //!\todo Décommenter les lignes suivantes lorsque vous avez ajouté la matrice de rotation à la classe CTP
  //m_matRot(0,0) = cos(m_dAngleRad);   m_matRot(0,1) = -sin(m_dAngleRad);   m_matRot(0,2) = 0; 
  //m_matRot(1,0) = sin(m_dAngleRad);   m_matRot(1,1) =  cos(m_dAngleRad);   m_matRot(1,2) = 0; 
  //m_matRot(2,0) = 0;                  m_matRot(2,1) = 0;                   m_matRot(2,2) = 1; 
  ComputeTransform();
}

/*!
 * \brief
 * Décrémente l'angle de 1 degré.
 */
void CTP::DecreaseAngle()
{
  m_dAngleRad -= M_PI/180.0;
  if(m_dAngleRad < -M_PI)
    m_dAngleRad += 2.0*M_PI;
  //!\todo Décommenter les lignes suivantes lorsque vous avez ajouté la matrice de rotation à la classe CTP
  //m_matRot(0,0) = cos(m_dAngleRad);   m_matRot(0,1) = -sin(m_dAngleRad);   m_matRot(0,2) = 0; 
  //m_matRot(1,0) = sin(m_dAngleRad);   m_matRot(1,1) =  cos(m_dAngleRad);   m_matRot(1,2) = 0; 
  //m_matRot(2,0) = 0;                  m_matRot(2,1) = 0;                   m_matRot(2,2) = 1; 
  ComputeTransform();
}

/*!
 * \brief
 * Incrémente le facteur d'échelle en X.
 */
void CTP::IncreaseScaleX()
{
  //!\todo Décommenter les lignes suivantes lorsque vous avez ajouté la matrice d'échelle à la classe CTP
  m_matScale(0,0) += 0.1;
  if(m_matScale(0,0) > -0.05 && m_matScale(0,0) < 0.05)
    m_matScale(0,0) = 0.1;
  ComputeTransform();
}

/*!
 * \brief
 * Décrémente le facteur d'échelle en X.
 */
void CTP::DecreaseScaleX()
{
  //!\todo Décommenter les lignes suivantes lorsque vous avez ajouté la matrice d'échelle à la classe CTP
  m_matScale(0,0) -= 0.1;
  if(m_matScale(0,0) > -0.05 && m_matScale(0,0) < 0.05)
    m_matScale(0,0) = -0.1;
  ComputeTransform();
}

/*!
 * \brief
 * Incrémente le facteur d'échelle en Y.
 */
void CTP::IncreaseScaleY()
{
  //!\todo Décommenter les lignes suivantes lorsque vous avez ajouté la matrice d'échelle à la classe CTP
  m_matScale(1,1) += 0.1;
  if(m_matScale(1,1) > -0.05 && m_matScale(1,1) < 0.05)
    m_matScale(1,1) = 0.1;
  ComputeTransform();
}

/*!
 * \brief
 * Décrémente le facteur d'échelle en Y.
 */
void CTP::DecreaseScaleY()
{
  //!\todo Décommenter les lignes suivantes lorsque vous avez ajouté la matrice d'échelle à la classe CTP
  m_matScale(1,1) -= 0.1;
  if(m_matScale(1,1) > -0.05 && m_matScale(1,1) < 0.05)
    m_matScale(1,1) = -0.1;
  ComputeTransform();
}

/*!
 * \brief
 * Incrémente le facteur de déchirement en X.
 */
void CTP::IncreaseTearX()
{
  //!\todo Décommenter les lignes suivantes lorsque vous avez ajouté la matrice de déchirement à la classe CTP
  m_matTear(0,1) += 0.1;
  if(m_matTear(0,1) > -0.05 && m_matTear(0,1) < 0.05)
    m_matTear(0,1) = 0;
  ComputeTransform();
}

/*!
 * \brief
 * Décrémente le facteur de déchirement en X.
 */
void CTP::DecreaseTearX()
{
  //!\todo Décommenter les lignes suivantes lorsque vous avez ajouté la matrice de déchirement à la classe CTP
  m_matTear(0,1) -= 0.1;
  if(m_matTear(0,1) > -0.05 && m_matTear(0,1) < 0.05)
    m_matTear(0,1) = 0;
  ComputeTransform();
}

/*!
 * \brief
 * Incrémente le facteur de déchirement en Y.
 */
void CTP::IncreaseTearY()
{
  //!\todo Décommenter les lignes suivantes lorsque vous avez ajouté la matrice de déchirement à la classe CTP
  m_matTear(1,0) += 0.1;
  if(m_matTear(1,0) > 0.05 && m_matTear(1,0) < 0.05)
    m_matTear(1,0) = 0;
  ComputeTransform();
}

/*!
 * \brief
 * Décrémente le facteur de déchirement en Y.
 */
void CTP::DecreaseTearY()
{
  //!\todo Décommenter les lignes suivantes lorsque vous avez ajouté la matrice de déchirement à la classe CTP
  m_matTear(1,0) -= 0.1;
  if(m_matTear(1,0) > -0.05 && m_matTear(1,0) < 0.05)
    m_matTear(1,0) = 0;
  ComputeTransform();
}

/*!
 * \brief
 * Affiche le contenu de la fenêtre.
 */
void CTP::Draw()
{
  ILibGraph2* pLibgraph = GetLibGraph2();
  CSize sz = pLibgraph->getSize();
  pLibgraph->setPen(MakeARGB(255,0,0,0), 1, pen_DashStyles::Dash);
  pLibgraph->drawLine(CPoint(sz.m_fWidth/2, 0), CPoint(sz.m_fWidth/2, sz.m_fHeight-1));
  pLibgraph->drawLine(CPoint(0, sz.m_fHeight/2), CPoint(sz.m_fWidth-1, sz.m_fHeight/2));
  //Affiche l'image d'origine en haut à gauche de la fenêtre
  m_bmp.Draw(CPoint(m_bmp.GetWidth()/2.0f, m_bmp.GetHeight()/2.0f));
  m_bmpTrans.Draw(CPoint(sz.m_fWidth/2,sz.m_fHeight/2));

  //!\todo Décommentez le code suivant lorsque vous avez ajouté les matrices membres de la classe CTP
  //Affiche le texte d'aide et d'info en bas de la fenêtre
  wostringstream os;
  os<<"A/Q : Rotation +/- ("<<m_dAngleRad*180/M_PI<<"°) "
    <<"Z/S : Echelle X +/- ("<<m_matScale(0,0)<<") "
    <<"E/D : Echelle Y +/- ("<<m_matScale(1,1)<<") "
    <<"R/F : Déchirement X +/- ("<<m_matScale(1,0)<<") "
    <<"T/G : Déchirement Y +/- ("<<m_matScale(0,1)<<") "
    <<"O : Ouvrir un fichier";
  //Calcule la taille de la représentation graphique de la chaine de caractère os.str()
  CRectangle rectStr;
  pLibgraph->getStringDimension(os.str(), CPoint(0,0), rectStr);
  //Ajoute une marge de 5 pixels autour de ce cadre et le positionne en bas à gauche de la fenêtre
  rectStr.m_ptTopLeft.m_fX = 5;
  rectStr.m_ptTopLeft.m_fY = sz.m_fHeight - rectStr.m_szSize.m_fHeight - 5;
  //Affiche un rectangle de fond
  CRectangle rect2(rectStr);
  rect2.m_ptTopLeft.m_fX = 0.0f;
  rect2.m_ptTopLeft.m_fY -= 5.0f;
  rect2.m_szSize.m_fWidth = sz.m_fWidth;
  rect2.m_szSize.m_fHeight += 10.0f;
  pLibgraph->setPen(MakeARGB(255,100,122,153), 1.0f);
  pLibgraph->setSolidBrush(MakeARGB(85,100,122,153));
  pLibgraph->drawRectangle(rect2);
  //Dessine la chaîne de caractère
  pLibgraph->setSolidBrush(MakeARGB(255,0,0,0));
  pLibgraph->drawString(os.str(), rectStr.m_ptTopLeft);
}
