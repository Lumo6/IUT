#include "TP.h"
#include <random> // std::random_device, ...

#include "LibGraph2.h"

using namespace LibGraph2;

CGraph& CTP::GetGraph()
{
	return m_graph;
}

void CTP::Draw() const
{
	ILibGraph2* pLibgraph = GetLibGraph2();
	//Affiche les Arêtes
	for (auto const& pEdge : m_graph.GetEdges())
		if(pEdge)
			DrawEdge(pEdge);
	//Affiche les Noeuds
	for (auto const& pNode : m_graph.GetNodes())
		if(pNode)
			DrawNode(pNode);
}

void CTP::AddEdge(CNode::pNode pNode1, CNode::pNode pNode2)
{
	std::random_device rd;
	std::default_random_engine gen(rd());
	typeWeight weight = std::uniform_int_distribution<>{ 1, 9 }(gen);
	m_graph.AddNewEdge(CEdge::NewEdge(pNode1, pNode2, weight));
}

void CTP::AddNode(unsigned int x, unsigned int y)
{
	std::string nameNode{ "P" };
	nameNode += std::to_string(m_graph.GetNodes().size()+1);
	m_graph.AddNewNode(CNode::NewNode(nameNode, float(x), float(y)));
}

void CTP::DeleteNode(CNode::pNode p)
{
	m_graph.RemoveNode(p);
}

void CTP::DeleteEdge(CEdge::pEdge p)
{
	m_graph.RemoveEdge(p);
}


/********************************** DEBUT DES FONCTIONS PRIVEES *******************************/



void CTP::DrawNode(const CNode::pNode& pNode) const
{
	ILibGraph2* pLibgraph = GetLibGraph2();
	CRectangle rect(CPoint(pNode->GetX()-c_NodeSize/2, pNode->GetY()-c_NodeSize/2), CSize(c_NodeSize, c_NodeSize));
	pLibgraph->setPen(MakeARGB(255, 100, 122, 153), 1.0f);
	CPoint p1(pNode->GetX()- c_NodeSize/2, pNode->GetY());
	CPoint p2(pNode->GetX()+ c_NodeSize/2, pNode->GetY());
	pLibgraph->drawLine(p1, p2);
	p1 = CPoint(pNode->GetX(), pNode->GetY() - c_NodeSize / 2);
	p2 = CPoint(pNode->GetX(), pNode->GetY() + c_NodeSize / 2);
	pLibgraph->drawLine(p1, p2);
	// Affichage UP Red
	CPoint namePosition(pNode->GetX()-c_NodeSize/2 + 12, pNode->GetY() + 10 -c_NodeSize/2);
	pLibgraph->setSolidBrush(MakeARGB(255, 255, 0, 0));
	pLibgraph->drawString(std::to_string(pNode->Get_UP_Red()), namePosition);
	// Affichage UP Blue
	namePosition = CPoint(pNode->GetX() + 8, pNode->GetY() + 10 - c_NodeSize / 2);
	pLibgraph->setSolidBrush(MakeARGB(255, 0, 0, 255));
	pLibgraph->drawString(std::to_string(pNode->Get_UP_Blue()), namePosition);
	// Affichage Ressource Green
	namePosition = CPoint(pNode->GetX() - c_NodeSize / 2 + 12, pNode->GetY() + 6);
	pLibgraph->setSolidBrush(MakeARGB(255, 0, 255, 0));
	pLibgraph->drawString(std::to_string(pNode->Get_UP_Blue()), namePosition);
	// Affichage Ressource Violet
	namePosition = CPoint(pNode->GetX() +8, pNode->GetY() + 6);
	pLibgraph->setSolidBrush(MakeARGB(255, 238, 130, 238));
	pLibgraph->drawString(std::to_string(pNode->Get_UP_Blue()), namePosition);
	// Affichage du cercle représentant le point
	pLibgraph->setSolidBrush(MakeARGB(30, 30, 30, 153));

	pLibgraph->drawEllipse(rect);
}

void CTP::DrawEdge(const CEdge::pEdge& pEdge) const
{
	ILibGraph2* pLibgraph = GetLibGraph2();
	pLibgraph->setPen(MakeARGB(255, 255, 100, 100), 2.0f);

	CNode::pNode pPoint1 = pEdge->GetFirstNode();
	CNode::pNode pPoint2 = pEdge->GetSecondNode();
	CPoint p1(pPoint1->GetX(), pPoint1->GetY());
	CPoint p2(pPoint2->GetX(), pPoint2->GetY());
	CPoint p1p2(p2.m_fX-p1.m_fX,p2.m_fY-p1.m_fY);
	float normeP1P2 = std::sqrt(p1p2.m_fX*p1p2.m_fX+ p1p2.m_fY * p1p2.m_fY);
	p1.m_fX += c_NodeSize * p1p2.m_fX / (2 * normeP1P2);
	p1.m_fY += c_NodeSize * p1p2.m_fY / (2 * normeP1P2);
	p2.m_fX -= c_NodeSize * p1p2.m_fX / (2 * normeP1P2);
	p2.m_fY -= c_NodeSize * p1p2.m_fY / (2 * normeP1P2);
	pLibgraph->drawLine(p1, p2);
	CPoint weightPosition;
	if (*pPoint1 == pPoint2) // si meme sommets on dessine une ellipse
	{
		CRectangle rect(CPoint(p1.m_fX - 45, p1.m_fY - 45), CSize(50, 50));
		pLibgraph->setSolidBrush(MakeARGB(0, 0, 0, 0)); // pas d intérieur à l ellipse
		pLibgraph->drawArc(rect, 52, 344);
		weightPosition = CPoint(p1.m_fX - 55, p1.m_fY - 55);
	}
	else
	{
		weightPosition = CPoint((p1.m_fX + p2.m_fX) / 2, (p1.m_fY + p2.m_fY) / 2);
	}
	pLibgraph->setSolidBrush(MakeARGB(255, 0, 0, 0));

	// PAS UTILISE TOUT DE SUITE

	//std::ostringstream os;
	//os << pEdge->GetWeight();
	//pLibgraph->drawString(os.str(), weightPosition);
}
