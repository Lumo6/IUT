/*!
 * \file  "prog.cpp"
 *
 * \brief Programme principal. 
 *
 */

/*!
 * \mainpage TP 09 – Exercice 2	Utilisation de la classe CMatrice dans un cas réel
 *
 * \tableofcontents
 * 
 * \section sec2_1 2.1 Objectif du programme.
 *
 * Il s’agit d’un programme qui applique une transformation géométrique à une image. La transformation est représentée par une matrice 3x3 dont le 
 * rôle est de calculer les nouvelles coordonnées des pixels de l’image originale.
 * 
 * \subsection sec2_1_1 2.1.1 Un peu de maths…
 *
 * \subsubsection sec2_1_1_1 2.1.1.1 Coordonnées homogènes et transformations géométriques
 *
 * Un point du plan est localisé à l’aide de son abscisse \f$ x \f$ et de son ordonnée \f$ y \f$. On définit les coordonnées homogènes de ce point comme étant tous 
 * les triplets de valeurs proportionnels à \f$\left(\begin{matrix}x\\y\\1\end{matrix}\right)\f$. C’est-à-dire que le même point est aussi bien repéré par \f$\left(\begin{matrix}x\\y\\1\end{matrix}\right)\f$ que par \f$\left(\begin{matrix}42 x\\42 y\\42\end{matrix}\right)\f$
 * ou encore \f$\left(\begin{matrix}\alpha x\\ \alpha y\\ \alpha\end{matrix}\right)\f$ avec \f$\alpha\f$ non nul.
 *
 * Ainsi, en utilisant les coordonnées homogènes, on peut représenter sous forme de matrices toutes les transformations homographiques (toutes les 
 * transformations qui conservent l’alignement des points). Par exemple, une translation de vecteur \f$\left(\begin{matrix}t_x \\ t_y \end{matrix}\right)\f$ (un cas particulier des 
 * homographies) est représentée par la matrice \f$\left(\begin{matrix}1&0&t_x \\ 0&1&t_y \\ 0&0&1\end{matrix}\right)\f$. Pour appliquer une transformation géométrique, il suffit de calculer le 
 * produit matriciel entre la matrice de transformation et les coordonnées homogènes du point à transformer. Ainsi, l’application de la translation 
 * précédente au point d’abscisse \f$ x \f$ et d’ordonnée \f$ y \f$ se traduit par : \f$\left(\begin{matrix}1&0&t_x \\ 0&1&t_y \\ 0&0&1\end{matrix}\right)\left(\begin{matrix}x \\ y \\ 1\end{matrix}\right)=\left(\begin{matrix}x+t_x \\ y+t_y \\ 1\end{matrix}\right)\f$.
 * 
 * \subsection sec2_1_2 2.1.2 Les différentes transformations considérées par l’application
 *
 * L’application pourra appliquer des rotations (matrice \f$ R\f$ ), agrandissements (matrice \f$ S\f$ ) et déchirements (matrice \f$ T\f$ ), ainsi que toutes les 
 * combinaisons de ces transformations. L’ensemble de ces combinaisons s’appellent les transformations affines (matrice \f$ A\f$ ) (toutes les 
 * transformations qui conservent le parallélisme – un sous ensemble des homographies). Pour combiner des transformations, il suffit de multiplier 
 * leurs matrices ensembles. Nous appliquerons dans l’ordre la rotation, la mise à l’échelle puis le déchirement, ainsi nous avons \f$ A=T S R\f$ .
 *
 * \subsubsection sec2_1_2_1 2.1.2.1 Matrices de rotation
 *
 * Une matrice de rotation d’angle \f$\theta\f$ autour de l’origine s’écrit : \f$R=\left(\begin{matrix}\cos{\theta}&-\sin{⁡\theta}&0 \\ \sin{⁡\theta}&\cos{\theta}&0 \\ 0&0&1\end{matrix}\right)\f$.
 *
 * \subsubsection sec2_1_2_2 2.1.2.2 Matrices d’agrandissement / réduction
 *
 * Une matrice de mise à l’échelle de facteurs \f$\alpha_x\f$ selon les abscisses et \f$\alpha_y\f$ selon les ordonnées s’écrit : \f$S=\left(\begin{matrix}\alpha_x&0&0 \\ 0&\alpha_y&0 \\ 0&0&1\end{matrix}\right)\f$.
 *
 * \subsubsection sec2_1_2_3 2.1.2.3 Matrices de déchirement
 *
 * Une matrice de déchirement de facteurs \f$\beta_x\f$ selon les abscisses et \f$\beta_y\f$ selon les ordonnées s’écrit : \f$T=\left(\begin{matrix}1&\beta_x&0 \\ \beta_y&1&0 \\ 0&0&1\end{matrix}\right)\f$.
 *
 * \subsection sec2_1_3 2.1.3 Transformer une image
 *
 * Pour transformer une image, il suffit de calculer la nouvelle position des pixels. Soit \f$p=\left(\begin{matrix}x \\ y \\ 1\end{matrix}\right)\f$ 
 * les coordonnées d’un pixel de l’image originale, sa position dans l’image transformée sera alors \f$p'=A p\f$. Or les 
 * coordonnées des pixels doivent être entières, et avec le calcul \f$A p\f$ il y a peu de chance de tomber sur un résultat entier. Donc si l’on souhaite 
 * appliquer l’algorithme dans ce sens direct, il faudra rendre entière les coordonnées et l’on risque alors de rater des pixels de l’image 
 * d’arrivée. Le plus sûr est alors de déterminer la position d’un pixel dans l’image originale à partir de sa position dans l’image transformée, 
 * c’est-à-dire calculer \f$p\f$ à partir de \f$p'\f$. L’algorithme consiste alors à parcourir tous les pixels \f$p'\f$ de l’image transformée et de calculer leur 
 * position \f$p=A^{-1} p'\f$ dans l’image de départ pour connaitre leur couleur. Si le calcul ne tombe pas sur une position de pixel entière, alors on 
 * prendra le pixel le plus proche.
 * 
 * \section sec2_2 2.2 Présentation de la structure du programme
 *
 * \subsection sec2_2_1 2.2.1 La classe CTP (fichiers TP.h et TP.cpp)
 *
 * Le programme s’articule toujours autour d’un objet de type CTP dont les méthodes sont appelées par le programme principal en fonction des actions 
 * de l’utilisateur. Cette classe gèrera (une fois que vous l’aurez fait dans la partie \ref sec2_3 "2.3") les transformations de l’image.
 *
 * \subsection sec2_2_2 2.2.2 La classe CBitMap
 *
 * La classe CBitMap gère un tableau de pixel. La fonction CBitMap::Transform implémente l’algorithme précédent pour transformer l’image.
 *
 * \section sec2_3 2.3 Travail à réaliser
 *
 * \subsection sec2_3_1 2.3.1 Classe CTP
 *
 * <ul>
 *   <li>Ajouter à la classe CTP 3 matrices membres privés. Ces matrices 3x3 doivent travailler sur des \c double.</li>
 *   <ul>
 *     <li>Une matrice \c m_matRot pour la matrice de rotation.</li>
 *     <li>Une matrice \c m_matScale pour la matrice de mise à l'échelle.</li>
 *     <li>Une matrice \c m_matTear pour la matrice de déchirement.</li>
 *   </ul>
 *   <li>Dans le fichier CTP, référez-vous aux commentaires \c "\todo" pour modifier le code.</li>
 * </ul>
 *
 * \subsection sec2_3_2 2.3.2 Classe CBitMap
 *
 * <ul>
 *   <li>Modifiez la fonction CBitMap::Transform en vous référant aux commentaires \c "\todo".</li>
 * </ul>
 *
 */
