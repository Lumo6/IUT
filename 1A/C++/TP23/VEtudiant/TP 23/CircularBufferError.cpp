/*!
 * \file  "CircularBufferError.cpp"
 *
 * \brief Définition de la classe CCircularBufferError. 
 *
 * \author Benjamin ALBOUY-KISSI
 * \date   29/03/2020
 *
 */
#include "CircularBufferError.h"


CCircularBufferError::CCircularBufferError(ErrorCodes nErrorCode)
 : m_nErrorCode(nErrorCode)
{
  switch (m_nErrorCode)
  {
  case ErrorCodes::SizeIsNotPowerOf2:
    m_strError = "The size of the circular buffer is not a power of 2.";
    break;
  case ErrorCodes::NotEnoughFreeSpace:
    m_strError = "The circular buffer is too small.";
    break;
  case ErrorCodes::UnknownError:
  default:
    m_strError = "Unknown error";
  }
}

/*!\brief Retranscrit en chaine de caractères le code de l'erreur
 * \param errorCode Le code d'erreur à retranscrire
 * \return Une chaîne de caractères correspondant au code d'erreur
 * \remark La chaîne de caractères retournée n'est pas une description de l'erreur, mais une retranscription du code.
 */
std::string to_string(CCircularBufferError::ErrorCodes errorCode)
{
  switch (errorCode)
  {
  case CCircularBufferError::ErrorCodes::SizeIsNotPowerOf2:
    return "SizeIsNotPowerOf2";
  case CCircularBufferError::ErrorCodes::NotEnoughFreeSpace:
    return "NotEnoughFreeSpace";
  case CCircularBufferError::ErrorCodes::UnknownError:
  default:
    return "UnknownError";
  }
}

/*!\brief Opérateur de sortie vers flux d'un objet CCircularBufferError
 *
 * Sort l'objet \p cbe sous forme de texte de deux lignes :<br>
 * <pre>Error code : </pre><em>error_code</em><br>
 * <pre>Description : </pre><em>human understandable string description</em>
 *
 * \param [in,out] out Le flux
 * \param [in] cbe L'objet CCircularBufferError à sortir
 * \return l'objet \p out
 */
std::ostream& operator<<(std::ostream& out, const CCircularBufferError& cbe)
{
  return out << "Error code : " << to_string(cbe.errorCode()) << "\n"
                "Description : " << cbe.what();
}
