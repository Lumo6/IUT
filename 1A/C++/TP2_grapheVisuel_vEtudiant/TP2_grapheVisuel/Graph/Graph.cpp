#include "Graph/Graph.h"
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <functional>

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
	pEdge->GetFirstNode()->AddDegre(1);
	pEdge->GetSecondNode()->AddDegre(1);
}

CGraph::pEdgeSet::iterator CGraph::RemoveEdge(CEdge::pEdge pEdge)
{
	// On cherche l arete dans le set d arete
	auto itpEdge = std::find(m_spEdges.begin(), m_spEdges.end(), pEdge);
	 // Si elle est dans le set 
		  // on l enleve
	if (itpEdge != m_spEdges.end()) {
		(*itpEdge)->GetFirstNode()->SubDegre(1);
		(*itpEdge)->GetSecondNode()->SubDegre(1);
		itpEdge = m_spEdges.erase(itpEdge);
	}
		
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
		for (auto itpEdge = m_spEdges.begin(); itpEdge != m_spEdges.end(); )
		{
			if ((*itpEdge)->GetFirstNode() == (*itpNode) || (*itpEdge)->GetSecondNode() == (*itpNode)) {
				itpEdge = m_spEdges.erase(itpEdge);
				if ((*itpEdge)->GetFirstNode() == (*itpNode)) (*itpEdge)->GetSecondNode()->SubDegre(1);
				else (*itpEdge)->GetFirstNode()->SubDegre(1);
			}
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
	for (const auto& Pnode : m_spNodes) {
		float distpNode = sqrt((x - Pnode->GetX()) * (x - Pnode->GetX()) + (y - Pnode->GetY()) * (y - Pnode->GetY()));
		if (distpNode < distMin) {
			distMin = distpNode;
			pNodeNear = Pnode;
		}
	}
	// A FAIRE : 
	// On parcourt les noeuds du graphe
	 // on cherche le noeud le plus proche du clic

	return pNodeNear;
}

const CEdge::pEdge CGraph::GetEdgeNear(unsigned int x, unsigned int y) const
{
	float distMin = FLT_MAX; // la distance min  est initialisée à l'infini (pour les float)
	CEdge::pEdge pEdgeNear = nullptr;
	for (const auto& Pedge : m_spEdges) {
		float dispEdge = sqrt((x - Pedge->GetMilieuX()) * (x - Pedge->GetMilieuX()) + (y - Pedge->GetMilieuY()) * (y - Pedge->GetMilieuY()));
		if (dispEdge < distMin) {
			distMin = dispEdge;
			pEdgeNear=Pedge;
		}
	}
	// A FAIRE :
	// ON parcourt les arêtes du graphe 
	  // On cherche le milieu de l'arete le plus proche du clic

	return pEdgeNear;
}

/********************** FIN DES FONCTION PUBLIQUES DEBUT DES FONCTIONS PROTEGEES *************************/


void CGraph::Clear()
{
	m_spEdges.clear();
	m_spNodes.clear();
	// on vide le conteneur des aretes
	// on vide le conteneur des noeuds
}

void CGraph::ClearEdges()
{
	m_spEdges.clear();
	// on vide le conteneur des aretes
}

bool CGraph::CheckNodesAreNeighbors(CNode::pNode pNode1, CNode::pNode pNode2) const
{
	// On cherche si 2 noeuds sont reliés (appartiennent à la mêm arête)
	for (const auto& pedge : m_spEdges) {
		if (pedge->GetFirstNode() == pNode1 && pedge->GetSecondNode() == pNode2 || pedge->GetFirstNode() == pNode2 && pedge->GetSecondNode() == pNode1) {
			return true;
		}
	}
	return false;
}

bool tri(CNode::pNode i, CNode::pNode j) { return (i->GetDegre() < j->GetDegre()); }

void CGraph::ColorFunction()
{
	std::vector<CNode::pNode> uncolored;
	for (const auto& pNode : m_spNodes) {
		pNode->SetColor(-1);
	}
	uncolored = GetUncolored(uncolored);
	int color = 0;
	std::sort(uncolored.begin(), uncolored.end(), tri);
	while (!uncolored.empty()) {
		std::vector<CNode::pNode> coloredtemp;
		CNode::pNode temp = uncolored.back();
		uncolored.pop_back();
		temp->SetColor(color);
		coloredtemp.push_back(temp);
		for (size_t i = 0; i < uncolored.size(); ) {
			bool Voisin = false;
			for (size_t j = 0; j < coloredtemp.size(); j++) {
				if (uncolored[i]->GetColor() == -1 && CheckNodesAreNeighbors(coloredtemp[j], uncolored[i])) {
					Voisin = true;
					break;
				}
			}
			if (!Voisin) {
				uncolored[i]->SetColor(color);
				coloredtemp.push_back(uncolored[i]);
				uncolored.erase(uncolored.begin() + i);
			}
			else {
				i++;
			}
		}
		color++;
	}
}

const std::vector<CNode::pNode>& CGraph::GetUncolored(std::vector<CNode::pNode>& uncolored) const
{
	for (const auto& pNode : m_spNodes) {
		if (pNode->GetColor() == -1) uncolored.push_back(pNode);
	}
	return uncolored;
}

typeWeight CGraph::MaxFlux() const
{
	typeWeight Max = 0;
	for (auto pEdge : m_spEdges) {
		if (pEdge->GetSecondNode() == GetNodeEnd()) {
			Max += pEdge->GetFlux();
		}
	}
	return typeWeight();
}

// TODO : Attention ceci est la fonction la plus difficile à faire en dernier !!!!
// On parcourt la liste des chaines commencant par le noeud de départ et finissant par le noeud d'arrivée
// Pour chaque chaine on parcourt la liste des aretes avec leur orientation
//                         ET on cherche si c'est une chaine améliorante (le minimum de flux de chaque arête est > 0 (strictement)
//                         SI elle améliore on ajoute ce fluxAmeliorant aux arêtes dans le bon sens (true)
//                                          on enlève ce fluxAmeliorant aux arêtes dans le mauvais sens (false)
void CGraph::OptimisationFF() {
	GetNodeStart()->SetColor(1);
	GetNodeEnd()->SetColor(0);
	for (const auto& pEdge : GetEdges()) {
		if (pEdge->GetSecondNode() == GetNodeStart() || pEdge->GetFirstNode() == GetNodeEnd()) {
			RemoveEdge(pEdge);
		}
	}
	std::list<CGraph::Chaine> chaines = GetAllChaine(GetNodeStart(), GetNodeEnd());
	for (const auto& pchaine : chaines) {
		bool amelio = true;
		std::list<std::pair<CEdge::pEdge, bool>> Edges = GetListeEdgesFromChaine(pchaine);
		typeWeight Min = Edges.front().first->GetWeight() - Edges.front().first->GetFlux();
		for (const auto& pEdge : Edges) {
			if (pEdge.first->GetWeight() - pEdge.first->GetFlux() <= 0) {
				amelio = false;
			}
			else if (Min > pEdge.first->GetWeight() - pEdge.first->GetFlux()) {
				Min = pEdge.first->GetWeight() - pEdge.first->GetFlux();
				}
		}
		if (amelio) {
			for (const auto& pEdge : Edges) {
				pEdge.first->AddFlux(Min);
			}
		}
	}

}

std::list<CEdge::pEdge> CGraph::GetEdgesIn(CNode::pNode pNode) const
{
	std::list<CEdge::pEdge> list;
	for (const auto& pEdge : m_spEdges) {
		if (pEdge->GetSecondNode() == pNode) list.push_back(pEdge);
	}
	return list;
}

std::list<CEdge::pEdge> CGraph::GetEdgesOut(CNode::pNode pNode) const
{
	std::list<CEdge::pEdge> list;
	for (const auto& pEdge : m_spEdges) {
		if (pEdge->GetFirstNode() == pNode) list.push_back(pEdge);
	}
	return list;	
}

bool CGraph::IsInChaine(CNode::pNode pNode, CGraph::Chaine chaine) const
{
	return false;
}

std::pair<CEdge::pEdge, bool> CGraph::GetEdgeFromNodes(CNode::pNode pNode1, CNode::pNode pNode2) const
{
	for (const auto& pEdge : m_spEdges) {
		if (pEdge->GetFirstNode() == pNode1 && pEdge->GetSecondNode() == pNode2) return std::pair<CEdge::pEdge, bool>(pEdge, true);
		else if(pEdge->GetFirstNode() == pNode2 && pEdge->GetSecondNode() == pNode1) return std::pair<CEdge::pEdge, bool>(pEdge, false);
	}
	return std::pair<CEdge::pEdge, bool>(nullptr,false);
}

std::list<CGraph::Chaine> CGraph::GetAllChaine(CNode::pNode pNodeStart, CNode::pNode pNodeEnd) const
{
	std::list<CGraph::Chaine>	Chaines;

	if (pNodeStart == pNodeEnd)
	{
		CGraph::Chaine chaine;
		chaine.push_back(pNodeStart);
		Chaines.push_back(chaine);
		return Chaines;
	}

	std::set<CNode::pNode> visited;

	std::function<void(CNode::pNode, CGraph::Chaine)> findChains = [&](CNode::pNode currentNode, CGraph::Chaine currentChain) {
		currentChain.push_back(currentNode);

		visited.insert(currentNode);

		if (currentNode == pNodeEnd)
		{
			Chaines.push_back(currentChain);
		}
		else
		{
			for (const auto& edge : GetEdgesOut(currentNode))
			{
				CNode::pNode nextNode = edge->GetSecondNode();

				if (visited.find(nextNode) == visited.end())
				{
					findChains(nextNode, currentChain);
				}
			}
		}

		currentChain.pop_back();
		visited.erase(currentNode);
	};

	CGraph::Chaine ChaineInitiale;
	findChains(pNodeStart, ChaineInitiale);

	return Chaines;
}

std::list<std::pair<CEdge::pEdge, bool>> CGraph::GetListeEdgesFromChaine(CGraph::Chaine chaine) const
{
	std::list<std::pair<CEdge::pEdge, bool>> listEdges;
	for (const auto& pEdge : m_spEdges) {
		bool found = false;
		bool sens = false;
		for (const auto& node : chaine) {
			if (pEdge->GetFirstNode() == node || pEdge->GetSecondNode() == node) {
				found = true;
				for (const auto& pNode : chaine) {
					if (pNode == pEdge->GetFirstNode()) {
						sens = true;
						break;
					}
					else if (pNode == pEdge->GetSecondNode()) {
						sens = false;
						break;
					}
				}
				break;
			}
		}
		if (found) {
			listEdges.emplace_back(pEdge, sens);
		}
	}
	return listEdges;
}
