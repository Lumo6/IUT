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
class CCircularBuffer
{
private:
  size_t m_nSizeBitmask = 0;          //!< Masque de bits permettant le cyclage en puissance de 2 selon la taille du buffer.
  std::vector<unsigned char> m_data;  //!< Données stockées par le buffer.

  size_t m_readPos = 0;               //!< Position du curseur de lecture
  size_t m_writePos = 0;              //!< Position du curseur d'écriture

  bool m_bEmpty = true;               //!< \c true si le buffer est vide

public:

  //! \name Construction / destruction

  //! \brief Constructeur
  CCircularBuffer(size_t size = 0);

  //! \name Accesseurs

  //! \brief Retourne la taille du buffer
  size_t size() const { return m_data.size(); }
  //! \brief Retourne l'espace libre du buffer
  size_t freeSpace() const;
  //! \brief Retourne l'espace utilisé dans le buffer
  size_t usedSpace() const;
  //! \brief Retourne le buffer linéaire interne. Peut être utile pour débuggage.
  const std::vector<unsigned char>& rawData() const { return m_data; }

  //! \name Méthodes / fonctions membres
  size_t read(std::vector<unsigned char>& data);
  void write(const std::vector<unsigned char>& data);

  void unrollTo(std::vector<unsigned char>& linearBuffer);

};

