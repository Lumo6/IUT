#include <LibGraph2.h>
#include "TP.h"

using namespace LibGraph2;
using namespace std;

unsigned CNode::m_uiNbNodes = 0;


// TP Noté : 
// TODO : Ajouter une étape à l'énumeration pour gérer le lancement de l'algorithme de Kruskal



int APIENTRY _tWinMain(HINSTANCE hInstance,	HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hInstance); UNREFERENCED_PARAMETER(hPrevInstance); UNREFERENCED_PARAMETER(lpCmdLine); UNREFERENCED_PARAMETER(nCmdShow);

#ifdef _DEBUG
	_CrtMemState mem1, mem2, memdiff;
#endif
	_CrtMemCheckpoint(&mem1);
	{
		ILibGraph2* pLibgraph = GetLibGraph2();
		pLibgraph->show();
		CTP tp;
		// Création du graphe d exemple
		tp.CreateExempleGraph();
		enum class Etape
		{
			Noop,
			AddNode,
			AddEdge,
			DeleteNode,
			DeleteEdge // A COMPLETER ***************************  TP Noté ****************************************** 
		};
		Etape etape = Etape::Noop;
		evt e;
		bool point1Select = false;
		CNode::pNode pPoint1;
		CEdge::pEdge pEdge1;
		while (pLibgraph->waitForEvent(e)) {
			switch (e.type) {
			case evtRefresh:
				pLibgraph->beginPaint();
					tp.Draw();
				pLibgraph->endPaint();
				break;
			case evtKeyDown:
				switch (e.vkKeyCode)
				{
				case 'N':
					if (etape == Etape::AddNode)
						etape = Etape::Noop;
					else
						etape = Etape::AddNode;
					break;
				case 'E':
					if (etape == Etape::AddEdge)
						etape = Etape::Noop;
					else
						etape = Etape::AddEdge;
					break;
				case 'D':
					if (etape == Etape::DeleteNode)
						etape = Etape::Noop;
					else
						etape = Etape::DeleteNode;
					break;
				case 'Z':
					if (etape == Etape::DeleteEdge)
						etape = Etape::Noop;
					else
						etape = Etape::DeleteEdge;
					break;
				case 'K':
					tp.CreateGraphFull();
					etape = Etape::Noop;
					pLibgraph->askForRefresh();
					break;
	// A COMPLETER                        ***************************  TP Noté ****************************************** 
				}
				break;
			case evtMouseDown:
				switch (etape) {
					case Etape::AddNode: {
						tp.AddNode(e.x, e.y);
						pLibgraph->askForRefresh();
						break;
					}
					case Etape::AddEdge: {
						if (!point1Select) {
							pPoint1 = tp.GetGraph().GetNodeNear(e.x, e.y);
							point1Select = true;
						}
						else {
							tp.AddEdge(pPoint1, tp.GetGraph().GetNodeNear(e.x, e.y));
							point1Select = false;
						}
						pLibgraph->askForRefresh();
						break;
					}
					case Etape::DeleteNode:	{
						pPoint1 = tp.GetGraph().GetNodeNear(e.x, e.y);
						tp.DeleteNode(pPoint1);
						pLibgraph->askForRefresh();
						break;
					}
					case Etape::DeleteEdge:	{
						pEdge1 = tp.GetGraph().GetEdgeNear(e.x, e.y);
						tp.DeleteEdge(pEdge1);
						pLibgraph->askForRefresh();
						break;
					}
				}
				break;
			}
		}
		ReleaseLibGraph2();
	}
	_CrtMemCheckpoint(&mem2);
	if (_CrtMemDifference(&memdiff, &mem1, &mem2))
	{
		_CrtMemDumpAllObjectsSince(&mem1);
		GetLibGraph2()->guiMessageBox("Fuites mémoires !", "Des fuites mémoires ont été détectées, vérifiez vos allocations et désallocations !", MsgBtnOK, MsgIcnStop);
		ReleaseLibGraph2();
	}
	return 0;
}
