/*!
 * \file  "CircularBufferError.h"
 *
 * \brief Déclaration de la classe CCircularBufferError. 
 *
 * \author Benjamin ALBOUY-KISSI
 * \date   29/03/2020
 *
 */
#pragma once
#include <iostream>
#include <stdexcept>

/*!
 * \brief
 * Classe de gestion d'erreur pour les buffers circulaires.
 * 
 * \see operator<<(std::ostream& out, const CCircularBufferError& cbe)
 */
class CCircularBufferError
{
public:
  /*!
   * \brief Codes d'erreur
   *
   * \see to_string(CCircularBufferError::ErrorCodes errorCode)
   */
  enum class ErrorCodes
  {
    UnknownError,       //!< Erreur inconnue. Ne devrait jamais se produire.
    SizeIsNotPowerOf2,  //!< La taille demandée pour le buffer circulaire n'est pas une puissance de 2.
    NotEnoughFreeSpace  //!< L'espace libre dans le buffer circulaire n'est pas assez grand.
  };
private:
  const ErrorCodes m_nErrorCode;  //!< Code de l'erreur
  std::string m_strError;         //!< Description de l'erreur
public:
  /*!\brief Constructeur
   * \param nErrorCode Le code de l'erreur
   */
  CCircularBufferError(ErrorCodes nErrorCode = ErrorCodes::UnknownError);
  //!\brief retourne le code de l'erreur
  ErrorCodes errorCode() const {return m_nErrorCode;}

  //!\brief retourne la description de l'erreur
  const std::string& what() const { return m_strError; }
};

std::string to_string(CCircularBufferError::ErrorCodes errorCode);

std::ostream& operator<<(std::ostream& out, const CCircularBufferError& cbe);
