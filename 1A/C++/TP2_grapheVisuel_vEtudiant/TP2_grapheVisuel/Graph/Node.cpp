#include "Graph/Node.h"

// TP 2, 3 et 4 : 
// TODO : CNode         : création du constructeur : un noeud c'est pour l instant juste un nom (std::string) une donnée (size_t) permettant de compter le nombre d instances de noeud
//                        et ses coordonnées en x et en y (float) initialisées à 0 par défaut
// TODO : New           : fonction renvoyant un nouveau pNode
// TODO : GetName		: renvoie le nom du noeud
// TODO : SetName		: permet de modifier le nom du noeud
// 
// ICI COMMENCE LES NOUVEAUTES DU TP2
// 
// TODO : GetNbNodes	: renvoie le nombre d instances de CNode va permettre d être sûr que 2 noeuds auront des noms différents (P1, P2, P3, ...)
// TODO : GetX			: renvoie l abscisse du noeud
// TODO : GetY			: renvoie l ordonnée du noeud
// TODO : SetX			: modifie l abscisse du noeud
// TODO : SetY			: modifie l ordonnée du noeud
// TODO : operator==	: renvoie vrai si 2 noeuds ont même nom et mêmes coordonnées
// TODO : operator==	: renvoie vrai si 2 noeuds ont même nom et mêmes coordonnées
// TODO : size_t GetDegre()const;
// TODO : void AddDegre(size_t degreToAdd);
// TODO : void SubDegre(size_t degreToSub);

CNode::CNode(const std::string& name, float x, float y)
{
	SetName(name);
	SetX(x);
	SetY(y);
	++m_NbNodes;
}

CNode::pNode CNode::New(const std::string& name, float x, float y)
{
	return std::make_shared<CNode>(name,x,y);
}

const std::string& CNode::GetName() const
{
	return m_Name;
}

void CNode::SetName(const std::string& name)
{
	m_Name = name;
}

// ICI COMMENCE LE TP2

size_t CNode::GetNbNodes() const
{
	return m_NbNodes;
}

float CNode::GetX() const
{
	return m_PosX;
}

float CNode::GetY() const
{
	return m_PosY;
}

void CNode::SetX(float x)
{
	m_PosX=x;
}

void CNode::SetY(float y)
{
	m_PosY=y;
}

bool CNode::operator==(const CNode& node) const
{
	if (GetName() == node.GetName() && GetX() == node.GetX() && GetY() && node.GetY() && GetDegre() == node.GetDegre()) {
		return true;
	}
	else {
		return false;
	}
}

bool CNode::operator==(const CNode::pNode& pNode) const 
{
	return (*this)==(*pNode);
}

size_t CNode::GetDegre()const
{
	return m_degre;
}

void   CNode::AddDegre(size_t degreToAdd)
{
	m_degre += degreToAdd;
}

void   CNode::SubDegre(size_t degreToSub)
{
	m_degre -= degreToSub;
}

void CNode::SetColor(int color) {
	m_iColor = color;
}

int CNode::GetColor()const {
	return m_iColor;
}