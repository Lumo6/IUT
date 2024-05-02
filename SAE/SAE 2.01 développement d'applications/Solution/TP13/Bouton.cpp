#include "Bouton.h"

void SButton::DrawButton()
{
    LibGraph2::GetLibGraph2()->setSolidBrush(LibGraph2::MakeARGB(255, 255, 255, 255));
    LibGraph2::GetLibGraph2()->drawRectangle(LibGraph2::CRectangle{ m_Pos,m_Size });
    LibGraph2::GetLibGraph2()->setSolidBrush(LibGraph2::MakeARGB(255, 0, 0, 0));
    LibGraph2::GetLibGraph2()->setFont("Calibri", 25.0f, LibGraph2::FontStyleRegular);
    LibGraph2::GetLibGraph2()->drawBitmap(m_image, m_Pos + LibGraph2::CPoint{ 1,1 }, LibGraph2::CPoint{ 0,0 }, 0.32f, 0);
}
