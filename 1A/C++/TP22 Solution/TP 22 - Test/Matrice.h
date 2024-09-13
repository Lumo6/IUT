/*!\todo
 * 1) Copiez ici le contenu du fichier Matrice.h du TP 9, puis modifiez la classe 
 * de sorte à ajouter la gestion d'erreurs.\n
 */
/*!
 * \file  "Matrice.h"
 *
 * \brief Déclaration de la classe CMatrice. 
 *
 */
//Solution
#pragma once
#include "ErreurMatrice.h"
#include <iostream>
#include <iomanip>
#include <vector>

/*!
 * \brief
 * Classe de gestion d'une matrice.
 * 
 * La gestion des matrices est réalisée de façon générale à l'aide d'un 
 * template. Le paramètre du template défini le type des données stockées dans 
 * la matrice.
 * 
 * \remarks
 * Cette classe n'est pas du tout optimisée.
 */
template<typename T>
class CMatrice
{
private:
  //! Tableau 2D des valeurs. 
  std::vector<std::vector<T>> m_vvData;

public:

  //! \name Construction / destruction

  //! \brief Constructeur par défaut. La matrice est vide.
  CMatrice() {};
  //! \brief Constructeur avec deux paramètres. 
  CMatrice(size_t nNbRows, size_t nNbCols);
  //! \brief Constructeur de conversion. 
  template<typename T2>
  CMatrice(const CMatrice<T2>& mat);

  //! \name Opérations

  //! \brief Met toutes les valeurs à zéro
  CMatrice& Zeros();
  //! \brief Initialise une matrice identité
  CMatrice& Identity();

  //! \name Opérateurs

  //! \brief Opérateur d'affectation avec conversion. 
  template<typename T2>
  CMatrice<T>& operator =(const CMatrice<T2>& mat);
  //! \brief Opérateur -. 
  CMatrice operator -()const;
  //! \brief Opérateur +. 
  CMatrice operator +(const CMatrice& mat)const;
  //! \brief Opérateur -. 
  CMatrice operator -(const CMatrice& mat)const;
  //! \brief Opérateur *. 
  CMatrice operator *(const CMatrice& mat)const;
  //! \brief Opérateur +=. 
  CMatrice& operator +=(const CMatrice& mat);
  //! \brief Opérateur -=. 
  CMatrice& operator -=(const CMatrice& mat);
  //! \brief Opérateur ==. 
  bool operator ==(const CMatrice& mat)const;
  //! \brief Opérateur !=. 
  bool operator !=(const CMatrice& mat)const;


  //! \name Accesseurs

  //! \brief Opérateurs d'accès à une valeur constante. 
  const T& operator() (size_t i, size_t j) const;
  //! \brief Opérateurs d'accès à une valeur. 
  T& operator() (size_t i, size_t j);

  //! \brief Retourne le nombre de lignes. 
  size_t GetNbRows()const {
    if (GetNbCols() == 0) return 0;
    return m_vvData.front().size();
  }
  //! \brief Retourne le nombre de colonnes. 
  size_t GetNbCols()const { return m_vvData.size(); }
};

//! \brief  Opérateur de sortie de flux pour les Matrices
template<typename T>
std::ostream& operator <<(std::ostream& out, const CMatrice<T>& mat);

/*!
 * \param nNbRows Nombre de lignes. 
 * \param nNbCols Nombre de colonnes. 
 */
template<typename T>
CMatrice<T>::CMatrice(size_t nNbRows, size_t nNbCols)
{
  m_vvData.resize(nNbCols);
  for (auto& col : m_vvData)
    col.resize(nNbRows);
}

/*!
 * \param mat Matrice à convertir. 
 */
template<typename T>
template<typename T2>
CMatrice<T>::CMatrice(const CMatrice<T2>& mat)
{
  *this = mat;
}

/*!
 * \param mat La matrice à copier. 
 *
 * \return  Une référence vers cette matrice nouvellement copiée. 
 */
template<typename T>
template<typename T2>
CMatrice<T>& CMatrice<T>::operator=(const CMatrice<T2>&mat)
{
  const size_t nNbRows = mat.GetNbRows();
  const size_t nNbCols = mat.GetNbCols();
  m_vvData.resize(nNbCols);
  for (auto& col : m_vvData)
  {
    col.resize(nNbRows);
  }
  for (size_t i = 0; i < nNbRows; ++i)
    for (size_t j = 0; j < nNbCols; ++j)
      m_vvData[j][i] = (T)mat(i, j);
  return *this;
}

/*!
 * \param i Indice de la ligne
 * \param j Indice de la colonne
 *
 * Accède de façon constante à un élément de la matrice. Si les indices sont hors de la plage 
 * autorisée, la fonction échoue.
 * 
 * \return  une référence constante vers la valeur demandée. 
 */
template<typename T>
const T& CMatrice<T>::operator() (size_t i, size_t j) const
{
  if (i < 0 || i >= GetNbRows() || j < 0 || j >= GetNbCols())
  {
    throw(CErreurMatrice(1, __FUNCTION__));
  }
  return m_vvData[j][i];
}

/*!
 * \param i Indice de la ligne
 * \param j Indice de la colonne
 *
 * Accède à un élément de la matrice. Si les indices sont hors de la plage autorisée, la fonction 
 * échoue.
 * 
 * \return  une référence vers la valeur demandée. 
 */
template<typename T>
T& CMatrice<T>::operator() (size_t i, size_t j)
{
  if (i < 0 || i >= GetNbRows() || j < 0 || j >= GetNbCols())
  {
    throw(CErreurMatrice(1, __FUNCTION__));
  }
  return m_vvData[j][i];
}

