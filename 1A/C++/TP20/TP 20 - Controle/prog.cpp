/// 
/// \file  "prog.cpp"
/// 
/// \brief Programme principal.
/// 
/// \xrefitem todo5 "Todo" "2 Travail à faire"
/// Référez vous aux instructions de la page principale \ref sec2.
/// 

/// 
/// \mainpage TP08 – Contrôle sur le polymorphisme \n Horlogerie
/// 
/// \tableofcontents
/// 
/// \section sec0 Exercice 0 Présentation
/// 
/// \subsection sec0_1 0.1 Objectifs du programme
/// 
/// \image HTML capture.png "Capture d'écran de l'application"
/// 
/// Il s’agit d’une représentation d’un mur sur lequel il est possible d'accrocher des horloges. Une horloge 
/// générique est caractérisée par son décalage horaire par rapport au temps universel (UTC). Plus 
/// spécifiquement, les horloges peuvent être de deux types : des horloges électroniques et des horloges 
/// mécaniques.
/// 
/// Les horloges mécaniques ont la particularité d'être mues par l'énergie emmagasinée dans un ressort.
/// A chaque tic d'horloge, le ressort se détend un peu plus jusqu'à l'être totalement. L'horloge s'arrête
/// alors. Il est alors nécessaire de "remonter" régulièrement l'horloge de façon à retendre le ressort 
/// pour lui redonner de l'énergie. A l'affichage, un arc de cercle coloré entourant l'horloge symbolise 
/// l'énergie restante dans le ressort.
/// 
/// Les horloges électroniques sont quant à elles totalement automatiques. Elles disposent d'une quantité 
/// d'énergie considérée infinie, elles ne cessent donc jamais de fonctionner.
/// 
/// Les horloges sont alors accrochées sur le mur et peuvent être sélectionnées pour afficher 
/// leurs caractéristiques. Des représentations d'horloges sont affichées en haut à gauche de la 
/// fenêtre. Lors d’un clic sur l’une d’elles, une horloge du même type est créée et peut alors être 
/// placée à l’aide de la souris sur le mur. Les horloges qui sont sur le mur 
/// peuvent être sélectionnées à la souris pour afficher leurs caractéristiques détaillées en haut 
/// au milieu de la fenêtre. Si l'horloge sélectionnée est une horloge mécanique, alors on peut la
/// remonter en appuyant sur la touche ‘\c R’.
/// 
/// \subsection sec0_2 0.2 Présentation de la structure du programme
/// 
/// Le schéma suivant représente le diagramme de classe du programme.
/// 
/// \image HTML classdiag.png "Diagramme de classes du programme"
/// 
/// \subsubsection sec0_2_1 0.2.1 La classe CTP (fichiers TP.h et TP.cpp)
/// 
/// Le programme s’articule autour d’un objet de type CTP dont les méthodes sont appelées par le 
/// programme principal en fonction des actions de l’utilisateur. Cette classe gère le mur,
/// crée les horloges à accrocher et les manipule.
/// 
/// \subsubsection sec0_2_2 0.2.2 La classe CGUI (fichiers gui.h et gui.cpp)
/// 
/// L’interface graphique utilisateur est gérée par cette classe. Toutes les fonctionnalités de 
/// LibGraph2 sont encapsulées dans cette unique classe. Les objets « clients » de cette classe 
/// (l’objet de type CTP, le mur de type CWall et les horloges de type CClock) l’utilisent 
/// pour s’afficher.
/// 
/// \subsubsection sec0_2_3 0.2.3 La classe CWall (fichiers Wall.h et Wall.cpp)
/// 
/// La classe CWall représente un mur. Les horloges sont associées au mur par 
/// des pointeurs intelligents dans le vecteur CWall::m_Clocks. Ce vecteur de 40 pointeurs 
/// correspond aux 40 horloges qui peuvent être accrochées sur le mur (4 lignes et 10 
/// colonnes).
/// 
/// \subsubsection sec0_2_4 0.2.4 La classe CClock (fichiers Clock.h et Clock.cpp)
/// 
/// Il s’agit de la classe centrale de ce programme. Elle gère une horloge au sens général, 
/// c’est-à-dire qu’elle a pour caractéristiques un décalage horaire et un point dans le temps
/// universel. Cette classe est destinée à être dérivée en horloge électronique (CAutoClock) et en 
/// horloge mécanique (CMechClock). 
/// 
/// \subsubsection sec0_2_5 0.2.5 La classe CAutoClock (fichiers AutoClock.h et AutoClock.cpp)
/// 
/// Cette classe représente une horloge électronique. Elle ne diffère de l'horloge au sens générique 
/// que par le fait qu'il est possible de l'afficher.
/// 
/// \subsubsection sec0_2_6 0.2.6 La classe CMechClock (fichiers MechClock.h et MechClock.cpp)
/// 
/// Cette classe représente une horloge mécanique. En plus des caractéristiques générales des horloges,
/// une horloge mécanique est caractérisée par l'énergie stockée dans son ressort moteur.
/// 
/// \section sec1 Exercice 1 Travail à réaliser
///
/// \note  	Le programme vous est fourni dans une version non compilable. Il doit l’être à l’issue 
/// de l’exercice \ref sec1_1 "1.1"
/// 
/// \subsection sec1_1 1.1 La hiérarchie de classes CClock, CAutoClock et CMechClock.
/// 
/// <UL>
///   <LI>Rendez la classe CClock polymorphe avec les classes CAutoClock et CMechClock pour permettre
///       l’affichage correct des horloges.</LI>
///   <UL>
///     <LI>Assurez-vous que la classe CClock ne soit pas instanciable.</LI>
///   </UL>
///   <LI>Complétez les constructeurs des classes CAutoClock et CMechClock pour les rendre 
///       fonctionnels.</LI>
///   <UL>
///     <LI>A partir de ce point, le programme doit être compilable, mais non encore fonctionnel.</LI>
///   </UL>
///   <LI>Complétez les fonctions CTP::CreateMechClock et CTP::CreateAutoClock pour créer les 
///       horloges.</LI>
///   <UL>
///     <LI>Compilez et testez. Vous devriez pouvoir créer des horloges et les accrocher sur le mur.</LI>
///   </UL>
/// </UL>
/// 
/// \subsection sec1_2 1.2 La classe CAutoClock
/// 
/// <UL>
///   <LI>Complétez la fonction CAutoClock::AfficherInfos.</LI>
///   <UL>
///     <LI>Référez-vous aux commentaires du code.</LI>
///     <UL><LI>Cette fonction est appelée par le biais de la fonction CTP::Afficher()</LI></UL>
///   </UL>
///   <LI>Compilez et testez. Vous devriez pouvoir voir les informations détaillées des horloges
///       électroniques en haut au milieu de la fenêtre graphique.</LI>
/// </UL>
/// 
/// \subsection sec1_3 1.3 La classe CMechClock
/// 
/// \subsubsection sec1_3_1 1.3.1 Spécialisation de la classe CMechClock
///
/// <UL>
///   <LI>Munissez la classe CMechClock d'une nouvelle donnée membre :</LI>
///   <UL>
///     <LI>Une donnée membre \c m_nSpringTension de type \c unsigned \c int pour stocker l'énergie 
///         disponible dans le ressort de l'horloge.</LI>
///     <UL>
///       <LI>Cette valeur doit être initialisée à 60.</LI>
///       <LI>Il est préférable d’utiliser une constante pour la valeur d’initialisation.</LI>
///     </UL>
///   </UL>
///   <LI>Complétez le corps de la fonction CMechClock::TightenSpring.</LI>
///   <LI>Complétez le corps de la fonction CMechClock::GetSpringTension.</LI>
/// </UL>
/// 
/// \subsubsection sec1_3_2 1.3.2	Affichage des informations spécialisées de la classe CMechClock
///
/// <UL>
///   <LI>Complétez la fonction CMechClock::AfficherInfos.</LI>
///   <UL>
///     <LI>Référez - vous aux commentaires du code.</LI>
///   </UL>
///   <LI>Compilez et testez. Vous devriez pouvoir voir les informations détaillées des horloges
///       mécaniques en haut au milieu de la fenêtre graphique.</LI>
/// </UL>
/// 
/// \subsubsection sec1_3_3 1.3.3	Retendre le ressort de l’horloge mécanique
///
/// <UL>
///   <LI>Dans la méthode CTP::TightenSpring, déterminez si l’horloge sélectionnée (donnée membre 
///       CTP::m_pSelectedClock) est une horloge mécanique :</LI>
///   <UL>
///     <LI>Si oui, alors continuer l'exécution de la fonction en retendant le ressort de l’horloge.</LI>
///     <LI>Si non, alors sortir de la fonction.</LI>
///     <UL><LI>Normalement, à cette étape, l'appuie sur la touche ‘\c R’ doit remonter l'horloge.</LI></UL>
///   </UL>
/// </UL>
/// 
/// \subsubsection sec1_3_4 1.3.4	Arrêt des horloges mécaniques quand leur ressort est détendu
///
/// <UL>
///   <LI>En utilisant le principe du polymorphisme, faites en sorte que les horloges mécaniques cessent 
///       de fonctionner lorsque le ressort est totalement détendu. Utilisez pour cela le membre 
///       CMechClock::m_nSpringTension</LI>
/// </UL>
///
/// \section sec2 Exercice 2	Remettez votre travail sur le cours en ligne
///
/// \note Il est important de savoir diffuser ses codes sources. Tout fichier qui peut être régénéré 
/// ne doit **JAMAIS** être diffusé. Supprimer ces fichiers permet de passer votre code source de plusieurs
/// méga octets à seulement quelques kilo octets.
///
/// <UL><LI> Vous remettrez sur l’ENT une archive compressée contenant toute votre solution Visual Studio. 
/// Avant de créer l’archive, **quittez Visual Studio**, et **supprimez** les fichiers inutiles.</LI></UL>
/// 
/// \warning La présence de l’un ou l’autre de ces fichiers dans votre archive entrainera une perte de points.
/// \warning La suppression de trop de fichiers (absence de la solution, absence d’un fichier source, etc...) entrainera une perte de points.
/// \warning La copie sur un de vos camarades entrainera un 0 pour vous et votre camarade. <small>(J’ai des outils très puissants pour déterminer s’il y a eu copie.)</small>
/// \warning La copie sur internet entrainera un 0 car de toute façon, il n’y a pas la solution sur internet.
/// 

