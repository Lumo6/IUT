/*!
 * \file "CircularBuffer.h"
 * \brief Déclaration de la classe CCircularBuffer. 
 *
 * \author Benjamin ALBOUY-KISSI
 * \date   29/03/2020
 *
 */

#pragma once
#include "CircularBufferError.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

//TODO : Modifiez la classe pour que le buffer circulaire puisse stocker n'importe quel type de donné.
//Dans l'état actuel, la classe CCircularBuffer ne stocke que des \c unsigned \c char.
//Faites en sorte de modifier cela de façon à ce qu'à l'usage de la classe, le type de données internes puisse être configuré.

/*!
 * \brief Gère un buffer circulaire. 
 *
 */
template<typename T>
class CCircularBuffer
{
private:
  size_t m_nSizeBitmask = 0;          //!< Masque de bits permettant le cyclage en puissance de 2 selon la taille du buffer.
  std::vector<T> m_data;  //!< Données stockées par le buffer.

  size_t m_readPos = 0;               //!< Position du curseur de lecture
  size_t m_writePos = 0;              //!< Position du curseur d'écriture

  bool m_bEmpty = true;               //!< \c true si le buffer est vide

public:
    size_t Getwritepos() const { return m_readPos; }
    size_t Getreadpos() const { return m_writePos; }
    std::vector<T> GetVec() const { return m_data; }
  //! \name Construction / destruction

  //! \brief Constructeur
  CCircularBuffer(size_t size = 0);

  //! \name Accesseurs

  //! \brief Retourne la taille du buffer
  size_t size() const { return m_data.size(); }
  //! \brief Retourne l'espace libre du buffer
  size_t freeSpace() const { return m_data.size() - usedSpace(); }
  //! \brief Retourne l'espace utilisé dans le buffer
  size_t usedSpace() const {
      if (m_bEmpty) return 0;
      return ((m_writePos - m_readPos - !m_bEmpty) & m_nSizeBitmask) + 1;
  }
  //! \brief Retourne le buffer linéaire interne. Peut être utile pour débuggage.
  const std::vector<T>& rawData() const { return m_data; }

  //! \name Méthodes / fonctions membres
  size_t read(std::vector<T>& data);
  void write(const std::vector<T>& data);

  template<typename T2>
  void unrollTo(std::vector<T2>& linearBuffer);

};

///
///Crée un buffer circulaire en spécifiant sa taille
///
///\param size Taille du buffer
///
///\remark La taille du buffer doit être une puissance de 2 afin d'optimiser le cycle du buffer.
///Dans le cas contraire, une exception CCircularBufferError de code CCircularBufferError::ErrorCodes::SizeIsNotPowerOf2 est lancée.
///
template<typename T>
CCircularBuffer<T>::CCircularBuffer(size_t size)
    : m_nSizeBitmask(size != 0 ? size - 1 : 0)
{
    if (size == 0)
        return;

    if ((size & (size - 1)) != 0)
    {
        throw CCircularBufferError(CCircularBufferError::ErrorCodes::SizeIsNotPowerOf2);
    }

    m_data.resize(size);
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

template<typename T>
size_t CCircularBuffer<T>::read(std::vector<T>& data)
{
    const size_t spaceToRead = std::min(data.size(), usedSpace());

    size_t usedSpaceBeforeEndOfTheWorld = m_data.size() - m_readPos;
    if (spaceToRead <= usedSpaceBeforeEndOfTheWorld)
    {
        std::memcpy(data.data(), m_data.data() + m_readPos, spaceToRead * sizeof(T));
#ifdef _DEBUG
        //"Erase" just read data
        std::memset(m_data.data() + m_readPos, 0, spaceToRead * sizeof(T));
#endif
    }
    else
    {
        std::memcpy(data.data(), m_data.data() + m_readPos, usedSpaceBeforeEndOfTheWorld * sizeof(T));
        std::memcpy(data.data() + usedSpaceBeforeEndOfTheWorld, m_data.data(), (spaceToRead - usedSpaceBeforeEndOfTheWorld) * sizeof(T));
#ifdef _DEBUG
        //"Erase" just read data
        std::memset(m_data.data() + m_readPos, 0, usedSpaceBeforeEndOfTheWorld * sizeof(T));
        std::memset(m_data.data(), 0, (spaceToRead - usedSpaceBeforeEndOfTheWorld) * sizeof(T));
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

template<typename T>
void CCircularBuffer<T>::write(const std::vector<T>& data)
{
    //TODO : Modifiez la méthode CCircularBuffer::write de façon à lancer une exception si la taille de data est supérieure à l'espace libre dans le buffer circulaire.
    //       L'exception doit être un objet CCircularBufferError de code d'erreur CCircularBufferError::ErrorCodes::NotEnoughFreeSpace
    //NB : L'espace libre dans le buffer circulaire est retourné par la fonction membre freeSpace().
    if (freeSpace() < data.size())
        throw CCircularBufferError(CCircularBufferError::ErrorCodes::NotEnoughFreeSpace);
    if (data.size() == 0)
        return;

    size_t freeSpaceBeforeEndOfTheWorld = m_data.size() - m_writePos;
    
    if (freeSpaceBeforeEndOfTheWorld < data.size())
    {
        
        std::memcpy(m_data.data() + m_writePos, data.data(), freeSpaceBeforeEndOfTheWorld * sizeof(T));
        std::memcpy(m_data.data(), data.data() + freeSpaceBeforeEndOfTheWorld, (data.size() - freeSpaceBeforeEndOfTheWorld) * sizeof(T));
        
    }
    else
        std::memcpy(m_data.data() + m_writePos, data.data(), data.size() * sizeof(T));
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

template<typename T>
template<typename T2>
void CCircularBuffer<T>::unrollTo(std::vector<T2>& linearBuffer)
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