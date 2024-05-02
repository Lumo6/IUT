#include "GraphRect.h"

void GraphRect::DrawGraph(unsigned int x, unsigned int y)
{

	//Création et dessin du tableau avec des couleurs différentes en fonction de la température
	auto data = GetInfos();
	unsigned int annees = data.back().first.first - data[0].first.first;
	LibGraph2::CPoint Pointdeb = LibGraph2::CPoint(40, 25);
	LibGraph2::CPoint Pointfin = LibGraph2::CPoint(675, 675);
	LibGraph2::CPoint Point = Pointdeb;
	LibGraph2::GetLibGraph2()->setFont("Calibri", 12.0f, LibGraph2::FontStyleRegular);
	LibGraph2::GetLibGraph2()->setPen(LibGraph2::MakeARGB(255, 0, 0, 0), 1.0f, LibGraph2::pen_DashStyles::Solid);
	LibGraph2::CSize size = LibGraph2::CSize((Pointfin.m_fX - Pointdeb.m_fX) / 12, (Pointfin.m_fY - Pointdeb.m_fY) / annees);
	while (annees != 0) {
		auto annee = GetAnnee(data.back().first.first - annees);
		for (size_t i = 0; i < 12; i++) {
			bool found = false;
			size_t ite = annee.size();
			for (int j = 0; j < annee.size(); j++)
			{
				if (annee[j].first == i + 1)
				{
					ite = j;
					found = true;
					break;
				}
			}
			if (found) {
				auto color = GetColorBytemp(annee[ite].second);

				LibGraph2::GetLibGraph2()->setSolidBrush(LibGraph2::MakeARGB(255, color[0], color[1], color[2]));
			}
			else {
				LibGraph2::GetLibGraph2()->setSolidBrush(LibGraph2::MakeARGB(255, 0, 0, 0));
			}


			LibGraph2::GetLibGraph2()->drawRectangle(LibGraph2::CRectangle{ Point,size });

			if ((data.back().first.first - annees) % 10 == 0) {
				LibGraph2::GetLibGraph2()->setSolidBrush(LibGraph2::MakeARGB(255, 0, 0, 0));
				LibGraph2::GetLibGraph2()->drawString(std::to_string(data.back().first.first - annees), LibGraph2::CPoint{ 0,Point.m_fY - size.m_fHeight * 2 });
			}
			Point = LibGraph2::CPoint(Point.m_fX + size.m_fWidth, Point.m_fY);
		}
		Point = LibGraph2::CPoint(Pointdeb.m_fX, Point.m_fY + size.m_fHeight);
		annees--;
	}
	LibGraph2::CPoint PointMois = LibGraph2::CPoint(Pointdeb.m_fX + size.m_fWidth / 5.0f, Pointfin.m_fY);
	LibGraph2::GetLibGraph2()->setSolidBrush(LibGraph2::MakeARGB(255, 0, 0, 0));
	for (auto& ele : mois) {
		LibGraph2::GetLibGraph2()->drawString(ele, PointMois);
		PointMois = LibGraph2::CPoint(PointMois.m_fX + size.m_fWidth, PointMois.m_fY);
	}

	//Création de la légende
	size = LibGraph2::CSize((Pointfin.m_fY - Pointdeb.m_fY) / 27, (Pointfin.m_fY - Pointdeb.m_fY) / 27);
	LibGraph2::CPoint PointColor = LibGraph2::CPoint(Pointfin.m_fX + size.m_fWidth / 2, Pointdeb.m_fY);
	float col = -9.0f;
	for (int i = 0; i < 8; i++) {
		auto color = GetColorBytemp(col);
		LibGraph2::GetLibGraph2()->setSolidBrush(LibGraph2::MakeARGB(255, color[0], color[1], color[2]));
		LibGraph2::GetLibGraph2()->drawRectangle(LibGraph2::CRectangle{ PointColor, size });
		LibGraph2::CPoint PointString = LibGraph2::CPoint(PointColor.m_fX + size.m_fWidth * 1.25f, PointColor.m_fY);
		LibGraph2::GetLibGraph2()->setSolidBrush(LibGraph2::MakeARGB(255, 0, 0, 0));
		switch (std::to_string(i)[0]) {
		case '0':
			LibGraph2::GetLibGraph2()->drawString("<-8,2", PointString);
			break;
		case '1':
			LibGraph2::GetLibGraph2()->drawString("-8,1 - 4,5", PointString);
			break;
		case '2':
			LibGraph2::GetLibGraph2()->drawString("-4,4 - -0,7", PointString);
			break;
		case '3':
			LibGraph2::GetLibGraph2()->drawString("-0,6 - 2,8", PointString);
			break;
		case '4':
			LibGraph2::GetLibGraph2()->drawString("2,9 - 6,6", PointString);
			break;
		case '5':
			LibGraph2::GetLibGraph2()->drawString("6,7 - 10,4", PointString);
			break;
		case '6':
			LibGraph2::GetLibGraph2()->drawString("10,5 - 14,1", PointString);
			break;
		case '7':
			LibGraph2::GetLibGraph2()->drawString(">14,2", PointString);
			break;
		default:
			break;
		}
		PointColor = LibGraph2::CPoint(PointColor.m_fX, PointColor.m_fY + size.m_fHeight * 2);
		col += 3.5f;
	}
	LibGraph2::CPoint PointString = LibGraph2::CPoint(PointColor.m_fX + size.m_fWidth * 1.25f, PointColor.m_fY);
	LibGraph2::GetLibGraph2()->setSolidBrush(LibGraph2::MakeARGB(255, 0, 0, 0));
	LibGraph2::GetLibGraph2()->drawRectangle(LibGraph2::CRectangle{ PointColor, size });
	LibGraph2::GetLibGraph2()->drawString("Pas de\ndonnees", PointString);
}

std::vector<int> GraphRect::GetColorBytemp(float temp)
{
	//Retourne la couleur en fonction de la température
	std::vector<int> color;
	if (temp < -8.2) {
		color = { 33,103,174 };
	}
	else if (-8.2 <= temp && -4.5 > temp) {
		color = { 69,147,195 };
	}
	else if (-4.5 <= temp && -0.7 > temp) {
		color = { 146,199,223 };
	}
	else if (-0.7 <= temp && 2.8 > temp) {
		color = { 210,230,241 };
	}
	else if (2.8 <= temp && 6.6 > temp) {
		color = { 255,220,200 };
	}
	else if (6.6 <= temp && 10.4 > temp) {
		color = { 245,167,131 };
	}
	else if (10.4 <= temp && 14.1 > temp) {
		color = { 215,95,79 };
	}
	else if (14.1 <= temp) {
		color = { 176,25,43 };
	}
	else {
		color = { 0,0,0 };
	}
	return color;
}