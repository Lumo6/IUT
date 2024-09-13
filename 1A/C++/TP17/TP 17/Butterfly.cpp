#include "Butterfly.h"
#include <random>
/*!\file
 * \brief Définition de la classe CButterfly
 * \author Benjamin ALBOUY-KISSI
 */

const double pi = 3.14159265359; //!< C'est PI !

CButterfly::CButterfly(double width,double height):m_vSpeed{ 0,0 }, m_ptPos{ 0,0 },m_ptMax{width,height}
{
	std::random_device rd;
	std::default_random_engine gen(rd());
	unsigned int val = std::uniform_int_distribution<unsigned int>{ 10, 30 }(gen);
	m_nLifeTimeInSec = val;
	val = std::uniform_int_distribution<unsigned int>{ 100, 200 }(gen);
	m_nViewingDistance = val;
	val = std::uniform_int_distribution<>{ 0, (int)width}(gen);
	m_ptPos.setX(val);
	val = std::uniform_int_distribution<>{ 0, (int)height }(gen);
	m_ptPos.setY(val);
	m_timeBirth = std::chrono::high_resolution_clock::now();
	m_timeLastMove = std::chrono::high_resolution_clock::now();
}


bool CButterfly::isAlive()
{
	return (std::chrono::high_resolution_clock::now() - m_timeBirth) <= (std::chrono::seconds)m_nLifeTimeInSec;
}

void CButterfly::MoveAfraidOf(CPoint2D ptNet)	
{
	std::chrono::duration<double, std::milli> Tps = std::chrono::high_resolution_clock::now() - m_timeLastMove;
	
	if (!isAlive()) {
		m_ptPos += CPoint2D{ 0.0,1.0 } *Tps.count();
	}
	else {
		CVecteur2D NetToPap{ m_ptPos - ptNet };
		if (NetToPap.Norm() < (double)m_nViewingDistance) {
			m_vSpeed.setNorm(m_vSpeed.Norm() + Tps.count() / 10);
			m_vSpeed.setOrientation(NetToPap.Orientation());
		}
		else {
			m_vSpeed.setNorm(Tps.count() / 4);
			m_vSpeed.setOrientation(m_vSpeed.Orientation() + Tps.count() / 500);
		}
		m_ptPos += m_vSpeed;
		if(m_ptPos.X()<0) m_ptPos.setX(0);
		if (m_ptPos.X() > m_ptMax.X()) m_ptPos.setX(m_ptMax.X());
		if (m_ptPos.Y() < 0) m_ptPos.setY(0);
		if (m_ptPos.Y() > m_ptMax.Y()) m_ptPos.setY(m_ptMax.Y());
	}

	m_timeLastMove = std::chrono::high_resolution_clock::now();
}
