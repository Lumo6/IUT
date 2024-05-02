#pragma once
#include <memory>
struct CelluleA {
	int _info;
	std::shared_ptr<CelluleA> _pFilsG = nullptr;
	std::shared_ptr<CelluleA> _pFilsD = nullptr;

	CelluleA() { _info = 0; };
	CelluleA(int elem) { _info = elem; };
};
