#include "Graph/Node.h"

// TP 2, 3 et 4 : 
// TODO : CNode         : création du constructeur : un noeud c'est pour l instant juste un nom (std::string) une donnée (size_t) permettant de compter le nombre d instances de noeud
//                        et ses coordonnées en x et en y (float) initialisées à 0 par défaut
// TODO : NewNode       : fonction renvoyant un nouveau pNode
// TODO : GetName		: renvoie le nom du noeud
// TODO : SetName		: permet de modifier le nom du noeud
// 
// ICI COMMENCE LES NOUVEAUTES DU TP2
// 
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
}

CNode::pNode CNode::NewNode(const std::string& name, float x, float y)
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
	m_PosX = x;
}

void CNode::SetY(float y)
{
	; m_PosY = y;
}

bool CNode::operator==(const CNode& node) const
{
	return (m_degre==node.m_degre && m_Name == node.m_Name && m_PosX == node.m_PosX && m_PosY == node.m_PosY);
}

bool CNode::operator==(const CNode::pNode& pNode) const 
{
	return (*this)==(*pNode);
}

Color CNode::GetColor() const
{
	return Color(m_color+c_nb_UP_type+c_nb_R_type);
}

void CNode::SetColor(Color color)
{
	m_color = color;
}

unsigned CNode::Get_UP_Red() const
{
	return m_UP_Red;
}

void CNode::Add_UP_Red(unsigned UP_Red_toAdd)
{
	m_UP_Red += UP_Red_toAdd;
}

unsigned CNode::Get_UP_Blue() const
{
	return m_UP_Blue;
}

void CNode::Add_UP_Blue(unsigned UP_Blue_toAdd)
{
	m_UP_Blue += UP_Blue_toAdd;
}

void CNode::Sub_UP_Blue(unsigned UP_Blue_toSub)
{
	if (UP_Blue_toSub >= m_UP_Blue)
		m_UP_Blue -= UP_Blue_toSub;
	else
		m_UP_Blue = 0; // on devrait lancer une exception
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
	if (m_degre >= degreToSub)
		m_degre -= degreToSub;
	else
		m_degre = 0; // Attention il faudrait lancer une exception
}