#include "stdafx.h"
#include "incLibGraph2.h"
#include "TP.h"
using namespace LibGraph2;
using namespace std;


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
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
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

    pLibgraph->show();

    CTP tp;
    if(!tp.OpenPPMFile())
      return 0;

    evt e;
    while(pLibgraph->waitForEvent(e))
    {
      switch(e.type)
      {
      case evt_type::evtRefresh:
        pLibgraph->beginPaint();
        {
          tp.Draw();
        }
        pLibgraph->endPaint();
        break;
      case evt_type::evtKeyDown:
        switch(e.vkKeyCode)
        {
        case 'O':
          if(tp.OpenPPMFile())
            pLibgraph->askForRefresh();
          break;
        case 'A':
          tp.IncreaseAngle();
          pLibgraph->askForRefresh();
          break;
        case 'Q':
          tp.DecreaseAngle();
          pLibgraph->askForRefresh();
          break;
        case 'Z':
          tp.IncreaseScaleX();
          pLibgraph->askForRefresh();
          break;
        case 'S':
          tp.DecreaseScaleX();
          pLibgraph->askForRefresh();
          break;
        case 'E':
          tp.IncreaseScaleY();
          pLibgraph->askForRefresh();
          break;
        case 'D':
          tp.DecreaseScaleY();
          pLibgraph->askForRefresh();
          break;
        case 'R':
          tp.IncreaseTearX();
          pLibgraph->askForRefresh();
          break;
        case 'F':
          tp.DecreaseTearX();
          pLibgraph->askForRefresh();
          break;
        case 'T':
          tp.IncreaseTearY();
          pLibgraph->askForRefresh();
          break;
        case 'G':
          tp.DecreaseTearY();
          pLibgraph->askForRefresh();
          break;
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
