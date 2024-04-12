/*!
 * \file  "Arc.h"
 *
 * \brief Declares the arc class.
 *
 *
 * \todo Déclarer dans ce fichier la classe CArc
 */
#pragma once
#include "forme.h"

class CArc : public CForme {
private:
	float m_startAngle = 45;
	float m_sweepAngle = 270;
public:
	void Afficher() const override;

	void SetStartAngle(float startAngle) { m_startAngle = startAngle; }
	float GetStartAngle() { return m_startAngle; }
	void SetSweepAngle(float sweepAngle) { m_sweepAngle = sweepAngle; }
};