#pragma once

// TP 1 2 et 3 : 
// TODO : CNode         : cr�ation du constructeur : un noeud c'est pour l instant juste un nom (std::string) une donn�e (size_t) permettant de compter le nombre d instances de noeud
//                        et ses coordonn�es en x et en y (float) initialis�es � 0 par d�faut
// TODO : New           : fonction renvoyant un nouveau pNode
// TODO : GetName		: renvoie le nom du noeud
// TODO : SetName		: permet de modifier le nom du noeud
// TODO : GetNbNodes	: renvoie le nombre d instances de CNode va permettre d �tre s�r que 2 noeuds auront des noms diff�rents (P1, P2, P3, ...)
// TODO : GetX			: renvoie l abscisse du noeud
// TODO : GetY			: renvoie l ordonn�e du noeud
// TODO : SetX			: modifie l abscisse du noeud
// TODO : SetY			: modifie l ordonn�e du noeud
// TODO : operator==	: renvoie vrai si 2 noeuds ont m�me nom et m�mes coordonn�es
// TODO : operator==	: renvoie vrai si 2 noeuds ont m�me nom et m�mes coordonn�es

#include <string>
#include <memory>

class CNode {
protected:
	std::string m_sName;
	// will later hold more infos
public:
	using  pNode = std::shared_ptr<CNode> ; // Alias pour pointeur sur CNode

	static pNode New(const std::string& name = std::string()) { return std::make_shared<CNode>(name); }

	CNode(const std::string& name = std::string()) { SetName(name); m_uiNbNodes++; };

	const std::string& GetName() const { return m_sName; }
	void SetName(const std::string& name) { m_sName = name; }

	bool operator==(const CNode & node)const { return m_sName == node.m_sName; }
	bool operator==(const CNode::pNode& pNode) { return m_sName == pNode->m_sName; }

protected : 
	
	size_t m_uiDegre = 0;
	static  unsigned m_uiNbNodes;
	float m_fPosX = 0;
	float m_fPosY = 0;

public : 
	
	float GetX() const { return m_fPosX; }
	float GetY() const { return m_fPosY; }
	void SetX(float x) { m_fPosX = x; }
	void SetY(float y) { m_fPosY = y; }
	static unsigned GetNbNodes() { return m_uiNbNodes; }

	/*********************** TP Not�  � compl�ter **************************************************/
	// ajouter l'attribut : composante connexe
	// d�clarer et d�finir ses 2 accesseurs
};




