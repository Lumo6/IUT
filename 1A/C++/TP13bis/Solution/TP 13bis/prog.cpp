/*!
 * \file "prog.cpp"
 * Programme principal.
 * 
 * Copyright (c) 2015 by Benjamin ALBOUY-KISSI
 */
#include <Windows.h>
#include <tchar.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <LibGraph2.h>
#include "maze.h"

#include <iostream>
using namespace std;
using namespace LibGraph2;

/*!\mainpage
 * Référez-vous au sujet du TP.
 */

//Solution
void drawCase(const CCase& cs, bool bBackOrFront);
//Fin Solution

const CSize g_szCase{ 30, 30 }; //!<\brief Taille de l'affichage des cases

//!\if include
//![main]
//!\endif

/*!\todo 1) Créer 4 objets de types CCase A, B, C et D disposées en carré au commentaire <CODE>//A faire 1)</CODE> dans la fonction _tWinMain()\n
 * La première ligne est A - B, la seconde ligne est C - D.\n
 * Les connexions entre les cases doivent être : B à droite de A, D en dessous de B, C à gauche de D.
 */

/*!\todo 2) Afficher les quatres cases A, B, C, D au commentaire <CODE>//A faire 2)</CODE> dans la fonction _tWinMain()\n
* Pour cela, vous créerez une fonction \p drawCase() qui réalisera le travail pour la case passée en paramètre\n
* Les côtés des cases doivent être affichées si le passage vers sa voisine est impossible. Utiliser pour cela
* <CODE>libgraph->setPen(MakeARGB(20, 0, 0, 0), 0.5f);</CODE> et <CODE>libgraph->setPen(MakeARGB(255, 0, 0, 0), 2.0f);</CODE>
* pour respectivement rendre le stylo translucide ou opaque.\n
* Pour le moment, le fond des cases reste transparent : <CODE>libgraph->setSolidBrush(MakeARGB(0, 0, 0, 0));</CODE>
*/

/*!\todo 3) Commentez les créations et utilisation des cases A, B, C, D que vous venez de tester dans la fonction _tWinMain()
 */

/*!\todo 4) Créer un objet de type CMaze au commentaire <CODE>//A faire 4)</CODE> dans la fonction _tWinMain()
 */

/*!\todo 5) Initialisez les variables \p nNbCasesX et \p nNbCasesY en fonction des données internes de l'objet maze au commentaire <CODE>//A faire 5)</CODE> dans la fonction _tWinMain()
 */

/*!\todo 6) Dessiner chaque case du labyrinthe au commentaire <CODE>//A faire 6)</CODE> dans la fonction _tWinMain()\n
 * \n
 * Les cases normales doivent être affichées en fond transparent en utilisant <CODE>libgraph->setSolidBrush(MakeARGB(0, 0, 0, 0));</CODE>\n
 * Les cases visitées doivent être affichées en fond jaune en utilisant <CODE>libgraph->setSolidBrush(MakeARGB(255, 255, 255, 0));</CODE>\n
 * Les cases de mauvais chemin doivent être affichées en fond rouge en utilisant <CODE>libgraph->setSolidBrush(MakeARGB(255, 255, 0, 0));</CODE>\n
 * \n
 * Les côtés des cases doivent être affiché si le passage vers sa voisine est impossible. Utiliser pour cela
 * <CODE>libgraph->setPen(MakeARGB(20, 0, 0, 0), 0.5f);</CODE> et <CODE>libgraph->setPen(MakeARGB(255, 0, 0, 0), 2.0f);</CODE>
 * pour respectivement rendre le stylo translucide ou opaque
 *
 */

/*!\todo 7) Réaliser un pas de l'algorithme de résolution du labyrinthe au commentaire <CODE>//A faire 7)</CODE> dans la fonction _tWinMain()
 */

/*!\todo 8) Dessiner le chemin de résolution du labyrinthe au commentaire <CODE>//A faire 8)</CODE> dans la fonction _tWinMain()\n
 * \n
 * Pour cela, tracez un trait vert (<CODE>libgraph->setPen(MakeARGB(255, 0, 192, 0), 1.0f);</CODE>)
 * le long du parcours déterminé par l'algorithme de résolution du labyrinthe.
 */

