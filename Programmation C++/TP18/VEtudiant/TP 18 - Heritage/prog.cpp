/*!
 * \file  "prog.cpp"
 *
 * \brief Programme principal. 
 *
 */

/*!
 * \mainpage TP 18 - Héritage - Tracé de formes géométriques
 *
 * \tableofcontents
 * 
 * \section sec1 Exercice 1 Présentation
 * \subsection sec1_1 1.1 Objectifs du programme
 *
 * Il s’agit de réaliser un programme simpliste de dessin par ordinateur. Le programme est capable d’afficher des rectangles et des ellipses. Ces 
 * formes peuvent être affichées avec différents styles, couleurs et épaisseurs de trait. Elles sont toutes les deux gérées par deux points appelés 
 * origine et arrivée. Le point d’origine est le premier point cliqué par l’utilisateur pour créer la forme, le point d’arrivée est la position à 
 * laquelle l’utilisateur a relâché la souris. La forme est alors tracée dans la boîte englobante formée par ces deux points.
 * 
 * Pour choisir la forme à créer, l’utilisateur peut appuyer sur la touche ‘R’ pour un rectangle, sur la touche ‘E’ pour une ellipse ou sur la 
 * touche ‘A’ pour un arc elliptique. La touche ‘T’ permet de choisir les attributs de tracé pour la prochaine forme créée.
 * 
 * \subsection sec1_2 1.2 Présentation de la structure du programme
 * \subsubsection sec1_2_1 1.2.1 La classe CTP (fichiers TP.h et TP.cpp)
 *
 * Le programme s’articule autour d’un objet de type CTP dont les méthodes sont appelées par le programme principal en fonction des actions de 
 * l’utilisateur.
 * 
 * \subsubsection sec1_2_2 1.2.2 La classe CForme (fichiers Forme.h et Forme.cpp)
 *
 * La classe CForme gère toutes les propriétés communes à toutes les formes. Les attributs de tracés sont :
 * \li CForme::m_colColor : La couleur du tracé
 * \li CForme::m_fThickness : l’épaisseur du tracé
 * \li CForme::m_eStyle : le style du tracé
 * \li CForme::m_ptP1 : le point d’origine de la forme
 * \li CForme::m_ptP2 : le point d’arrivée de la forme
 * \li CForme::m_rectBounds : la boite englobante de la forme, automatiquement calculée lors de la modification de CForme::m_ptP1 et CForme::m_ptP2 par les fonctions CForme::SetP1 et CForme::SetP2.
 * 
 * Enfin, la fonction membre CForme::Afficher() définit les attributs du tracé avant affichage, de façon que la forme spécifique (rectangle ou ellipse) n’ait pas à le faire.
 * 
 * \section sec2 Exercice 2 Travail à réaliser
 *
 * \subsection sec2_1 2.1 La classe CRect
 *
 * La classe CRect modélise un rectangle. Le rectangle doit être affiché en suivant la boîte englobante de la forme définie par un point d’origine 
 * et un point d’arrivée.
 * <UL>
 *    <LI>Vous devez implémenter la classe CRect dans les fichiers Rectangle.h et Rectangle.cpp.</LI>
 *    <UL>
 *      <LI>Quel type de relation y a-t-il entre un rectangle et une forme ? Est-ce une relation de composition, d’agrégation ou d’héritage ?</LI>
 *      <LI>Quel(s) attribut(s) supplémentaire(s) à ceux de la classe CForme faut-il ajouter à la classe CRect ?</LI>
 *      <LI>Quel comportement de la forme faut-il modifier ou ajouter à la classe CRect ?</LI>
 *    </UL>
 *    <LI>Vous devez ensuite ajouter à la classe CTP une liste de CRect et modifier les comportements de la classe CTP de façon à rendre opérationnel la création et l’affichage des rectangles.</LI>
 *    <UL>
 *      <LI>Référez-vous aux commentaires \c "\todo" des fichiers TP.h et TP.cpp.</LI>
 *    </UL>
 * </UL>
 *
 * \subsection sec2_2 2.2 La classe CEllipse
 *
 * La classe CEllipse modélise une ellipse. L’ellipse doit être affichée en suivant la boîte englobante de la forme définie par un point d’origine 
 * et un point d’arrivée.
 * <UL>
 *   <LI> Implémentez la classe CEllipse sur le même modèle que la classe CRect </LI>
 *   <LI> Vous devez ensuite ajouter à la classe CTP une liste de CEllipse sur le même principe que pour les rectangles et modifier les comportements de la classe CTP de façon à rendre opérationnel la création et l’affichage des ellipses. </LI>
 *   <LI> Référez-vous aux commentaires \c "\todo" des fichiers TP.h et TP.cpp. </LI>
 * </UL>
 *
 * \subsection sec2_3 2.3 La classe CArc
 *
 * La classe CArc modélise un arc elliptique. L’arc doit être affiché en suivant la boîte englobante de son ellipse. L’arc est défini sur son 
 * ellipse génératrice par un angle de départ et un angle de balayage.
 * <UL>
 *    <LI>Implémentez la classe CArc sur le même modèle que la classe CRect</LI>
 *    <UL>
 *      <LI>Quelles données membres faut-il rajouter ?</LI>
 *      <LI>Vous devez ensuite ajouter à la classe CTP une liste de CArc sur le même principe que pour les rectangles et modifier les comportements de la classe CTP de façon à rendre opérationnel la création et l’affichage des arcs.</LI>
 *      <LI>Référez-vous aux commentaires \c "\todo" des fichiers TP.h et TP.cpp.</LI>
 *    </UL>
 * </UL>
 */
