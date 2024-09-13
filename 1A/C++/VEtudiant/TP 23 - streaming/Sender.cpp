/*!
 * \file  "Sender.cpp"
 *
 * \brief Définition de la classe CSender.
 *
 * \author Benjamin ALBOUY-KISSI
 * \date   29/03/2020
 *
 */
#include "Sender.h"
#include <algorithm>

CSender::CSender()
{
  auto itStartWord = m_strText.begin();
  auto itSpace = std::find(m_strText.begin(), m_strText.end(), ' ');
  while (itSpace != m_strText.end())
  {
    itSpace++;
    m_lstPackets.push_back(std::vector<char>(itStartWord, itSpace));
    itStartWord = itSpace;
    itSpace = std::find(itSpace, m_strText.end(), ' ');
  }

  if (itStartWord != m_strText.end())
  {
    m_lstPackets.push_back(std::vector<char>(itStartWord, m_strText.end()));
  }

  m_lstPackets.push_back(std::vector<char>{'\0'});
  m_itCurPacket = m_lstPackets.begin();
}

/*!\brief Simule l'envoie d'un paquet en streaming
 *
 * \param maxSize Taille maximal du paquet que l'on peut recevoir
 * \return Un vecteur de \c char constituant le paquet transmit
 *
 * \remark Si le mot à envoyer est plus grand que \p maxSize, alors un vecteur vide est retourné et le paquet est placé en attente.
 */
std::vector<char> CSender::SendNextPacket(size_t maxSize)
{
  if (m_itCurPacket != m_lstPackets.end() && maxSize >= m_itCurPacket->size())
  {
    auto itRet = m_itCurPacket;
    m_itCurPacket++;
    return *itRet;
  }
  return std::vector<char>();
}
