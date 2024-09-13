/*!
 * \file  "TP.h"
 *
 * \brief Déclaration de la classe CTP. 
 *
 */
#pragma once
#include "Graph/Graph.h"
#include "Graph/Edge.h"
#include "Graph/Node.h"
#include <LibGraph2.h>

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
 
 * Elle contient un graphe en donnée membre
 * Les fonctions pour dessiner : node, edge, et du coup le graphe
 * les fonctions pour ajouter, supprimer node, edge
 * une fonction pour créer un graphe complet 
 * une fonction pour créer un graphe d'exemple

 */
using namespace LibGraph2;
class CTP
{
	//!\brief graphe
	CGraph m_graph;
	//!\brief fonction affichage de noeud
	void DrawNode(CNode::pNode pNode);

	//!\brief fonction affichage d arrête
	
	void DrawEdge(CEdge::pEdge pEdge);
public:
	CTP(void) { } // constructeur fait un graph vide par défaut

	CGraph& GetGraph() { return m_graph; }

	/*******************************************************************************************/
	// TP Noté : A MODIFIER
	// TODO : Afficher le poids du graphe en haut à gauche de la fenêtre
	void Draw(); // Affiche les noeuds et les arêtes 

	CEdge::pEdge AddEdge(CNode::pNode p1, CNode::pNode p2); 

	CEdge::pEdge AddEdge(CNode::pNode p1, CNode::pNode p2, typeWeight weight); 

	CNode::pNode AddNode(unsigned int x, unsigned int y); 

	void DeleteNode(CNode::pNode p) { m_graph.RemoveNode(p); }
	
	void DeleteEdge(CEdge::pEdge p) { m_graph.RemoveEdge(p); }
	
	void CreateGraphFull();

	void CreateExempleGraph(); 

	/*********************** TP Noté  à compléter **************************************************/
};