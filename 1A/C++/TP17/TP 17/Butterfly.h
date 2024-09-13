#pragma once
/*!\file
 * \brief Déclaration de la classe CButterfly
 * \author Benjamin ALBOUY-KISSI
 */


#include "vecteur2D.h"
#include "vecteur2D.h"
#include <chrono>
class CButterfly {
	unsigned int m_nLifeTimeInSec;
	unsigned int m_nViewingDistance;
	CPoint2D m_ptPos;
	std::chrono::high_resolution_clock::time_point m_timeBirth;
	std::chrono::high_resolution_clock::time_point m_timeLastMove;
	CVecteur2D m_vSpeed;
	CPoint2D m_ptMax;
public:
	CButterfly(double, double);
	CPoint2D getPos()const {return m_ptPos;}
	CVecteur2D getSpeed()const { return m_vSpeed; }
	bool isAlive();
	void MoveAfraidOf(CPoint2D);
};