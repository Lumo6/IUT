/// 
/// \file  "AutoClock.cpp"
/// 
/// \brief Définition de la classe CAutoClock. 
/// 
/// 
#include "StdAfx.h"
#include "AutoClock.h"
#include <sstream>
#include <format>
using namespace LibGraph2;
using namespace std;

/// \brief
/// Constructeur.
/// 
/// \param durUTCOffset
/// Décalage horaire de la zone par rapport au temps UTC. Exprimé en minutes.
/// 
/// \xrefitem todo1_1 "Todo" "1.1 Travail à faire" 
/// Complétez le corps du constructeur de la classe CAutoClock
CAutoClock::CAutoClock(const std::chrono::minutes& durUTCOffset) : CClock(durUTCOffset)
{
}

/// \brief
/// Affiche l'horloge électronique.
/// 
/// \param AbsPixelPos
/// Position absolue de l'horloge dans la fenêtre.
/// 
/// \see CClock::Afficher
void CAutoClock::Afficher(const CPoint2D& AbsPixelPos) const
{
  m_pGUI->drawAutoClock(AbsPixelPos, *this);
}

/// \brief
/// Affiche les infos détaillées de l'horloge.
/// 
/// Cette fonction doit afficher le texte conformément aux spécifications 
/// précisées pour la fonction CClock::AfficherInfos
/// 
/// \see CClock::AfficherInfos
void CAutoClock::AfficherInfos() const
{
  /// \xrefitem todo1_2 "Todo" "1.2 Travail à faire" 
  /// Afficher le texte adéquat en appelant la fonction \c AfficherTexte() de la classe CClock,
  /// conformément aux spécifications précisées pour la fonction CClock::AfficherInfos
	AfficherTexte("Je suis une horloge automatique.");
}
