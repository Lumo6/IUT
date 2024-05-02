#pragma once
#include "Donnee.h"
class GraphRect :
    public Donnee
{
private:
    std::vector<std::string> mois = { "Jan.","Fev.","Mars","Avr.","Mai","Juin","Jui.","Aout","Sep.","Oct.","Nov.","Dec." };
public:

    GraphRect() :Donnee() {}
    void DrawGraph(unsigned int, unsigned int);
    std::vector<int> GetColorBytemp(float temp);
};
