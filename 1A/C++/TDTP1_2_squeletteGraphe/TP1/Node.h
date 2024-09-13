#pragma once

#include <string>
#include <memory>
#include <vector>

class CNode {

public:
	using pNode = std::shared_ptr<CNode>; // PtrInt (Pointeur intelligent) sur noeud
	
	CNode(const std::string& name = std::string()) { SetName(name); } // constructeur par défaut le nom du noeud est vide

	void SetName(const std::string& name) { m_Name = name; }
	std::string GetName() const { return m_Name; }
	CNode::pNode GetFather() { return Father; }
	VectorNodes GetSons() { return Sons; }
	void SetFather(CNode::pNode pere) { Father = pere; }
	void SetSons(CNode::pNode fils) { Sons.push_back(fils); }

protected:
	CNode::pNode Father;
	VectorNodes Sons;
	std::string m_Name;
};

using VectorNodes = std::vector<CNode::pNode>;