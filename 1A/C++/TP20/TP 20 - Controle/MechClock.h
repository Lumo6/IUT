/// 
/// \file  "MechClock.h"
/// 
/// \brief Déclaration de la classe CMechClock. 
/// 
/// 
#pragma once
#include "Clock.h"

/// 
/// \brief
/// Classe représentant une horloge mécanique.
/// 
/// Cette classe gère une horloge mécanique. En plus des caractéristiques 
/// générales des horloges, une horloge mécanique est caractérisée par son
/// ressort moteur qui se détend au fil du temps. Il faut régulièrement 
/// "remonter" l'horloge pour qu'elle continue à fonctionner.
/// 
/// La classe CMechClock est déclarée dans le fichier MechClock.h.
/// \code
/// #include "MechClock.h"
/// \endcode
/// 
/// \xrefitem todo1_1 "Todo" "1.1 Travail à faire" Complétez la déclaration de la
/// classe CMechClock. Cette classe doit hériter de la classe CClock.
/// 
/// \xrefitem todo1_3_1 "Todo" "1.3.1 Travail à faire"
/// Munissez la classe CMechClock du membre \c m_nSpringTension. Ce membre doit être initialisé 
/// à la valeur 60. Il est préférable d'utiliser une constante pour cette valeur d'initialisation.
/// 
/// \xrefitem todo1_3_4 "Todo" "1.3.4 Travail à faire"
/// En utilisant le principe du polymorphisme, faites en sorte que les horloges 
/// mécaniques cessent de fontionner lorsque le ressort est totalement détendu.
/// Utilisez pour cela le membre CMechClock::m_nSpringTension.
/// 
class CMechClock : public CClock
{
public:
  CMechClock(const std::chrono::minutes& durUTCOffset);

  void Afficher(const CPoint2D& AbsPixelPos) const override;
  void AfficherInfos() const override;

  /// \brief Remonte l'horloge en réinitialisant le membre CMechClock::m_nSpringTension
  void TightenSpring();
  /// \brief Accesseur en lecture de la tension du ressort en pourcentage (compris entre 0 et 1).
  float GetSpringTension() const;

  //Const d'initialisation / Reinitialisation de la tension du ressort
  const unsigned int Tension = 60;

  //Valeur de la tension du ressort
  unsigned int m_nSpringTension = Tension;

  //Redefinition de la fonction Tick pour gerer le cas ou le ressort est entierement détendu
  bool Tick() override;
};
