#pragma once

#include "Node.h"
#include <memory> // std::shared_ptr
#include <vector>

using typeWeight = unsigned;  // alias pour connaitre le type d une ar�te 
// peut �tre templater pour les plus avanc� en C++

class CEdge {
public : 
	using pEdge = std::shared_ptr<CEdge>; // Alias sur un pointeur sur une ar�te
	using pNodeArray = CNode::pNode[2]; // Alias sur notre tableau de 2 pointeur sur noeud 

	CEdge(CNode::pNode pNode1, CNode::pNode pNode2, typeWeight weight = 0); // constructeur permet de cr�er une nouvelle ar�te � partir de 2 pNode et d un poids
	
	static pEdge New(CNode::pNode pNode1, CNode::pNode pNode2, typeWeight weight = 0); // permet de cr�er un nouveau pEdge � partir de 2 pNode et d un poids et le renvoie

	CNode::pNode GetFirstNode() const; // renvoie le pNode � l indice 0
	CNode::pNode GetSecondNode() const; // renvoie le pNode � l indice 1

	bool operator==(const CEdge& edge)const; // renvoie vrai si 2 ar�tes ont m�mes noeuds et m�me poids
	bool operator==(const CEdge::pEdge& pEdge)const;

	float GetMilieuX()const; // renvoie l abscisse du point au milieu de l ar�te
	float GetMilieuY()const; // renvoie l ordonn�e du point au milieu de l ar�te
	
	typeWeight GetWeight() const; // renvoie le poids de l ar�te

	// TP 4 :
// TODO : ajouter un Geteur et un additionneur et un soustracteur sur le flux actuel
	typeWeight GetFlux()const;  // A MODIFIER
	void AddFlux(typeWeight n); // A COMPLETER
	void SubFlux(typeWeight n);// A COMPLETER

protected:
	typeWeight m_Weight; // le poids de l ar�te
	pNodeArray m_spNodes; // le tableau des 2 pNode

	// TP 6-7 :
// TODO : ajouter une donn�e membre de type size_t correspondant au flux actuel passant par l ar�te
	typeWeight m_Flux = 0;
};