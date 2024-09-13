#pragma once

#include "../inc/Graph/Graph.h"

#include <climits>
#include <algorithm> // std::sort
#include <list>
#include <utility>

	// TP 1 2 3 :
	// TODO : ajouter une fonction qui ajoute une arête 
	//         Attention de vérifier que les 2 noeuds existe dans le graphe
// ************ A Modifier dans le TP Noté : est susceptible de modifier les composantes connexes ***************
//   ATTENTION : on ne doit pas ajouter de boucle !!!!
	void CGraph::AddNewEdge(CEdge::pEdge pEdge) {
		for (auto& pNode : pEdge->GetNodes())
			if (m_spNodes.count(pNode) == 0) // si cette arête référence un sommet non existant dans ce graphe
				return; // idéalement, un throw. 
		m_spEdges.insert(pEdge);
	}

	// TP 1 2 3 :
	// TODO : ajouter une fonction qui enleve une arête 
	// ************ A Modifier dans le TP Noté : est susceptible de modifier les composantes connexes ***************
	void CGraph::RemoveEdge(CEdge::pEdge pEdge) {
		// On cherche l'arete dans le set d arete
		auto itpEdge = std::find(m_spEdges.begin(), m_spEdges.end(), pEdge);
		if (itpEdge != m_spEdges.end())
			m_spEdges.erase(itpEdge);
		// else warning dans la console ?
	}

	// TP 1 2 3 :
	// TODO : ajouter une fonction qui enleve un noeud
	//      : ATTENTION c'est la fonction la plus complexe :
	// il faut d'abord chercher toutes les arêtes qui touchent ce noeud
	// puis il faut enlever ces arêtes
	// enfin on enlève le noeud
	// ************ A Modifier dans le TP Noté : est susceptible de modifier les composantes connexes ***************
	void CGraph::RemoveNode(CNode::pNode pNode) {
		// On cherche le noeud dans le set de noeud
		auto itpNode = std::find(m_spNodes.begin(), m_spNodes.end(), pNode);
		// Si ce noeud existe
		if (itpNode != m_spNodes.end()) {
			// On enleve toutes les aretes touchant ce noeud
			for (auto itpEdge = m_spEdges.begin(); itpEdge != m_spEdges.end();/* RIEN */ ){
				if ((*itpEdge)->GetFirstNode() == (*itpNode) || (*itpEdge)->GetSecondNode() == (*itpNode))
					itpEdge = m_spEdges.erase(itpEdge);
				else
					itpEdge++;
			}
			// on enleve le noeud car il ne touche plus d arete
			m_spNodes.erase(itpNode);
		}
	}

	// TP 1 2 3 :
	// TODO :
	// Retourne le pointeur sur le noeud ayant le même nom ou nullptr si pas trouvé
	CNode::pNode CGraph::GetNodeFromName(const std::string& name) const {
		// On parcourt le set de noeud et on renvoie celui qui a le bon nom
		for (auto& pNode : m_spNodes)
			if (pNode->GetName() == name)
				return pNode;
		// si non trouvé :
		return CNode::pNode(nullptr);
	}

	// TP 2 :
	// TODO : parcourir toutes les arêtes pour compter combien de fois le noeud apparait
	std::size_t CGraph::GetNodeDegree(CNode::pNode pNode) const {
		std::size_t countDegree = 0;
		// Pour chaque arete si elle touche le noeud on incremente le degre
		for (auto const& pEdge : m_spEdges) {
			if (pEdge->GetFirstNode() == pNode)
				++countDegree;
			if (pEdge->GetSecondNode() == pNode)
				++countDegree;
		}
		return countDegree;
	}

	// TP 2 :
	// TODO : On cherche le noeud le plus proche du point(x,y)
	// On initialise une distanceMin au max des float : FLT_MAX
	// Pour chaque noeud on calcule la distance euclienne (au carré) entre lui et le point(x,y)
	// Si cette distance est inferieure a la distance min
	//       On met a jour la nouvelle distance et le pointeur sur le noeud le plus proche
	const CNode::pNode CGraph::GetNodeNear(unsigned int x, unsigned int y) const {
		float distMin = FLT_MAX; // max de distance 
		float dist; // distance du point aux parametres
		CNode::pNode pNodeNear = nullptr;
		for (auto const& pNode : m_spNodes) {// on cherche le noeud le plus proche du clic
			LibGraph2::CPoint node(pNode->GetX(), pNode->GetY());
			dist = (node.m_fX - x) * (node.m_fX - x) + (node.m_fY - y) * (node.m_fY - y);
			if (dist < distMin) {
				distMin = dist;
				pNodeNear = pNode;
			}
		}
		return pNodeNear;
	}

	// TP 2 :
	// TODO : On cherche l arete la plus proche du point(x,y)
