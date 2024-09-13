/// 
/// \file  "Wall.cpp"
/// 
/// \brief Définition de la classe CWall. 
/// 
/// 

#include "StdAfx.h"
#include "Wall.h"
#include <cassert>

using namespace std;

/// \brief Constructeur
/// 
/// \param pGUI pointeur partagé vers l'objet gérant l'interface utilisateur
CWall::CWall(shared_ptr<CGUI> pGUI)
  : m_pGUI{ pGUI }
{
}


/// \brief
/// Retourne l'indice de la case du tableau CWall::m_Clocks correspondant 
/// au point \c RelPixelPos.
/// 
/// \param RelPixelPos
/// Position du curseur relative au coin supérieur gauche du mur.
/// 
/// \returns
/// L'indice dans le tableau CWall::m_Clocks de l'horloge pointée par le curseur
/// à la position relative RelPixelPos. Si aucune case du tableau ne se situe
/// sous la position du curseur, alors la valeur -1 est retournée
int CWall::GetCaseAt(const CPoint2D& RelPixelPos) const
{
  for(int i=0; i<sc_nNbCases; ++i)
  {
    size_t lig = i/sc_nNbCol;
    size_t col = i%sc_nNbCol;
    CPoint2D ptCaseTopLeft(col*m_pGUI->mc_szWall.X() / sc_nNbCol + m_pGUI->mc_ptWallRelPos.X(),
                           lig*m_pGUI->mc_szWall.Y() / sc_nNbLig + m_pGUI->mc_ptWallRelPos.Y());
    CPoint2D ptCaseBottomRight((col + 1)*m_pGUI->mc_szWall.X() / sc_nNbCol + m_pGUI->mc_ptWallRelPos.X(),
                               (lig + 1)*m_pGUI->mc_szWall.Y() / sc_nNbLig + m_pGUI->mc_ptWallRelPos.Y());
    if (   RelPixelPos.X() >= ptCaseTopLeft.X() && RelPixelPos.X() < ptCaseBottomRight.X()
        && RelPixelPos.Y() >= ptCaseTopLeft.Y() && RelPixelPos.Y() < ptCaseBottomRight.Y())
      return i;
  }
  return -1;
}

/// \brief
/// Affiche le mur et son contenu.
/// 
/// \param AbsPixelPos
/// Position absolue du coin supérieur gauche du mur.
void CWall::Afficher(const CPoint2D& AbsPixelPos)const
{
  m_pGUI->drawWall(AbsPixelPos);
  for(int i=0; i<sc_nNbCases; ++i)
  {
    if(i != m_nHighLightCase && m_Clocks[i] == nullptr)
      continue;
    size_t lig = i/sc_nNbCol;
    size_t col = i%sc_nNbCol;
    CPoint2D ptCaseTopLeft(col*m_pGUI->mc_szWall.X() / sc_nNbCol + m_pGUI->mc_ptWallRelPos.X(),
                           lig*m_pGUI->mc_szWall.Y() / sc_nNbLig + m_pGUI->mc_ptWallRelPos.Y());
    CPoint2D ptCaseBottomRight((col + 1)*m_pGUI->mc_szWall.X() / sc_nNbCol + m_pGUI->mc_ptWallRelPos.X(),
                               (lig + 1)*m_pGUI->mc_szWall.Y() / sc_nNbLig + m_pGUI->mc_ptWallRelPos.Y());
    ptCaseTopLeft += AbsPixelPos;
    ptCaseBottomRight += AbsPixelPos;
    if(i == m_nHighLightCase)
    {
      m_pGUI->drawHighlight(ptCaseTopLeft, CSize2D{ ptCaseBottomRight - ptCaseTopLeft });
    }
    if(m_Clocks[i] == nullptr)
      continue;
    m_Clocks[i]->Afficher(CPoint2D{ (ptCaseTopLeft.X() + ptCaseBottomRight.X()) / 2, (ptCaseTopLeft.Y() + ptCaseBottomRight.Y()) / 2 });
  }
}

/// \brief
/// Retourne un pointeur vers l'horloge située sous le point \c RelPixePos.
/// 
/// \param RelPixelPos
/// Position du curseur relative au coin supérieur gauche du mur.
/// 
/// \returns
/// Un pointeur vers l'horloge située sous le point \c RelPixelPos ou nullptr 
/// si aucune horloge n'est présente.
shared_ptr<CClock> CWall::GetClock(const CPoint2D& RelPixelPos)
{
  int i = GetCaseAt(RelPixelPos);
  if(i == -1)
    return nullptr;
  return m_Clocks[i];
}

/// \brief
/// Accroche une horloge sur le mur.
/// 
/// \param RelPixelPos
/// Position du curseur relative au coin supérieur gauche du mur.
/// 
/// \param pClock
/// Pointeur vers l'horloge à accrocher.
/// 
/// \returns
/// \c true si l'horloge a pu être accrochée (une place existe sous \c elPixelPos et
/// est libre) ou \c false si l'horloge n'a pas pu être accrochée (aucune place
/// n'existe sous \c RelPixelPos ou elle n'est pas libre)
bool CWall::HangClock(const CPoint2D& RelPixelPos, shared_ptr<CClock> pClock)
{
  int i = GetCaseAt(RelPixelPos);
  if(i == -1)
    return false;
  if(m_Clocks[i] != nullptr)
    return false;
  m_Clocks[i] = pClock;
  return true;
}

/// \brief
/// Met en surbrillance une case du mur.
/// 
/// \param RelPixelPos
/// Position du curseur relative au coin supérieur gauche du mur.
/// 
/// La case mise en surbrillance est celle qui se situe sous le curseur défini 
/// par la position relative \c RelPixelPos.
void CWall::HighLight(const CPoint2D& RelPixelPos)
{
  m_nHighLightCase = GetCaseAt(RelPixelPos);
}

/// \brief
/// Occasione un tic d'horlge à l'ensemble des horloges accrochées sur le mur..
void CWall::Tick()
{
  for (auto& pClock : m_Clocks)
  {
    if (pClock)
    {
      if (!pClock->Tick())
        if (!m_bGameOver)
        {
          m_pGUI->showExclamation("Perdu !", "Une horloge mécanique est totalement arrêtée !");
          m_bGameOver = true;
        }

    }
  }
}

