#pragma once
#include "Donnee.h"
class SButton
{
private:
    LibGraph2::CPoint m_Pos;
    LibGraph2::CSize m_Size;
    std::string m_Nom;
    std::string m_image;
public:
    SButton(LibGraph2::CPoint Pos, LibGraph2::CSize Size, std::string Nom = "", std::string image = "") :m_Pos(Pos), m_Size(Size), m_Nom(Nom), m_image(image) {}
    void DrawButton();
    LibGraph2::CPoint GetPos() { return m_Pos; };
    LibGraph2::CSize GetSize() { return m_Size; };
    std::string GetString() { return m_Nom; };
};
