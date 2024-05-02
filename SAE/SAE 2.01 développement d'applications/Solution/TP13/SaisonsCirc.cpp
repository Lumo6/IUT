#include "SaisonsCirc.h"


void Saisons::TriDonnee()
{
	std::vector<std::pair<std::pair<unsigned int, unsigned int>, float>> Infos = GetInfos();
	
	//Tri des données en saisons
	for (auto& pinfos : Infos) {
		if (pinfos.first.second <= 3) {
			HiverTemp.push_back(pinfos.second);
		}
		else if (pinfos.first.second <= 6) {
			PrintempsTemp.push_back(pinfos.second);
		}
		else if (pinfos.first.second <= 9) {
			EteTemp.push_back(pinfos.second);
		}
		else {
			AutomneTemp.push_back(pinfos.second);
		}
	}
}

std::vector<LibGraph2::CPoint> Saisons::DrawCercles(LibGraph2::CSize& taillecercle, float size)
{
	std::vector< LibGraph2::CPoint> tab;
	
	//Création et dessin des cercles des graphes
	LibGraph2::CPoint cerclehiver = LibGraph2::CPoint{ 100,50 };
	LibGraph2::CPoint cercleprintemps = LibGraph2::CPoint{ 450,50 };
	LibGraph2::CPoint cercleete = LibGraph2::CPoint{ 100,400 };
	LibGraph2::CPoint cercleautomne = LibGraph2::CPoint{ 450,400 };
	tab.push_back(cerclehiver); tab.push_back(cercleprintemps); tab.push_back(cercleete); tab.push_back(cercleautomne);
	LibGraph2::GetLibGraph2()->setSolidBrush(LibGraph2::MakeARGB(0, 0, 255, 0));
	LibGraph2::GetLibGraph2()->setPen(LibGraph2::MakeARGB(255, 0, 0, 255), 5.0f, LibGraph2::pen_DashStyles::Solid);
	LibGraph2::GetLibGraph2()->drawEllipse(LibGraph2::CRectangle{ cerclehiver,taillecercle });
	LibGraph2::GetLibGraph2()->setPen(LibGraph2::MakeARGB(255, 0, 255, 0), 5.0f, LibGraph2::pen_DashStyles::Solid);
	LibGraph2::GetLibGraph2()->drawEllipse(LibGraph2::CRectangle{ cercleprintemps,taillecercle });
	LibGraph2::GetLibGraph2()->setPen(LibGraph2::MakeARGB(255, 255, 255, 0), 5.0f, LibGraph2::pen_DashStyles::Solid);
	LibGraph2::GetLibGraph2()->drawEllipse(LibGraph2::CRectangle{ cercleete,taillecercle });
	LibGraph2::GetLibGraph2()->setPen(LibGraph2::MakeARGB(255, 255, 0, 0), 5.0f, LibGraph2::pen_DashStyles::Solid);
	LibGraph2::GetLibGraph2()->drawEllipse(LibGraph2::CRectangle{ cercleautomne,taillecercle });
	LibGraph2::GetLibGraph2()->setSolidBrush(LibGraph2::MakeARGB(255, 0, 0, 0));
	LibGraph2::GetLibGraph2()->setFont("Calibri", size, LibGraph2::FontStyleRegular);
	LibGraph2::CPoint stringH = LibGraph2::CPoint{ (cerclehiver.m_fX + taillecercle.m_fWidth / 2.0f) - (size / 1.5f),cerclehiver.m_fY + taillecercle.m_fHeight / 2.0f - (size / 1.5f) - (size / 10.0f) - 2.0f };
	LibGraph2::CPoint stringP = LibGraph2::CPoint{ (cercleprintemps.m_fX + taillecercle.m_fWidth / 2.0f) - (size / 1.5f) + 8.0f ,cercleprintemps.m_fY + taillecercle.m_fHeight / 2.0f - (size / 1.5f) - (size / 10.0f) - 2.0f };
	LibGraph2::CPoint stringE = LibGraph2::CPoint{ cercleete.m_fX + taillecercle.m_fWidth / 2.0f - (size / 1.5f) + 3.0f,cercleete.m_fY + taillecercle.m_fHeight / 2.0f - (size / 1.5f) - (size / 10.0f) - 2.0f };
	LibGraph2::CPoint stringT = LibGraph2::CPoint{ cercleautomne.m_fX + taillecercle.m_fWidth / 2.0f - (size / 1.5f) + 3.0f ,cercleautomne.m_fY + taillecercle.m_fHeight / 2.0f - (size / 1.5f) - (size / 10.0f) - 2.0f };
	LibGraph2::GetLibGraph2()->drawString("H", stringH);
	LibGraph2::GetLibGraph2()->drawString("P", stringP);
	LibGraph2::GetLibGraph2()->drawString("E", stringE);
	LibGraph2::GetLibGraph2()->drawString("A", stringT);
	return tab;
}

