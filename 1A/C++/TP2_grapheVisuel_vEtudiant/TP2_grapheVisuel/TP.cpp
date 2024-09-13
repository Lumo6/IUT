#include "TP.h"


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
	
	pLibgraph->drawString(std::to_string(m_graph.MaxFlux()), CPoint{0,0});
}

void CTP::AddEdge(CNode::pNode pNode1, CNode::pNode pNode2)
{
	std::random_device rd;
	std::default_random_engine gen(rd());
	pNode1->AddDegre(1);
	pNode2->AddDegre(1);
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
	CGraph graph;
	for (const auto& pnode : graph.GetNodes()) {
		if (p->GetFirstNode() == pnode) pnode->AddDegre(1);
		if (p->GetSecondNode() == pnode) pnode->AddDegre(1);
	}
	m_graph.RemoveEdge(p);
}

void CTP::CreateGraphFull()
{
	for (const auto& pnode1 : m_graph.GetNodes()) {
		for (const auto& pnode2 : m_graph.GetNodes()) {
			if (pnode1 != pnode2) {
				if (!(m_graph.CheckNodesAreNeighbors(pnode1, pnode2))) {
					pnode1->AddDegre(1);
					pnode2->AddDegre(1);
					AddEdge(pnode1, pnode2);
				}	
			}
		}
	}
	// Un graphe est complet s il relie tous ses noeuds entre eux
}


/********************************** DEBUT DES FONCTIONS PRIVEES *******************************/



void CTP::DrawNode(const CNode::pNode& pNode) const
{
	ILibGraph2* pLibgraph = GetLibGraph2();
	CRectangle rect(CPoint(pNode->GetX(), pNode->GetY()), CSize(26, 26));
	pLibgraph->setPen(MakeARGB(255, 100, 122, 153), 1.0f);

	enum class Color
	{
		Red, Green, Blue, Yellow, Cyan, Magenta, Brown, Salmon, Chocolate, Orange, Tan, Gold, Olive, Chartreuse, Teal, RoyalBlue, Indigo, Turquoise, Purple, Violet, Crimson

	};

	switch (pNode->GetColor())
	{
	  case static_cast<int> (Color::Red):
		  pLibgraph->setSolidBrush(MakeARGB(255, 255, 0, 0));
		  break;
	  case static_cast<int> (Color::Olive):
		  pLibgraph->setSolidBrush(MakeARGB(255, 128, 128, 0));
		  break;
	  case static_cast<int> (Color::Yellow):
		  pLibgraph->setSolidBrush(MakeARGB(255, 255, 255, 0));
		  break;
	  case static_cast<int> (Color::Blue):
		  pLibgraph->setSolidBrush(MakeARGB(255, 0, 0, 255));
		  break;
	  case static_cast<int> (Color::Brown):
		  pLibgraph->setSolidBrush(MakeARGB(255, 165, 42, 42));
		  break;
	  case static_cast<int> (Color::Chocolate):
		  pLibgraph->setSolidBrush(MakeARGB(255, 210, 105, 30));
		  break;
	  case static_cast<int> (Color::Orange):
		  pLibgraph->setSolidBrush(MakeARGB(255, 255, 165, 0));
		  break;
	  case static_cast<int> (Color::Tan):
		  pLibgraph->setSolidBrush(MakeARGB(255, 210, 180, 140));
		  break;
	  case static_cast<int> (Color::Gold):
		  pLibgraph->setSolidBrush(MakeARGB(255, 255, 215, 0));
		  break;
	  case static_cast<int> (Color::Chartreuse):
		  pLibgraph->setSolidBrush(MakeARGB(255, 127, 255, 0));
		  break;
	  case static_cast<int> (Color::Green):
		  pLibgraph->setSolidBrush(MakeARGB(255, 0, 255, 0));
		  break;
	  case static_cast<int> (Color::Turquoise):
		  pLibgraph->setSolidBrush(MakeARGB(255, 64, 224, 208));
		  break;
	  case static_cast<int> (Color::Teal):
		  pLibgraph->setSolidBrush(MakeARGB(255, 0, 128, 128));
		  break;
	  case static_cast<int> (Color::Salmon):
		  pLibgraph->setSolidBrush(MakeARGB(255, 250, 128, 114));
		  break;
	  case static_cast<int> (Color::Cyan):
		  pLibgraph->setSolidBrush(MakeARGB(255, 0, 255, 255));
		  break;
	  case static_cast<int> (Color::RoyalBlue):
		  pLibgraph->setSolidBrush(MakeARGB(255, 65, 105, 225));
		  break;
	  case static_cast<int> (Color::Indigo):
		  pLibgraph->setSolidBrush(MakeARGB(255, 75, 0, 130));
		  break;
	  case static_cast<int> (Color::Purple):
		  pLibgraph->setSolidBrush(MakeARGB(255, 128, 0, 128));
		  break;
	  case static_cast<int> (Color::Magenta):
		  pLibgraph->setSolidBrush(MakeARGB(255, 255, 0, 255));
		  break;
	  case static_cast<int> (Color::Violet):
		  pLibgraph->setSolidBrush(MakeARGB(255, 238, 130, 238));
		  break;
	  case static_cast<int> (Color::Crimson):
		  pLibgraph->setSolidBrush(MakeARGB(255, 220, 20, 60));
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
	os << pEdge->GetFlux()<< " / "<< pEdge->GetWeight(),
	pLibgraph->drawString(os.str(), weightPosition);
}
