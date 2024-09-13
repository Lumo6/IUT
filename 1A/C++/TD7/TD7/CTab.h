#pragma once
#include "StdAfx.h"
#include <iostream>

//class CTab {
//private:
//	float m_tab[3];
//public:
//	float* begin() { return m_tab; }
//	float* end() { return m_tab + 3; }
//	const float* begin() const { return m_tab; }
//	const float* end() const { return m_tab + 3; }
//
//};
//std::ostream& operator<<(std::ostream& os, const CTab& obj) {
//		os << "{";
//		for (const float* p = obj.begin(); p != obj.end(); p++) {
//			os << *p;
//			if (p != obj.end() - 1)
//				os << ", ";
//		}
//		os << "}";
//		return os;
//}
//


//template<size_t N>
//class CTab {
//private:
//	float m_tab[N];
//public:
//	float* begin() { return m_tab; }
//	float* end() { return m_tab + N; }
//	const float* begin() const { return m_tab; }
//	const float* end() const { return m_tab + N; }
//};
//
//template<size_t N>
//std::ostream& operator<<(std::ostream& os, const CTab<N>& obj) {
//	os << "{";
//	for (const float* p = obj.begin(); p != obj.end(); p++) {
//		os << *p;
//		if (p != obj.end() - 1)
//			os << ", ";
//	}
//	os << "}";
//	return os;
//}


//template<typename T,size_t N>
//class CTab {
//private:
//	T m_tab[N];
//public:
//	
//
//	using iterator = T*;
//	using const_iterator = const T*;
//
//	iterator begin() { return m_tab; }
//	iterator end() { return m_tab + N; }
//	const_iterator begin() const { return m_tab; }
//	const_iterator end() const { return m_tab + N; }
//	size_t size() { return N; };
//
//
//};
//
//template<typename T, size_t N>
//std::ostream& operator<<(std::ostream& os, const CTab<T,N>& obj) {
//		os << "{";
//		for (const auto* p = obj.begin(); p != obj.end(); p++) {
//			os << *p;
//			if (p != obj.end() - 1)
//				os << ", ";
//		}
//		os << "}";
//		return os;
//}




template<typename T,size_t N>
class CTab {
private:
	T m_tab[N];
public:
	CTab() {}
	template<typename T2, size_t N2>
	CTab(const CTab<T2, N2>& autre);

	using iterator = T*;
	using const_iterator = const T*;

	iterator begin() { return m_tab; }
	iterator end() { return m_tab + N; }
	const_iterator begin() const { return m_tab; }
	const_iterator end() const { return m_tab + N; }
	size_t size() { return N; };

	template<typename T3>
	void Convertir(const T3*, size_t);

	size_t factorielleIt(size_t valeur)
	{
		int total = 1;
		int curValeur;
		for (curValeur = 1; curValeur <= valeur; curValeur++)
			total *= curValeur;
		return total;
	}
	size_t factorielleRec(size_t valeur)
	{
		if (valeur == 0)
			return 1;
		else
			return valeur * factorielleRec(valeur - 1);
	}

};

template<typename T, size_t N>
template<typename T2,size_t N2>
CTab<T, N>::CTab(const CTab<T2, N2>& autre) {
	if (N2 < N) {
		Convertir(autre.begin(), N2);
	}
	else {
		Convertir(autre.begin(), N);
	}
}

template<typename T, size_t N>
template<typename T3>
void CTab<T,N>::Convertir(const T3* autre,size_t size) {
	size_t tempSize = size < N ? size : N;
	for (size_t i = 0; i < tempSize; i++) {
		m_tab[i]=static_cast<T>(autre[i]);
	}
}

template<typename T, size_t N>
std::ostream& operator<<(std::ostream& os, const CTab<T,N>& obj) {
		os << "{";
		for (const auto* p = obj.begin(); p != obj.end(); p++) {
			os << *p;
			if (p != obj.end() - 1)
				os << ", ";
		}
		os << "}";
		return os;
}