#pragma once

#include <string> // std::string
#include <memory> // std::shared_ptr

enum Color
{
	Red, Blue, Green, Violet, Yellow, Cyan, Magenta, Brown, Salmon, Chocolate, Orange, Tan, Gold, Olive, Chartreuse, Teal, RoyalBlue, Indigo, Turquoise, Purple, Crimson

};

class CNode {

public:
	using pNode = std::shared_ptr<CNode>; // alias 

	CNode(const std::string& name = "P", float x=0, float y=0); 
	
	static pNode NewNode(const std::string& name = "P", float x=0, float y=0); // Fonction pour ajouter des noeuds{ }

	const std::string& GetName() const; // renvoie le nom du noeud
	void SetName(const std::string& name); // modifie le nom du noeud

	// ICI COMMENCE LE TP2

	float GetX()const; // renvoie l abscisse du noeud
	float GetY()const; // renvoie l ordonnee du noeud
	void SetX(float x); // modifie l abscisse du noeud 
	void SetY(float y); // modifie l abscisse du noeud 

	size_t GetDegre()const;
	void AddDegre(size_t degreToAdd);
	void SubDegre(size_t degreToSub);

	bool operator==(const CNode& node)const; // renvoie vrai si les 2 noeuds ont même noms et mêmes coordonnées
	bool operator==(const CNode::pNode& pNode)const; // renvoie vrai si les 2 noeuds ont même noms et mêmes coordonnées

	Color GetColor() const;
	void SetColor(Color color);

	unsigned Get_UP_Red()const;
	void Add_UP_Red(unsigned UP_Red_toAdd );

	unsigned Get_UP_Blue()const;
	void Add_UP_Blue(unsigned UP_Blue_toAdd);
	void Sub_UP_Blue(unsigned UP_Blue_toSub);


protected : 
	std::string m_Name;  // nom du noeud (std::string)

	// ICI COMMENCE LE TP2

	// will later hold more infos

	size_t m_degre = 0;
	float m_PosX = 0; // abcisse du noeud 
	float m_PosY = 0; // ordonnée du noeud
	Color m_color=Color::Red;
	const unsigned c_nb_UP_type = 2;
	const unsigned c_nb_R_type = 2;
	unsigned m_UP_Red = 0; // unité de production rouge
	unsigned m_UP_Blue = 0; // unité de production bleue
	unsigned m_R_Green = 0; // ressource verte
	unsigned m_R_Violet = 0; // ressource violette
	unsigned m_owner = 0;// ID player, 0 si n'appartient à personne
};
