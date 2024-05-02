#pragma once
#include "Arbre.h"

#include <array>

struct CelluleStation
{
    int _ID; // numero identification station
    std::array<Arbre, 12> tab_arbres; // 1 arbre par mois
    std::shared_ptr<CelluleStation> _pSuiv;
    std::shared_ptr<CelluleStation> _pPred;



    CelluleStation(int ID = -1) : _ID{ ID }, _pSuiv{ nullptr }, _pPred{ nullptr } {}
};

