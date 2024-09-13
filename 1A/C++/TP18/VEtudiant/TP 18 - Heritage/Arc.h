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
	float m_angDebut = 45;
	float m_angBal = 270;
public:
	void Afficher() const;
	void SetAngBal(float);
	float GetAngDeb() { return m_angDebut; };
	void SetAngDeb(float n) { m_angDebut = n; };
};