#include "StdAfx.h"
#include "TP.h"
#include "incLibGraph2.h"
#include <iostream>

/*!
* \brief Enumération des différentes étapes de construction des objets
*/
enum EtapeConstruction
{
  //!\brief Prochain clic définira P1
  EtapeP1,
  //!\brief Prochain clic définira P2
  EtapeP2,
  //!\brief Prochain clic définira l'angle de départ pour les arc
  EtapeStartAngle,
  //!\brief Prochain clic définira l'angle de balayage pour les arc
  EtapeSweepAngle
};

/*!
* \brief Opérateur préfixé d'incrémentation pour les étapes de construction
*/
EtapeConstruction& operator++(EtapeConstruction& eEtape)
{
  if(eEtape == EtapeSweepAngle)
    eEtape = EtapeP1;
  else
    eEtape = (EtapeConstruction)(((int)eEtape)+1);
  return eEtape;
}

/*!
* \brief Opérateur postfixé d'incrémentation pour les étapes de construction
*/
EtapeConstruction operator++(EtapeConstruction& eEtape, int)
{
  EtapeConstruction retVal(eEtape);
  if(eEtape == EtapeSweepAngle)
    eEtape = EtapeP1;
  else
    eEtape = (EtapeConstruction)(((int)eEtape)+1);
  return retVal;
}

/*!\brief Affiche l'aide en ligne
 */
void Help()
{
  LibGraph2::GetLibGraph2()->guiMessageBox("Aide", "Commandes claviers :\n"
                                           "A : Crée des arcs\n"
                                           "R : Crée des rectangles\n"
                                           "E : Crée des ellipses\n"
                                           "T : Modifie les attributs de tracés\n"
                                           "F1 : Affiche cette aise", LibGraph2::msgbtn_types::MsgBtnOK, LibGraph2::msgicon_types::MsgIcnInformation);
}


