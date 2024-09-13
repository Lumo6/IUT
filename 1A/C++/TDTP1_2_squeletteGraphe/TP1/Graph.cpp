#include "Graph.h"

// operateur pour afficher un graphe

std::ostream& operator<<(std::ostream& os, const CGraph& g)
{
	os << "\n";
	os << "\tGraph : " << std::endl;
	os << "\tSommets : " << g.GetNumberOfNodes() << "   ";
	for (const auto& pNode : g.GetNodes()) os << "  " << pNode->GetName() << ", ";
	os << std::endl << "\tAretes  : " << g.GetNumberOfEdges() << "   ";
	for (const auto& pEdge : g.GetEdges())
	{
		os << "  ";
		for (const auto& pNode : pEdge->GetNodes())
			os << pNode->GetName() << "->";
		os << pEdge->GetWeight() << " ,    ";
	}
	os << "\n";
	return os;
}

void CGraph::RemoveNode(CNode::pNode pNode)
{ 
	for (auto it = m_spEdges.begin(); it != m_spEdges.end();) {
		auto PEdge = *it;
		if (PEdge->GetFirstNode() == pNode || PEdge->GetSecondNode() == pNode) {
			it = m_spEdges.erase(it);
		}
		else {
			++it;
		}
	}
	m_spNodes.erase(pNode);
}

CNode::pNode CGraph::GetNodeFromName(const std::string& name) const
{
	for (auto PNode : m_spNodes) {
		if (PNode->GetName() == name){
			return PNode;
		}
	}
	return CNode::pNode();
}

std::size_t CGraph::GetNodeDegree(CNode::pNode node) const
{
	size_t deg = 0;
	for (auto PEdge : m_spEdges) {
		if (PEdge->GetFirstNode() == node || PEdge->GetSecondNode() == node) {
			if (PEdge->GetFirstNode() == node && PEdge->GetSecondNode() == node) {
				deg++;
			}
			deg++;
		}
	}
	return deg;
}
