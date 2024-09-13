#include "Graph/Graph.h"
#include <random> // std::random_device, ...

// TP 2 3  et 4 : 
// TODO : GetNodes			: renvoie le set de pNode
// TODO : GetEdges			: renvoie le set de pEdge
// TODO : AddNewNode		: ajoute un pNode dans le set de pNode
// TODO : AddNewEdge		: ajoute un pEdge dans le set de pEdge
// TODO : RemoveEdge		: renvoie l iterateur sur le successeur de pEdge après l avoir supprimé
// TODO : RemoveNode		: supprime le noeud après avoir supprimé toutes les arêtes le touchant
// TODO : GetNodeFromName	: renvoie le pNode ayant le même nom (nullptr si pas trouvé)
// TODO : GetNodeNear		: renvoie le noeud le plus proche du point(x,y)
//							: On initialise une distanceMin au max des float : FLT_MAX
//							: Pour chaque noeud on calcule la distance euclienne entre lui et le point(x,y)
//							: Si cette distance est inferieure a la distance min
//							: On met a jour la nouvelle distance et le pointeur sur le noeud le plus proche
// TODO : GetEdgeNear		: renvoie l arete la plus proche du point(x,y)
//							: On initialise une distanceMin au max des float : FLT_MAX
//							: Pour chaque arete on calcule la distance euclienne entre le milieu de l arete et le point(x,y)
//							: Si cette distance est inferieure a la distance min
//							: On met a jour la nouvelle distance et le pointeur sur l arete la plus proche
// 
// **************************** FIN FONCTIONS PUBLIQUES
// 
// TODO : Clear					 : vide le set de pNode et le set de pEdge
// TODO : ClearEdges			 : vide le set de pEdge (va servir pour créer le graphe complet)
// TODO : CheckNodesAreNeighbors : renvoie vrai si les 2 noeuds appartiennent à une même arête

const CGraph::pNodeSet& CGraph::GetNodes() const
{
	return m_spNodes; // RAS
}

const CGraph::pEdgeSet& CGraph::GetEdges() const
{
	return m_spEdges; // RAS
}

void CGraph::AddNewNode(CNode::pNode pNode)
{
	m_spNodes.insert(pNode);
}

void CGraph::AddNewEdge(CEdge::pEdge pEdge)
{
	m_spEdges.insert(pEdge);
}

CGraph::pEdgeSet::iterator CGraph::RemoveEdge(CEdge::pEdge pEdge)
{
	// On cherche l arete dans le set d arete
	auto itpEdge = std::find(m_spEdges.begin(), m_spEdges.end(), pEdge);
	 // Si elle est dans le set 
		  // on l enleve
	if (itpEdge != m_spEdges.end())
		itpEdge = m_spEdges.erase(itpEdge);
	// else warning dans la console ?
	return itpEdge; // on renvoie l iterateur sur le successeur de pEdge dans le set (ou la fin du set)
}

CGraph::pNodeSet::iterator CGraph::RemoveNode(CNode::pNode pNode)
{
	// On cherche le noeud dans le set de noeud
	auto itpNode = std::find(m_spNodes.begin(), m_spNodes.end(), pNode);
	// Si ce noeud existe
	if (itpNode != m_spNodes.end())
	{
		// On enleve toutes les aretes touchant ce noeud
		for (auto itpEdge = m_spEdges.begin(); itpEdge != m_spEdges.end();/* RIEN */)
		{
			if ((*itpEdge)->GetFirstNode() == (*itpNode) || (*itpEdge)->GetSecondNode() == (*itpNode))
				itpEdge = m_spEdges.erase(itpEdge);
			else
				itpEdge++;
		}
		// on enleve le noeud car il ne touche plus d arete
		itpNode = m_spNodes.erase(itpNode);
	}
	return itpNode;
}

CNode::pNode CGraph::GetNodeFromName(const std::string& name) const
{
	// On parcourt le set de noeud et on renvoie celui qui a le bon nom
	for (auto& pNode : m_spNodes)
		if (pNode->GetName() == name)
			return pNode;
	// si non trouvé : on devrait faire une gestion d erreur
	return CNode::pNode(nullptr);
}



// ICI COMMENCE LE TP2 ***************************************************************************



const CNode::pNode CGraph::GetNodeNear(unsigned int x, unsigned int y) const
{
	float distMin = FLT_MAX; // la distance min  est initialisée à l'infini (pour les float)
	CNode::pNode pNodeNear = nullptr;
	// A FAIRE : 
	// On parcourt les noeuds du graphe
	 // on cherche le noeud le plus proche du clic
	float dist_pNode;
	for (const auto &pNode : m_spNodes)
	{
		dist_pNode = (pNode->GetX() - x) * (pNode->GetX() - x) + (pNode->GetY() - y) * (pNode->GetY() - y);
		if (dist_pNode < distMin)
		{
			pNodeNear = pNode;
			distMin = dist_pNode;
		}
	}
	return pNodeNear;
}

const CEdge::pEdge CGraph::GetEdgeNear(unsigned int x, unsigned int y) const
{
	float distMin = FLT_MAX; // la distance min  est initialisée à l'infini (pour les float)
	CEdge::pEdge pEdgeNear = nullptr;
	// A FAIRE :
	// ON parcourt les arêtes du graphe 
	  // On cherche le milieu de l'arete le plus proche du clic
	float dist_pEdge;
	for (const auto& pEdge : m_spEdges)
	{
		dist_pEdge = (pEdge->GetMilieuX() - x) * (pEdge->GetMilieuX() - x) + (pEdge->GetMilieuY() - y) * (pEdge->GetMilieuY() - y);
		if (dist_pEdge < distMin)
		{
			pEdgeNear = pEdge;
			distMin = dist_pEdge;
		}
	}
	return pEdgeNear;
}

void CGraph::CreateGraphFull()
{
	std::random_device rd;
	std::default_random_engine gen(rd());
	ClearEdges();
	for(auto const & pNode1 : m_spNodes)
		for (auto const& pNode2 : m_spNodes)
			if (pNode1 < pNode2)
			{
				typeWeight weight = std::uniform_int_distribution<>{ 1, 9 }(gen);
				AddNewEdge(std::make_shared <CEdge>(pNode1, pNode2, weight));
			}
}

/********************** FIN DES FONCTION PUBLIQUES DEBUT DES FONCTIONS PROTEGEES *************************/


void CGraph::Clear()
{
	// on vide le conteneur des aretes
	// on vide le conteneur des noeuds
	m_spEdges.clear();
	m_spNodes.clear();
}

void CGraph::ClearEdges()
{
	// on vide le conteneur des aretes
	m_spEdges.clear();
}

bool CGraph::CheckNodesAreNeighbors(CNode::pNode pNode1, CNode::pNode pNode2) const
{
	// On cherche si 2 noeuds sont reliés (appartiennent à la même arête)
	for (const auto& pEdge : m_spEdges)
		if ((pEdge->GetFirstNode() == pNode1 and pEdge->GetSecondNode() == pNode2) or (pEdge->GetFirstNode() == pNode2 and pEdge->GetSecondNode() == pNode1))
			return true;
	return false;
}
