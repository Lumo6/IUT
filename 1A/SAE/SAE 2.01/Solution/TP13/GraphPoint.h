#pragma once
#include "Donnee.h"

class GraphPoint : public Donnee {
private:
public:
	void GraphPointMoyenne5Ans(unsigned int,unsigned int);
	std::pair<float, float> GetMinMax(std::vector<std::pair<unsigned int, float>>&);
	std::vector<float> Moyenne5Ans(std::vector<std::pair<unsigned int, float>>);
};