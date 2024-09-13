#include "Graph/Graph.h"

// TP 6 et 7 : 

// Fonctions publiques 

// TODO : Ajouter la somme de tous les flux des arêtes entrantes
typeWeight CGraph::MaxFlux() const
{
	typeWeight rt = 0;
	for(auto& edges:m_spEdges){
		if (edges->GetSecondNode() == m_pNodeEnd) {
			rt += edges->GetFlux();
		}
	}
	return rt;
}

// TODO : Attention ceci est la fonction la plus difficile à faire en dernier !!!!
// On parcourt la liste des chaines commencant par le noeud de départ et finissant par le noeud d'arrivée
// Pour chaque chaine on parcourt la liste des aretes avec leur orientation
//                         ET on cherche si c'est une chaine améliorante (le minimum de flux de chaque arête est > 0 (strictement)
//                         SI elle améliore on ajoute ce fluxAmeliorant aux arêtes dans le bon sens (true)
//                                          on enlève ce fluxAmeliorant aux arêtes dans le mauvais sens (false)
void CGraph::OptimisationFF()
{
	for (auto it = m_spEdges.begin(); it != m_spEdges.end();) {
		if (((*it)->GetSecondNode() == GetNodeStart()) || (*it)->GetFirstNode() == GetNodeEnd()) {
			it = RemoveEdge(*it);
		}
		else {
			it++;
		}
	}
	for (auto& arete : m_spEdges)
		arete->SubFlux(arete->GetFlux());
	
	auto allchaines = GetAllChaine(m_pNodeStart,m_pNodeEnd);
	for (auto& chaine : allchaines) {
		auto alllistedges = GetListeEdgesFromChaine(chaine);
		typeWeight min = alllistedges.front().first->GetWeight()- alllistedges.front().first->GetFlux();
		for (auto& edge : alllistedges) {
			if (edge.second == true) {
				if (min > edge.first->GetWeight() - edge.first->GetFlux())
					min = edge.first->GetWeight() - edge.first->GetFlux();
			}
			else {
				if (min > edge.first->GetFlux())
					min = edge.first->GetFlux();
			}
		}
		for (auto& edge : alllistedges) {
			edge.first->AddFlux(min);
		}
	
	}

}



// Fonctions protégées 

// GetEdgeFromNodes renvoie l arête qui touche les 2 noeuds et un booléen sur son sens de parcours (vrai dans le sens de la flèche !!!)
std::pair<CEdge::pEdge, bool> CGraph::GetEdgeFromNodes(CNode::pNode pNode1, CNode::pNode pNode2) const
{
	std::pair<CEdge::pEdge, bool> pEdgeRetour = std::make_pair(nullptr, true);
	for (auto pEdge : m_spEdges)
		if (*pNode1 == pEdge->GetFirstNode() && *pNode2 == pEdge->GetSecondNode())
			pEdgeRetour = std::make_pair(pEdge, true);
		else
			if (*pNode2 == pEdge->GetFirstNode() && *pNode1 == pEdge->GetSecondNode())
				pEdgeRetour = std::make_pair(pEdge, false);
	return pEdgeRetour;
}

// GetAllChaine renvoie la liste de toutes les chaines (liste de noeuds) qui partents du départ et vont jusqu'à l'arrivée 
std::list<CGraph::Chaine> CGraph::GetAllChaine(CNode::pNode pNodeStart, CNode::pNode pNodeEnd) const
{
	auto pNode = pNodeStart;
	std::list<CGraph::Chaine> listeChaineFinale;
	std::list<CGraph::Chaine> listeChaine;
	CNode::pNode pNodeNext = nullptr;
	CGraph::Chaine uneChaine;
	uneChaine.push_back(pNode);
	listeChaine.push_back(uneChaine);

	while (!listeChaine.empty()) // Pour toutes les chaines on va essayer de les compléter
	{
		auto chaine = listeChaine.back(); // on recupere la derniere chaine
		listeChaine.pop_back();
		pNode = chaine.back(); // On recupere le dernier sommet de la chaine
		if (pNode == pNodeEnd) // Cette chaine est arrivee
			listeChaineFinale.push_back(chaine);
		else // Sinon on essaye de completer la chaine
		{
			auto listeEdgesOut = GetEdgesOut(pNode); // On regarde les arêtes sortantes
			for (auto pEdges : listeEdgesOut)
			{
				pNodeNext = pEdges->GetSecondNode(); // Le potentiel noeud suivant est le second noeud de l arete
				if (!IsInChaine(pNodeNext, chaine)) // On regarde si le noeud ne fait pas déjà partie de la chaine
				{
					auto chaineAjout(chaine); // On cree une nouvelle chaine copie de la chaine actuelle et on enlève son dernier noeud
					chaineAjout.push_back(pNodeNext);
					listeChaine.push_back(chaineAjout);
				}
			}
			auto listeEdgesIn = GetEdgesIn(pNode); // On regarde les arêtes entrantes
			for (auto pEdges : listeEdgesIn)
			{
				pNodeNext = pEdges->GetFirstNode(); // Le potentiel noeud suivant est le premier noeud de l arete
				if (!IsInChaine(pNodeNext, chaine)) // On regarde si le noeud ne fait pas déjà partie de la chaine
				{
					auto chaineAjout(chaine); // On cree une nouvelle chaine copie de la chaine actuelle 
					chaineAjout.push_back(pNodeNext);
					listeChaine.push_back(chaineAjout);
				}
			}
		}
	}
	return listeChaineFinale;
}

