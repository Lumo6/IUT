#pragma once
#include <memory>
struct Cellule {
	int _info;
	std::shared_ptr<Cellule> _pSuiv=nullptr;

	Cellule() { _info = 0; };
	Cellule(int elem) { _info = elem; };
};
