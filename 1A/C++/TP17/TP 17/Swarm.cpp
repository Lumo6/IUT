#include "Swarm.h"
/*!\file
 * \brief Définition de la classe CNet
 * \author Benjamin ALBOUY-KISSI
 */

void CSwarm::RemoveOutOfScreenDead()
{
	for (auto pap : m_butterflies) {
		if (!pap->isAlive()) {
			RemoveButterfly(pap);
		}
	}
}

std::shared_ptr<CButterfly> CSwarm::GetFirst()
{
	if (m_butterflies.size() < 1) {
		return nullptr;
	}
	else {
		return *m_butterflies.begin();
	}
}

std::shared_ptr<CButterfly> CSwarm::GetNext(std::shared_ptr<CButterfly> pap) {

	auto iterator = m_butterflies.find(pap);
	if (m_butterflies.end() == iterator) return nullptr;
	iterator++;
	if (m_butterflies.end() == iterator) return nullptr;
	else return *iterator;
}
