#include "Graph/Edge.h"

// TP 1 2  et 3 : 
// TODO : CEdge         : cr�ation du constructeur : une ar�te c'est un tableau de 2 pNode et un poids
// TODO : New           : fonction renvoyant un nouveau pEdge
// TODO : GetFirstNode  : fonction renvoyant le pNode � l'indice 0 du tableau
// TODO : GetSecondNode : fonction renvoyant le pNode � l'indice 1 du tableau
// TODO : GetMilieuX    : fonction renoyant l abscisse du milieu de l ar�te ( � calculer faire la moyenne des abscisses des 2 noeuds)
// TODO : GetMilieuY    : fonction renoyant l ordonn�e du milieu de l ar�te ( � calculer faire la moyenne des ordonn�e des 2 noeuds)
// TODO : GetWeight     : fonction renvoyant le poids de l ar�te
// TODO : operator==    : fonction renvoyant vrai si les 2 ar�tes ont m�me poids et m�mes noeuds

CEdge::CEdge(CNode::pNode pNode1, CNode::pNode pNode2, typeWeight weight)
	: m_Weight(weight), m_Nodes{ pNode1,pNode2 }
{  // Rien A Faire utilisation liste d'initialisation pour initialiser les donn�es membres
}

CEdge::pEdge CEdge::NewEdge(CNode::pNode pNode1, CNode::pNode pNode2, typeWeight weight)
{
	return std::make_shared<CEdge>(pNode1, pNode2, weight);  // RAS
}

CNode::pNode CEdge::GetFirstNode() const
{
	return m_Nodes[0]; // RAS
}

CNode::pNode CEdge::GetSecondNode() const
{
	return m_Nodes[1]; // RAS
}


typeWeight CEdge::GetWeight() const
{
	return m_Weight;  // RAS
}

bool CEdge::operator==(const CEdge& edge) const
{
	return m_Weight == edge.m_Weight && m_Nodes[0] == edge.m_Nodes[0] && m_Nodes[1] == edge.m_Nodes[1];
}

bool CEdge::operator==(const CEdge::pEdge& pEdge) const
{
	return (*this) == (*pEdge);
}

// ICI COMMENCE LE TP2 *********************************************************************************

float CEdge::GetMilieuX() const
{
	return (m_Nodes[0]->GetX() + m_Nodes[1]->GetX()) / 2.0f;
}

float CEdge::GetMilieuY() const
{
	return (m_Nodes[0]->GetY() + m_Nodes[1]->GetY()) / 2.0f;
}

/************************ FIN TP 2 3 4 ********************************/