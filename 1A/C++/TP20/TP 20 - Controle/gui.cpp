/// 
/// \file  "gui.cpp"
/// 
/// \brief Définition de la classe CGUI.
/// 
/// 
#include "stdafx.h"
#include "gui.h"
#include "MechClock.h"
#include "AutoClock.h"
#include <algorithm>

using namespace LibGraph2;
using namespace std;

/// \brief C'est PI !
const double gc_pi = 3.1415926535897932384626433832795;

/// \brief Dessine une horloge électronique
/// 
/// \param [in] ptPos Position d'affichage de l'horloge 
/// \param [in] clock Horloge électronique à afficher 
void CGUI::drawAutoClock(const CPoint2D& ptPos, const CAutoClock& clock) const
{
  auto ptLGPos = toLibGraph2Point(ptPos);
  auto ptLGPivot = CPoint(static_cast<float>(mc_ClockSize.X()) / 2.0f, static_cast<float>(mc_ClockSize.Y()) / 2.0f);
  m_pLibGraph->drawBitmap("AutoClock-bg.png", ptLGPos, ptLGPivot, 1.0, 0.0);

  std::time_t curTime = std::chrono::system_clock::to_time_t(clock.GetTimePoint());
  std::tm curTm = *localtime(&curTime);

  //Affiche les secondes avec des points
  for (int i = 0; i <= curTm.tm_sec; ++i)
  {
    CPoint ptDotPos;
    ptDotPos.m_fX = static_cast<float>(cos((1.0 - i / 30.0 - 0.5) * gc_pi) * 40.3);
    ptDotPos.m_fY = static_cast<float>(-sin((1.0 - i / 30.0 - 0.5) * gc_pi) * 40.3);
    m_pLibGraph->drawBitmap("AutoClock-LED.png", ptLGPos+ptDotPos, CPoint(3.0f,3.0f), 1.0, 0.0);
  }

  //Affiche les deux points pour les secondes paires
  if (curTm.tm_sec % 2)
  {
    m_pLibGraph->drawBitmap("AutoClock-tick.png", ptLGPos + CPoint(44.0f,40.0f) - ptLGPivot);
  }

  //Affiche la dizaine des heures
  int nVal = curTm.tm_hour / 10;
  std::string strFileName = "AutoClock-" + std::to_string(nVal) + ".png";
  m_pLibGraph->drawBitmap(strFileName, ptLGPos + CPoint(9.0f, 32.5f) - ptLGPivot);
  //Affiche l'unité des heures
  nVal = curTm.tm_hour - nVal * 10;
  strFileName = "AutoClock-" + std::to_string(nVal) + ".png";
  m_pLibGraph->drawBitmap(strFileName, ptLGPos + CPoint(25.0f, 32.5f) - ptLGPivot);

  //Affiche la dizaine des minutes
  nVal = curTm.tm_min / 10;
  strFileName = "AutoClock-" + std::to_string(nVal) + ".png";
  m_pLibGraph->drawBitmap(strFileName, ptLGPos + CPoint(47.0f, 32.5f) - ptLGPivot);
  //Affiche l'unité des minutes
  nVal = curTm.tm_min - nVal * 10;
  strFileName = "AutoClock-" + std::to_string(nVal) + ".png";
  m_pLibGraph->drawBitmap(strFileName, ptLGPos + CPoint(64.0f, 32.5f) - ptLGPivot);
}

/// \brief Dessine une horloge mécanique
/// 
/// \param [in] ptPos Position d'affichage de l'horloge 
/// \param [in] clock Horloge mécanique à afficher 
void CGUI::drawMechClock(const CPoint2D& ptPos, const CMechClock& clock) const
{
  auto ptLGPos = toLibGraph2Point(ptPos);
  auto ptLGPivot = CPoint(static_cast<float>(mc_ClockSize.X()) / 2.0f, static_cast<float>(mc_ClockSize.Y()) / 2.0f);
  auto ptLGPivotX4 = CPoint(static_cast<float>(mc_ClockSize.X()) * 2.0f, static_cast<float>(mc_ClockSize.Y()) * 2.0f);
  m_pLibGraph->drawBitmap("MechClock-bg.png", ptLGPos, ptLGPivot, 1.0, 0.0);

  //Dessine l'arc représentant la tension du ressort
  m_pLibGraph->setPen(MakeARGB(255, 
    static_cast<BYTE>(std::round(std::min(2.0f-clock.GetSpringTension()*2.0f, 1.0f) * 255.0f)),
    static_cast<BYTE>(std::round(std::min(clock.GetSpringTension()*2.0f,1.0f) * 255.0f))
    , 0), 2.0f);
  m_pLibGraph->setSolidBrush(MakeARGB(0, 0, 0, 0));
  m_pLibGraph->drawArc(CRectangle(CPoint(0.0f, 0.0f) + ptLGPos - ptLGPivot, toLibGraph2Size(mc_ClockSize)), 360.0f - clock.GetSpringTension() * 360.0f -90, clock.GetSpringTension() * 360.0f);

  //Décode le temps et calcule les angles des aiguilles
  std::time_t curTime = std::chrono::system_clock::to_time_t(clock.GetTimePoint());
  std::tm curTm = *localtime(&curTime);
  double dAngleSecs = curTm.tm_sec * 6.0;
  double dAngleMins = (curTm.tm_min + dAngleSecs/360.0) * 6.0;
  double dAngleHours = (curTm.tm_hour + dAngleMins / 360) * 30.0;

  //Dessine les aiguilles
  m_pLibGraph->drawBitmap("MechClock-hour.png", ptLGPos, ptLGPivotX4, 0.25, dAngleHours);
  m_pLibGraph->drawBitmap("MechClock-min.png", ptLGPos, ptLGPivotX4, 0.25, dAngleMins);
  m_pLibGraph->drawBitmap("MechClock-sec.png", ptLGPos, ptLGPivotX4, 0.25, dAngleSecs);
  m_pLibGraph->drawBitmap("MechClock-fg.png", ptLGPos, ptLGPivot, 1.0, 0.0);
}