void Saisons::DrawGraphs(unsigned int x, unsigned int y)
{
	LibGraph2::CSize taillecercle = LibGraph2::CSize{ 200,200 };
	float size = 40.0f;
	auto tabcercles = DrawCercles(taillecercle, size);
	LibGraph2::GetLibGraph2()->setPen(LibGraph2::MakeARGB(255, 255, 0, 0), 1.0f, LibGraph2::pen_DashStyles::Solid);
	LibGraph2::GetLibGraph2()->setSolidBrush(LibGraph2::MakeARGB(255, 0, 0, 0));
	LibGraph2::GetLibGraph2()->setFont("Calibri", 5.0f, LibGraph2::FontStyleRegular);


	//Création et calcul des positions des points min et max de chaque cercle pour chaque mois
	std::pair<float, float> MinMax;
	GetMinMax(MinMax, HiverTemp);
	float truc = MaxDeltaTempSaison();
	float Ratio = abs(MinMax.second-MinMax.first) / MaxDeltaTempSaison();
	LibGraph2::CPoint stringA = LibGraph2::CPoint{ tabcercles[0].m_fX + taillecercle.m_fWidth / 2,tabcercles[0].m_fY+taillecercle.m_fHeight / 2 - 32.0f };
	LibGraph2::CPoint stringB = LibGraph2::CPoint{ tabcercles[0].m_fX + taillecercle.m_fWidth / 2.0f - 20.0f,tabcercles[0].m_fY  + taillecercle.m_fHeight / 2.0f + 20.0f};
	LibGraph2::CPoint stringC = LibGraph2::CPoint{ tabcercles[0].m_fX + taillecercle.m_fWidth / 2.0f + 20.0f,tabcercles[0].m_fY  + taillecercle.m_fHeight / 2.0f + 20.0f};
	LibGraph2::CPoint stringD = LibGraph2::CPoint{ tabcercles[0].m_fX + (taillecercle.m_fWidth / 2)*Ratio ,tabcercles[0].m_fY +( 5.0f)* Ratio };
	LibGraph2::CPoint stringE = LibGraph2::CPoint{ tabcercles[0].m_fX + (35.0f)* Ratio,tabcercles[0].m_fY +( taillecercle.m_fHeight - 35.0f)* Ratio };
	LibGraph2::CPoint stringF = LibGraph2::CPoint{ tabcercles[0].m_fX + (taillecercle.m_fWidth - 35.0f)* Ratio,tabcercles[0].m_fY + (taillecercle.m_fHeight - 35.0f)* Ratio };
	
	GetMinMax(MinMax, PrintempsTemp);
	Ratio = abs(MinMax.second - MinMax.first) / MaxDeltaTempSaison();
	LibGraph2::CPoint stringG = LibGraph2::CPoint{ tabcercles[1].m_fX + taillecercle.m_fWidth / 2,tabcercles[1].m_fY + taillecercle.m_fHeight / 2 - 32.0f };
	LibGraph2::CPoint stringH = LibGraph2::CPoint{ tabcercles[1].m_fX + taillecercle.m_fWidth / 2.0f - 20.0f,tabcercles[1].m_fY + taillecercle.m_fHeight / 2.0f + 20.0f };
	LibGraph2::CPoint stringI = LibGraph2::CPoint{ tabcercles[1].m_fX + taillecercle.m_fWidth / 2.0f + 20.0f,tabcercles[1].m_fY + taillecercle.m_fHeight / 2.0f + 20.0f };
	LibGraph2::CPoint stringJ = LibGraph2::CPoint{ tabcercles[1].m_fX + (taillecercle.m_fWidth / 2)* Ratio ,tabcercles[1].m_fY +( 5.0f)* Ratio };
	LibGraph2::CPoint stringK = LibGraph2::CPoint{ tabcercles[1].m_fX + (35.0f)* Ratio,tabcercles[1].m_fY + (taillecercle.m_fHeight - 35.0f)* Ratio };
	LibGraph2::CPoint stringL = LibGraph2::CPoint{ tabcercles[1].m_fX +( taillecercle.m_fWidth - 35.0f)* Ratio,tabcercles[1].m_fY +( taillecercle.m_fHeight - 35.0f) * Ratio };

	GetMinMax(MinMax, EteTemp);
	Ratio = abs(MinMax.second - MinMax.first) / MaxDeltaTempSaison();
	LibGraph2::CPoint stringM = LibGraph2::CPoint{ tabcercles[2].m_fX + taillecercle.m_fWidth / 2,tabcercles[2].m_fY  + taillecercle.m_fHeight / 2 - 32.0f};
	LibGraph2::CPoint stringN = LibGraph2::CPoint{ tabcercles[2].m_fX + taillecercle.m_fWidth / 2.0f - 20.0f,tabcercles[2].m_fY + taillecercle.m_fHeight / 2.0f + 20.0f };
	LibGraph2::CPoint stringO = LibGraph2::CPoint{ tabcercles[2].m_fX + taillecercle.m_fWidth / 2.0f + 20.0f,tabcercles[2].m_fY + taillecercle.m_fHeight / 2.0f + 20.0f };
	LibGraph2::CPoint stringP = LibGraph2::CPoint{ tabcercles[2].m_fX + (taillecercle.m_fWidth / 2) * Ratio,tabcercles[2].m_fY +( 5.0f)* Ratio };
	LibGraph2::CPoint stringQ = LibGraph2::CPoint{ tabcercles[2].m_fX + (35.0f)* Ratio,tabcercles[2].m_fY +( taillecercle.m_fHeight - 35.0f)* Ratio };
	LibGraph2::CPoint stringR = LibGraph2::CPoint{ tabcercles[2].m_fX + (taillecercle.m_fWidth - 35.0f) * Ratio,tabcercles[2].m_fY + (taillecercle.m_fHeight - 35.0f) * Ratio };

	GetMinMax(MinMax, AutomneTemp);
	Ratio = abs(MinMax.second - MinMax.first) / MaxDeltaTempSaison();
		LibGraph2::CPoint stringS = LibGraph2::CPoint{ tabcercles[3].m_fX + taillecercle.m_fWidth / 2,tabcercles[3].m_fY + taillecercle.m_fHeight / 2 - 32.0f };
	LibGraph2::CPoint stringT = LibGraph2::CPoint{ tabcercles[3].m_fX + taillecercle.m_fWidth / 2.0f - 20.0f,tabcercles[3].m_fY + taillecercle.m_fHeight / 2.0f + 20.0f };
	LibGraph2::CPoint stringU = LibGraph2::CPoint{ tabcercles[3].m_fX + taillecercle.m_fWidth / 2.0f + 20.0f,tabcercles[3].m_fY + taillecercle.m_fHeight / 2.0f + 20.0f };
	LibGraph2::CPoint stringV = LibGraph2::CPoint{ tabcercles[3].m_fX + (taillecercle.m_fWidth / 2) * Ratio,tabcercles[3].m_fY +( 5.0f)* Ratio };
	LibGraph2::CPoint stringW = LibGraph2::CPoint{ tabcercles[3].m_fX + (35.0f)* Ratio,tabcercles[3].m_fY +( taillecercle.m_fHeight - 35.0f)* Ratio };
	LibGraph2::CPoint stringX = LibGraph2::CPoint{ tabcercles[3].m_fX + (taillecercle.m_fWidth - 35.0f)* Ratio,tabcercles[3].m_fY +( taillecercle.m_fHeight - 35.0f)* Ratio };
	

	const std::vector<LibGraph2::CPoint> PointsHMin = { stringA,stringB,stringC };
	const std::vector<LibGraph2::CPoint> PointsHMax = { stringD,stringE,stringF };
	const std::vector<LibGraph2::CPoint> PointsPMin = { stringG,stringH,stringI };
	const std::vector<LibGraph2::CPoint> PointsPMax = { stringJ,stringK,stringL };
	const std::vector<LibGraph2::CPoint> PointsEMin = { stringM,stringN,stringO };
	const std::vector<LibGraph2::CPoint> PointsEMax = { stringP,stringQ,stringR };
	const std::vector<LibGraph2::CPoint> PointsAMin = { stringS,stringT,stringU };
	const std::vector<LibGraph2::CPoint> PointsAMax = { stringV,stringW,stringX };
	

	std::vector<LibGraph2::CPoint> ValH;
	std::vector<LibGraph2::CPoint> ValP;
	std::vector<LibGraph2::CPoint> ValE;
	std::vector<LibGraph2::CPoint> ValA;



	PointsOneSaison(ValH,PointsHMin,PointsHMax,HiverTemp);
	PointsOneSaison(ValP, PointsPMin, PointsPMax, PrintempsTemp);
	PointsOneSaison(ValE, PointsEMin, PointsEMax, EteTemp);
	PointsOneSaison(ValA, PointsAMin, PointsAMax, AutomneTemp);

	//Creation des boutons et de leurs intéractions.
	SButton Buthiver( LibGraph2::CPoint{ 100,50 }, LibGraph2::CSize{ 200,200 },"");
	SButton Butprintemps( LibGraph2::CPoint{ 450,50 }, LibGraph2::CSize{ 200,200 },"");
	SButton Butete(  LibGraph2::CPoint{ 100,400 }, LibGraph2::CSize{ 200,200 },"");
	SButton Butautomne( LibGraph2::CPoint{ 450,400 }, LibGraph2::CSize{ 200,200 },"");
	LibGraph2::GetLibGraph2()->setPen(LibGraph2::MakeARGB(255, 255, 0, 0), 1.0f, LibGraph2::pen_DashStyles::Solid);
	SButton ButTout(LibGraph2::CPoint{ 275,275 }, LibGraph2::CSize{ 200,40 }, "Tout Afficher");
	ButTout.DrawButton();
	LibGraph2::GetLibGraph2()->drawString(ButTout.GetString(), LibGraph2::CPoint{ButTout.GetPos().m_fX + 5.0f,ButTout.GetPos().m_fY});

	if (x > ButTout.GetPos().m_fX && x<(ButTout.GetPos().m_fX + ButTout.GetSize().m_fWidth) && y>ButTout.GetPos().m_fY && y < (ButTout.GetPos().m_fY + ButTout.GetSize().m_fHeight)) {
		for (size_t i = 1; i < ValH.size() - 1; i++) {
			LibGraph2::GetLibGraph2()->setPen(LibGraph2::MakeARGB(255, 255 - i / 2, 0, i / 2), 1.0f, LibGraph2::pen_DashStyles::Solid);
			LibGraph2::GetLibGraph2()->drawLine(ValH[i], ValH[i + 1]);
			LibGraph2::GetLibGraph2()->askForRefresh();
		}

		for (size_t i = 1; i < ValP.size() - 1; i++) {
			LibGraph2::GetLibGraph2()->setPen(LibGraph2::MakeARGB(255, 255 - i / 2, 0, i / 2), 1.0f, LibGraph2::pen_DashStyles::Solid);
			LibGraph2::GetLibGraph2()->drawLine(ValP[i], ValP[i + 1]);
			LibGraph2::GetLibGraph2()->askForRefresh();
		}

		for (size_t i = 1; i < ValE.size() - 1; i++) {
			LibGraph2::GetLibGraph2()->setPen(LibGraph2::MakeARGB(255, 255 - i / 2, 0, i / 2), 1.0f, LibGraph2::pen_DashStyles::Solid);
			LibGraph2::GetLibGraph2()->drawLine(ValE[i], ValE[i + 1]);
			LibGraph2::GetLibGraph2()->askForRefresh();
		}

		for (size_t i = 1; i < ValA.size() - 1; i++) {
			LibGraph2::GetLibGraph2()->setPen(LibGraph2::MakeARGB(255, 255 - i / 2, 0, i / 2), 1.0f, LibGraph2::pen_DashStyles::Solid);
			LibGraph2::GetLibGraph2()->drawLine(ValA[i], ValA[i + 1]);
			LibGraph2::GetLibGraph2()->askForRefresh();
		}
	}

	if (x > Buthiver.GetPos().m_fX && x<(Buthiver.GetPos().m_fX + Buthiver.GetSize().m_fWidth) && y>Buthiver.GetPos().m_fY && y < (Buthiver.GetPos().m_fY + Buthiver.GetSize().m_fHeight)) {
		for (size_t i = 1; i < ValH.size() - 1; i++) {
			LibGraph2::GetLibGraph2()->setPen(LibGraph2::MakeARGB(255, 255 - i / 2, 0, i / 2), 1.0f, LibGraph2::pen_DashStyles::Solid);
			LibGraph2::GetLibGraph2()->drawLine(ValH[i], ValH[i + 1]);
			LibGraph2::GetLibGraph2()->askForRefresh();
		}
	}
	
	if (x > Butprintemps.GetPos().m_fX && x<(Butprintemps.GetPos().m_fX + Butprintemps.GetSize().m_fWidth) && y>Butprintemps.GetPos().m_fY && y < (Butprintemps.GetPos().m_fY + Butprintemps.GetSize().m_fHeight)) {
		for (size_t i = 1; i < ValP.size() - 1; i++) {
			LibGraph2::GetLibGraph2()->setPen(LibGraph2::MakeARGB(255, 255 - i / 2, 0, i / 2), 1.0f, LibGraph2::pen_DashStyles::Solid);
			LibGraph2::GetLibGraph2()->drawLine(ValP[i], ValP[i + 1]);
			LibGraph2::GetLibGraph2()->askForRefresh();
		}
	}
	
	if (x > Butete.GetPos().m_fX && x<(Butete.GetPos().m_fX + Butete.GetSize().m_fWidth) && y>Butete.GetPos().m_fY && y < (Butete.GetPos().m_fY + Butete.GetSize().m_fHeight)) {
		for (size_t i = 1; i < ValE.size() - 1; i++) {
			LibGraph2::GetLibGraph2()->setPen(LibGraph2::MakeARGB(255, 255 - i / 2, 0, i / 2), 1.0f, LibGraph2::pen_DashStyles::Solid);
			LibGraph2::GetLibGraph2()->drawLine(ValE[i], ValE[i + 1]);
			LibGraph2::GetLibGraph2()->askForRefresh();
		}
	}
	
	if (x > Butautomne.GetPos().m_fX && x<(Butautomne.GetPos().m_fX + Butautomne.GetSize().m_fWidth) && y>Butautomne.GetPos().m_fY && y < (Butautomne.GetPos().m_fY + Butautomne.GetSize().m_fHeight)) {
		for (size_t i = 1; i < ValA.size() - 1; i++) {
			LibGraph2::GetLibGraph2()->setPen(LibGraph2::MakeARGB(255, 255 - i / 2, 0, i / 2), 1.0f, LibGraph2::pen_DashStyles::Solid);
			LibGraph2::GetLibGraph2()->drawLine(ValA[i], ValA[i + 1]);
			LibGraph2::GetLibGraph2()->askForRefresh();
		}
	}


	//Affichage des mois dans la graphe
	Graphcercle:LibGraph2::GetLibGraph2()->setFont("Calibri", 10.0f, LibGraph2::FontStyleRegular);
	LibGraph2::GetLibGraph2()->drawString("Janvier", LibGraph2::CPoint{ stringD.m_fX-15.0f,stringD.m_fY - 25.0f });
	LibGraph2::GetLibGraph2()->drawString("Fevrier", LibGraph2::CPoint{ stringE.m_fX-25.0f,stringE.m_fY+25.0f });
	LibGraph2::GetLibGraph2()->drawString("Mars", LibGraph2::CPoint{ stringF.m_fX + 15.0f,stringF.m_fY + 25.0f });
	LibGraph2::GetLibGraph2()->drawString("Avril", LibGraph2::CPoint{ stringJ.m_fX - 15.0f,stringJ.m_fY - 25.0f });
	LibGraph2::GetLibGraph2()->drawString("Mai", LibGraph2::CPoint{ stringK.m_fX - 25.0f,stringK.m_fY + 25.0f });
	LibGraph2::GetLibGraph2()->drawString("Juin", LibGraph2::CPoint{ stringL.m_fX + 15.0f,stringL.m_fY + 25.0f });
	LibGraph2::GetLibGraph2()->drawString("Juillet", LibGraph2::CPoint{ stringP.m_fX - 15.0f,stringP.m_fY - 25.0f });
	LibGraph2::GetLibGraph2()->drawString("Aout", LibGraph2::CPoint{ stringQ.m_fX - 35.0f,stringQ.m_fY + 35.0f });
	LibGraph2::GetLibGraph2()->drawString("Septembre", LibGraph2::CPoint{ stringR.m_fX + 25.0f,stringR.m_fY + 35.0f });
	LibGraph2::GetLibGraph2()->drawString("Octobre", LibGraph2::CPoint{ stringV.m_fX - 15.0f,stringV.m_fY - 25.0f });
	LibGraph2::GetLibGraph2()->drawString("Novembre", LibGraph2::CPoint{ stringW.m_fX - 35.0f,stringW.m_fY + 35.0f });
	LibGraph2::GetLibGraph2()->drawString("Decembre", LibGraph2::CPoint{ stringX.m_fX + 25.0f,stringX.m_fY + 35.0f });
}

