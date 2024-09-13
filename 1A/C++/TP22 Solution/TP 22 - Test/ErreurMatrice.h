/*!
 * \file  "ErreurMatrice.h"
 *
 * \brief Déclaration de la classe CErreurMatrice. 
 *
 * \author Benjamin ALBOUY-KISSI
 * \date 2016
 *
 * \todo Déclarer dans le fichier ErreurMatrice.h la classe CErreurMatrice
 */
//Solution
#pragma once
#include <iostream>
#include <string>

/*!
 * \brief
 * Classe de gestion des erreurs de la classe CMatrice.
 */
class CErreurMatrice
{
private:
  //!\brief Code de l'erreur
  int m_nCodeErreur;
  //!\brief Nom de la fonction ayant généré cette erreur
  std::string m_strNomFonction;
public:
  /*!\brief Constructeur
   * \param nCodeErreur Code de l'erreur
   * \param strNomFonction Nom de la fonction qui a généré l'erreur
   */
  CErreurMatrice(int nCodeErreur, const std::string& strNomFonction) : m_nCodeErreur(nCodeErreur), m_strNomFonction(strNomFonction) {}
  //!\brief Récupère le code de l'erreur
  int GetCodeErreur()const { return m_nCodeErreur; }
  //!\brief Récupère le nom de la fonction qui a généré l'erreur
  const std::string& GetNomFonction()const { return m_strNomFonction; }
};

std::ostream& operator<<(std::ostream& out, const CErreurMatrice& em);

//Fin Solution