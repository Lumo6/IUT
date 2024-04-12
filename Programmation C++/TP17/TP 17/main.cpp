/*!\file
 * \brief Programme principal
 * \author Benjamin ALBOUY-KISSI
 */
#define NOMINMAX
#include <Windows.h>
#include <tchar.h>
#include <random>
#include <chrono>
#include <memory>
#include <thread>
#include "Butterfly.h"
#include "vecteur2D.h"
#include "Swarm.h"
#include "Net.h"
#include "incLibGraph2.h"
using namespace LibGraph2;
using namespace std;

const double pi = 3.14159265359; //!< C'est PI !


__if_exists(CButterfly)
{
  void drawButterfly(const CButterfly& but);
}
CPoint toLibGraph2Point(const CPoint2D& pt2D);
CPoint2D toPoint2D(const CPoint& pt);

/*!\brief Point d'entrée principal du programme
 *
 * \param[in] hInstance ignoré
 * \param[in] hPrevInstance ignoré
 * \param[in] lpCmdLine ignoré
 * \param[in] nCmdShow ignoré
 * \return 0
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
#ifdef _DEBUG
  _CrtMemState mem1, mem2, memdiff;
#endif
  _CrtMemCheckpoint(&mem1);
  {

    ILibGraph2* pLibgraph = GetLibGraph2();
    evt e;
    //Affiche la fenêtre graphique avec une taille par défaut
    pLibgraph->show(CSize{ 1280.0f, 720.0f });

    chrono::high_resolution_clock::time_point TimeLastBirth = chrono::high_resolution_clock::now();
    
    CPoint ptMousePos;
    bool bFaceToLeft = true;

    pLibgraph->setFont("Calibri", 28.0f, font_styles::FontStyleBold);
    pLibgraph->setSolidBrush(MakeARGB(255, 0, 193, 0));
    //Boucle principale d'événements
    std::shared_ptr<CButterfly> pap = std::make_shared<CButterfly>(pLibgraph->getSize().m_fWidth, pLibgraph->getSize().m_fHeight);
    CSwarm swarm;
    CNet net;
    while(pLibgraph->waitForEvent(e))
    {
      switch(e.type) //En fonction du type du dernier événement
      {
      case evt_type::evtRefresh: //Raffraichissement de l'affichage (tout redessiner)
      {
        //Utiliser éventuellement les fonctions beginPaint() / endPaint() pour activer le backbuffer
        pLibgraph->beginPaint();
        //Utiliser ici les fonctions de dessins

          pLibgraph->drawBitmap("grass.png", CPoint{});
          //!\todo Réaliser ici une boucle qui pour chaque papillon de l'essaim le fait se déplacer en ayant peur du filet (dont la position est en \c ptMousePos ) et l'affiche en utilisant la fonction drawButterfly
          
          std::shared_ptr<CButterfly> pap = swarm.GetFirst();
          while (pap) {
              pap->MoveAfraidOf(toPoint2D(ptMousePos));
              drawButterfly(*pap);
              pap = swarm.GetNext(pap);
          }

          if (bFaceToLeft)
            pLibgraph->drawBitmap("butterfly-net-left.png", ptMousePos, CPoint{ 111.0f, 168.0f }, 0.5, 0.0);
          else
            pLibgraph->drawBitmap("butterfly-net-right.png", ptMousePos, CPoint{ 249.0f, 168.0f }, 0.5, 0.0);

          size_t cnt = 0;
          //!\todo Modifier la variable cnt pour qu'elle soit égale au nombre de papillons vivants présents dans le filet
          pLibgraph->drawString(to_string(net.Count()) + " papillon" + (net.Count() > 1 ? "s" : "") + " dans votre filet", CPoint{ 10.0f, 10.0f });

        pLibgraph->endPaint();

        //Fait naitre un papillon si plus de 3 secondes se sont écoulées depuis la dernière naissance
        if ((chrono::high_resolution_clock::now() - TimeLastBirth) >= chrono::seconds(3))
        {
          TimeLastBirth = chrono::high_resolution_clock::now();
          //!\todo Ajouter ici un nouveau papillon à l'essaim
          std::shared_ptr<CButterfly> pap = std::make_shared<CButterfly>(pLibgraph->getSize().m_fWidth, pLibgraph->getSize().m_fHeight);
          swarm.AppendButterfly(pap);
        }
        pLibgraph->askForRefresh();
        break;
      }
      case evt_type::evtMouseMove: //Déplacement de la souris
        if (e.x < ptMousePos.m_fX)
          bFaceToLeft = true;
        else
          bFaceToLeft = false;
        ptMousePos.m_fX = (float)e.x;
        ptMousePos.m_fY = (float)e.y;
        {
          //!\todo Créer ici une boucle sur tous les papillons de l'essaim pour voir s'il sont à moins de 25 pixels du filet. Si c'est le cas alors les retirer de l'essaim et les ajouter au filet.
            std::shared_ptr<CButterfly> pap = swarm.GetFirst();
            while (pap) {
                CVecteur2D dist{ pap->getPos() - toPoint2D(ptMousePos) };
                if (dist.Norm() <= 25) {
                    swarm.RemoveButterfly(pap);
                    net.AppendButterfly(pap);
                }
                pap = swarm.GetNext(pap);
            }
        }
        break;
      }
    }
    ReleaseLibGraph2();
  }

  _CrtMemCheckpoint(&mem2);
  if(_CrtMemDifference(&memdiff, &mem1, &mem2))
  {
    _CrtMemDumpAllObjectsSince(&mem1);
    GetLibGraph2()->guiMessageBox("Fuites mémoires !", "Des fuites mémoires ont été détectées, vérifiez vos allocations et désallocations !", msgbtn_types::MsgBtnOK, msgicon_types::MsgIcnStop);
    ReleaseLibGraph2();
  }
  return 0;
}

/*!\brief Fonction utilitaire pour convertir un CPoint2D en LibGraph2::CPoint
 *
 * \param[in] pt2D Point à convertir
 * \return Point convertit
 * \see toPoint2D
 */
CPoint toLibGraph2Point(const CPoint2D& pt2D)
{
  return CPoint{ (float)pt2D.X(), (float)pt2D.Y() };
}

/*!\brief Fonction utilitaire pour convertir un LibGraph2::CPoint en CPoint2D
 * \param[in] pt Point à convertir
 * \return Point convertit
 * \see toLibGraph2Point
 */
CPoint2D toPoint2D(const CPoint& pt)
{
  return CPoint2D{ (double)pt.m_fX, (double)pt.m_fY };
}

__if_exists(CButterfly)
{
/*!\fn void drawButterfly(const CButterfly& but)
  * \brief Dessine un papillon à l'écran
  * \param[in] but Papillon à dessiner
  */
  void drawButterfly(const CButterfly& but)
  {
    ILibGraph2* pLibGraph = GetLibGraph2();

    pLibGraph->drawBitmap("butterfly.png", toLibGraph2Point(but.getPos()), 0.15, but.getSpeed().Orientation()*180.0 / pi, true);
  }
}
