/// 
/// \file  "TP.cpp"
/// 
/// \brief Définition de la classe CTP. 
/// 
/// 
#include "StdAfx.h"
#include "TP.h"
#include <time.h>
#include <regex>
using namespace std;

/// \brief Constructeur
/// 
/// \param pGUI pointeur partagé vers l'objet gérant l'interface utilisateur
CTP::CTP(std::shared_ptr<CGUI> pGUI)
  : m_wall{ pGUI }
  , m_pGUI{ pGUI }
{
}


/// \brief
/// Affiche l'ensemble des données du TP.
/// 
/// Cette fonction affiche le mur au centre de la fenêtre et les informations détaillées de 
/// l'horloge sélectionnée.
void CTP::Afficher() const
{
  CSize2D szWnd = m_pGUI->getWndSize();
  //Dessine le mur
  m_wall.Afficher(m_pGUI->mc_ptWholeWallRelPos);
  //Affiche les infos de l'horloge sélectionnée en haut au milieu
  if(m_pSelectedClock)
  {
    m_pSelectedClock->AfficherInfos();
  }
}

/// \brief
/// Crée une horloge mécanique.
/// 
/// \returns
/// Un pointeur vers la nouvelle horloge.
/// 
/// Cette fonction demande à l'utilisateur de saisir un décalage temporel par rapport au temps universel.
/// 
/// \remarks Cette fonction n'accroche pas l'horloge sur le mur, elle ne fait que la créer.
shared_ptr<CClock> CTP::CreateMechClock()
{
  string strUTCOffset = "+01:00";
  if(!m_pGUI->askForValue(strUTCOffset,"Décalage temps universel", "Veuillez entrer le décalage temporel de l'horloge sous la forme +01:00 : "))
    return nullptr;

  std::chrono::minutes durUTCOffset;
  //Valide l'entrée saisie
  if(!ValidateUTCOffsetString(strUTCOffset, durUTCOffset))
  {
    m_pGUI->showExclamation("Erreur de saisie", "Le décalage temporel n'est pas saisie dans le bon format.");
    return nullptr;
  }


  shared_ptr<CClock> pMechClock;
  /// \xrefitem todo1_1 "Todo" "1.1 Travail à faire" Créer une horloge mécanique ici,
  /// pointée par le pointeur intelligent pMechClock.
  /// Son décalage horaire est défini par \c durUTCOffset.
  pMechClock = make_shared<CMechClock>(durUTCOffset);
  return pMechClock;
}

/// \brief
/// Crée une horloge électronique.
/// 
/// \returns
/// Un pointeur vers la nouvelle horloge.
/// 
/// Cette fonction demande à l'utilisateur de saisir un décalage temporel par rapport au temps universel.
/// 
/// \remarks Cette fonction n'accroche pas l'horloge sur le mur, elle ne fait que la créer.
shared_ptr<CClock> CTP::CreateAutoClock()
{
  string strUTCOffset = "+01:00";
  if (!m_pGUI->askForValue(strUTCOffset, "Décalage temps universel", "Veuillez entrer le décalage temporel de l'horloge sous la forme +01:00 : "))
    return nullptr;

  std::chrono::minutes durUTCOffset;
  //Valide l'entrée saisie
  if (!ValidateUTCOffsetString(strUTCOffset, durUTCOffset))
  {
    m_pGUI->showExclamation("Erreur de saisie", "Le décalage temporel n'est pas saisie dans le bon format.");
    return nullptr;
  }

  shared_ptr<CClock> pAutoClock;
  /// \xrefitem todo1_1 "Todo" "1.1 Travail à faire" Créer une horloge électronique ici,
  /// pointée par le pointeur intelligent pAutoClock.
  /// Son décalage horaire est défini par \c durUTCOffset.
  pAutoClock = make_shared<CAutoClock>(durUTCOffset);
  return pAutoClock;
}

/// \brief
/// Sélectionne une horloge sur le mur.
/// 
/// \param AbsPixelPos
/// Position de la souris par raport au coin suppérieur gauche de la fenêtre.
/// 
/// Sélectionne l'horloge qui se trouve sous la position \c AbsPixelPos et 
/// la met en surbrillance.
void CTP::SelectClock(const CPoint2D& AbsPixelPos)
{
  CPoint2D RelPixelPos = AbsToRelPixelPos(AbsPixelPos);
  m_wall.HighLight(RelPixelPos);
  m_pSelectedClock = m_wall.GetClock(RelPixelPos);
}