/// \brief Dessine le mur
/// 
/// \param [in] ptPos Position d'affichage du mur 
void CGUI::drawWall(const CPoint2D& ptPos) const
{
  m_pLibGraph->setPen(MakeARGB(0, 0, 0, 0), 0);
  m_pLibGraph->setTextureBrush("wall.png");
  m_pLibGraph->drawRectangle(CRectangle(toLibGraph2Point(ptPos), toLibGraph2Size(mc_szWholeWallSize)));
}

/// \brief Dessine un rectangle de mise en valeur
/// 
/// Cette fonction dessine un rectangle bleuté translucide, pouvant servir à mettre en valeur un élément.
/// 
/// \param [in] ptPos Position du coin supérieur gauche du rectangle
/// \param [in] szSize Taille du rectangle
void CGUI::drawHighlight(const CPoint2D& ptPos, const CSize2D& szSize)const
{
  m_pLibGraph->setPen(MakeARGB(255, 0, 108, 255), 1.0f);
  m_pLibGraph->setSolidBrush(MakeARGB(64, 0, 108, 255));
  m_pLibGraph->drawRectangle(CRectangle{ toLibGraph2Point(ptPos), toLibGraph2Size(szSize) });
}


/// \brief
/// Affiche le texte \c strText en haut au milieu de la fenêtre.
/// 
/// \param strText
/// Texte à afficher.
void CGUI::drawString(const string& strText) const
{
  //Copie de la chaîne passée en paramètre qui sera affichée
  CString strToPrint{ strText };

  //Retrouve la taille de la fenêtre LibGraph2
  CSize szWnd = m_pLibGraph->getSize();
  //Calcule la taille de la représentation graphique de la chaine de caractère os.str()
  CRectangle rectStr;
  m_pLibGraph->getStringDimension(strToPrint, CPoint(0, 0), rectStr);
  //Ajoute une marge de 5 pixels au dessus de ce cadre et le positionne en haut au milieu de la fenêtre
  rectStr.m_ptTopLeft.m_fX = (szWnd.m_fWidth - rectStr.m_szSize.m_fWidth) / 2.0f;
  rectStr.m_ptTopLeft.m_fY = 5.0f;
  //Affiche un rectangle de fond
  CRectangle rect2(rectStr);
  rect2.m_ptTopLeft.m_fX -= 5.0f;
  rect2.m_ptTopLeft.m_fY -= 5.0f;
  rect2.m_szSize.m_fWidth += 10.0f;
  rect2.m_szSize.m_fHeight += 10.0f;
  m_pLibGraph->setPen(MakeARGB(255, 100, 122, 153), 1.0f);
  m_pLibGraph->setSolidBrush(MakeARGB(85, 100, 122, 153));
  m_pLibGraph->drawRectangle(rect2);
  //Dessine la chaîne de caractère
  m_pLibGraph->setSolidBrush(MakeARGB(255, 0, 0, 0));
  m_pLibGraph->drawString(strToPrint, rectStr.m_ptTopLeft);
}

/// \brief Affiche une boîte de dialogue de saisie de valeur
/// 
/// \param [in, out] value Valeur à saisir. En sortie, ce paramètre prend la valeur saisie.
/// \param [in] title Titre de la boîte de dialogue
/// \param [in] prompt Message affiché dans la boîte de dialogue pour inviter l'utilisateur à enterr une valeur.
/// 
/// \return \c true si la valeur a été correctement saisie, \c false sinon (par exemple, l'utilisateur a cliqué sur le bouton "Annuler")
bool CGUI::askForValue(std::string& value, const std::string& title, const std::string& prompt) const
{
  CString strValue = value;
  bool bRet = m_pLibGraph->guiGetValue(strValue, title, prompt);
  value = static_cast<std::string>(strValue);
  return bRet;
}

/// \brief Affiche une boîte de dialogue d'exclamation
/// 
/// \param [in] title Titre de la boîte de dialogue
/// \param [in] prompt Message affiché dans la boîte de dialogue pour inviter l'utilisateur à enterr une valeur.
void CGUI::showExclamation(const std::string& title, const std::string& prompt) const
{
  m_pLibGraph->guiMessageBox(title, prompt, LibGraph2::msgbtn_types::MsgBtnOK, LibGraph2::msgicon_types::MsgIcnExclamation);
}
