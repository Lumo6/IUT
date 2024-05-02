#define NOMINMAX
#include <Windows.h>
#include <tchar.h>
#include <chrono>
#define LIBGRAPH2_LEVEL 4
#include <LibGraph2.h>
using namespace LibGraph2;

#include <iostream>
#include "SaisonsCirc.h"
#include "GraphPoint.h"
#include "GraphRect.h"
#include "Bouton.h"


void Help()
{
    LibGraph2::GetLibGraph2()->guiMessageBox("Aide", "Commandes claviers :\n"
        "C : Crée un graphe circulaire montrant les variations de températures entre les saisons\n"
        "R : Crée un graphe à cases de couleurs différentes en fonction de la température de chaque mois\n"
        "P : Crée un graphe à points montrant les moyennes des années 1892 à 2022\n"
        "M : Affiche le menu\n"
        "F1 : Affiche cette aide\n"
        "Q : Quitter \n", LibGraph2::msgbtn_types::MsgBtnOK, LibGraph2::msgicon_types::MsgIcnInformation);
}

int APIENTRY _tWinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPTSTR    lpCmdLine,
    int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    Help();

    //Affiche la fenêtre graphique avec une taille par défaut
    ILibGraph2* pLibgraph = GetLibGraph2();
    float Width = 950;
    float Height = 800;
    pLibgraph->show(CSize{ Width, Height });

    //Enumération de toute les "pages" qu'il y a dans l'application
    enum class Page
    {
        Main,
        Cercle,
        Points,
        Rectangle
    };

    //Déclaration de toute les variables utilisées
    evt e;
    Page Bouton = Page::Main;
    Saisons GraphCirc;
    GraphCirc.TriDonnee();
    GraphPoint GraphaPoint;
    GraphRect GraphRectangulaire;
    SButton Menu(LibGraph2::CPoint{ pLibgraph->getSize().m_fWidth / 3,pLibgraph->getSize().m_fHeight / 10 }
    , LibGraph2::CSize{ pLibgraph->getSize().m_fWidth / 3 ,50 }, "MENU");
    SButton Graph1(LibGraph2::CPoint{ 10,Menu.GetPos().m_fY + Menu.GetSize().m_fHeight*1.5f }
    , LibGraph2::CSize{ pLibgraph->getSize().m_fWidth / 4 - 10 / 2,pLibgraph->getSize().m_fWidth / 4 - 10 / 2 }, "", "GraphesRect.png");
    SButton Graph2(Graph1.GetPos() + LibGraph2::CPoint{ Graph1.GetSize().m_fWidth*1.5f,0.0f }
    , LibGraph2::CSize{ Graph1.GetSize() }, "", "GraphesPoints.png");
    SButton Graph3(Graph2.GetPos() + LibGraph2::CPoint{ Graph1.GetSize().m_fWidth * 1.5f,0.0f }
    , LibGraph2::CSize{ Graph1.GetSize() }, "", "GraphesCercle.png");
    SButton HelpB(LibGraph2::CPoint{ Menu.GetPos().m_fX,Menu.GetPos().m_fY*8 }
    , Menu.GetSize(), "HELP");
    SButton Quitter(LibGraph2::CPoint{ Menu.GetPos().m_fX,Menu.GetPos().m_fY*9 }
    , Menu.GetSize(), "QUITTER");
    SButton Retour(LibGraph2::CPoint{ Width - 75,Height - 775 }
    , LibGraph2::CSize{ 50,50 }, "X");

    //Boucle principale
    while (pLibgraph->waitForEvent(e))
    {
        switch (e.type)  //En fonction du type du dernier événement
        {
        case evt_type::evtRefresh:
            switch (Bouton) {
            case Page::Cercle:
                    LibGraph2::GetLibGraph2()->beginPaint();
                    Retour.DrawButton();
                    LibGraph2::GetLibGraph2()->drawString(Retour.GetString(), LibGraph2::CPoint{ Retour.GetPos().m_fX + 11.0f,Retour.GetPos().m_fY + 3.0f });
                    GraphCirc.DrawGraphs(e.x, e.y);
                    LibGraph2::GetLibGraph2()->askForRefresh();
                    LibGraph2::GetLibGraph2()->endPaint();
                    if (e.x > Retour.GetPos().m_fX && e.x<(Retour.GetPos().m_fX + Retour.GetSize().m_fWidth) && e.y>Retour.GetPos().m_fY && e.y < (Retour.GetPos().m_fY + Retour.GetSize().m_fHeight)) {
                        Bouton = Page::Main;
                        LibGraph2::GetLibGraph2()->askForRefresh();
                    }
                break;
            case Page::Main:
                Menu.DrawButton();
                Graph1.DrawButton();
                Graph2.DrawButton();
                Graph3.DrawButton();
                HelpB.DrawButton();
                Quitter.DrawButton();
                LibGraph2::GetLibGraph2()->drawString(Menu.GetString(), LibGraph2::CPoint{ Menu.GetPos().m_fX + Menu.GetSize().m_fWidth / 3,Menu.GetPos().m_fY });
                LibGraph2::GetLibGraph2()->drawString(HelpB.GetString(), LibGraph2::CPoint{ HelpB.GetPos().m_fX + HelpB.GetSize().m_fWidth / 3,HelpB.GetPos().m_fY });
                LibGraph2::GetLibGraph2()->drawString(Quitter.GetString(), LibGraph2::CPoint{ Quitter.GetPos().m_fX + Quitter.GetSize().m_fWidth / 3 - 23.0f,Quitter.GetPos().m_fY });
                if (e.x > Graph1.GetPos().m_fX && e.x<(Graph1.GetPos().m_fX + Graph1.GetSize().m_fWidth) && e.y>Graph1.GetPos().m_fY && e.y < (Graph1.GetPos().m_fY + Graph1.GetSize().m_fHeight)) {
                    Bouton = Page::Rectangle;
                    LibGraph2::GetLibGraph2()->askForRefresh();
                }
                if (e.x > Graph2.GetPos().m_fX && e.x<(Graph2.GetPos().m_fX + Graph2.GetSize().m_fWidth) && e.y>Graph2.GetPos().m_fY && e.y < (Graph2.GetPos().m_fY + Graph2.GetSize().m_fHeight)) {
                    Bouton = Page::Points;
                    LibGraph2::GetLibGraph2()->askForRefresh();
                }
                if (e.x > Graph3.GetPos().m_fX && e.x<(Graph3.GetPos().m_fX + Graph3.GetSize().m_fWidth) && e.y>Graph3.GetPos().m_fY && e.y < (Graph3.GetPos().m_fY + Graph3.GetSize().m_fHeight)) {
                    Bouton = Page::Cercle;
                    LibGraph2::GetLibGraph2()->askForRefresh();
                }
                if (e.x > HelpB.GetPos().m_fX && e.x<(HelpB.GetPos().m_fX + HelpB.GetSize().m_fWidth) && e.y>HelpB.GetPos().m_fY && e.y < (HelpB.GetPos().m_fY + HelpB.GetSize().m_fHeight)) {
                    Help();
                    LibGraph2::GetLibGraph2()->askForRefresh();
                }
                if (e.x > Quitter.GetPos().m_fX && e.x<(Quitter.GetPos().m_fX + Quitter.GetSize().m_fWidth) && e.y>Quitter.GetPos().m_fY && e.y < (Quitter.GetPos().m_fY + Quitter.GetSize().m_fHeight)) {
                    return 0;
                }
                break;
            case Page::Points:
                    LibGraph2::GetLibGraph2()->beginPaint();
                    Retour.DrawButton();
                    LibGraph2::GetLibGraph2()->drawString(Retour.GetString(), LibGraph2::CPoint{ Retour.GetPos().m_fX + 11.0f,Retour.GetPos().m_fY + 3.0f });
                    GraphaPoint.GraphPointMoyenne5Ans(e.x, e.y);
                    LibGraph2::GetLibGraph2()->askForRefresh();
                    LibGraph2::GetLibGraph2()->endPaint();
                    if (e.x > Retour.GetPos().m_fX && e.x<(Retour.GetPos().m_fX + Retour.GetSize().m_fWidth) && e.y>Retour.GetPos().m_fY && e.y < (Retour.GetPos().m_fY + Retour.GetSize().m_fHeight)) {
                        Bouton = Page::Main;
                        LibGraph2::GetLibGraph2()->askForRefresh();
                    }
                break;
            case Page::Rectangle:
                    LibGraph2::GetLibGraph2()->beginPaint();
                    Retour.DrawButton();
                    LibGraph2::GetLibGraph2()->drawString(Retour.GetString(), LibGraph2::CPoint{ Retour.GetPos().m_fX + 11.0f,Retour.GetPos().m_fY + 3.0f });
                    GraphRectangulaire.DrawGraph(e.x, e.y);
                    LibGraph2::GetLibGraph2()->askForRefresh();
                    LibGraph2::GetLibGraph2()->endPaint();
                    if (e.x > Retour.GetPos().m_fX && e.x<(Retour.GetPos().m_fX + Retour.GetSize().m_fWidth) && e.y>Retour.GetPos().m_fY && e.y < (Retour.GetPos().m_fY + Retour.GetSize().m_fHeight)) {
                        Bouton = Page::Main;
                        LibGraph2::GetLibGraph2()->askForRefresh();
                    }
                break;
            }


            break;

        case evt_type::evtKeyDown:  //Enfoncement d'une touche
            switch (e.vkKeyCode) //En fonction de la touche enfoncée
            {
            case 'C':
                Bouton = Page::Cercle;
                pLibgraph->askForRefresh();
                break;
            case 'R':
                Bouton = Page::Rectangle;
                pLibgraph->askForRefresh();
                break;
            case'P':
                Bouton = Page::Points;
                pLibgraph->askForRefresh();
                break;
            case'M':
                Bouton = Page::Main;
                pLibgraph->askForRefresh();
                break;
            case VK_F1:
                Help();
                break;
            case 'Q':
                return 0;
                break;
            }
            break;

        case evt_type::evtMouseDown:
            pLibgraph->askForRefresh();
            break;
        }
    }

    ReleaseLibGraph2();
    return 0;
}