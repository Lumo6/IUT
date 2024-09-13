#pragma once
#include "Edge.h"

#include <memory>
#include <set>
#include <vector>
#include <iostream>

class CGraph{

public:
	
	using pNodeSet = std::set<CNode::pNode> ;
	using pEdgeSet = std::set<CEdge::pEdge> ;

	CGraph() {};

	// GETTER
	std::size_t GetNumberOfEdges() const { return m_spEdges.size(); }
	std::size_t GetNumberOfNodes() const { return m_spNodes.size(); }
	const pNodeSet& GetNodes() const { return m_spNodes; }
	const pEdgeSet& GetEdges() const { return m_spEdges; }

	void AddNewNode(CNode::pNode pNode) { m_spNodes.insert(pNode); }
	void AddNewEdge(CEdge::pEdge pEdge) { m_spEdges.insert(pEdge); }

	void RemoveEdge(CEdge::pEdge pEdge) { m_spEdges.erase(pEdge); }
	void RemoveNode(CNode::pNode pNode);

	CNode::pNode GetNodeFromName(const std::string& name) const;
	std::size_t GetNodeDegree(CNode::pNode node) const;
	
protected : 
	
	pEdgeSet m_spEdges; // un set d'aretes et de noeuds
	pNodeSet m_spNodes;
};

std::ostream& operator<<(std::ostream& os, const CGraph& g);