void Saisons::PointsOneSaison(std::vector<LibGraph2::CPoint>& list,const std::vector<LibGraph2::CPoint>& listPMin,const std::vector<LibGraph2::CPoint>& listPMax, std::vector<float>& ValTemp)
{
	size_t control = 0;
	std::pair<float, float> MinMax;
	GetMinMax(MinMax, ValTemp);

	//Calculde la position de chaques points en fonction de sa température et des valeurs min et max pouvant etre atteintes
	for (auto& pTemp : ValTemp) {
		if (control == 0) {
			list.push_back(listPMin[0] + (LibGraph2::CPoint((listPMax[0].m_fX - listPMin[0].m_fX) * (abs(pTemp - MinMax.first) / abs(MinMax.second- MinMax.first)), (listPMax[0].m_fY - listPMin[0].m_fY) * (abs(pTemp - MinMax.first) / abs(MinMax.second - MinMax.first)))));
			control++;
		}
		else if (control == 1) {
			list.push_back(listPMin[1] + (LibGraph2::CPoint((listPMax[1].m_fX - listPMin[1].m_fX) * (abs(pTemp - MinMax.first) / abs(MinMax.second - MinMax.first)), (listPMax[1].m_fY - listPMin[1].m_fY) * (abs(pTemp - MinMax.first) / abs(MinMax.second - MinMax.first)))));
			control++;
		}
		else if (control == 2) {
			list.push_back(listPMin[2] + (LibGraph2::CPoint((listPMax[2].m_fX - listPMin[2].m_fX) * (abs(pTemp - MinMax.first) / abs(MinMax.second - MinMax.first)), (listPMax[2].m_fY - listPMin[2].m_fY) * (abs(pTemp - MinMax.first) / abs(MinMax.second - MinMax.first)))));
			control = 0;
		}
	}
}

