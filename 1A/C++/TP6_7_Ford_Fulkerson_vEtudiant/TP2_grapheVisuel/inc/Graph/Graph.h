#pragma once
#include <LibGraph2.h>

#include "Edge.h"
#include "Node.h"

#include <set> // std::set
#include <algorithm> // std::sort
#include <list> // std::list

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
	void AddNewEdge(CNode::pNode pNode1, CNode::pNode pNode2, typeWeight weight); // ajoute un pEdge à partir des données dans le set

	CNode::pNode GetNodeFromName(const std::string& name) const; // renvoie le pNode ayant le même nom

	pEdgeSet::iterator RemoveEdge(CEdge::pEdge pEdge); // renvoie l iterateur sur le successeur de pEdge après l avoir supprimé
	pNodeSet::iterator RemoveNode(CNode::pNode pNode); // renvoie l iterateur sur le successeur de pNode après avoir supprimé toutes les arêtes le touchant supprime le pNode

	const CNode::pNode GetNodeNear(unsigned int x, unsigned int y) const; // renvoie le pNode le plus proche du clic	
	const CEdge::pEdge GetEdgeNear(unsigned int x, unsigned int y) const; // renvoie le pEdge dont le clic est le plus proche du milieu de l arête
	
protected : 
	pEdgeSet m_spEdges;  // le set de pEdge
	pNodeSet m_spNodes; // le set de pNode

	void Clear(); // vide le set de pNode et le set de pEdge

	void ClearEdges();  // vide le set de pEdge (va servir pour créer le graphe complet)

	bool CheckNodesAreNeighbors(CNode::pNode pNode1, CNode::pNode pNode2) const; // renvoie vrai si les 2 noeuds appartiennent à une même arête
	

/**************************                   DEBUT TP 6 7                 **********************************************************************/


	// TP 6 7 : par défaut le graphe n est pas orienté mais pour ce TP il faut le rendre orienté
	bool m_Oriented = true;

	// TODO : ajouter 2 données membres représentant des pointeurs sur le noeud de départ et le noeud d arrivée
	CNode::pNode m_pNodeStart = nullptr;
	CNode::pNode m_pNodeEnd = nullptr;

public:

	// TP 6 7 : AJout d'un alias : une chaine c'est une liste de sommet
	using Chaine = std::list<CNode::pNode>; // Alias sur une liste d'arêtes (une chaine)

	// TP 6 7 :
	// TODO :  Fonction qui ajoute un graphe d'exemple qui va bien
	void CreateExempleGraph() {
		SetOrientation(true);
		auto pNode1 = std::make_shared<CNode>("P0",300, 300);
		AddNewNode(pNode1);
		auto pNode2 = std::make_shared<CNode>("P1",400, 450);
		AddNewNode(pNode2);
		auto pNode3 = std::make_shared<CNode>("P2",500, 50);
		AddNewNode(pNode3);
		auto pNode4 = std::make_shared<CNode>("P3",700, 350);
		AddNewNode(pNode4);
		auto pNode5 = std::make_shared<CNode>("P4", 900, 150);
		AddNewNode(pNode5);
		auto pNode6 = std::make_shared<CNode>("P5", 700, 50);
		AddNewNode(pNode6);
		auto pNode7 = std::make_shared<CNode>("P6", 100, 500);
		AddNewNode(pNode7);
		auto pNode8 = std::make_shared<CNode>("P7", 1000, 50);
		AddNewNode(pNode8);
		auto pNode9 = std::make_shared<CNode>("P8", 600, 200);
		AddNewNode(pNode9);
		auto pNode10 = std::make_shared<CNode>("P9", 200, 150);
		AddNewNode(pNode10);
		/*AddNewEdge(pNode1, pNode2, 4);
		AddNewEdge(pNode1, pNode3, 3);
		AddNewEdge(pNode1, pNode5, 2);
		AddNewEdge(pNode2, pNode3, 1);
		AddNewEdge(pNode2, pNode4, 2);
		AddNewEdge(pNode3, pNode5, 5);
		AddNewEdge(pNode4, pNode5, 1);*/
		AddNewEdge(pNode10, pNode3, 7);
		AddNewEdge(pNode3, pNode6, 14);
		AddNewEdge(pNode8, pNode6, 9);
		AddNewEdge(pNode5, pNode8, 5);
		AddNewEdge(pNode7, pNode10, 2);
		AddNewEdge(pNode2, pNode7, 5);
		AddNewEdge(pNode10, pNode1, 20);
		AddNewEdge(pNode1, pNode7, 19);
		AddNewEdge(pNode2, pNode1, 19);
		AddNewEdge(pNode4, pNode2, 3);
		AddNewEdge(pNode5, pNode4, 13);
		AddNewEdge(pNode1, pNode3, 6);
		AddNewEdge(pNode9, pNode1, 14);
		AddNewEdge(pNode6, pNode9, 12);
		AddNewEdge(pNode9, pNode8, 8);
		AddNewEdge(pNode5, pNode9, 6);
		AddNewEdge(pNode9,pNode4, 14);
		AddNewEdge(pNode2, pNode9, 13);

	}

	// TP 6 7 :
	// TODO : fonction permettant de savoir si le graphe est orienté
	bool IsOriented()const { return m_Oriented; } 

	// TP 6 7 :
	// TODO : fonction permettant de changer l'orientation du graphe
	void SetOrientation(bool orientation) { m_Oriented = orientation; } 

	// TP 6 7 :
	// TODO : retourne le flux entrant du sommet d arrivée
	typeWeight MaxFlux() const;// A FAIRE

	// TP 6 7 :
	// TODO : Rajouter les 2 accesseurs : 1 sur le noeud de départ et 1 sur le noeud d arrivée
	CNode::pNode GetNodeStart()const { return m_pNodeStart; }
	CNode::pNode GetNodeEnd()const { return m_pNodeEnd; }
	void SetNodeStart(CNode::pNode pNode) { m_pNodeStart = pNode; }
	void SetNodeEnd(CNode::pNode pNode) { m_pNodeEnd = pNode; }

	// TP 6 7 :
	// TODO : fonction permettant de calculer le flux maximal arrivant sur le noeud d arrivée
	void OptimisationFF(); // A FAIRE // Modifie le graphe car change le flux de chaque arête !!!

protected:

	// Fonctions protégées 

	// TP 6 7 :
	// TODO : 
	std::list<CEdge::pEdge> GetEdgesIn(CNode::pNode pNode)const;
	std::list<CEdge::pEdge> GetEdgesOut(CNode::pNode pNode)const;
	bool IsInChaine(CNode::pNode pNode, CGraph::Chaine chaine)const;



	// TP 6 7 : Fonctions privées que je vous donne
	// GetEdgeFromNodes renvoie l arête qui touche les 2 noeuds et un booléen sur son sens de parcours (vrai dans le sens de la flèche !!!)
	std::pair<CEdge::pEdge, bool> GetEdgeFromNodes(CNode::pNode pNode1, CNode::pNode pNode2)const;

	// GetAllChaine renvoie la liste de toutes les chaines (liste de noeuds) qui partents du départ et vont jusqu'à l'arrivée 
	std::list<CGraph::Chaine> GetAllChaine(CNode::pNode pNodeStart, CNode::pNode pNodeEnd)const;

	// GetListeEdgesFromChaine renvoie une liste d'arêtes avec leur sens de parcours (bool) à partir d'une chaine de noeuds
	std::list<std::pair<CEdge::pEdge, bool>> GetListeEdgesFromChaine(CGraph::Chaine chaine)const;
};
