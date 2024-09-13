/*!\file
 * \brief Déclaration de la classe CSwarm
 * \author Benjamin ALBOUY-KISSI
 */
#include <set>
#include <memory>
#include "Butterfly.h"

class CSwarm {
	std::set<std::shared_ptr<CButterfly>> m_butterflies;
public:
	void AppendButterfly(std::shared_ptr<CButterfly> pap) { m_butterflies.insert(pap); };
	void RemoveButterfly(std::shared_ptr<CButterfly> pap) { m_butterflies.erase(pap); };
	void RemoveOutOfScreenDead();
	std::shared_ptr<CButterfly> GetFirst();
	std::shared_ptr<CButterfly> GetNext(std::shared_ptr<CButterfly>);
	//std::set<std::shared_ptr<CButterfly>>& GetPap() { return m_butterflies; };
};