/*!\todo 9) Afficher les images des cases de départ d'arrivée et en cours au commentaire <CODE>//A faire 9)</CODE> dans la fonction _tWinMain()\n
 * L'image de la case de départ est dans le fichier \p start.png\n
 * L'image de la case d'arrivée est dans le fichier \p exit.png\n
 * L'image de la case en cours (fin du chemin) est dans le fichier \p me.png
 */

/*!
 * \brief
 * Point d'entrée principal.
 * 
 * \param hInstance
 * Ignoré.
 * 
 * \param hPrevInstance
 * Ignoré.
 * 
 * \param lpCmdLine
 * Ignoré.
 * 
 * \param nCmdShow
 * Ignoré.
 * 
 * \returns
 * 0
 * 
 * \snippet prog.cpp main
 */
int APIENTRY _tWinMain(HINSTANCE hInstance,
  HINSTANCE hPrevInstance,
  LPTSTR lpCmdLine,
  int nCmdShow)
{
  UNREFERENCED_PARAMETER(hInstance);
  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);
  UNREFERENCED_PARAMETER(nCmdShow);

  //Récupération de l'objet principal de LibGraph 2
  ILibGraph2* libgraph = GetLibGraph2();

  //Nombre de cases dans le labyrinthe (configure la taille de la fenêtre)
  size_t nNbCasesX = 1;
  size_t nNbCasesY = 1;

  //A faire 1)
  //Solution
  //CCase A{ 0, 0 }, B{ 1, 0 }, C{ 0, 1 }, D{ 1, 1 };
  //A.setRightCase(&B);
  //B.setBottomCase(&D);
  //D.setLeftCase(&C);
  //nNbCasesX = 2;
  //nNbCasesY = 2;
  //Fin Solution

  //A faire 4)
  //Solution
  CMaze maze;
  //Fin Solution

  //A faire 5)
  //Solution
  nNbCasesX = maze.getMaze().size();
  nNbCasesY = maze.getMaze()[0].size();
  //Fin Solution

  //Affiche un message d'aide succint
  libgraph->guiMessageBox("Aide", "Appuyez sur la barre d'espace pour faire un pas dans l'algorithme de résolution", msgbtn_types::MsgBtnOK, msgicon_types::MsgIcnInformation);
  //Affiche la fenêtre graphique avec une taille par défaut
  libgraph->show(CSize{ nNbCasesX*g_szCase.m_fWidth, nNbCasesY*g_szCase.m_fHeight });

  evt e;  //Evénement LibGraph 2
  //Boucle principale d'événements
  while (libgraph->waitForEvent(e))
  {
    switch (e.type)  //En fonction du type d'événement
    {
    case evt_type::evtRefresh:  //Raffraichissement de l'affichage (tout redessiner)
      //Utilisation des fonctions libgraph->beginPaint() / libgraph->endPaint() pour activer le backbuffer
      libgraph->beginPaint();
      {
        //A faire 2)
        //Solution
        //drawCase(A, false);
        //drawCase(B, false);
        //drawCase(C, false);
        //drawCase(D, false);
        //Fin Solution

        //A faire 6)
        //Solution
        //Trace les fonds des cases
        for (auto& col : maze.getMaze())
          for (auto& cs : col)
            drawCase(cs, true);
        //Trace les bordures des cases
        for (auto& col : maze.getMaze())
          for (auto& cs : col)
            drawCase(cs, false);
        //Fin Solution
        
        //A faire 8)
        //Solution
        libgraph->setPen(MakeARGB(255, 0, 192, 0), 1.0f);
        vector<CPoint> polyline;
        for (CCase* cs : maze.getPath())
        {
          polyline.push_back(CPoint{ cs->getPosX()*g_szCase.m_fWidth + g_szCase.m_fWidth / 2.0f, cs->getPosY()*g_szCase.m_fHeight + g_szCase.m_fHeight / 2.0f });
        }
        libgraph->drawPolylines(polyline);
        //Fin Solution

        //A faire 9)
        //Solution
        libgraph->drawBitmap("start.png", CPoint{ maze.getStart()->getPosX()*g_szCase.m_fWidth, maze.getStart()->getPosY()*g_szCase.m_fHeight }, g_szCase.m_fWidth / 640.0f);
        libgraph->drawBitmap("exit.png", CPoint{ maze.getExit()->getPosX()*g_szCase.m_fWidth, maze.getExit()->getPosY()*g_szCase.m_fHeight }, g_szCase.m_fWidth / 640.0f);
        libgraph->drawBitmap("me.png", CPoint{ maze.getPath().back()->getPosX()*g_szCase.m_fWidth, maze.getPath().back()->getPosY()*g_szCase.m_fHeight }, g_szCase.m_fWidth / 114.0f);
        //Fin Solution
      }
      libgraph->endPaint();
      break;
    case evt_type::evtKeyDown:  //Enfoncement d'une touche
      switch (e.vkKeyCode) //En fonction de la touche enfoncée
      {
      case VK_SPACE:
        //A faire 7)
        //Solution
        maze.step();
        //Fin Solution

        libgraph->askForRefresh();
        break;
      }
      break;
    }
  }
  //Libération de l'objet principal de LibGraph 2
  ReleaseLibGraph2();
  return 0;
}
//!\if include
//![main]
//!\endif


