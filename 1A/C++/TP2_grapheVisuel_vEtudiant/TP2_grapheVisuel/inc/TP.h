/*!
 * \file  "TP.hpp"
 *
 * \brief Déclaration de la classe CTP. 
 *
 */
#pragma once
#include "Graph/Graph.h"
#include "Graph/Edge.h"
#include "Graph/Node.h"
#include<LibGraph2.h>

#include <cstdlib>
#include <ctime>

#include <sstream>
#include <iomanip>
#include <random>

/*!
 * \brief
 * Classe de gestion du TP.
 * 
 * Cette classe est instanciée une seule fois pour répresenter toutes les actions du TP.
 * 
 * \todo 
 
 */
using namespace LibGraph2;


class CTP
{
public:
	CTP(void) { } // constructeur fait un graphe vide par défaut
	CGraph& GetGraph();  // renvoie le graph
	void Draw()const ; // Affiche les noeuds et les arêtes 
	
	void AddEdge(CNode::pNode pNode1, CNode::pNode pNode2);
	void AddNode(unsigned int x, unsigned int y);
	
	void DeleteNode(CNode::pNode p);
	void DeleteEdge(CEdge::pEdge p); 

	// TP 2 : TODO ajouter une fonction qui crée un graphe complet à partir des noeuds du graphe
	void CreateGraphFull();
	
private:
  //!\brief graphe
  CGraph m_graph;
  //!\brief fonction affichage de noeud
  void DrawNode(const CNode::pNode& pNode)const ;
 
  //!\brief fonction affichage d arête
  void DrawEdge(const CEdge::pEdge& pEdge) const;
  
  //Fin Solution

};