// On initialise une distanceMin au max des float : FLT_MAX
// Pour chaque arete on calcule la distance euclienne entre le milieu de l arete et le point(x,y)
// Si cette distance est inferieure a la distance min
//       On met a jour la nouvelle distance et le pointeur sur l arete la plus proche
	const CEdge::pEdge CGraph::GetEdgeNear(unsigned int x, unsigned int y) const {
		float distMin = FLT_MAX; // max de distance 
		float dist; // distance du point aux parametres
		CEdge::pEdge pEdgeNear = nullptr;
		for (auto const& pEdge : m_spEdges) { // On cherche le milieu de l'arete le plus proche du clic
			LibGraph2::CPoint milieu(pEdge->GetMilieuX(), pEdge->GetMilieuY());
			dist = (milieu.m_fX - x) * (milieu.m_fX - x) + (milieu.m_fY - y) * (milieu.m_fY - y);
			if (dist < distMin) {
				distMin = dist;
				pEdgeNear = pEdge;
			}
		}
		return pEdgeNear;
	}

	// TP 4 5 :
	// TODO : renvoie vrai si les 2 noeuds passés en paramêtre sont voisins
	bool CGraph::CheckNodesAreNeighbors(CNode::pNode pNode1, CNode::pNode pNode2) const {
		for (auto const& pEdge : m_spEdges)
			if ((pEdge->GetFirstNode() == pNode1 && pEdge->GetSecondNode() == pNode2) || (pEdge->GetFirstNode() == pNode2 && pEdge->GetSecondNode() == pNode1))
				return true;
		return false;
	}


	/******************************************************************************************************************************************/

	// TP Noté :  ATTENTION A Modifier : modifie les composantes connexes
	void CGraph::ClearEdges()
	{
		m_spEdges.clear();
	}


	// TP Noté : A MODIFIER
	typeWeight CGraph::ComputeWeight() const { return 0; }

	// TP Noté : A CREER
	// On enlève toutes les arêtes qui bouclent sur elle_même
	// On met les arêtes dans un vecteur
	// On trie le vecteur des arêtes par poids décroissant
	// On part juste des noeuds donc on enlève les arêtes
	// pour chaque arête dans le vecteur trié
	//             Si les 2 points de l'arête ne font pas partie de la même composante connexe on ajoute l'arête à notre graphe
	void CGraph::Simplify() {}

	// TP Noté : A CREER
	// Si les 2 noeuds sont de composante connexe différente
	// On va mettre tous les noeuds, ayant la valeur de composante connexe égal à la valeur du premier,  
	// à la valeur de la  composante connexe du 2em
	void CGraph::FusionConnexe(CNode::pNode pNode1, CNode::pNode pNode2) {}


	// TP Noté : A CREER
	// On met tous les noeuds à des valeurs de composante connexe différente
	// Par exemple on met les valeurs 0 1 2 3 4 5 ...
	// Pour chaque arête on fait la fusionConnexe entre ses 2 noeuds
	void CGraph::ComputeComposanteConnexe() {}