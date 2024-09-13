#pragma once

#include "../inc/Graph/Graph.h"

#include <climits>
#include <algorithm> // std::sort
#include <list>
#include <utility>

void CGraph::AddNewNode(CNode::pNode pNode)
{
	//On initialise la valeur connexe à la valeur max + 1 pour etre sur qu'elle ne soit pas déjà utilisés.
	size_t max = 0;
	for (const auto& pNode : m_spNodes) {
		if (max < pNode->GetCompConn())
			max = pNode->GetCompConn();
	}
	pNode->SetCompConn(max+1);
	m_spNodes.insert(pNode);
}

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
	//On lance le programme pour recalculer les composante connexe
	ComputeComposanteConnexe();
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
	//On lance le programme pour recalculer les composante connexe
	ComputeComposanteConnexe();
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
		for (auto itpEdge = m_spEdges.begin(); itpEdge != m_spEdges.end();/* RIEN */) {
			if ((*itpEdge)->GetFirstNode() == (*itpNode) || (*itpEdge)->GetSecondNode() == (*itpNode))
				itpEdge = m_spEdges.erase(itpEdge);
			else
				itpEdge++;
		}
		// on enleve le noeud car il ne touche plus d arete
		m_spNodes.erase(itpNode);
	}
	ComputeComposanteConnexe();
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
		typeWeight n = 0;
		for (auto& pNode : m_spNodes) {
			pNode->SetCompConn(n);
			n++;
		}
	}


	// TP Noté : A MODIFIER
	typeWeight CGraph::ComputeWeight() const { 
		typeWeight rt = 0;
		for (auto& edges : m_spEdges) {
				rt += edges->GetWeight();
		}
		return rt;
	}

	void CGraph::Simplify() {
		// On met les arêtes dans un vecteur
		std::vector<CEdge::pEdge> vecEdges;
		for (auto const& pEdge : m_spEdges) {
			if (pEdge->GetFirstNode() != pEdge->GetSecondNode())
				vecEdges.push_back(pEdge);
		}
		// On trie le vecteur des arêtes par poids décroissant
		std::sort(vecEdges.begin(), vecEdges.end(), TriEdge());
		// On part juste des noeuds donc on enlève les arêtes
		ClearEdges();
		// pour chaque arête dans le vecteur trié
		for (auto const& pEdge : vecEdges) {
			ComputeComposanteConnexe();
			//Si les 2 points de l'arête ne font pas partie de la même composante connexe on ajoute l'arête à notre graphe
			if (pEdge->GetFirstNode()->GetCompConn() != pEdge->GetSecondNode()->GetCompConn()) {
				pEdge->GetFirstNode()->SetCompConn(pEdge->GetSecondNode()->GetCompConn());
				m_spEdges.insert(pEdge);
			}
		}

	};

	// TP Noté : A CREER
	void CGraph::FusionConnexe(CNode::pNode pNode1, CNode::pNode pNode2) {
		size_t connexe1 = pNode1->GetCompConn();
		size_t connexe2 = pNode2->GetCompConn();
		// Si les 2 noeuds sont de composante connexe différente
		if (connexe1 != connexe2) {
			for (auto const& pNode : m_spNodes) {
				// On va mettre tous les noeuds, ayant la valeur de composante connexe égal à la valeur du premier,  
				if (pNode->GetCompConn() == connexe1)
					// à la valeur de la  composante connexe du 2em
					pNode->SetCompConn(connexe2);
			}
		}
	};


	// TP Noté : A CREER
	void CGraph::ComputeComposanteConnexe() {
		// On met tous les noeuds à des valeurs de composante connexe différente
		// Par exemple on met les valeurs 0 1 2 3 4 5 ...
		unsigned int i = 0;
		for (auto const& pNode : m_spNodes) {
			pNode->SetCompConn(i);
			++i;
		}
		// Pour chaque arête on fait la fusionConnexe entre ses 2 noeuds
		for (auto const& pEdge : m_spEdges) {
			FusionConnexe(pEdge->GetFirstNode(), pEdge->GetSecondNode());
		}
	};