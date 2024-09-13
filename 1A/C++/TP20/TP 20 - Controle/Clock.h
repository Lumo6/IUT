/// 
/// \file  "Clock.h"
/// 
/// \brief Déclaration de la classe CClock. 
/// 
/// 
#pragma once
#include "vecteur2D.h"
#include "gui.h"
#include <memory>
#include <string>
#include <chrono>

/// \brief
/// Classe représentant une horloge.
/// 
/// Cette classe gère une horloge au sens général. Une horloge représente le temps sur un fuseau horraire. 
/// Cette classe est destinée à être dérivée pour spécialiser l'horloge en horloge mécanique ou horloge électronique.
/// 
/// La classe CClock est déclarée dans le fichier Clock.h.
/// \code
/// #include "Clock.h"
/// \endcode
/// 
/// \xrefitem todo1_1 "Todo" "1.1 Travail à faire" Mettre en place le polymorphisme
/// pour la hiérarchie de classe des horloges. Faire en sorte que la classe CClock 
/// ne puisse pas être instanciable.
/// 
class CClock
{
protected:
  
  std::chrono::minutes m_durUTCOffset;                   ///< \brief Décalage temporel par rapport au temps UTC
  std::chrono::system_clock::time_point m_tpCurUTCTime;  ///< \brief Temps de l'horloge

  /// \brief Objet de type CGUI utilisé pour réaliser l'affichage des différentes informations
  std::shared_ptr<CGUI> m_pGUI;

protected:
  void AfficherTexte(const std::string& strText) const;

public:
  /// \brief Constructeur
  /// \param durUTCOffset Décalage temporel en minutes par rapport au temps universel
  CClock(const std::chrono::minutes& durUTCOffset);

  /// \brief Définit l'objet utilisé pour la représentation graphique de l'horloge
  /// \param pGUI Pointeur intelligent vers l'objet de gestion de l'interface graphique
  /// \remark Cette fonction existe pour alléger le nombre de paramètres du constructeur, afin que vous évitiez de vous poser des questions.
  void SetGUI(std::shared_ptr<CGUI> pGUI) { m_pGUI = pGUI; }

  /// \brief Affiche cette horloge à la position absolue \c AbsPixelPos
  /// \param AbsPixelPos Position absolue de l'horloge
  /// \remark \c AbsPixelPos définit la position du centre de l'horloge.
  virtual void Afficher(const CPoint2D& AbsPixelPos) const = 0;

  /// \brief L'horloge fait tick ! Avance le temps d'une seconde
  /// \return \c true si la seconde a été effectivement ajoutée \c false sinon
  virtual bool Tick();

  /// \brief Affiche les informations détaillées de cette horloge
  /// 
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
  virtual void AfficherInfos() const = 0;

  /// \brief Retourne le temps local de l'horloge
  /// \return Un time_point représentant l'heure locale (non UTC) de l'horloge
  std::chrono::system_clock::time_point GetTimePoint() const { return m_tpCurUTCTime + m_durUTCOffset; }

  virtual ~CClock() = default;
};
