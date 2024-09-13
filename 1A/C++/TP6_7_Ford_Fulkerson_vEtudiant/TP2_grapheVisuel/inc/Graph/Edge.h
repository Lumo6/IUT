#pragma once

#include "Node.h"
#include <memory> // std::shared_ptr
#include <vector>

using typeWeight = unsigned;  // alias pour connaitre le type d une arête 
// peut être templater pour les plus avancé en C++

class CEdge {
public : 
	using pEdge = std::shared_ptr<CEdge>; // Alias sur un pointeur sur une arête
	using pNodeArray = CNode::pNode[2]; // Alias sur notre tableau de 2 pointeur sur noeud 

	CEdge(CNode::pNode pNode1, CNode::pNode pNode2, typeWeight weight = 0); // constructeur permet de créer une nouvelle arête à partir de 2 pNode et d un poids
	
	static pEdge New(CNode::pNode pNode1, CNode::pNode pNode2, typeWeight weight = 0); // permet de créer un nouveau pEdge à partir de 2 pNode et d un poids et le renvoie

	CNode::pNode GetFirstNode() const; // renvoie le pNode à l indice 0
	CNode::pNode GetSecondNode() const; // renvoie le pNode à l indice 1

	bool operator==(const CEdge& edge)const; // renvoie vrai si 2 arêtes ont mêmes noeuds et même poids
	bool operator==(const CEdge::pEdge& pEdge)const;

	float GetMilieuX()const; // renvoie l abscisse du point au milieu de l arête
	float GetMilieuY()const; // renvoie l ordonnée du point au milieu de l arête
	
	typeWeight GetWeight() const; // renvoie le poids de l arête

	// TP 4 :
// TODO : ajouter un Geteur et un additionneur et un soustracteur sur le flux actuel
	typeWeight GetFlux()const;  // A MODIFIER
	void AddFlux(typeWeight n); // A COMPLETER
	void SubFlux(typeWeight n);// A COMPLETER

protected:
	typeWeight m_Weight; // le poids de l arête
	pNodeArray m_spNodes; // le tableau des 2 pNode

	// TP 6-7 :
// TODO : ajouter une donnée membre de type size_t correspondant au flux actuel passant par l arête
	typeWeight m_Flux = 0;
};