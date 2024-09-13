/// 
/// \file  "MechClock.cpp"
/// 
/// \brief Définition de la classe CMechClock. 
/// 
/// 
#include "StdAfx.h"
#include "MechClock.h"
#include <sstream>
using namespace std;

/// 
/// \brief
/// Constructeur.
/// 
/// \param durUTCOffset
/// Décalage horaire de la zone par rapport au temps UTC. Exprimé en minutes.
/// 
/// \xrefitem todo1_1 "Todo" "1.1 Travail à faire" 
/// Complétez le corps du constructeur de la classe CMechClock.
/// 
CMechClock::CMechClock(const std::chrono::minutes& durUTCOffset) : CClock(durUTCOffset)
{
}

/// 
/// \brief
/// Affiche l'horloge mécanique.
/// 
/// \param AbsPixelPos
/// Position absolue de l'horloge dans la fenêtre.
/// 
/// \see CClock::Afficher
/// 
void CMechClock::Afficher(const CPoint2D& AbsPixelPos) const
{
  m_pGUI->drawMechClock(AbsPixelPos, *this);
}

/// 
/// \brief
/// Affiche les infos détaillées de l'horloge mécanique.
/// 
/// Cette fonction doit afficher le texte conformément aux spécifications 
/// précisées pour la fonction CClock::AfficherInfos
/// 
/// \see CClock::AfficherInfos
/// 
void CMechClock::AfficherInfos() const
{
  ostringstream os;
  /// \xrefitem todo1_3_2 "Todo1" "1.3.2 Travail à faire"
  /// Modifiez la ligne suivante pour que le pourcentage de la tension du ressort s'affiche à la place du "XX" 
  ///

  //On utilise GetSrpingTension pour avoir la tension actuelle du ressort en pourcentage entre 0 et 1
  os << "Je suis une horloge mécanique. Mon ressort est tendu à "<<GetSpringTension()*100<<"% \n";
  
  const string strText = os.str();
  AfficherTexte(strText);
  /// \xrefitem todo1_3_2 "Todo3" "1.3.2 Travail à faire"
  /// Afficher le texte \c strText en appelant la fonction \c AfficherTexte() de la classe CClock.
}


void CMechClock::TightenSpring()
{
  /// \xrefitem todo1_3_1 "Todo" "1.3.1 Travail à faire" 
  /// Implémenter la fonction de réinitialisation de la tension du ressort.
	m_nSpringTension = Tension;
}

float CMechClock::GetSpringTension() const
{
  /// \xrefitem todo1_3_1 "Todo" "1.3.1 Travail à faire" 
  /// Implémenter l'accesseur en lecture de la tension du ressort. La valeur retournée doit exprimer 
  /// un pourcentage de tension compris entre 0 et 1.

  //Transformation de m_nSpringTension en un float pour faire une division réelle
	float res = (m_nSpringTension * 1.0) / Tension;
  return res;
}

bool CMechClock::Tick()
{
	//Check si le ressort est totalement détendu
	if (m_nSpringTension == 0) {

		return false;
	}
	//Sinon, on fait un tick et on detend le spring de 1
	else {
		m_tpCurUTCTime += std::chrono::seconds(1);
		m_nSpringTension -= 1;
		return true;
	}
}
