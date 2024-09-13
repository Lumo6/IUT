#pragma once
#include "Node.h"

#include <array>
#include <memory>

class CEdge {

public : 
	using pEdge =  std::shared_ptr<CEdge>;           // PtrInt (Pointeur intelligent) sur arete
	using Array2Nodes = std::array<CNode::pNode,2> ; // tableau statique (array) contenant les PtrInt sur les 2 noeuds de l'arete

	CEdge(CNode::pNode pNode1, CNode::pNode pNode2, unsigned weight) { m_apNodes[0] = pNode1; m_apNodes[1] = pNode2; m_Weight = weight; }

	// GETTER
	const Array2Nodes& GetNodes() const { return m_apNodes; }
	CNode::pNode GetFirstNode() const { return m_apNodes[0]; }
	CNode::pNode GetSecondNode() const { return m_apNodes[1]; }
	size_t GetWeight() const { return m_Weight; }

	bool operator==(const CEdge& edge) const { if (this->GetWeight() == edge.GetWeight() && this->GetFirstNode() == edge.GetFirstNode() && this->GetSecondNode() == edge.GetSecondNode()) return true; else return false; }
	bool operator==(const CEdge::pEdge& pEdge) const { return *this == *pEdge; }

protected :
	unsigned m_Weight;    // poids de l arete
	Array2Nodes m_apNodes; // vecteur statique (array) de 2 noeuds m_apNodes[0] = pNode1 et m_apNodes[1] = pNode2
};