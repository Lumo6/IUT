#pragma once
#include <set>
#include "CMarble.h"
#include <vector>

class CMarbleBag {
	std::vector<std::shared_ptr<CMarble>> sac;

public:
	CMarbleBag();
	size_t ValPrestige();
	size_t NbMarble() { return sac.size(); };
	void AddMarble(std::shared_ptr<CMarble> b) { sac.push_back(b); };
	void RemoveMarble(std::shared_ptr<CMarble>);
	std::shared_ptr<CMarble> RandomMarble();
	std::vector<std::shared_ptr<CMarble>> GetSac() { return sac; };
};