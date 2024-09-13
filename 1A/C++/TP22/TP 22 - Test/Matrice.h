#ifndef MATRICE_H
#define MATRICE_H

#pragma once
#include "StdAfx.h"
#include <iostream>
#include <vector>
#include "ErreurMatrice.h"
#include <iomanip>
#include <cassert>

template <typename T>
class CMatrice
{
private:
    //! Tableau 2D des valeurs. 
    std::vector<std::vector<T>> m_vvdData;

public:
    using iterator = T*;
    using const_iterator = const T*;
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

    //! \name Opérateurs

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
    size_t GetNbRows()const
    {
        if (GetNbCols() == 0) return 0;
        return m_vvdData.front().size();
    }
    //! \brief Retourne le nombre de colonnes. 
    size_t GetNbCols()const { return m_vvdData.size(); }

    template<typename T2>
    CMatrice<T>& operator =(const CMatrice<T2>& mat);

    template<typename T2>
    CMatrice(const CMatrice<T2>& mat);
};

//! \brief  Opérateur de sortie de flux pour les Matrices
template <typename T>
std::ostream& operator <<(std::ostream& out, const CMatrice<T>& mat);

//Fin Solution
template <typename T>
CMatrice<T>::CMatrice(size_t nNbRows, size_t nNbCols)
    : m_vvdData(nNbCols, std::vector<T>(nNbRows))
{
}

template <typename T>
const T& CMatrice<T>::operator() (size_t i, size_t j) const
{
    if (i >= GetNbRows() || j >= GetNbCols())
    {
        throw CErreurMatrice(1, __FUNCTION__);
    }
    assert(i < GetNbRows() && j < GetNbCols());
    return m_vvdData[j][i];
}

template <typename T>
T& CMatrice<T>::operator() (size_t i, size_t j)
{
    if (i >= GetNbRows() || j >= GetNbCols())
    {
        throw CErreurMatrice(1, __FUNCTION__);
    }
    assert(i < GetNbRows() && j < GetNbCols());
    return m_vvdData[j][i];
}

template <typename T>
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

template <typename T>
CMatrice<T> CMatrice<T>::operator+(const CMatrice& mat) const
{
    if (GetNbRows() != mat.GetNbRows() || GetNbCols() != mat.GetNbCols())
    {
        throw CErreurMatrice(2, __FUNCTION__);
    }
    assert(GetNbRows() == mat.GetNbRows() && GetNbCols() == mat.GetNbCols());
    CMatrice ret{ *this };
    ret += mat;
    return ret;
}

template <typename T>
CMatrice<T> CMatrice<T>::operator-() const
{
    CMatrice ret{ GetNbRows(), GetNbCols() };
    for (size_t i = 0; i < GetNbRows(); ++i)
    {
        for (size_t j = 0; j < GetNbCols(); ++j)
        {
            ret.m_vvdData[j][i] = -m_vvdData[j][i];
        }
    }
    return ret;
}

template <typename T>
CMatrice<T> CMatrice<T>::operator-(const CMatrice& mat) const
{
    if (GetNbRows() != mat.GetNbRows() || GetNbCols() != mat.GetNbCols())
    {
        throw CErreurMatrice(2, __FUNCTION__);
    }
    assert(GetNbRows() == mat.GetNbRows() && GetNbCols() == mat.GetNbCols());
    CMatrice ret{ *this };
    ret -= mat;
    return ret;
}

template <typename T>
CMatrice<T> CMatrice<T>::operator*(const CMatrice& mat) const
{
    if (GetNbCols() != mat.GetNbRows())
    {
        throw CErreurMatrice(2, __FUNCTION__);
    }
    assert(GetNbCols() == mat.GetNbRows());
    CMatrice ret{ GetNbRows(), mat.GetNbCols() };
    ret.Zeros();
    for (size_t i = 0; i < GetNbRows(); ++i)
    {
        for (size_t j = 0; j < mat.GetNbCols(); ++j)
        {
            for (size_t k = 0; k < GetNbCols(); ++k)
            {
                ret.m_vvdData[j][i] += m_vvdData[k][i] * mat.m_vvdData[j][k];
            }
        }
    }
    return ret;
}

template <typename T>
CMatrice<T>& CMatrice<T>::operator+=(const CMatrice& mat)
{
    if (GetNbRows() != mat.GetNbRows() || GetNbCols() != mat.GetNbCols())
    {
        throw CErreurMatrice(2, __FUNCTION__);
    }
    assert(GetNbRows() == mat.GetNbRows() && GetNbCols() == mat.GetNbCols());
    for (size_t i = 0; i < GetNbRows(); ++i)
    {
        for (size_t j = 0; j < GetNbCols(); ++j)
        {
            m_vvdData[j][i] += mat.m_vvdData[j][i];
        }
    }
    return *this;
}

template <typename T>
CMatrice<T>& CMatrice<T>::operator-=(const CMatrice& mat)
{
    if (GetNbRows() != mat.GetNbRows() || GetNbCols() != mat.GetNbCols()) {
        throw CErreurMatrice(2, __FUNCTION__);
    }
    assert(GetNbRows() == mat.GetNbRows() && GetNbCols() == mat.GetNbCols());
    for (size_t i = 0; i < GetNbRows(); ++i)
    {
        for (size_t j = 0; j < GetNbCols(); ++j)
        {
            m_vvdData[j][i] -= mat.m_vvdData[j][i];
        }
    }
    return *this;
}

template <typename T>
bool CMatrice<T>::operator==(const CMatrice& mat) const
{
    if (GetNbRows() != mat.GetNbRows() || GetNbCols() != mat.GetNbCols())
    {
        return false;
    }
    for (size_t i = 0; i < GetNbRows(); ++i)
    {
        for (size_t j = 0; j < GetNbCols(); ++j)
        {
            if (m_vvdData[j][i] != mat.m_vvdData[j][i])
            {
                return false;
            }
        }
    }
    return true;
}

template <typename T>
CMatrice<T>& CMatrice<T>::Zeros()
{
    for (auto& col : m_vvdData)
    {
        for (auto& val : col)
        {
            val = 0;
        }
    }
    return *this;
}

template <typename T>
CMatrice<T>& CMatrice<T>::Identity()
{
    for (size_t i = 0; i < GetNbRows(); ++i)
        for (size_t j = 0; j < GetNbCols(); ++j)
            m_vvdData[j][i] = (i == j ? 1 : 0);
    return *this;
}

template<typename T>
template<typename T2>
inline CMatrice<T>& CMatrice<T>::operator=(const CMatrice<T2>& mat2)
{
    m_vvdData.resize(mat2.GetNbCols());
    for (auto& col : m_vvdData)
    {
        col.resize(mat2.GetNbRows());
    }
    for (int i = 0; i < mat2.GetNbRows(); i++)
    {
        for (int j = 0; j < mat2.GetNbCols(); j++)
        {
            m_vvdData[j][i] = (T)mat2(i, j);
        }
    }
    return *this;
}
template<typename T>
template<typename T2>
inline CMatrice<T>::CMatrice(const CMatrice<T2>& mat)
{
    *this = mat;
}

#endif // MATRICE_H