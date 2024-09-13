#include "Graph/Edge.h"

// TP 1 2  et 3 : 
// TODO : CEdge         : cr�ation du constructeur : une ar�te c'est un tableau de 2 pNode et d un poids
// TODO : New           : fonction renvoyant un nouveau pEdge
// TODO : GetFirstNode  : fonction renvoyant le pNode � l'indice 0 du tableau
// TODO : GetSecondNode : fonction renvoyant le pNode � l'indice 1 du tableau
// TODO : GetMilieuX    : fonction renoyant l abscisse du milieu de l ar�te ( � calculer faire la moyenne des abscisses des 2 noeuds)
// TODO : GetMilieuY    : fonction renoyant l ordonn�e du milieu de l ar�te ( � calculer faire la moyenne des ordonn�e des 2 noeuds)
// TODO : GetWeight     : fonction renvoyant le poids de l ar�te
// TODO : operator==    : fonction renvoyant vrai si les 2 ar�tes ont m�me poids et m�mes noeuds

CEdge::CEdge(CNode::pNode pNode1, CNode::pNode pNode2, typeWeight weight)
	: m_Weight(weight), m_spNodes{ pNode1,pNode2 }
{  // Rien A Faire utilisation liste d'initialisation pour initialiser les donn�es membres
}

CEdge::pEdge CEdge::New(CNode::pNode pNode1, CNode::pNode pNode2, typeWeight weight)
{
	return std::make_shared<CEdge>(pNode1, pNode2, weight);  // RAS
}

CNode::pNode CEdge::GetFirstNode() const
{
	return m_spNodes[0]; // RAS
}

CNode::pNode CEdge::GetSecondNode() const
{
	return m_spNodes[1]; // RAS
}


typeWeight CEdge::GetWeight() const
{
	return m_Weight;  // RAS
}

bool CEdge::operator==(const CEdge& edge) const
{
	return m_Weight == edge.m_Weight && m_spNodes[0] == edge.m_spNodes[0] && m_spNodes[1] == edge.m_spNodes[1];
}

bool CEdge::operator==(const CEdge::pEdge& pEdge) const
{
	return (*this) == (*pEdge);
}

float CEdge::GetMilieuX() const
{
	return (m_spNodes[0]->GetX()+ m_spNodes[1]->GetX())/2;
}

float CEdge::GetMilieuY() const
{
	return (m_spNodes[0]->GetY() + m_spNodes[1]->GetY()) / 2;;
}

// ICI COMMENCE LE TP6 7 Ford Fulkerson *********************************************************************************


typeWeight CEdge::GetFlux() const  // A MODIFIER doit renvoyer le flux passant dans cette arete
{
	return m_Flux;
}

void CEdge::AddFlux(typeWeight n)  // A COMPLETER doit ajouter (si c'est possible) le flux � l'arete
{
	if ((m_Flux + n) <= m_Weight) {
		m_Flux += n;
	}
}

void CEdge::SubFlux(typeWeight n)  // A COMPLETER doit enlever (si c'est possible) le flux � l'arete
{
	if ((m_Flux - n) > 0) {
		m_Flux -= n;
	}
}