//Solution
/*!\brief Dessine une case de labyrinthe
 * \param cs Case à dessiner
 * \param bBackOrFront \p true s'il faut afficher le fond de la case, \p false s'il faut afficher les bordures
 */
void drawCase(const CCase& cs, bool bBackOrFront)
{
  ILibGraph2* libgraph = GetLibGraph2();

  if (bBackOrFront)
  {
    //Trace le fond de la case
    libgraph->setPen(MakeARGB(0, 0, 0, 0), 0.0f);
    if (cs.isBadWay())
      libgraph->setSolidBrush(MakeARGB(255, 255, 0, 0)); //Rouge
    else if (cs.isVisited())
      libgraph->setSolidBrush(MakeARGB(255, 255, 255, 0)); //Jaune
    else
      libgraph->setSolidBrush(MakeARGB(0, 0, 0, 0)); //Blanc
    libgraph->drawRectangle(CRectangle{ CPoint{ cs.getPosX()*g_szCase.m_fWidth, cs.getPosY()*g_szCase.m_fHeight }, g_szCase });
  }
  else
  {
    //Trace les bordures de la case
    CPoint p1, p2;

    if (!cs.getRightCase())
      libgraph->setPen(MakeARGB(255, 0, 0, 0), 2.0f);
    else
      libgraph->setPen(MakeARGB(20, 0, 0, 0), 0.5f);
    p1 = CPoint{ cs.getPosX()*g_szCase.m_fWidth + g_szCase.m_fWidth, cs.getPosY()*g_szCase.m_fHeight };
    p2 = CPoint{ cs.getPosX()*g_szCase.m_fWidth + g_szCase.m_fWidth, cs.getPosY()*g_szCase.m_fHeight + g_szCase.m_fHeight };
    libgraph->drawLine(p1, p2);

    if (!cs.getTopCase())
      libgraph->setPen(MakeARGB(255, 0, 0, 0), 2.0f);
    else
      libgraph->setPen(MakeARGB(20, 0, 0, 0), 0.5f);
    p1 = CPoint{ cs.getPosX()*g_szCase.m_fWidth, cs.getPosY()*g_szCase.m_fHeight };
    p2 = CPoint{ cs.getPosX()*g_szCase.m_fWidth + g_szCase.m_fWidth, cs.getPosY()*g_szCase.m_fHeight };
    libgraph->drawLine(p1, p2);

    if (!cs.getLeftCase())
      libgraph->setPen(MakeARGB(255, 0, 0, 0), 2.0f);
    else
      libgraph->setPen(MakeARGB(20, 0, 0, 0), 0.5f);
    p1 = CPoint{ cs.getPosX()*g_szCase.m_fWidth, cs.getPosY()*g_szCase.m_fHeight };
    p2 = CPoint{ cs.getPosX()*g_szCase.m_fWidth, cs.getPosY()*g_szCase.m_fHeight + g_szCase.m_fHeight };
    libgraph->drawLine(p1, p2);

    if (!cs.getBottomCase())
      libgraph->setPen(MakeARGB(255, 0, 0, 0), 2.0f);
    else
      libgraph->setPen(MakeARGB(20, 0, 0, 0), 0.5f);
    p1 = CPoint{ cs.getPosX()*g_szCase.m_fWidth, cs.getPosY()*g_szCase.m_fHeight + g_szCase.m_fHeight };
    p2 = CPoint{ cs.getPosX()*g_szCase.m_fWidth + g_szCase.m_fWidth, cs.getPosY()*g_szCase.m_fHeight + g_szCase.m_fHeight };
    libgraph->drawLine(p1, p2);

  }
}
//Fin Solution