/*!
 *
 * \brief Définition de la classe CMatrice.
 *
 * \author Benjamin ALBOUY-KISSI
 * \date 2009-2017
 * \version 1.1
 */
#include "Matrice.h"
#include <cassert>
#include <iostream>
#include <iomanip>

CMatrice::CMatrice()
{
	m_vvdData.resize(0,std::vector<double>(0));	
}

CMatrice::CMatrice(size_t row, size_t col)
{
	m_vvdData.resize(col, std::vector<double>(row));
}

size_t CMatrice::GetNbCols()
{
	return m_vvdData.size();
}

size_t CMatrice::GetNbRows()
{
	if (m_vvdData.size()==0) {
		return 0;
	}
	else {
	return m_vvdData.front().size();
	}
}

double& CMatrice::operator()(size_t i, size_t j)
{
	return(m_vvdData[j][i]);
}

CMatrice& CMatrice::Zeros()
{
	for (size_t i = 0; i < GetNbRows(); ++i) {
		for (size_t j = 0; j < GetNbCols(); ++j) {
			m_vvdData[j][i] = 0;
		}
	}
	return *this;
}

CMatrice& CMatrice::Identity()
{
	for (size_t i = 0; i < GetNbRows(); ++i) {
		for (size_t j = 0; j < GetNbCols(); ++j) {
			if (i == j) 
				m_vvdData[j][i] = 1;
			else 
				m_vvdData[j][i] = 0;
		}
	}
	return *this;
}

bool CMatrice::operator==(CMatrice& mat)
{
	if (GetNbCols() != mat.GetNbCols() || GetNbRows() != mat.GetNbRows()) {
		return false;
	}
	else {
		for (size_t i = 0; i < GetNbRows(); ++i) {
			for (size_t j = 0; j < GetNbCols(); ++j) {
				if (this->m_vvdData[j][i] != mat.m_vvdData[j][i])
					return false;
			}
		}
	}
	return true;
}

bool CMatrice::operator!=(CMatrice& mat)
{
	return !(this->operator==(mat));
}

CMatrice CMatrice::operator-()
{
	CMatrice inverse(GetNbRows(), GetNbCols());
	for (size_t i = 0; i < GetNbRows(); ++i) {
		for (size_t j = 0; j < GetNbCols(); ++j) {
			inverse.m_vvdData[j][i] = -(m_vvdData[j][i]);
		}
	}
	return inverse;
}

CMatrice CMatrice::operator-(CMatrice& mat)
{
	CMatrice moinssimple(GetNbRows(), GetNbCols());
	for (size_t i = 0; i < GetNbRows(); ++i) {
		for (size_t j = 0; j < GetNbCols(); ++j) {
			moinssimple.m_vvdData[j][i] = m_vvdData[j][i]-mat.m_vvdData[j][i];
		}
	}
	return moinssimple;
}

CMatrice& CMatrice::operator-=(CMatrice& mat)
{
	for (size_t i = 0; i < GetNbRows(); ++i) {
		for (size_t j = 0; j < GetNbCols(); ++j) {
			m_vvdData[j][i] -= mat.m_vvdData[j][i];
		}
	}
	return *this;
}

CMatrice CMatrice::operator+(CMatrice& mat)
{
	CMatrice plussimple(GetNbRows(), GetNbCols());
	for (size_t i = 0; i < GetNbRows(); ++i) {
		for (size_t j = 0; j < GetNbCols(); ++j) {
			plussimple.m_vvdData[j][i] = m_vvdData[j][i] + mat.m_vvdData[j][i];
		}
	}
	return plussimple;
}

CMatrice& CMatrice::operator+=(CMatrice& mat)
{
	for (size_t i = 0; i < GetNbRows(); ++i) {
		for (size_t j = 0; j < GetNbCols(); ++j) {
			m_vvdData[j][i] = m_vvdData[j][i] + mat.m_vvdData[j][i];
		}
	}
	return *this;
}

CMatrice CMatrice::operator*(CMatrice& mat)
{
	assert(GetNbCols() == mat.GetNbRows());

	CMatrice result(GetNbRows(), mat.GetNbCols());
	result.Zeros();
	for (size_t i = 0; i < GetNbRows(); ++i) {
		for (size_t j = 0; j < mat.GetNbCols(); ++j) {
			for (size_t k = 0; k < GetNbCols(); k++) {
				result.m_vvdData[j][i] += (m_vvdData[k][i] * mat.m_vvdData[j][k]);
			}
		}
	}
	return result;
}

std::ostream& operator<<(std::ostream& out, CMatrice& mat)
{
	for (size_t i = 0; i < mat.GetNbRows(); ++i) {
		for (size_t j = 0; j < mat.GetNbCols(); ++j) {
			out << std::setw(6) << mat(i, j);
		}
		if (i != mat.GetNbRows() - 1) {
			out << '\n';
		}
	}
	return out;
}
