#pragma once

// TP 1 2  et 3 : Graphe visuel
// TODO : CEdge         : cr�ation du constructeur : une ar�te c'est un tableau de 2 pNode et d un poids
// TODO : New           : fonction renvoyant un nouveau pEdge
// TODO : GetFirstNode  : fonction renvoyant le pNode � l'indice 0 du tableau
// TODO : GetSecondNode : fonction renvoyant le pNode � l'indice 1 du tableau
// TODO : GetMilieuX    : fonction renoyant l abscisse du milieu de l ar�te ( � calculer faire la moyenne des abscisses des 2 noeuds)
// TODO : GetMilieuY    : fonction renoyant l ordonn�e du milieu de l ar�te ( � calculer faire la moyenne des ordonn�e des 2 noeuds)
// TODO : GetWeight     : fonction renvoyant le poids de l ar�te
// TODO : operator==    : fonction renvoyant vrai si les 2 ar�tes ont m�me poids et m�mes noeuds

#include "Node.h"

#include <array>
#include <memory>

using typeWeight = unsigned;

class CEdge 
{
public : 
	using  pEdge = std::shared_ptr<CEdge> ;// Alias pour pointeur sur noeud
	using   pNodeArray = std::array<CNode::pNode, 2>; 
	static pEdge New(CNode::pNode pNode1, CNode::pNode pNode2, typeWeight weight = 0) { return std::make_shared<CEdge>(pNode1, pNode2, weight); }

	CEdge(CNode::pNode pNode1, CNode::pNode pNode2, typeWeight weight)
		: m_Weight(weight), m_apNodes{ pNode1,pNode2 } {}

	const pNodeArray& GetNodes() const { return m_apNodes; }
	CNode::pNode GetFirstNode() const { return m_apNodes[0]; }
	CNode::pNode GetSecondNode() const { return m_apNodes[1]; }
	
protected:
	typeWeight m_Weight;   // poids de l'ar�te
	pNodeArray m_apNodes; // Vecteur de 2 noeuds

public:

	float GetMilieuX()const { return (m_apNodes[0]->GetX() + m_apNodes[1]->GetX()) / 2; }
	float GetMilieuY()const { return (m_apNodes[0]->GetY() + m_apNodes[1]->GetY()) / 2; }
	typeWeight GetWeight() const { return m_Weight; }

	bool operator==(const CEdge& edge) { return m_Weight == edge.m_Weight && m_apNodes[0] == edge.m_apNodes[0] && m_apNodes[1] == edge.m_apNodes[1]; }

	
};

// TP Not� : 
// Ajouter un foncteur pour trier les ar�tes en fonction de leur poids decroissant

class TriEdge
{
public:

	bool operator()(const CEdge::pEdge& edge1, const CEdge::pEdge& edge2) const
	{
		return edge1->GetWeight() > edge2->GetWeight();
	}
};