/*!
 * \file "TP.h"
 * 
 * \version 2016
 *
 * \brief Déclaration de la classe CTP
 */
#pragma once
#include "Rectangle.h"
#include "Ellipse.h"
#include "Arc.h"
#include "incLibGraph2.h"
#include <list>
#include <memory>

/*!
 * \brief
 * Classe "métier" du TP.
 * 
 * Cette classe concentre toutes les actions du programme nécessaires pour le 
 * fonctionnement du programme. Les méthodes publiques sont les points d'entrées 
 * événementiels qui sont appelés par le programme principal en réponse des 
 * interactions de l'utilisateur.
 *
 * La classe CTP est déclarée dans le fichier TP.h.
 * \code
 * #include "TP.h"
 * \endcode
 * 
 * \todo Ajouter en données membres privées une liste de pointeurs intelligents
 * vers des CForme. Cette collection référencera tous les objets graphiques à 
 * afficher.
 *
 */
class CTP
{
public:
    using ListePointerForm = std::list<std::shared_ptr<CForme>>;
private:
  ListePointerForm m_ListePointerForm;
  //! Couleur à utiliser pour la création des objets
  LibGraph2::ARGB m_argbCurColor = 0xFF000000;
  //! Couleur de remplissage à utiliser pour la création des objets
  LibGraph2::ARGB m_argbCurFill = 0xFFFF0000;
  //! Epaisseur de trait à utiliser pour la création des objets
  float m_fCurThickness = 1.0f;
  //! Style de trait à utiliser pour la création des objets
  LibGraph2::pen_DashStyles m_eCurStyle = LibGraph2::pen_DashStyles::Solid;

public:
  /*!
  * \brief Types d'objets graphiques supportés
  */
  enum class TypeObjet
  {
    //!\brief objet de type Rectangle
    TypeRectangle,
    //!\brief objet de type Ellipse
    TypeEllipse,
    //!\brief objet de type Arc
    TypeArc
  };

public:
  void Afficher() const;
  void GuiSetDefaultStyle();
  void GuiSetDefaultFill();
  void AjouterForme(TypeObjet to, const LibGraph2::CPoint& ptP1);
  void ModifierDerniereForme(const LibGraph2::CPoint& ptP2);
  void ModifierDernierArcStartAngle(const LibGraph2::CPoint& pt);
  void ModifierDernierArcSweepAngle(const LibGraph2::CPoint& pt);
  void MettreEnPremierPlan();
  void MettreEnArrierePlan();
};