/*!
 * \param [in,out] out Flux de sortie
 * \param          mat La matrice à afficher
 *
 * \return  une référence vers le flux de façon à pouvoir cascader les appels
 */
template<typename T>
std::ostream& operator <<(std::ostream& out, const CMatrice<T>& mat)
{
  const size_t rows = mat.GetNbRows();
  const size_t cols = mat.GetNbCols();
  for (size_t i = 0; i < rows; ++i)
  {
    for (size_t j = 0; j < cols; ++j)
    {
      out << std::setw(6) << mat(i, j);
    }
    if (i != rows - 1)
      out << '\n';
  }
  if (rows == 0 || cols == 0)
    out << "Matrice vide";
  return out;
}

/*!
 * \param mat La matrice à ajouter avec cette matrice. 
 *
 * \return  Le résultat de l'operation. 
 */
template<typename T>
CMatrice<T> CMatrice<T>::operator+(const CMatrice&mat)const
{
  CMatrice ret{ *this };
  ret += mat;
  return ret;
}

/*!
 * \return  La matrice opposée. 
 */
template<typename T>
CMatrice<T> CMatrice<T>::operator-()const
{
  CMatrice ret{ GetNbRows(), GetNbCols() };
  for (size_t i = 0; i < GetNbRows(); ++i)
    for (size_t j = 0; j < GetNbCols(); ++j)
      ret.m_vvData[j][i] = -m_vvData[j][i];
  return ret;
}

/*!
 * \param mat La matrice à soustraire depuis cette matrice. 
 *
 * \return  Le résultat de l'operation. 
 */
template<typename T>
CMatrice<T> CMatrice<T>::operator-(const CMatrice&mat)const
{
  CMatrice ret{ *this };
  ret -= mat;
  return ret;
}

/*!
 * \param mat La matrice de droite du produit avec cette matrice. 
 *
 * \return  Le résultat de l'operation. 
 */
template<typename T>
CMatrice<T> CMatrice<T>::operator*(const CMatrice&mat)const
{
  if (GetNbCols() != mat.GetNbRows())
  {
    throw(CErreurMatrice(2, __FUNCTION__));
  }
  CMatrice ret{ GetNbRows(), mat.GetNbCols() };
  ret.Zeros();
  for (size_t i = 0; i < GetNbRows(); ++i)
    for (size_t j = 0; j < mat.GetNbCols(); ++j)
      for (size_t k = 0; k < GetNbCols(); ++k)
        ret.m_vvData[j][i] += m_vvData[k][i] * mat.m_vvData[j][k];
  return ret;
}

/*!
 * \param mat La matrice à ajouter à cette matrice. 
 *
 * \return Une référence vers cette matrice après l'addition. 
 */
template<typename T>
CMatrice<T>& CMatrice<T>::operator+=(const CMatrice&mat)
{
  if (GetNbRows() != mat.GetNbRows() || GetNbCols() != mat.GetNbCols())
  {
    throw(CErreurMatrice(2, __FUNCTION__));
  }
  for (size_t i = 0; i < GetNbRows(); ++i)
    for (size_t j = 0; j < GetNbCols(); ++j)
      m_vvData[j][i] += mat.m_vvData[j][i];
  return *this;
}

/*!
 * \param mat La matrice à soustraire de cette matrice. 
 *
 * \return Une référence vers cette matrice après la soustraction. 
 */
template<typename T>
CMatrice<T>& CMatrice<T>::operator-=(const CMatrice&mat)
{
  if (GetNbRows() != mat.GetNbRows() || GetNbCols() != mat.GetNbCols())
  {
    throw(CErreurMatrice(2, __FUNCTION__));
  }
  for (size_t i = 0; i < GetNbRows(); ++i)
    for (size_t j = 0; j < GetNbCols(); ++j)
      m_vvData[j][i] -= mat.m_vvData[j][i];
  return *this;
}

/*!
 * \param mat La matrice à vérifier. 
 *
 * \return \c true si les deux matrices sont égales. 
 */
template<typename T>
bool CMatrice<T>::operator==(const CMatrice&mat)const
{
  if (GetNbRows() != mat.GetNbRows() || GetNbCols() != mat.GetNbCols())
    return false;
  for (size_t i = 0; i < GetNbRows(); ++i)
    for (size_t j = 0; j < GetNbCols(); ++j)
      if (m_vvData[j][i] != mat.m_vvData[j][i])
        return false;
  return true;
}

/*!
 * \param mat La matrice à vérifier. 
 *
 * \return \c true si les deux matrices sont différente. 
 */
template<typename T>
bool CMatrice<T>::operator!=(const CMatrice&mat)const
{
  return !(*this == mat);
}

/*!
 * \return Une référence vers cette matrice. 
 */
template<typename T>
CMatrice<T>& CMatrice<T>::Zeros(void)
{
  for (auto& col : m_vvData)
    for (auto& val : col)
      val = 0;
  return *this;
}

/*!
 * Les éléments de la première diagonale de la matrice valent 1, les autres valeurs valent 0.
 *
 * \return Une référence vers cette matrice. 
 */
template<typename T>
CMatrice<T>& CMatrice<T>::Identity(void)
{
  for (size_t i = 0; i < GetNbRows(); ++i)
    for (size_t j = 0; j < GetNbCols(); ++j)
      m_vvData[j][i] = (i == j ? 1 : 0);
  return *this;
}

//Fin Solution