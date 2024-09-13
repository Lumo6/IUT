#pragma once

#include <string> // std::string
#include <memory> // std::shared_ptr

class CNode {

public:
	using pNode = std::shared_ptr<CNode>; // alias pour pointeur sur CNode

	CNode(const std::string& name = "P", float x=0, float y=0); 
	
	static pNode New(const std::string& name = "P", float x=0, float y=0); // Fonction pour ajouter des noeuds{ }

	const std::string& GetName() const; // renvoie le nom du noeud
	void SetName(const std::string& name); // modifie le nom du noeud

	size_t GetNbNodes()const; // renvoie le nombre d'instance de noeud dans le programme (va permettre de s assurer que les noeuds auront tous des noms différents (P1, P2, ...)

	float GetX()const; // renvoie l abscisse du noeud
	float GetY()const; // renvoie l ordonnee du noeud
	void SetX(float x); // modifie l abscisse du noeud 
	void SetY(float y); // modifie l abscisse du noeud 

	int GetColor()const;      // Renvoie la couleur du noeud
	void SetColor(int color); // Modifie la couleur du noeud

	bool operator==(const CNode& node)const; // renvoie vrai si les 2 noeuds ont même noms et mêmes coordonnées
	bool operator==(const CNode::pNode& pNode)const; // renvoie vrai si les 2 noeuds ont même noms et mêmes coordonnées

protected : 
	std::string m_Name;  // nom du noeud (std::string)

	static  size_t m_NbNodes; // variable statique m_nbNodes qui totalisera les instances de CNode initialisée à 0 ( dans le prog.cpp !!!)
	float m_PosX = 0; // abcisse du noeud 
	float m_PosY = 0; // ordonnée du noeud

	int m_Color = -1;

	// will later hold more infos
};
