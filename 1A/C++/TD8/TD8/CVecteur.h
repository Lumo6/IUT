#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <stdexcept>

#define STDEXCEPT

template<typename T>
class CVecteur
{
	std::vector<T> m_vData;
public:
	typedef typename std::vector<T>::iterator
		iterator;
	typedef typename std::vector<T>::const_iterator
		const_iterator;
	CVecteur(void) {}
	void resize(size_t nNewSize) {
		m_vData.resize(nNewSize);
		throw(std::length_error("Il n'y a pas suffisamment de place dans la mémoire pour créer un tableau de cette taille."));
	}
	bool empty() const { return m_vData.empty(); }
	size_t size() const { return m_vData.size(); }
	iterator begin() { return m_vData.begin(); }
	const_iterator begin() const {
		return m_vData.begin();
	}
	iterator end() { return m_vData.end(); }
	const_iterator end() const {
		return m_vData.end();
	}
	T& operator[](size_t nPos) {
		if (nPos < 0 || nPos > m_vData.size())
#ifndef STDEXCEPT
			throw(0);
#else
			throw(std::out_of_range("L'indice donnée est supérieur à la taille du tableau, veillez en donner un plus petit que celle-ci."));
#endif
		return m_vData[nPos];
	}
	const T& operator[] (size_t nPos) const {
		if (nPos < 0 || nPos > m_vData.size())
#ifndef STDEXCEPT
			throw(0);
#else
			throw(std::out_of_range("L'indice donnée est supérieur à la taille du tableau, veillez en donner un plus petit que celle-ci."));
#endif 
			
		return m_vData[nPos];
	}
	CVecteur operator + (const CVecteur& vect);
	CVecteur operator - (const CVecteur& vect);
};
template<typename T>
std::ostream& operator<<(std::ostream& out, const
	CVecteur<T>& vect)
{
	if (vect.empty())
	{
		out << "{ }";
		return out;
	}
	auto it = vect.begin();
	out << "{ " << *it++;
	for (; it != vect.end(); it++)
		out << ", " << *it;
	out << " }";
	return out;
}
template<typename T>
CVecteur<T> CVecteur<T>::operator + (const
	CVecteur& vect)
{
	CVecteur<T> res(*this);
	if (size() == vect.size())
	{
		iterator it = res.begin();
		const_iterator it2 = vect.begin();
		for (; it != res.end(); it++, it2++)
			*it += *it2;
	}
	else {
#ifndef STDEXCEPT
		throw(2);
#else
		throw(std::overflow_error("Les 2 vecteurs ne sont pas de memes tailles, veuillez utiliser 2 vecteurs de meme taille."));
#endif 

		
	}
	return res;
}
template<typename T>
CVecteur<T> CVecteur<T>::operator - (const
	CVecteur& vect)
{
	CVecteur<T> res(*this);
	if (size() == vect.size())
	{
		iterator it = res.begin();
		const_iterator it2 = vect.begin();
		for (; it != res.end(); it++, it2++)
			*it -= *it2;
	}
	else {
#ifndef STDEXCEPT
		throw(2);
#else
		throw(std::overflow_error("Les 2 vecteurs ne sont pas de memes tailles, veuillez utiliser 2 vecteurs de meme taille."));
#endif 
	}
	return res;
}
