/*!
 * \file  "TP.h"
 *
 * \brief Déclaration de la classe CTP. 
 *
 */
#pragma once
#include "inc/TP.h"

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
 
 */

	//!\brief fonction affichage de noeud
	void CTP::DrawNode(CNode::pNode pNode)
	{
		ILibGraph2* pLibgraph = GetLibGraph2();
		CRectangle rect(CPoint(pNode->GetX(), pNode->GetY()), CSize(26, 26));
		pLibgraph->setPen(MakeARGB(255, 100, 122, 153), 1.0f);

		pLibgraph->setSolidBrush(MakeARGB(30, 30, 30, 153));
		
		pLibgraph->drawEllipse(rect);

		pLibgraph->setSolidBrush(MakeARGB(255, 0, 0, 0));
		CPoint namePosition(rect.m_ptTopLeft);
		namePosition.m_fX += 1;
		namePosition.m_fY += 6;
		pLibgraph->drawString(pNode->GetName(), namePosition);
	}

	//!\brief fonction affichage d arrête
	
	void CTP::DrawEdge(CEdge::pEdge pEdge) {
		ILibGraph2* pLibgraph = GetLibGraph2();
		pLibgraph->setPen(MakeARGB(255, 255, 100, 100), 2.0f);

		CNode::pNode pPoint1 = pEdge->GetFirstNode();
		CNode::pNode pPoint2 = pEdge->GetSecondNode();
		CPoint p1(pPoint1->GetX() + 13, pPoint1->GetY() + 13);
		CPoint p2(pPoint2->GetX() + 13, pPoint2->GetY() + 13);
		CPoint weightPosition;
		if (*pPoint1 == pPoint2) { // si meme sommets on dessine une ellipse
			CRectangle rect(CPoint(p1.m_fX - 45, p1.m_fY - 45), CSize(50, 50));
			pLibgraph->setSolidBrush(MakeARGB(0, 0, 0, 0)); // pas d intérieur à l ellipse
			pLibgraph->drawArc(rect, 52, 344);
			weightPosition = CPoint(p1.m_fX - 55, p1.m_fY - 55);
		}
		else {
			weightPosition = CPoint((p1.m_fX + p2.m_fX) / 2, (p1.m_fY + p2.m_fY) / 2);
			pLibgraph->drawLine(p1, p2);		
		}
		pLibgraph->setSolidBrush(MakeARGB(255, 0, 0, 0));
		std::ostringstream os;
		os << std::setprecision(3) << pEdge->GetWeight();
		pLibgraph->drawString(os.str(), weightPosition);
	}

	/************************************************************************************************************/
	// TP Noté : A MODIFIER
	// TODO : Afficher le poids du graphe en haut à gauche de la fenêtre
	void CTP::Draw() {// Affiche les noeuds et les arêtes 
		ILibGraph2* pLibgraph = GetLibGraph2();
		//Affiche les Arêtes
		for (auto const& pedge : m_graph.GetEdges())
			DrawEdge(pedge);
		//Affiche les Noeuds
		for (auto const& pnode : m_graph.GetNodes())
			DrawNode(pnode);
	}

	// TP4  :
	// TODO : renvoyer l arête créée
	CEdge::pEdge CTP::AddEdge(CNode::pNode p1, CNode::pNode p2) {
		std::random_device rd;
		std::default_random_engine gen(rd());
		typeWeight weight = std::uniform_int_distribution<>{ 1, 9 }(gen);
		CEdge::pEdge pEdge = CEdge::New(p1, p2, weight);
		m_graph.AddNewEdge(pEdge);
		return pEdge;
	}

	// TP4  : AddEdge avec un paramètre en plus de type typeweight
	// TODO : renvoyer l arête créée
	CEdge::pEdge CTP::AddEdge(CNode::pNode p1, CNode::pNode p2, typeWeight weight) {
		CEdge::pEdge pEdge = CEdge::New(p1, p2, weight);
		m_graph.AddNewEdge(pEdge);
		return pEdge;
	}

	// TP4  :
	// TODO : renvoyer le noeud créé
	CNode::pNode CTP::AddNode(unsigned int x, unsigned int y) {
		std::string nameNode{ "P" };
		CNode::pNode pNode = CNode::New(nameNode);
		nameNode += std::to_string(pNode->GetNbNodes());
		pNode->SetName(nameNode);
		pNode->SetX(float(x));
		pNode->SetY(float(y));
		m_graph.AddNewNode(pNode);
		return pNode;
	}


	
	// TP 3 : 
	// TODO : ajouter une fonction qui crée un graphe complet à partir des noeuds du graphe
	void CTP::CreateGraphFull() {
		if (m_graph.GetNumberOfNodes() > 1) {
			m_graph.ClearEdges();
			for (auto const& pNode1 : m_graph.GetNodes())
				for (auto const& pNode2 : m_graph.GetNodes())
					if (pNode1 < pNode2)
						AddEdge(pNode1, pNode2);
		}
	}

	// TP4
	// TODO :  Fonction qui ajoute un graphe d'exemple qui va bien
	void CTP::CreateExempleGraph() {
		m_graph.Clear();
		auto pNode1 = AddNode(200, 250);
		auto pNode2 = AddNode(400, 450);
		auto pNode3 = AddNode(500, 50);
		auto pNode4 = AddNode(700, 350);
		auto pNode5 = AddNode(900, 150);
		AddEdge(pNode1, pNode2, 4);
		AddEdge(pNode1, pNode3, 3);
		AddEdge(pNode1, pNode5, 2);
		AddEdge(pNode2, pNode3, 1);
		AddEdge(pNode2, pNode4, 2);
		AddEdge(pNode3, pNode5, 5);
		AddEdge(pNode4, pNode5, 1);
	}