void Saisons::GetMinMax(std::pair<float, float>& Pair,std::vector<float>& valTemp) {
	Pair.first = valTemp[0];
	Pair.second = valTemp[0];
	for (auto temp : valTemp) {
		if (Pair.first > temp)Pair.first = temp;
		if (Pair.second < temp)Pair.second = temp;
	}
}

float Saisons::MaxDeltaTempSaison()
{
	float Min = HiverTemp[0],Max = HiverTemp[0];
	float Delta = 0;
	for (auto& pDate : HiverTemp) {
		if (Max < pDate)Max = pDate;
		if (Min > pDate)Min = pDate;
	}
	Delta = abs(Max - Min);
	Min = PrintempsTemp[0], Max = PrintempsTemp[0];
	for (auto& pDate : PrintempsTemp) {
		if (Max < pDate)Max = pDate;
		if (Min > pDate)Min = pDate;
	}
	if (Delta < (Max - Min))Delta = abs(Max - Min);
	Min = EteTemp[0], Max = EteTemp[0];
	for (auto& pDate : EteTemp) {
		if (Max < pDate)Max = pDate;
		if (Min > pDate)Min = pDate;
	}
	if (Delta < (Max - Min))Delta = abs(Max - Min);
	Min = AutomneTemp[0], Max = AutomneTemp[0];
	for (auto& pDate : AutomneTemp) {
		if (Max < pDate)Max = pDate;
		if (Min > pDate)Min = pDate;
	}
	if (Delta < (Max - Min))Delta = abs(Max - Min);
	return Delta;
}