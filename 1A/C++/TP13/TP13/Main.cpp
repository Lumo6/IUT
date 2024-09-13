#include <Windows.h>
#include <tchar.h>
#include <LibGraph2.h>
#include <chrono>
using namespace LibGraph2;

int APIENTRY _tWinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPTSTR    lpCmdLine,
    int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    //R�cup�ration de l'objet principal de LibGraph 2
    ILibGraph2* libgraph = GetLibGraph2();
    //Affiche la fen�tre graphique avec une taille par d�faut
    libgraph->show();
    evt e;  //Ev�nement LibGraph 2
    bool cercle = true;
    //Boucle principale d'�v�nements
    std::chrono::high_resolution_clock::time_point tpStart = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point tpStop = std::chrono::high_resolution_clock::now();
    float fDuree;
    while (libgraph->waitForEvent(e))
    {
        switch (e.type)  //En fonction du type d'�v�nement
        {
        case evt_type::evtRefresh:  //Raffraichissement de l'affichage (tout redessiner)
            tpStop = std::chrono::high_resolution_clock::now();
            
            //Dur�e entre les deux points temporels exprim�e en s
            libgraph->beginPaint();
            //Choisit un stylo rouge d'�paisseur 5 pixels tra�ant des pointill�s
            libgraph->setPen(MakeARGB(255, 255, 0, 0), 5.0f, LibGraph2::pen_DashStyles::Dash);
            //Choisit un pinceau jaune
            libgraph->setSolidBrush(MakeARGB(255, 255, 255, 0));
            //Dessine un rectangle avec le stylo et le pinceau s�lectionn�
            libgraph->drawRectangle(CRectangle{ CPoint{20,40 },CSize{200,100} });
            //Choisit un pinceau cyan translucide
            libgraph->setSolidBrush(MakeARGB(128, 0, 255, 255));
            //Dessine une ellipse
            if (cercle) {
                tpStop = std::chrono::high_resolution_clock::now();
                std::chrono::duration<float, std::chrono::seconds::period> dur = tpStop - tpStart;
                if (dur.count() > 2.0) {
                    tpStart = tpStop;
                }
                float haut = 100.0 * ((dur.count() - 1.0) * (dur.count() - 1.0)) + 100.0;
                std::cout << haut<<"    ";
                libgraph->drawEllipse(CRectangle{ CPoint{100,haut},CSize{200,200} });
                libgraph->askForRefresh();
            }
            //Affiche r�ellement � l��cran l�ensemble du dessin
            libgraph->endPaint();
            break;

        case evt_type::evtKeyDown:  //Enfoncement d'une touche
            switch (e.vkKeyCode) //En fonction de la touche enfonc�e
            {
            case 'A':
                libgraph->hide();
                break;
            case 'C':
                libgraph->show(CSize{400,400},bool(false));
                break;
            }
            break;

        case evt_type::evtMouseDown:  //D�placement de la souris
            //Position de la souris dans les variables e.x et e.y
            std::cout << "Clic de la souris en position : " << e.x << ", " << e.y;
            break;
        }
    }

    //Lib�ration de l'objet principal de LibGraph 2
    ReleaseLibGraph2();
    return 0;
}