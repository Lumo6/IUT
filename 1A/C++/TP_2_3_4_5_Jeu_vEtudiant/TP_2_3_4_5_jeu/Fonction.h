#pragma once
#include "Graph/Graph.h"
#include "Graph/Edge.h"
#include "Graph/Node.h"


void sauvegarder(std::ofstream&, CGraph);

CGraph Restaurer(std::ifstream&);