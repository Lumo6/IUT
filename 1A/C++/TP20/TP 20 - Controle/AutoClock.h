/// 
/// \file  "AutoClock.h"
/// 
/// \brief Déclaration de la classe CAutoClock. 
/// 
/// 
#pragma once
#include "Clock.h"

/// \brief
/// Classe représentant une horloge électronique.
/// 
/// Cette classe gère une horloge électronique. Une horloge électronique fonctionne pour une durée infinie.
/// 
/// La classe CAutoClock est déclarée dans le fichier AutoClock.h.
/// \code
/// #include "AutoClock.h"
/// \endcode
/// 
/// \xrefitem todo1_1 "Todo" "1.1 Travail à faire" Complétez la déclaration de la classe
/// CAutoClock. Cette classe doit hériter de la classe CClock.
class CAutoClock : public CClock
{
public:
  CAutoClock(const std::chrono::minutes& durUTCOffset);
  void Afficher(const CPoint2D& AbsPixelPos) const override;
  void AfficherInfos() const override;
};
