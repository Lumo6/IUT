/*!\file
 * \brief Déclaration de la classe CNet
 * \author Benjamin ALBOUY-KISSI
 */
#include <set>
#include <memory>
#include "Butterfly.h"

class CNet {
	std::set<std::shared_ptr<CButterfly>> m_butterflies;
	void RemoveDead();
public:
	void AppendButterfly(std::shared_ptr<CButterfly> pap) { m_butterflies.insert(pap); };
	size_t Count() { return m_butterflies.size(); };
};