#pragma once
#include <memory>
#include<random>

class CMarble {
	size_t Poids;
	size_t Prestige;

public:
	CMarble();
	bool operator< (std::shared_ptr<CMarble>);
	bool operator> (std::shared_ptr<CMarble>);
	bool operator<= (std::shared_ptr<CMarble>);
	bool operator>= (std::shared_ptr<CMarble>);
	bool operator== (std::shared_ptr<CMarble>);
	bool operator!= (std::shared_ptr<CMarble>);
	size_t GetPoids() { return Poids; };
	size_t GetPrestige() { return Prestige; };
};