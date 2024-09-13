#pragma once

#include "../inc/Graph/Graph.h"

#include <climits>
#include <algorithm> // std::sort
#include <list>
#include <utility>

	// TP 1 2 3 :
	// TODO : ajouter une fonction qui ajoute une ar�te 
	//         Attention de v�rifier que les 2 noeuds existe dans le graphe
// ************ A Modifier dans le TP Not� : est susceptible de modifier les composantes connexes ***************
//   ATTENTION : on ne doit pas ajouter de boucle !!!!
	void CGraph::AddNewEdge(CEdge::pEdge pEdge) {
		for (auto& pNode : pEdge->GetNodes())
			if (m_spNodes.count(pNode) == 0) // si cette ar�te r�f�rence un sommet non existant dans ce graphe
				return; // id�alement, un throw. 
		m_spEdges.insert(pEdge);
	}

	// TP 1 2 3 :
	// TODO : ajouter une fonction qui enleve une ar�te 
	// ************ A Modifier dans le TP Not� : est susceptible de modifier les composantes connexes ***************
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
	// il faut d'abord chercher toutes les ar�tes qui touchent ce noeud
	// puis il faut enlever ces ar�tes
	// enfin on enl�ve le noeud
	// ************ A Modifier dans le TP Not� : est susceptible de modifier les composantes connexes ***************
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
	// Retourne le pointeur sur le noeud ayant le m�me nom ou nullptr si pas trouv�
	CNode::pNode CGraph::GetNodeFromName(const std::string& name) const {
		// On parcourt le set de noeud et on renvoie celui qui a le bon nom
		for (auto& pNode : m_spNodes)
			if (pNode->GetName() == name)
				return pNode;
		// si non trouv� :
		return CNode::pNode(nullptr);
	}

	// TP 2 :
	// TODO : parcourir toutes les ar�tes pour compter combien de fois le noeud apparait
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
	// Pour chaque noeud on calcule la distance euclienne (au carr�) entre lui et le point(x,y)
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
	// TODO : renvoie vrai si les 2 noeuds pass�s en param�tre sont voisins
	bool CGraph::CheckNodesAreNeighbors(CNode::pNode pNode1, CNode::pNode pNode2) const {
		for (auto const& pEdge : m_spEdges)
			if ((pEdge->GetFirstNode() == pNode1 && pEdge->GetSecondNode() == pNode2) || (pEdge->GetFirstNode() == pNode2 && pEdge->GetSecondNode() == pNode1))
				return true;
		return false;
	}


	/******************************************************************************************************************************************/

	// TP Not� :  ATTENTION A Modifier : modifie les composantes connexes
	void CGraph::ClearEdges()
	{
		m_spEdges.clear();
	}


	// TP Not� : A MODIFIER
	typeWeight CGraph::ComputeWeight() const { return 0; }

	// TP Not� : A CREER
	// On enl�ve toutes les ar�tes qui bouclent sur elle_m�me
	// On met les ar�tes dans un vecteur
	// On trie le vecteur des ar�tes par poids d�croissant
	// On part juste des noeuds donc on enl�ve les ar�tes
	// pour chaque ar�te dans le vecteur tri�
	//             Si les 2 points de l'ar�te ne font pas partie de la m�me composante connexe on ajoute l'ar�te � notre graphe
	void CGraph::Simplify() {}

	// TP Not� : A CREER
	// Si les 2 noeuds sont de composante connexe diff�rente
	// On va mettre tous les noeuds, ayant la valeur de composante connexe �gal � la valeur du premier,  
	// � la valeur de la  composante connexe du 2em
	void CGraph::FusionConnexe(CNode::pNode pNode1, CNode::pNode pNode2) {}


	// TP Not� : A CREER
	// On met tous les noeuds � des valeurs de composante connexe diff�rente
	// Par exemple on met les valeurs 0 1 2 3 4 5 ...
	// Pour chaque ar�te on fait la fusionConnexe entre ses 2 noeuds
	void CGraph::ComputeComposanteConnexe() {}