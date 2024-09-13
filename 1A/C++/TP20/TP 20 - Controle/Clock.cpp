/// 
/// \file  "Clock.cpp"
/// 
/// \brief Définition de la classe CClock. 
/// 
/// 
#include "StdAfx.h"
#include "Clock.h"
#include <cassert>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

/// \brief
/// Affiche le texte \c strText en haut au milieu de la fenêtre.
/// 
/// \param strText
/// Texte à afficher.
void CClock::AfficherTexte(const string& strText) const
{
  assert(m_pGUI);

  ostringstream os;
  os << strText << '\n';
  //Ajoute les informations communes aux horloges aux informations à afficher
  std::time_t curLocalTime = std::chrono::system_clock::to_time_t(m_tpCurUTCTime + m_durUTCOffset);
  std::tm curLocalTm = *localtime(&curLocalTime);
  os << "Selon moi, il est " << std::setfill('0') << std::setw(2) << curLocalTm.tm_hour << ":" << std::setfill('0') << std::setw(2) << curLocalTm.tm_min << '\n';

  m_pGUI->drawString(os.str());
}

CClock::CClock(const std::chrono::minutes& durUTCOffset)
  : m_durUTCOffset(durUTCOffset) 
{
  std::time_t start = time(nullptr);
  m_tpCurUTCTime = std::chrono::system_clock::from_time_t(std::mktime(std::gmtime(&start)));
}

void CClock::Afficher(const CPoint2D& /*AbsPixelPos*/) const
{
}
/// Les informations détaillées sont affichées dans un rectangle en 
  /// haut au milieu de la fenêtre. Ces informations dépendent du type d'horloge.
  /// \li Les horloges electroniques
  /// Une horloge électronique doit afficher les informations suivantes :\n
  /// <tt>\"Je suis une horloge automatique.\"</tt>\n
  /// <tt>\"Selon moi, il est <b><em style="color:#FF8040">XX:XX</em></b>.\"</tt>\n
  /// \li Les horloges mécaniques
  /// Une horloge mécanique doit afficher les informations suivantes :\n
  /// <tt>\"Je suis une horloge mécanique. Mon ressort est tendu à <b><em style="color:#FF8040">XX</em></b>%\"</tt>\n
  /// <tt>\"Selon moi, il est <b><em style="color:#FF8040">XX:XX</em></b>.\"</tt>\n
void CClock::AfficherInfos() const
{
}

bool CClock::Tick()
{
  m_tpCurUTCTime += std::chrono::seconds(1);
  return true;
}

