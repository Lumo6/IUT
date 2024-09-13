#pragma once
#include <LibGraph2.h>

#include "Edge.h"
#include "Node.h"

#include <set> // std::set
#include <algorithm> // std::sort

class CGraph{
public:
	
	using pNodeSet = std::set<CNode::pNode>; // set contenant les pNode
	using pEdgeSet = std::set<CEdge::pEdge>; // set contenant les pEdge

	CGraph() {} // constructeur ne fait rien
	~CGraph() { Clear(); } // destructeur vide les sets

	const pNodeSet& GetNodes() const; // renvoie le set de pNode
	const pEdgeSet& GetEdges() const; // renvoie le set de pEdge

	void AddNewNode(CNode::pNode pNode);  // ajoute un pNode dans le set
	void AddNewEdge(CEdge::pEdge pEdge); // ajoute un pEdge dans le set

	CNode::pNode GetNodeFromName(const std::string& name) const; // renvoie le pNode ayant le m�me nom
	
	// ICI COMMENCE LE TP2

	pEdgeSet::iterator RemoveEdge(CEdge::pEdge pEdge); // renvoie l iterateur sur le successeur de pEdge apr�s l avoir supprim�
	pNodeSet::iterator RemoveNode(CNode::pNode pNode); // renvoie l iterateur sur le successeur de pNode apr�s avoir supprim� toutes les ar�tes le touchant supprime le pNode

	const CNode::pNode GetNodeNear(unsigned int x, unsigned int y) const; // renvoie le pNode le plus proche du clic	
	const CEdge::pEdge GetEdgeNear(unsigned int x, unsigned int y) const; // renvoie le pEdge dont le clic est le plus proche du milieu de l ar�te

	// TP 2 : TODO ajouter une fonction qui cr�e un graphe complet � partir des noeuds du graphe
	void CreateGraphFull();
protected : 
	pEdgeSet m_spEdges;  // le set de pEdge
	pNodeSet m_spNodes; // le set de pNode

	// ICI COMMENCE LE TP2

	void Clear(); // vide le set de pNode et le set de pEdge

	void ClearEdges();  // vide le set de pEdge (va servir pour cr�er le graphe complet)

	bool CheckNodesAreNeighbors(CNode::pNode pNode1, CNode::pNode pNode2) const; // renvoie vrai si les 2 noeuds appartiennent � une m�me ar�te
	
};
