#pragma once
#include "Donnee.h"

class Saisons : public Donnee {
private:
	std::vector<float> HiverTemp;
	std::vector<float> PrintempsTemp;
	std::vector<float> EteTemp;
	std::vector<float> AutomneTemp;
	std::vector<LibGraph2::CPoint> DrawCercles(LibGraph2::CSize&, float);

public:
	void TriDonnee();
	void DrawGraphs(unsigned int, unsigned int);
	float MaxDeltaTempSaison();
	void PointsOneSaison(std::vector<LibGraph2::CPoint>&, const std::vector<LibGraph2::CPoint>&, const std::vector<LibGraph2::CPoint>&, std::vector<float>&);
	void GetMinMax(std::pair<float, float>& ,std::vector<float>&);
};