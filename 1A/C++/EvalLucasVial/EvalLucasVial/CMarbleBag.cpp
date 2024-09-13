#include "CMarbleBag.h"
#include <iostream>

CMarbleBag::CMarbleBag()
{
    for (size_t i = 0; i < 10; i++) {
        std::shared_ptr<CMarble> b = std::make_shared<CMarble>();
        AddMarble(b);
    }
}

size_t CMarbleBag::ValPrestige()
{
    size_t val = 0;
    for (auto pMarble : sac) {
        val += pMarble->GetPrestige();
    }
    return val;
}

std::shared_ptr<CMarble> CMarbleBag::RandomMarble()
{
    if(sac.size()==1)
        return sac[0];
    else {
        int s = static_cast<int>(sac.size());
        size_t nb;
        std::random_device rd;
        std::default_random_engine gen(rd());
        nb = std::uniform_int_distribution<>{ 0, s-1 }(gen);
        return sac[nb];
    }
}

void CMarbleBag::RemoveMarble(std::shared_ptr<CMarble> b)
{
    sac.erase(std::find(sac.begin(), sac.end(), b));
}
