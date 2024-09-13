// TP17bis.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "incLibGraph2.h"
#include "PetriDish.h"
#include "GUI.h"

using namespace std::chrono_literals;

/*!
 * Gère l'IHM bas niveau avec LibGraph2.
 * 
 * \param hInstance     Ignoré
 * \param hPrevInstance Ignoré
 * \param lpCmdLine     Ignoré
 * \param nCmdShow      Ignoré
 * \return 0 (=SUCCESS)
 */
int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                       _In_opt_ HINSTANCE hPrevInstance,
                       _In_ LPTSTR    lpCmdLine,
                       _In_ int       nCmdShow)
{
  UNREFERENCED_PARAMETER(hInstance);
  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);
  UNREFERENCED_PARAMETER(nCmdShow);

  //Récupération de l'objet principal de LibGraph 2
  LibGraph2::ILibGraph2* libgraph = LibGraph2::GetLibGraph2();

  CPetriDish petri(32);
  CGUI gui(petri);

  LibGraph2::evt e;  //Evénement LibGraph 2

  //Boucle principale d'événements
  while (libgraph->waitForEvent(e))
  {
    switch (e.type)  //En fonction du type d'événement
    {
    case LibGraph2::evt_type::evtRefresh:  //Raffraichissement de l'affichage (tout redessiner)
      libgraph->beginPaint();
        gui.DrawIt();
      libgraph->endPaint();
      break;

    case LibGraph2::evt_type::evtKeyDown:  //Enfoncement d'une touche
      switch (e.vkKeyCode) //En fonction de la touche enfoncée
      {
      case 'I':
        gui.Simulation(false);
        break;
      case 'O':
        gui.Simulation();
        break;
      case VK_UP:
      case VK_RIGHT:
        gui.SetStepDuration(gui.StepDuration() - 50ms);
        break;
      case VK_DOWN:
      case VK_LEFT:
        gui.SetStepDuration(gui.StepDuration() + 50ms);
        break;
      }
      break;

    case LibGraph2::evt_type::evtMouseDown:  //Déplacement de la souris
      gui.MousePressed(LibGraph2::CPoint(static_cast<float>(e.x), static_cast<float>(e.y)));
      break;
    }
  }

  //Libération de l'objet principal de LibGraph 2
  LibGraph2::ReleaseLibGraph2();
  return 0;
}
