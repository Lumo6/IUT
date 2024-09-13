/*!
 * \file  "prog.cpp"
 *
 * \brief Programme principal. 
 *
 */

/*!
 * \mainpage TP 07 - Polymorphisme - Tracé de formes géométriques mieux
 *
 * \tableofcontents
 * 
 * \section sec1 Exercice 1 Présentation
 * \subsection sec1_1 1.1 Objectifs du programme
 *
 * Il s’agit du même programme que pour le TP précédent. Cependant, cette fois les formes sont ordonnées comme si elles étaient empilées les unes 
 * par-dessus les autres. L’utilisateur a la possibilité de placer la forme la plus haute en bas de la pile par l’appui sur la touche ‘↓’ et 
 * inversement de placer la forme la plus basse en haut de la pile par l’appui sur la touche ‘↑’. Pour que cela soit mieux représenté, les formes 
 * sont maintenant remplies par une couleur de remplissage, qui est modifiable par la touche ‘C’ sur le même principe que les tracés.
 * 
 * \subsection sec1_2 1.2 Présentation de la structure du programme
 * \subsubsection sec1_2_1 1.2.1 La classe CTP (fichiers TP.h et TP.cpp)
 *
 * Le programme s’articule toujours autour d’un objet de type CTP dont les méthodes sont appelées par le programme principal en fonction des actions 
 * de l’utilisateur. Cette classe gèrera (une fois que vous l’aurez fait dans \ref sec2_2 "la section 2.2") les formes dans une seule et même liste, de façon à ce 
 * que les différentes formes puissent se placer les unes par-dessus les autres quelques soient leurs types.
 * 
 * \subsubsection sec1_2_2 1.2.2 La classe CForme (fichiers Forme.h et Forme.cpp)
 *
 * La classe CForme possède les mêmes caractéristiques que pour le TP précédent, avec en plus la donnée membre CForme::m_colRemplissage qui définit 
 * la couleur de remplissage de la forme. La fonction membre CForme::Afficher() définit la couleur de remplissage et les attributs du tracés avant 
 * affichage, de façon à ce que la forme spécifique (rectangle, ellipse ou arc) n’ait pas à le faire.
 * 
 * \section sec2 Exercice 2 Travail à réaliser
 *
 * \subsection sec2_1 2.1 La hiérarchie de classes CForme, CRect, CEllipse et CArc.
 *
 * <UL>
 *    <LI>Récupérez les fichiers sources des classes CRect, CEllipse et CArc du TP précédent pour les inclure dans votre projet (par copier-coller !).</LI>
 *    <LI>Rendez la classe CForme polymorphe pour permettre l'affichage correct des objets de types dérivés par la manipulation d'un pointeur de 
 *    type CForme.</LI>
 * </UL>
 *
 * \subsection sec2_2 2.2 La classe CTP
 *
 * <UL>
 *    <LI>Munissez la classe CTP d’une liste de pointeurs intelligents vers des CForme.</LI>
 *    <LI>Complétez les fonctions de la classe CTP pour rendre le code fonctionnel</LI>
 *    <UL>
 *      <LI>Référez-vous aux commentaires \c "\todo" des fichiers TP.h et TP.cpp.</LI>
 *      <LI>Beaucoup de code peut être copié-collé du TP précédent moyennant quelques modifications.</LI>
 *    </UL>
 * </UL>
 *
 */
#include "StdAfx.h"
#include "TP.h"
#include "incLibGraph2.h"
#include <iostream>

/*!
* \brief Enumération des différentes étapes de construction des objets
*/
enum class EtapeConstruction
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
  if(eEtape == EtapeConstruction::EtapeSweepAngle)
    eEtape = EtapeConstruction::EtapeP1;
  else
    eEtape = static_cast<EtapeConstruction>((static_cast<int>(eEtape))+1);
  return eEtape;
}

/*!
* \brief Opérateur postfixé d'incrémentation pour les étapes de construction
*/
EtapeConstruction operator++(EtapeConstruction& eEtape, int)
{
  EtapeConstruction retVal(eEtape);
  if(eEtape == EtapeConstruction::EtapeSweepAngle)
    eEtape = EtapeConstruction::EtapeP1;
  else
    eEtape = static_cast<EtapeConstruction>((static_cast<int>(eEtape)) + 1);
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
                                           "C : Modifie la couleur de remplissage des formes\n"
                                           "Haut : Passer en premier plan la forme du fond\n"
                                           "Bas : Passer en arrière plan la forme du haut\n"
                                           "F1 : Affiche cette aide", LibGraph2::msgbtn_types::MsgBtnOK, LibGraph2::msgicon_types::MsgIcnInformation);
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
    EtapeConstruction eEtapeConstruction = EtapeConstruction::EtapeP1;
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
          if(eEtapeConstruction != EtapeConstruction::EtapeP1)
            break;
          eTypeConstruit = CTP::TypeObjet::TypeArc;
          break;
        case 'R':
          if(eEtapeConstruction != EtapeConstruction::EtapeP1)
            break;
          eTypeConstruit = CTP::TypeObjet::TypeRectangle;
          break;
        case 'E':
          if(eEtapeConstruction != EtapeConstruction::EtapeP1)
            break;
          eTypeConstruit = CTP::TypeObjet::TypeEllipse;
          break;
        case 'T':
          if(eEtapeConstruction != EtapeConstruction::EtapeP1)
            break;
          tp.GuiSetDefaultStyle();
          break;
        case 'C':
          if(eEtapeConstruction != EtapeConstruction::EtapeP1)
            break;
          tp.GuiSetDefaultFill();
          break;
        case VK_UP:
          if(eEtapeConstruction != EtapeConstruction::EtapeP1)
            break;
          tp.MettreEnPremierPlan();
          libgraph->askForRefresh();
          break;
        case VK_DOWN:
          if(eEtapeConstruction != EtapeConstruction::EtapeP1)
            break;
          tp.MettreEnArrierePlan();
          libgraph->askForRefresh();
          break;
        case VK_F1:
          if(eEtapeConstruction != EtapeConstruction::EtapeP1)
            break;
          Help();
          break;
        }
        break;
      case LibGraph2::evt_type::evtMouseDown: //Enfoncement de la souris
        bMouseDown = true;
        if(eEtapeConstruction == EtapeConstruction::EtapeP1)
        {
          tp.AjouterForme(eTypeConstruit, LibGraph2::CPoint((float)e.x, (float)e.y));
          eEtapeConstruction = EtapeConstruction::EtapeP2;
        }
        break;
      case LibGraph2::evt_type::evtMouseMove: //Déplacement de la souris
        if(bMouseDown)
        {
          switch(eEtapeConstruction)
          {
          case EtapeConstruction::EtapeP2:
            tp.ModifierDerniereForme(LibGraph2::CPoint((float)e.x, (float)e.y));
            break;
          case EtapeConstruction::EtapeStartAngle:
            switch(eTypeConstruit)
            {
            case CTP::TypeObjet::TypeArc:
              tp.ModifierDernierArcStartAngle(LibGraph2::CPoint((float)e.x, (float)e.y));
              break;
            }
            break;
          case EtapeConstruction::EtapeSweepAngle:
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
          if(eEtapeConstruction == EtapeConstruction::EtapeP2)
            eEtapeConstruction = EtapeConstruction::EtapeP1;
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
