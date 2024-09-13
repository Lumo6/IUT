#pragma once
#include "Graph.h"

#include <vector>

class CTree : public CGraph {
public:
	CTree() {}
	void FindFamily(CNode::pNode);
	void enraciner(CNode::pNode);
	size_t hauteur(CNode::pNode, size_t);
	CNode::pNode GetRacine();
	std::ostream& ParcourirTree(std::ostream&, VectorNodes&);
};

std::ostream& operator<<(std::ostream&, CTree&);