/*!
 *
 * \brief Déclaration de la classe CMatrice.
 *
 * \author Benjamin ALBOUY-KISSI
 * \date 2009-2015
 * \version 1.1
 */
 //Solution
#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include <cassert>

/*!
 * \if MatriceHelp
 * \mainpage
 *
 * Ce document présente l'utilisation de la classe CMatrice. Référez-vous à la documentation de la classe CMatrice.
 *
 * \endif
 */

 /*!
  * \class CMatrice
  *
  * \brief Gère des matrices de réels.
  *
  * \author  Benjamin Albouy Kissi
  * \date  23/11/2009
  *
  * Gère des matrices de réels.
  */

template<typename T>
class CMatrice
{
private:
    //! Tableau 2D des valeurs. 
    std::vector<std::vector<T>> m_vvdData;

public:

    //! \name Construction / destruction

    //! \brief Constructeur par défaut. La matrice est vide.
    CMatrice() {};
    //! \brief Constructeur avec deux paramètres. 
    CMatrice(size_t nNbRows, size_t nNbCols);

    //! \name Opérations

    //! \brief Met toutes les valeurs à zéro
    CMatrice& Zeros();
    //! \brief Initialise une matrice identité
    CMatrice& Identity();

    //Construction avec conversion
    template<typename T2>
    CMatrice(const CMatrice<T2>& tab);

    template<typename T2>
    CMatrice& operator=(const CMatrice<T2>& tab);

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


    //! \name Accesseurs

    //! \brief Opérateurs d'accès à une valeur constante. 
    const T& operator() (size_t i, size_t j) const;
    //! \brief Opérateurs d'accès à une valeur. 
    T& operator() (size_t i, size_t j);

    //! \brief Retourne le nombre de lignes. 
    size_t GetNbRows()const {
        if (GetNbCols() == 0) return 0;
        return m_vvdData.front().size();
    }
    //! \brief Retourne le nombre de colonnes. 
    size_t GetNbCols()const { return m_vvdData.size(); }
};

template<typename T>
//! \brief  Opérateur de sortie de flux pour les Matrices
std::ostream& operator <<(std::ostream& out, const CMatrice<T>& mat);

//Fin Solution





// MATRICE.CPP






/*!
 *
 * \brief Définition de la classe CMatrice.
 *
 * \author Benjamin ALBOUY-KISSI
 * \date 2009-2017
 * \version 1.1
 */

 //Solution

/*!
 * \param nNbRows Nombre de lignes.
 * \param nNbCols Nombre de colonnes.
 */

template<typename T>
CMatrice<T>::CMatrice(size_t nNbRows, size_t nNbCols)
{
    m_vvdData.resize(nNbCols);
    for (auto& col : m_vvdData)
        col.resize(nNbRows);
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
    assert(i < GetNbRows() && j < GetNbCols());
    return m_vvdData[j][i];
}

/*!
 * \param i Indice de la ligne
 * \param j Indice de la colonne
 *
 * Accède à un élément de la matrice. En mode Debug, vérifie que les indice soient corrects.
 *
 * \return  une référence vers la valeur demandée.
 */
template<typename T>
T& CMatrice<T>::operator() (size_t i, size_t j)
{
    assert(i < GetNbRows() && j < GetNbCols());
    return m_vvdData[j][i];
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
CMatrice<T> CMatrice<T>::operator+(const CMatrice<T>& mat)const
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
            ret.m_vvdData[j][i] = -m_vvdData[j][i];
    return ret;
}

/*!
 * \param mat La matrice à soustraire depuis cette matrice.
 *
 * \return  Le résultat de l'operation.
 */
template<typename T>
CMatrice<T> CMatrice<T>::operator-(const CMatrice<T>& mat)const
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
CMatrice<T> CMatrice<T>::operator*(const CMatrice<T>& mat)const
{
    assert(GetNbCols() == mat.GetNbRows());
    CMatrice ret{ GetNbRows(), mat.GetNbCols() };
    ret.Zeros();
    for (size_t i = 0; i < GetNbRows(); ++i)
        for (size_t j = 0; j < mat.GetNbCols(); ++j)
            for (size_t k = 0; k < GetNbCols(); ++k)
                ret.m_vvdData[j][i] += m_vvdData[k][i] * mat.m_vvdData[j][k];
    return ret;
}

/*!
 * \param mat La matrice à ajouter à cette matrice.
 *
 * \return Une référence vers cette matrice après l'addition.
 */
template<typename T>
CMatrice<T>& CMatrice<T>::operator+=(const CMatrice<T>& mat)
{
    assert(GetNbRows() == mat.GetNbRows() && GetNbCols() == mat.GetNbCols());
    for (size_t i = 0; i < GetNbRows(); ++i)
        for (size_t j = 0; j < GetNbCols(); ++j)
            m_vvdData[j][i] += mat.m_vvdData[j][i];
    return *this;
}

/*!
 * \param mat La matrice à soustraire de cette matrice.
 *
 * \return Une référence vers cette matrice après la soustraction.
 */
template<typename T>
CMatrice<T>& CMatrice<T>::operator-=(const CMatrice<T>& mat)
{
    assert(GetNbRows() == mat.GetNbRows() && GetNbCols() == mat.GetNbCols());
    for (size_t i = 0; i < GetNbRows(); ++i)
        for (size_t j = 0; j < GetNbCols(); ++j)
            m_vvdData[j][i] -= mat.m_vvdData[j][i];
    return *this;
}

/*!
 * \param mat La matrice à vérifier.
 *
 * \return \c true si les deux matrices sont égales.
 *
 * \note Depuis C++20, l'opérateur != est défini automatiquement par le compilateur à partir de l'opérateur ==.
 */
template<typename T>
bool CMatrice<T>::operator==(const CMatrice& mat)const
{
    if (GetNbRows() != mat.GetNbRows() || GetNbCols() != mat.GetNbCols())
        return false;
    for (size_t i = 0; i < GetNbRows(); ++i)
        for (size_t j = 0; j < GetNbCols(); ++j)
            if (m_vvdData[j][i] != mat.m_vvdData[j][i])
                return false;
    return true;
}

/*!
 * \return Une référence vers cette matrice.
 */
template<typename T>
CMatrice<T>& CMatrice<T>::Zeros(void)
{
    for (auto& col : m_vvdData)
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
            m_vvdData[j][i] = (i == j ? 1 : 0);
    return *this;
}

template<typename T>
template<typename T2>
inline CMatrice<T>::CMatrice(const CMatrice<T2>& tab)
{
    *this = tab;
}

template<typename T>
template<typename T2>
CMatrice<T>& CMatrice<T>::operator=(const CMatrice<T2>& tab)
{
    this->m_vvdData.resize(tab.GetNbCols());
    for (auto& col : this->m_vvdData) {
        col.resize(tab.GetNbRows());
    }
    for (size_t i = 0; i < tab.GetNbRows(); i++) {
        for (size_t j = 0; j < tab.GetNbCols(); j++) {
            this->m_vvdData[j][i] = (T)tab(i, j);
        }
    }
    return *this;
}