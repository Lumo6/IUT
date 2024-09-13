/*!
 * \file  "ErreurMatrice.cpp"
 *
 * \brief Définition de la classe CErreurMatrice. 
 *
 * \author Benjamin ALBOUY-KISSI
 * \date 2016
 *
 * \todo Définir dans le fichier ErreurMatrice.cpp la classe CErreurMatrice
 */
#include "StdAfx.h"
//Solution
#include "ErreurMatrice.h"


/*!
 * \brief
 * Affiche l'erreur en fonction de son code.
 * 
 * \param out
 * flux de sortie dans lequel afficher les informations.
 * 
 * \param em
 * Objet de type CErreurMatrice à afficher.
 * 
 * \returns
 * Une référence vers le flux de sortie permettant de cascader les appels.
 * 
 */
std::ostream& operator<<(std::ostream& out, const CErreurMatrice& em)
{
  switch(em.GetCodeErreur())
  {
  case 1:
    out << "Les indices sont hors de la plage dans la fonction " + em.GetNomFonction();
    break;
  case 2:
    out << "Les tailles ne sont pas compatibles lors de l'appel de la fonction " + em.GetNomFonction();
    break;
  default:
    out << "Une erreur inconnue est apparue dans la fonction " + em.GetNomFonction();
  }
  return out;
}

//Fin Solution