/*!
* \brief
* Point d'entrée principal de l'application.
* 
* \param hInstance     Non utilisé
* \param hPrevInstance Non utilisé
* \param lpCmdLine     Non utilisé
* \param nCmdShow      Non utilisé
* 
* \returns
* 0.
*/
int APIENTRY _tWinMain(HINSTANCE hInstance,
  HINSTANCE hPrevInstance,
  LPTSTR lpCmdLine,
  int nCmdShow)
{
#ifdef _DEBUG
  _CrtMemState mem1, mem2, memdiff;
#endif
  _CrtMemCheckpoint(&mem1);

  {
    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);

    Help();

    //Récupération de l'objet principal de LibGraph 2
    LibGraph2::ILibGraph2* libgraph = LibGraph2::GetLibGraph2();
    //Affiche la fenêtre graphique avec une taille par défaut
    libgraph->show();
    LibGraph2::evt e; //Evénement LibGraph 2

    //Données de l'application
    CTP tp;

    //Données d'interfaces homme machine
    CTP::TypeObjet eTypeConstruit = CTP::TypeObjet::TypeRectangle;
    EtapeConstruction eEtapeConstruction = EtapeP1;
    bool bMouseDown = false;

    //Boucle principale d'événements
    while(libgraph->waitForEvent(e))
    {
      switch(e.type) //En fonction du type d'événement
      {
      case LibGraph2::evt_type::evtRefresh: //Raffraichissement de l'affichage (tout redessiner)
        libgraph->beginPaint();
          tp.Afficher();
        libgraph->endPaint();
        break;
      case LibGraph2::evt_type::evtKeyDown: //Enfoncement d'une touche
        switch(e.vkKeyCode) //En fonction de la touche enfoncée
        {
        case 'A':
          if(eEtapeConstruction != EtapeP1)
            break;
          eTypeConstruit = CTP::TypeObjet::TypeArc;
          break;
        case 'R':
          if(eEtapeConstruction != EtapeP1)
            break;
          eTypeConstruit = CTP::TypeObjet::TypeRectangle;
          break;
        case 'E':
          if(eEtapeConstruction != EtapeP1)
            break;
          eTypeConstruit = CTP::TypeObjet::TypeEllipse;
          break;
        case 'T':
          if(eEtapeConstruction != EtapeP1)
            break;
          tp.GuiSetDefaultStyle();
          break;
        case VK_F1:
          if(eEtapeConstruction != EtapeP1)
            break;
          Help();
          break;
        }
        break;
      case LibGraph2::evt_type::evtMouseDown: //Enfoncement de la souris
        bMouseDown = true;
        if(eEtapeConstruction == EtapeP1)
        {
          switch(eTypeConstruit)
          {
          case CTP::TypeObjet::TypeRectangle:
            tp.AjouterRectangle(LibGraph2::CPoint((float)e.x, (float)e.y));
            break;
          case CTP::TypeObjet::TypeEllipse:
            tp.AjouterEllipse(LibGraph2::CPoint((float)e.x, (float)e.y));
            break;
          case CTP::TypeObjet::TypeArc:
            tp.AjouterArc(LibGraph2::CPoint((float)e.x, (float)e.y));
            break;
          }
          eEtapeConstruction = EtapeP2;
        }
        break;
      case LibGraph2::evt_type::evtMouseMove: //Déplacement de la souris
        if(bMouseDown)
        {
          switch(eEtapeConstruction)
          {
          case EtapeP2:
            switch(eTypeConstruit)
            {
            case CTP::TypeObjet::TypeRectangle:
              tp.ModifierDernierRectangle(LibGraph2::CPoint((float)e.x, (float)e.y));
              break;
            case CTP::TypeObjet::TypeEllipse:
              tp.ModifierDerniereEllipse(LibGraph2::CPoint((float)e.x, (float)e.y));
              break;
            case CTP::TypeObjet::TypeArc:
              tp.ModifierDernierArc(LibGraph2::CPoint((float)e.x, (float)e.y));
              break;
            }
            break;
          case EtapeStartAngle:
            switch(eTypeConstruit)
            {
            case CTP::TypeObjet::TypeArc:
              tp.ModifierDernierArcStartAngle(LibGraph2::CPoint((float)e.x, (float)e.y));
              break;
            }
            break;
          case EtapeSweepAngle:
            switch(eTypeConstruit)
            {
            case CTP::TypeObjet::TypeArc:
              tp.ModifierDernierArcSweepAngle(LibGraph2::CPoint((float)e.x, (float)e.y));
              break;
            }
            break;
          }
          libgraph->askForRefresh();
        }
        break;
      case LibGraph2::evt_type::evtMouseUp: //Relachement de la souris
        if(!bMouseDown) //La souris a été relevé sur la fenêtre alors quelle n'y avait pas été enfoncée
          break;
        bMouseDown = false;
        switch(eTypeConstruit)
        {
        case CTP::TypeObjet::TypeRectangle:
        case CTP::TypeObjet::TypeEllipse:
          if(eEtapeConstruction == EtapeP2)
            eEtapeConstruction = EtapeP1;
          else
            ++eEtapeConstruction;
          break;
        case CTP::TypeObjet::TypeArc:
          ++eEtapeConstruction;
          break;
        }
        break;
      }
    }
    //Libération de l'objet principal de LibGraph 2
    LibGraph2::ReleaseLibGraph2();
  }

  _CrtMemCheckpoint(&mem2);
  if(_CrtMemDifference(&memdiff, &mem1, &mem2))
  {
    _CrtMemDumpAllObjectsSince(&mem1);
    LibGraph2::GetLibGraph2()->guiMessageBox("Fuites mémoires !", "Des fuites mémoires ont été détectées, vérifiez vos allocations et désallocations !", LibGraph2::msgbtn_types::MsgBtnOK, LibGraph2::msgicon_types::MsgIcnStop);
    LibGraph2::ReleaseLibGraph2();
  }

  return 0;
}
