#include "Tree.h"
#include <iomanip>

void CTree::FindFamily(CNode::pNode node)
{
	VectorNodes Sons;
	for (auto PEdge : m_spEdges) {
		if (PEdge->GetFirstNode() == node ) {
			if (PEdge->GetSecondNode() != node->GetFather()) {
				node->SetSons(PEdge->GetSecondNode());
				(PEdge->GetSecondNode())->SetFather(PEdge->GetFirstNode());
			}
		}
		if (PEdge->GetSecondNode() == node) {
			if (PEdge->GetFirstNode() != node->GetFather()) {
				node->SetSons(PEdge->GetFirstNode());
				(PEdge->GetFirstNode())->SetFather(PEdge->GetSecondNode());
			}
		}
	}
}


void CTree::enraciner(CNode::pNode racine)
{
	racine->SetFather(nullptr);
	for (auto PNode : m_spNodes) {
		FindFamily(PNode);
	}
}

size_t CTree::hauteur(CNode::pNode node,size_t h = 0)
{
	if (!node)
		return 0;

	size_t max = h;

	for (const auto& fils : node->GetSons()) {
		h = hauteur(fils, h + 1);
		if (max < h)
			max = h;
	}
	return max;
}

CNode::pNode CTree::GetRacine()
{
	for (const auto& racine : m_spNodes) {
		if (racine->GetFather() == nullptr)
			return racine;
	}
	return CNode::pNode(nullptr);
}

std::ostream& CTree::ParcourirTree(std::ostream& out,VectorNodes& nodes)
{
	VectorNodes nodesfils;
	for (const auto& node : nodes) {
		out << node->GetValue();
		nodesfils.push_back();
	}
	out << '\n';
	ParcourirTree(out, nodesfils);
	return out;
}

std::ostream& operator<<(std::ostream& out, CTree& Tree)
{
	VectorNodes nodes;
	nodes.pushback(Tree.GetRacine());
	Tree.ParcourirTree(out,nodes);
	return out;
}
