#include "CircularBuffer.h"


///
///Crée un buffer circulaire en spécifiant sa taille
///
///\param size Taille du buffer
///
///\remark La taille du buffer doit être une puissance de 2 afin d'optimiser le cycle du buffer.
///Dans le cas contraire, une exception CCircularBufferError de code CCircularBufferError::ErrorCodes::SizeIsNotPowerOf2 est lancée.
///
CCircularBuffer::CCircularBuffer(size_t size)
  : m_nSizeBitmask(size != 0 ? size - 1 : 0)
{
  if (size == 0)
    return;

  //TODO : Modifiez le constructeur de la classe de façon à lancer une exception si la taille des données n'est pas une puissance de 2.
  //
  //NB : L'exception doit être de type CCircularBufferError et de code CCircularBufferError::ErrorCodes::SizeIsNotPowerOf2.
  //NB : le code suivant permet de détecter si size est une puissance de 2 :
  //  if ((size & (size - 1)) == 0)
  //  {
  //    //C'est une puissance de 2 :o)
  //  }
  //  else
  //  {
  //    //Ce n'est pas une puissance de 2 :'(
  //  }

  m_data.resize(size, 0);
}

size_t CCircularBuffer::freeSpace() const
{
  return m_data.size() - usedSpace();
}

size_t CCircularBuffer::usedSpace() const
{
  if (m_bEmpty) return 0;
  return ((m_writePos - m_readPos - !m_bEmpty) & m_nSizeBitmask) + 1;
}

/// \brief Lit et consomme des données dans le buffer
///
///Cette fonction retourne les données stockées dans le buffer en les linéarisant.
///En interne du buffer circulaire, les données lues sont libérées de façon à pouvoir stocker de nouvelles données.
///
///\param [in,out] data Buffer utilisé pour stocker les données lues.
///En entrée, la taille de \p data est utilisée pour connaitre le nombre max de données à lire.
///En sortie, les données lues sont stocké au début du tableau \p data.
///Aucune réallocation n'a lieu lors de cet appel.
///
///\return Le nombre de données effectivement lues. Si cette valeur est inférieure à la taille de \p data, alors seules les premières valeurs de \p data sont valides.
///
size_t CCircularBuffer::read(std::vector<unsigned char>& data)
{
  const size_t spaceToRead = std::min(data.size(), usedSpace());

  size_t usedSpaceBeforeEndOfTheWorld = m_data.size() - m_readPos;
  if (spaceToRead <= usedSpaceBeforeEndOfTheWorld)
  {
    std::memcpy(data.data(), m_data.data() + m_readPos, spaceToRead * sizeof(unsigned char));
#ifdef _DEBUG
    //"Erase" just read data
    std::memset(m_data.data() + m_readPos, 0, spaceToRead * sizeof(unsigned char));
#endif
  }
  else
  {
    std::memcpy(data.data(), m_data.data() + m_readPos, usedSpaceBeforeEndOfTheWorld * sizeof(unsigned char));
    std::memcpy(data.data() + usedSpaceBeforeEndOfTheWorld, m_data.data(), (spaceToRead - usedSpaceBeforeEndOfTheWorld) * sizeof(unsigned char));
#ifdef _DEBUG
    //"Erase" just read data
    std::memset(m_data.data() + m_readPos, 0, usedSpaceBeforeEndOfTheWorld * sizeof(unsigned char));
    std::memset(m_data.data(), 0, (spaceToRead - usedSpaceBeforeEndOfTheWorld) * sizeof(unsigned char));
#endif
  }
  m_readPos = (m_readPos + spaceToRead) & m_nSizeBitmask;
  m_bEmpty = m_readPos == m_writePos;

  return spaceToRead;
}

/// \brief Ecrit des données dans le buffer
///
///Cette fonction écrit des données dans le buffer.
///
///\param [in] data Buffer des données à écrire.
///Dans le cas où l'espace disponible dans le buffer n'est pas suffisant pour stocker les données,
///une exception CCircularBufferError de code CCircularBufferError::ErrorCodes::NotEnoughFreeSpace est lancée.
///
void CCircularBuffer::write(const std::vector<unsigned char>& data)
{
  //TODO : Modifiez la méthode CCircularBuffer::write de façon à lancer une exception si la taille de data est supérieure à l'espace libre dans le buffer circulaire.
  //       L'exception doit être un objet CCircularBufferError de code d'erreur CCircularBufferError::ErrorCodes::NotEnoughFreeSpace
  //NB : L'espace libre dans le buffer circulaire est retourné par la fonction membre freeSpace().
  if (data.size() == 0)
    return;

  size_t freeSpaceBeforeEndOfTheWorld = m_data.size() - m_writePos;
  if (freeSpaceBeforeEndOfTheWorld < data.size())
  {
    std::memcpy(m_data.data() + m_writePos, data.data(), freeSpaceBeforeEndOfTheWorld * sizeof(unsigned char));
    std::memcpy(m_data.data(), data.data() + freeSpaceBeforeEndOfTheWorld, (data.size() - freeSpaceBeforeEndOfTheWorld) * sizeof(unsigned char));
  }
  else
    std::memcpy(m_data.data() + m_writePos, data.data(), data.size() * sizeof(unsigned char));
  m_writePos = (m_writePos + data.size()) & m_nSizeBitmask;
  m_bEmpty = false;
}

/// \brief Déroule le buffer circulaire dans un buffer linéaire.
///
///Déroule les données utiles du buffer circulaire dans un buffer linéaire.
///Les données ne sont pas consommées, ce qui fait que l'appel de cette fonction n'impacte pas les appels de la fonction read().
///
///\param [in,out] linearBuffer Vecteur recevant les données du buffer circulaire.
///
///\remark Les données du buffer circulaire sont ajoutées à la fin du vecteur \p linearBuffer. Des réallocations du vecteur \p linearBuffer sont donc possibles.
///
void CCircularBuffer::unrollTo(std::vector<unsigned char>& linearBuffer)
{
  const auto spaceToRead = usedSpace();
  size_t usedSpaceBeforeEndOfTheWorld = m_data.size() - m_readPos;
  if (spaceToRead <= usedSpaceBeforeEndOfTheWorld)
  {
    std::copy(m_data.data() + m_readPos, m_data.data() + m_readPos + spaceToRead, std::back_inserter(linearBuffer));
  }
  else
  {
    std::copy(m_data.data() + m_readPos, m_data.data() + m_readPos + usedSpaceBeforeEndOfTheWorld, std::back_inserter(linearBuffer));
    std::copy(m_data.data(), m_data.data() + spaceToRead - usedSpaceBeforeEndOfTheWorld, std::back_inserter(linearBuffer));
  }
}

