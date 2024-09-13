#include "TP.h"

CTP::CTP(void)
{
	m_graph.CreateExempleGraph();
}

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
	pLibgraph->setSolidBrush(MakeARGB(255, 0, 0, 0));
	std::ostringstream os;
	os <<m_graph.MaxFlux() ;
	pLibgraph->drawString(os.str(), CPoint{10,10});
}

void CTP::AddEdge(CNode::pNode pNode1, CNode::pNode pNode2)
{
	std::random_device rd;
	std::default_random_engine gen(rd());
	typeWeight weight = std::uniform_int_distribution<>{ 1, 9 }(gen);
	m_graph.AddNewEdge(CEdge::New(pNode1, pNode2, weight));
}

void CTP::AddNode(unsigned int x, unsigned int y)
{
	CNode::pNode pNode = std::make_shared<CNode>();
	std::string nameNode{ "P" };
	nameNode += std::to_string(pNode->GetNbNodes());
	pNode->SetName(nameNode);
	pNode->SetX(float(x));
	pNode->SetY(float(y));
	m_graph.AddNewNode(pNode);
}

void CTP::DeleteNode(CNode::pNode p)
{
	m_graph.RemoveNode(p);
}

void CTP::DeleteEdge(CEdge::pEdge p)
{
	m_graph.RemoveEdge(p);
}

void CTP::CreateGraphFull()
{
	// Un graphe est complet s il relie tous ses noeuds entre eux
}


/********************************** DEBUT DES FONCTIONS PRIVEES *******************************/



void CTP::DrawNode(const CNode::pNode& pNode) const
{
	ILibGraph2* pLibgraph = GetLibGraph2();
	CRectangle rect(CPoint(pNode->GetX(), pNode->GetY()), CSize(26, 26));
	pLibgraph->setPen(MakeARGB(255, 100, 122, 153), 1.0f);

	enum Color {
		Red, Green
	};

	switch (pNode->GetColor()) {
	case Red:
		pLibgraph->setSolidBrush(MakeARGB(255, 255, 0, 0));
		break;
	case Green:
		pLibgraph->setSolidBrush(MakeARGB(255, 0, 255, 0));
		break;
	default:
		pLibgraph->setSolidBrush(MakeARGB(30, 30, 30, 153));
		break;
	}

	pLibgraph->drawEllipse(rect);
	pLibgraph->setSolidBrush(MakeARGB(255, 0, 0, 0));
	CPoint namePosition(rect.m_ptTopLeft);
	namePosition.m_fX += 1;
	namePosition.m_fY += 6;
	pLibgraph->drawString(pNode->GetName(), namePosition);
}

void CTP::DrawEdge(const CEdge::pEdge& pEdge) const
{
	ILibGraph2* pLibgraph = GetLibGraph2();
	pLibgraph->setPen(MakeARGB(255, 255, 100, 100), 2.0f);

	CNode::pNode pPoint1 = pEdge->GetFirstNode();
	CNode::pNode pPoint2 = pEdge->GetSecondNode();
	CPoint p1(pPoint1->GetX() + 13, pPoint1->GetY() + 13);
	CPoint p2(pPoint2->GetX() + 13, pPoint2->GetY() + 13);
	pLibgraph->drawLine(p1, p2);
	// Si le graphe est orienté on dessine la fleche sur P2 (2 petits segments)
	if (m_graph.IsOriented())
	{
		CPoint P1P2(p2.m_fX - p1.m_fX, p2.m_fY - p1.m_fY); // Pour avoir la direction de P1P2
		float norme = static_cast<float> (std::sqrt(P1P2.m_fX * P1P2.m_fX + P1P2.m_fY * P1P2.m_fY)); // On normalise
		P1P2.m_fX /= norme;
		P1P2.m_fY /= norme;
		CPoint Ortho(-P1P2.m_fY, P1P2.m_fX); // On cherche l orthogonal direct a P1P2
		CPoint Fleche(p2.m_fX - 30 * P1P2.m_fX, p2.m_fY - 30 * P1P2.m_fY); // On se pose a la base de la fleche
		CPoint P0(Fleche.m_fX + 10 * Ortho.m_fX, Fleche.m_fY + 10 * Ortho.m_fY); // extremite nord de la fleche
		CPoint P3(Fleche.m_fX - 10 * Ortho.m_fX, Fleche.m_fY - 10 * Ortho.m_fY); // extremite sud de la fleche
		pLibgraph->setPen(MakeARGB(190, 200, 150, 100), 1.5f);
		pLibgraph->drawLine(P0, p2);
		pLibgraph->drawLine(P3, p2);
	}

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
	std::ostringstream os;
	os<<pEdge->GetFlux()<<" / " << pEdge->GetWeight();
	pLibgraph->drawString(os.str(), weightPosition);
}