/// \brief
/// Accroche une horloge sur le mur.
/// 
/// \param pClock
/// Pointeur vers l'horloge à accrocher.
/// 
/// \param AbsPixelPos
/// Position de la souris par raport au coin suppérieur gauche de la fenêtre.
/// 
/// \return 
/// \c true si l'horloge a pu être accrochée sur le mur (emplacement valide 
/// et libre) \c false sinon
bool CTP::HangClock(shared_ptr<CClock> pClock, const CPoint2D& AbsPixelPos)
{
  return m_wall.HangClock(AbsToRelPixelPos(AbsPixelPos), pClock);
}

/// \brief
/// Restore l'énergie du ressort de l'horloge mécanique sélectionnée.
/// 
/// Si l'horloge sélectionnée (donnée membre CTP::m_pSelectedClock) est une horloge
/// mécanique, alors son ressort est retendu. 
void CTP::TightenSpring()
{
  /// \xrefitem todo1_3_3 "Todo" "1.3.3 Travail à faire" 
  /// Déterminer si l'horloge sélectionnée (donnée membre 
  /// CTP::m_pSelectedClock) est une horloge mécanique.\n
  /// - Si oui, alors continuer l'exécution de la fonction.
  /// - Si non, alors sortir de la fonction.
    

    shared_ptr<CMechClock>pMechClock = std::dynamic_pointer_cast<CMechClock>(m_pSelectedClock);
    if (!pMechClock)
        return;

    /// \xrefitem todo1_3_3 "Todo" "1.3.3 Travail à faire" 
    /// Retendre le ressort de l'horloge.
    pMechClock->TightenSpring();
}

/// \brief
/// Convertit des coordonnées absolues de fenêtre en coordonnées relatives à la 
/// position du mur.
/// 
/// \param AbsPixelPos
/// Coordonnées absolues d'un point par rapport au coin supérieur gauche de la 
/// fenêtre.
/// 
/// \returns
/// Les coordonnées relatives du point par rapport au coin supérieur gauche du mur. 
CPoint2D CTP::AbsToRelPixelPos(const CPoint2D& AbsPixelPos) const
{
  return CPoint2D(AbsPixelPos.X() - m_pGUI->mc_ptWholeWallRelPos.X(), AbsPixelPos.Y() - m_pGUI->mc_ptWholeWallRelPos.Y());
}

/// \brief
/// Valide les données de décalage horaire saisies par l'utilisateur.
/// 
/// \param [in] strUTCOffset
/// Chaîne de caractères contenant le décalage horaire saisi.
///
/// \param [out] durUTCOffset
/// Le décalage horaire validé.
/// 
/// \returns
/// \c true si la chaîne de caractère est valide. Dans ce cas, le paramètre de sortie \c durUTCOffset 
/// contient la valeur numérique du décalage. 
bool CTP::ValidateUTCOffsetString(const std::string& strUTCOffset, std::chrono::minutes& durUTCOffset)
{
  const std::regex base_regex(R"regex(([\+\-])([0-9][0-9]):([0-9][0-9]))regex");
  std::smatch base_match;
  if (std::regex_match(strUTCOffset, base_match, base_regex) && base_match.size() == 4) {
    // Si la chaîne saisie est bien formée, base_match contient 4 éléments :
    // base_match[0] : la chaîne entière
    // base_match[1] : le +/-
    // base_match[2] : le décalage des heures
    // base_match[3] : le décalage des minutes

    durUTCOffset = std::chrono::hours(std::stoul(base_match[2].str()))
                 + std::chrono::minutes(std::stoul(base_match[3].str()));
    if (base_match[1].str() == "-")
      durUTCOffset = -durUTCOffset;

    return true;
  }

  return false;
}

/// \brief
/// Occasionne un tic d'horloge à toutes les horloges accrochées au mur.
/// 
void CTP::Tick()
{
  m_wall.Tick();
}