// GetListeEdgesFromChaine renvoie une liste d'arêtes avec leur sens de parcours (bool) à partir d'une chaine de noeuds
std::list<std::pair<CEdge::pEdge, bool>> CGraph::GetListeEdgesFromChaine(CGraph::Chaine chaine) const
{
	std::list<std::pair<CEdge::pEdge, bool>> listeEdges;
	CNode::pNode pNode1 = chaine.front();
	chaine.pop_front();
	while (!chaine.empty())
	{
		auto pNode2 = chaine.front();
		chaine.pop_front();
		auto pEdge = GetEdgeFromNodes(pNode1, pNode2);
		listeEdges.push_back(pEdge);
		pNode1 = pNode2;
	}
	return listeEdges;
}


// TODO :

// TP 6 7 : GetEdgesIn
// TODO   : Renvoie la liste de toutes les arêtes qui finissent en pNode
std::list<CEdge::pEdge> CGraph::GetEdgesIn(CNode::pNode pNode) const
{
	std::list<CEdge::pEdge> list;
	for (auto& edges : m_spEdges) {
		if (edges->GetSecondNode() == pNode) {
			list.push_back(edges);
		}
	}
	return list;
}

// TP 6 7 : GetEdgesOut
// TODO   : Renvoie la liste de toutes les arêtes qui partent de pNode
std::list<CEdge::pEdge> CGraph::GetEdgesOut(CNode::pNode pNode) const
{
	std::list<CEdge::pEdge> list;
	for (auto& edges : m_spEdges) {
		if (edges->GetFirstNode() == pNode) {
			list.push_back(edges);
		}
	}
	return list;
}

// TP 6 7 : IsInChaine
// TODO   : Renvoie vrai si le noeud appartient à la chaine et faux sinon
bool CGraph::IsInChaine(CNode::pNode pNode, CGraph::Chaine chaine) const
{
	return std::find(chaine.begin(), chaine.end(), pNode) != chaine.end();
}



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

void CGraph::AddNewEdge(CNode::pNode pNode1, CNode::pNode pNode2, typeWeight weight)
{
	m_spEdges.insert(CEdge::New(pNode1, pNode2, weight));
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
		for (auto itpEdge = m_spEdges.begin(); itpEdge != m_spEdges.end();/* RIEN ICI */)
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
	for (auto pNode : m_spNodes)
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
	for (auto const & pNode : m_spNodes)
	{
		float dist = static_cast<float> (std::sqrt((x - pNode->GetX()) * (x - pNode->GetX()) + (y - pNode->GetY()) * (y - pNode->GetY())));
		if (dist < distMin)
		{
			distMin = dist;
			pNodeNear = pNode;
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
	for (auto const& pEdge : m_spEdges)
	{
		float dist = static_cast<float> (std::sqrt((x - pEdge->GetMilieuX()) * (x - pEdge->GetMilieuX()) + (y - pEdge->GetMilieuY()) * (y - pEdge->GetMilieuY())));
		if (dist < distMin)
		{
			distMin = dist;
			pEdgeNear = pEdge;
		}
	}
	return pEdgeNear;
}



/********************** FIN DES FONCTION PUBLIQUES DEBUT DES FONCTIONS PROTEGEES *************************/


void CGraph::Clear()
{
	// on vide le conteneur des aretes
	m_spEdges.clear();
	// on vide le conteneur des noeuds
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
	if (m_Oriented)
	{
		for (const auto& pEdge : m_spEdges)
			if (pEdge->GetFirstNode() == pNode1 && pEdge->GetSecondNode() == pNode2)
				return true;
	}
	else
	{
		for (const auto& pEdge : m_spEdges)
			if (pEdge->GetFirstNode() == pNode1 && pEdge->GetSecondNode() == pNode2 || pEdge->GetFirstNode() == pNode2 && pEdge->GetSecondNode() == pNode1)
				return true;
	}
	return false;
}

