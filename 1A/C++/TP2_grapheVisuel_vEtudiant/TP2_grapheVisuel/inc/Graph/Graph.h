#pragma once
#include <LibGraph2.h>

#include "Edge.h"
#include "Node.h"

#include <set> // std::set
#include <algorithm> // std::sort
#include <list>

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

	CNode::pNode GetNodeFromName(const std::string& name) const; // renvoie le pNode ayant le même nom
	
	// ICI COMMENCE LE TP2

	pEdgeSet::iterator RemoveEdge(CEdge::pEdge pEdge); // renvoie l iterateur sur le successeur de pEdge après l avoir supprimé
	pNodeSet::iterator RemoveNode(CNode::pNode pNode); // renvoie l iterateur sur le successeur de pNode après avoir supprimé toutes les arêtes le touchant supprime le pNode

	const CNode::pNode GetNodeNear(unsigned int x, unsigned int y) const; // renvoie le pNode le plus proche du clic	
	const CEdge::pEdge GetEdgeNear(unsigned int x, unsigned int y) const; // renvoie le pEdge dont le clic est le plus proche du milieu de l arête
	
	

protected : 
	pEdgeSet m_spEdges;  // le set de pEdge
	pNodeSet m_spNodes; // le set de pNode

	// ICI COMMENCE LE TP2
public :

	void Clear(); // vide le set de pNode et le set de pEdge

	void ClearEdges();  // vide le set de pEdge (va servir pour créer le graphe complet)

	bool CheckNodesAreNeighbors(CNode::pNode pNode1, CNode::pNode pNode2) const; // renvoie vrai si les 2 noeuds appartiennent à une même arête
	
	void ColorFunction();

	const std::vector<CNode::pNode>& GetUncolored(std::vector<CNode::pNode>&) const;

	bool m_Oriented = false;

	CNode::pNode m_pNodeStart = nullptr;
	CNode::pNode m_pNodeEnd = nullptr;

public:

	using Chaine = std::list<CNode::pNode>; // Alias sur une liste d'arêtes (une chaine)

	void CreateExempleGraph() {
		SetOrientation(true);
		auto pNode1 = std::make_shared<CNode>("P0", 200, 250);
		AddNewNode(pNode1);
		auto pNode2 = std::make_shared<CNode>("P1", 400, 450);
		AddNewNode(pNode2);
		auto pNode3 = std::make_shared<CNode>("P2", 500, 50);
		AddNewNode(pNode3);
		auto pNode4 = std::make_shared<CNode>("P3", 700, 350);
		AddNewNode(pNode4);
		auto pNode5 = std::make_shared<CNode>("P4", 900, 150);
		AddNewNode(pNode5);
		auto pEdge6 = std::make_shared<CEdge>(pNode1, pNode2, 4);
		AddNewEdge(pEdge6);
		auto pEdge7 = std::make_shared<CEdge>(pNode1, pNode3, 3);
		AddNewEdge(pEdge7);
		auto pEdge8 = std::make_shared<CEdge>(pNode1, pNode5, 2);
		AddNewEdge(pEdge8);
		auto pEdge9 = std::make_shared<CEdge>(pNode2, pNode3, 1);
		AddNewEdge(pEdge9);
		auto pEdge10 = std::make_shared<CEdge>(pNode2, pNode4, 2);
		AddNewEdge(pEdge10);
		auto pEdge11 = std::make_shared<CEdge>(pNode3, pNode5, 5);
		AddNewEdge(pEdge11);
		auto pEdge12 = std::make_shared<CEdge>(pNode4, pNode5, 1);
		AddNewEdge(pEdge12);
	}

	bool IsOriented()const { return m_Oriented; }

	void SetOrientation(bool orientation) { m_Oriented = orientation; }

	// TODO : retourne le flux entrant du sommet d arrivée
	typeWeight MaxFlux() const;// A FAIRE

	// TODO : Rajouter les 2 accesseurs : 1 sur le noeud de départ et 1 sur le noeud d arrivée
	CNode::pNode GetNodeStart()const { return m_pNodeStart; }
	CNode::pNode GetNodeEnd()const { return m_pNodeEnd; }
	void SetNodeStart(CNode::pNode pNode) { m_pNodeStart = pNode; }
	void SetNodeEnd(CNode::pNode pNode) { m_pNodeEnd = pNode; }

	// TODO : fonction permettant de calculer le flux maximal arrivant sur le noeud d arrivée
	void OptimisationFF(); // A FAIRE // Modifie le graphe car change le flux de chaque arête !!!

protected:

	// TODO : 
	std::list<CEdge::pEdge> GetEdgesIn(CNode::pNode pNode)const;
	std::list<CEdge::pEdge> GetEdgesOut(CNode::pNode pNode)const;
	bool IsInChaine(CNode::pNode pNode, CGraph::Chaine chaine)const;

	// GetEdgeFromNodes renvoie l arête qui touche les 2 noeuds et un booléen sur son sens de parcours (vrai dans le sens de la flèche !!!)
	std::pair<CEdge::pEdge, bool> GetEdgeFromNodes(CNode::pNode pNode1, CNode::pNode pNode2)const;

	// GetAllChaine renvoie la liste de toutes les chaines (liste de noeuds) qui partents du départ et vont jusqu'à l'arrivée 
	std::list<CGraph::Chaine> GetAllChaine(CNode::pNode pNodeStart, CNode::pNode pNodeEnd)const;

	// GetListeEdgesFromChaine renvoie une liste d'arêtes avec leur sens de parcours (bool) à partir d'une chaine de noeuds
	std::list<std::pair<CEdge::pEdge, bool>> GetListeEdgesFromChaine(CGraph::Chaine chaine)const;
};
