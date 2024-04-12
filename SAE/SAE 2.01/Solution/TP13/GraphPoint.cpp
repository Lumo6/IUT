#include "GraphPoint.h"

void GraphPoint::GraphPointMoyenne5Ans(unsigned int x, unsigned int y)
{

    LibGraph2::GetLibGraph2()->setPen(LibGraph2::MakeARGB(255, 0, 0, 0), 1.0f, LibGraph2::pen_DashStyles::Solid);
    LibGraph2::GetLibGraph2()->setSolidBrush(LibGraph2::MakeARGB(255, 255, 255, 255));

    float sizeX = 800.0;
    float sizeY = 450.0;

    //Création des contours du graphe
    LibGraph2::CPoint Cadre(sizeX / 10, sizeY / 10);
    LibGraph2::CSize sizeCadre(sizeX, sizeY);
    LibGraph2::CRectangle rectCadre(Cadre, sizeCadre);

    LibGraph2::GetLibGraph2()->drawRectangle(rectCadre);
    LibGraph2::GetLibGraph2()->setSolidBrush(LibGraph2::MakeARGB(255, 0, 0, 0));

    std::vector<std::pair<unsigned int, float>> tabMoyenneAnnuelle;
    tabMoyenneAnnuelle = GetMoyenneAnnee();
    std::pair<float, float> MinMax = GetMinMax(tabMoyenneAnnuelle);
    float min = MinMax.first;
    float max = MinMax.second;

    //Affichage des valeurs des échelles du graphe
    LibGraph2::CPoint ptStr(sizeX / 10 - 60, sizeY / 10);
    LibGraph2::GetLibGraph2()->drawString(std::to_string(max), ptStr);
    ptStr.m_fY += sizeY;
    LibGraph2::GetLibGraph2()->drawString(std::to_string(min), ptStr);

    LibGraph2::CPoint posPoint(Cadre.m_fX + 10, 325);
    LibGraph2::CSize sizePoint(5, 5);
    LibGraph2::CRectangle Point(posPoint, sizePoint);

    //Remplissage du graphe a point avec les moyennes par années
    LibGraph2::GetLibGraph2()->setSolidBrush(LibGraph2::MakeARGB(255, 0, 0, 255));
    LibGraph2::GetLibGraph2()->setPen(LibGraph2::MakeARGB(255, 0 , 0, 255), 1.0f, LibGraph2::pen_DashStyles::Solid);
    std::vector<LibGraph2::CPoint> listElem;
    for (size_t i = 0; i < tabMoyenneAnnuelle.size(); i++) {
        Point.m_ptTopLeft.m_fY = Cadre.m_fY + sizeY - (tabMoyenneAnnuelle[i].second - min) * sizeY / (max - min);
        
        listElem.push_back(LibGraph2::CPoint{ Point.m_ptTopLeft.m_fX + 2.0f,Point.m_ptTopLeft.m_fY + 2.0f });
        LibGraph2::GetLibGraph2()->drawEllipse(Point);
        LibGraph2::GetLibGraph2()->askForRefresh();
        Point.m_ptTopLeft.m_fX += sizeX / tabMoyenneAnnuelle.size();
    }
    for (size_t i = 0; i < listElem.size() - 1; i++) {
        LibGraph2::GetLibGraph2()->setPen(LibGraph2::MakeARGB(255, 0, 0, 0), 1.0f, LibGraph2::pen_DashStyles::Solid);
        LibGraph2::GetLibGraph2()->drawLine(listElem[i], listElem[i + 1]);
        LibGraph2::GetLibGraph2()->askForRefresh();
    }

    //Remplissage du graphe a point avec les moyennes sur 5 ans
    std::vector<LibGraph2::CPoint> listElem2;
    LibGraph2::CRectangle Point2(posPoint, sizePoint);
    LibGraph2::GetLibGraph2()->setSolidBrush(LibGraph2::MakeARGB(255, 255, 0, 0));
    LibGraph2::GetLibGraph2()->setPen(LibGraph2::MakeARGB(255, 255, 0, 0), 1.0f, LibGraph2::pen_DashStyles::Solid);
    std::vector<float> Moy5 = Moyenne5Ans(tabMoyenneAnnuelle);
    for (size_t i = 0; i < Moy5.size(); i++) {
        Point2.m_ptTopLeft.m_fY = Cadre.m_fY + sizeY - (Moy5[i] - min) * sizeY / (max - min);

        listElem2.push_back(LibGraph2::CPoint{ Point2.m_ptTopLeft.m_fX + 2.0f,Point2.m_ptTopLeft.m_fY + 2.0f });
        LibGraph2::GetLibGraph2()->drawEllipse(Point2);
        LibGraph2::GetLibGraph2()->askForRefresh();
        Point2.m_ptTopLeft.m_fX += sizeX / Moy5.size();
    }
    for (size_t i = 0; i < listElem2.size() - 1; i++) {
        LibGraph2::GetLibGraph2()->setPen(LibGraph2::MakeARGB(255, 255, 0, 0), 1.0f, LibGraph2::pen_DashStyles::Solid);
        LibGraph2::GetLibGraph2()->drawLine(listElem2[i], listElem2[i + 1]);
        LibGraph2::GetLibGraph2()->askForRefresh();
    }
}

std::pair<float, float> GraphPoint::GetMinMax(std::vector<std::pair<unsigned int, float>>& list)
{
    std::pair<float, float> minmax;
    float min = list[0].second;
    float max = list[0].second;
    for (auto& elem : list) {
        if (min > elem.second)min = elem.second;
        if (max < elem.second)max = elem.second;
    }
    minmax.first = min;
    minmax.second = max;
    return minmax;
}

std::vector<float> GraphPoint::Moyenne5Ans(std::vector<std::pair<unsigned int, float>> listTemp)
{
    std::vector<float> Moy5;

    for (size_t i = 2; i <= listTemp.size() - 7; i = i + 5) {
        Moy5.push_back((listTemp[i - 2].second + listTemp[i - 1].second + listTemp[i].second + listTemp[i + 1].second + listTemp[i + 2].second) / 5);
    }

    return Moy5;
}
