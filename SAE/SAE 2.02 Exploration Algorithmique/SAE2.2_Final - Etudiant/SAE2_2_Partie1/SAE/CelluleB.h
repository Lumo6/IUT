#pragma once
#include <memory>
struct CelluleB {
	int _info;
	std::shared_ptr<CelluleB> _pSuiv = nullptr;
	std::shared_ptr<CelluleB> _pPred = nullptr;

	CelluleB() { _info = 0; };
	CelluleB(int elem) { _info = elem; };
};
