#pragma once

#include "Edge.h"
#include "Node.h"

#include <LibGraph2.h>

#include <memory>
#include <vector>
#include <set>

	// TODO :
	// TP 1 2 3 :
	// TODO : ajouter des Geteur sur les noeuds et ar�tes ainsi que leur nombre d'�l�ments
	// TP 1 2 3 : AddNewNode
	// TODO : ajouter une fonction qui ajoute un noeud
	// TP 1 2 3 : AddNewEdge
	// TODO : ajouter une fonction qui ajoute une ar�te 
	// TP 1 2 3 : RemoveEdge
	// TODO : ajouter une fonction qui enleve une ar�te 
	// TP 1 2 3 : RemoveNode
	// TODO : ajouter une fonction qui enleve un noeud
	// TP 1 2 3 : GetNodeFromName
	// TODO : Retourne le pointeur sur le noeud ayant le m�me nom ou nullptr si pas trouv�
	// TP 1 : Clear
	// TODO : Remet le graphe � z�ro 
	// TP 1 : ClearEdges
	// TODO : efface toutes les ar�tes 
	// TP 2 : GetNodeDegree
	// TODO : parcourir toutes les ar�tes pour compter combien de fois le noeud apparait
	// TP 2 : GetNodeNear
	// TODO : On cherche le noeud le plus proche du point(x,y)
	// TP 2 : GetEdgeNear
	// TODO : On cherche l arete la plus proche du point(x,y)
	// TP 4 5 : CheckNodesAreNeighbors
	// TODO : renvoie vrai si les 2 noeuds pass�s en param�tre sont voisins
class CGraph{

public:
	using pNodeSet = std::set<CNode::pNode>; // Alias sur un vecteur de noeud
	using pEdgeSet = std::set<CEdge::pEdge>; // Alias sur un vecteur d'ar�tes
	// TP 4 5 : On rajoute un alias sur un vecteur de pNode
	using  pNodeVector = std::vector<CNode::pNode>; // Alias sur un vecteur de noeud

protected:

	pEdgeSet m_spEdges;
	pNodeSet m_spNodes;

public:
	CGraph() {};

	std::size_t GetNumberOfEdges() const { return m_spEdges.size(); }
	std::size_t GetNumberOfNodes() const { return m_spNodes.size(); }
	const pNodeSet& GetNodes() const { return m_spNodes; }
	const pEdgeSet& GetEdges() const { return m_spEdges; }

	// ************ A Modifier dans le TP Not� : est susceptible de modifier les composantes connexes ***************
	void AddNewNode(CNode::pNode pNode);

	// ************ A Modifier dans le TP Not� : est susceptible de modifier les composantes connexes ***************
//   ATTENTION : on ne doit pas ajouter de boucle !!!!
	void AddNewEdge(CEdge::pEdge pEdge); 

	// ************ A Modifier dans le TP Not� : est susceptible de modifier les composantes connexes ***************
	void RemoveEdge(CEdge::pEdge pEdge);

	// ************ A Modifier dans le TP Not� : est susceptible de modifier les composantes connexes ***************
	void RemoveNode(CNode::pNode pNode); 

	CNode::pNode GetNodeFromName(const std::string& name) const;

	void Clear() { m_spEdges.clear(); m_spNodes.clear(); }

	// TP Not�  :  A MODIFIER
	// TODO : remettre les composantes connexes de tous les noeuds � 0  1 2 3 ...
	void ClearEdges();

	std::size_t GetNodeDegree(CNode::pNode pNode) const; 

	const CNode::pNode GetNodeNear(unsigned int x, unsigned int y) const;

	const CEdge::pEdge GetEdgeNear(unsigned int x, unsigned int y) const; 

	bool CheckNodesAreNeighbors(CNode::pNode pNode1, CNode::pNode pNode2) const; 

	/******************************************************************************************************************************************/

	// TP Not� :
	// TODO : retourne la somme du poids de toutes les ar�tes
	typeWeight ComputeWeight() const;

	// TP Not� :
	// TODO : fonction permettant de faire l'arbre de recouvrement de poids maximal
	void Simplify();

protected : 

	// Fonctions priv�es 
	
	// TP Not� :
	// TODO : fonction permettant de calculer les composantes connexes du graphe
	void ComputeComposanteConnexe();

	// TP Not� :
	// TODO : Fusion des composantes connexes
	void FusionConnexe(CNode::pNode pNode1, CNode::pNode pNode2);
};

