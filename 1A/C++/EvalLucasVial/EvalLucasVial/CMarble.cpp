#include "CMarble.h"

CMarble::CMarble()
{
    std::random_device rd;
    std::default_random_engine gen(rd());
    Prestige = std::uniform_int_distribution<unsigned int>{ 1, 10 }(gen);
    std::default_random_engine gen2(rd());
    Poids = std::uniform_int_distribution<unsigned int>{ 1, 10 }(gen2);
}

bool CMarble::operator<(std::shared_ptr<CMarble> b)
{
    return this->Poids<b->Poids;
}

bool CMarble::operator>(std::shared_ptr<CMarble> b)
{
    return this->Poids > b->Poids;
}

bool CMarble::operator<=(std::shared_ptr<CMarble> b)
{
    return this->Poids <= b->Poids;
}

bool CMarble::operator>=(std::shared_ptr<CMarble> b)
{
    return this->Poids >= b->Poids;
}

bool CMarble::operator==(std::shared_ptr<CMarble> b)
{
    return this->Poids == b->Poids;
}

bool CMarble::operator!=(std::shared_ptr<CMarble> b)
{
    return this->Poids != b->Poids;
}