#include "StdAfx.h"
#include "vecteur2D.h"
#include "TP.h"
#include "Wall.h"
#include "AutoClock.h"
#include "MechClock.h"
#include "incLibGraph2.h"
#include <memory>

using namespace LibGraph2;
using namespace std;

/// \brief Enumération des différentes étapes de l'IHM.
enum class Etape
{
  EtapeSelectCreate,
  EtapeMove
};

/// \brief
/// Point d'entrée principal de l'application.
/// 
/// \param hInstance     Non utilisé
/// \param hPrevInstance Non utilisé
/// \param lpCmdLine     Non utilisé
/// \param nCmdShow      Non utilisé
/// 
/// \returns
/// 0.
int APIENTRY _tWinMain(HINSTANCE hInstance,
  HINSTANCE hPrevInstance,
  LPTSTR lpCmdLine,
  int nCmdShow)
{
  UNREFERENCED_PARAMETER(hInstance);
  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);
  UNREFERENCED_PARAMETER(nCmdShow);

#ifdef _DEBUG
  _CrtMemState mem1, mem2, memdiff;
#endif
  _CrtMemCheckpoint(&mem1);

  {
    //Récupération de l'objet principal de LibGraph 2
    ILibGraph2* libgraph = GetLibGraph2();

    //Affiche la fenêtre graphique avec une taille par défaut (HDTV)
    libgraph->show(CSize{ 1280.0f,720.0f });

    evt e; //Evénement LibGraph 2

    shared_ptr<CGUI> pGUI = make_shared<CGUI>();
    CTP tp{ pGUI };
    Etape etape = Etape::EtapeSelectCreate;
    shared_ptr<CClock> pCreatedClock = nullptr;
    CPoint2D ptLastMousePos;

    auto startTP = std::chrono::steady_clock::now();
    unsigned long long nEllapsedSecs = 0;

    //Boucle principale d'événements
    while (libgraph->waitForEvent(e))
    {
      switch (e.type) //En fonction du type d'événement
      {
      case evt_type::evtRefresh: //Raffraichissement de l'affichage (tout redessiner)
        //Utiliser éventuellement les fonctions libgraph->beginPaint() / libgraph->endPaint() pour activer le backbuffer
        libgraph->beginPaint();
        {
          tp.Afficher();
          //Dessine une horloge mécanique en haut à gauche
          libgraph->drawBitmap("MechClock.png", CPoint{ 5.0f + 0.0f * (static_cast<float>(pGUI->mc_ClockSize.X()) + 10.0f), 5.0f });
          //Dessine unue horloge électronique à coté du précédent
          libgraph->drawBitmap("AutoClock.png", CPoint{ 5.0f + 1.0f * (static_cast<float>(pGUI->mc_ClockSize.X()) + 10.0f), 5.0f });
          if (pCreatedClock)
          {
            pCreatedClock->Afficher(ptLastMousePos);
          }
        }
        libgraph->endPaint();
        {
          unsigned long long nTemp = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - startTP).count();
          if (nTemp > nEllapsedSecs)
          {
            auto nNbSecs = nTemp - nEllapsedSecs;
            for (decltype(nNbSecs) i = 0; i < nNbSecs; ++i)
            {
              tp.Tick();
              if (pCreatedClock)
                pCreatedClock->Tick();
            }
            nEllapsedSecs = nTemp;
          }
        }
        libgraph->askForRefresh();//Animation !
        break;
      case evt_type::evtKeyDown: //Enfoncement d'une touche
        switch (e.vkKeyCode) //En fonction de la touche enfoncée
        {
        case 'R'://Remonte l'horloge sélectionnée
          tp.TightenSpring();
          libgraph->askForRefresh();
          break;
        }
        break;

      case evt_type::evtMouseDown:
        switch (etape)
        {
        case Etape::EtapeSelectCreate:
        {
          bool bBtnClicked = false;
          //vérifie si le click est dans un bouton de création
          //Horloge mécanique
          if (e.x < 1 * (pGUI->mc_ClockSize.X() + 10)
            && e.y < pGUI->mc_ClockSize.Y() + 10)
          {
            pCreatedClock = tp.CreateMechClock();
            bBtnClicked = true;
          }
          //Horloge électronique
          if (e.x >= 1 * (pGUI->mc_ClockSize.X() + 10) && e.x < 2 * (pGUI->mc_ClockSize.X() + 10)
            && e.y < pGUI->mc_ClockSize.Y() + 10)
          {
            pCreatedClock = tp.CreateAutoClock();
            bBtnClicked = true;
          }
          if (bBtnClicked)
          {
            if (pCreatedClock)
              pCreatedClock->SetGUI(pGUI);
            etape = Etape::EtapeMove;
            libgraph->askForRefresh();
            break;
          }
          tp.SelectClock(CPoint2D(e.x, e.y));
          libgraph->askForRefresh();
          break;
        }

        case Etape::EtapeMove:
          if (tp.HangClock(pCreatedClock, CPoint2D(e.x, e.y)))
          {
            tp.SelectClock(CPoint2D(e.x, e.y));
            pCreatedClock = nullptr;
            etape = Etape::EtapeSelectCreate;
          }
          libgraph->askForRefresh();
          break;
        }

        break;
      case evt_type::evtMouseMove: //Déplacement de la souris
        ptLastMousePos = CPoint2D(e.x, e.y);
        if (etape == Etape::EtapeMove)
        {
          tp.HighLightCase(ptLastMousePos);
          libgraph->askForRefresh();
        }
        break;
      }
    }

    //Libération de l'objet principal de LibGraph 2
    ReleaseLibGraph2();
  }

  _CrtMemCheckpoint(&mem2);
  if (_CrtMemDifference(&memdiff, &mem1, &mem2))
  {
    _CrtMemDumpAllObjectsSince(&mem1);
    GetLibGraph2()->guiMessageBox("Fuites mémoires !", "Des fuites mémoires ont été détectées, vérifiez vos allocations et désallocations !", msgbtn_types::MsgBtnOK, msgicon_types::MsgIcnStop);
    ReleaseLibGraph2();
  }

  return 0;
}
