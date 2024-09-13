/*!\file
 * \brief Définition de la classe CNet
 * \author Benjamin ALBOUY-KISSI
 */
#include "Net.h"

void CNet::RemoveDead()
{
	for (auto pap : m_butterflies) {
		if (!pap->isAlive()) {
			m_butterflies.erase(pap);
		}
	}
}

