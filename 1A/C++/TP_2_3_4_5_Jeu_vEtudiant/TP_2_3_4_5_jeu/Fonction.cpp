#pragma once

#include "Graph/Graph.h"
#include "Graph/Edge.h"
#include "Graph/Node.h"

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include "Fonction.h"


void sauvegarder(std::ofstream& out, CGraph graph) {
	
	out << graph.GetNodes().size() << '\n';
	out << graph.GetEdges().size() << '\n';

	for (auto nodes : graph.GetNodes()) {
		out << nodes->GetColor() << ',' << nodes->GetDegre() << ',' << nodes->GetName() << ',' << nodes->GetX() << ',' << nodes->GetY()
			<< ',' << nodes->Get_UP_Blue() << ',' << nodes->Get_UP_Red() << '\n';
	}
	for (auto edges : graph.GetEdges()) {
		out << edges->GetFirstNode() << ',' << edges->GetMilieuX() << ',' << edges->GetMilieuY() << ',' << edges->GetSecondNode() << ',' << edges->GetWeight() << '\n';
	}
}

CGraph Restaurer(std::ifstream& in) {
	
	CGraph graph;
	CNode node;
	std::string ligne;
	std::getline(in, ligne);
	size_t nbNodes = std::stoi(ligne);
	std::getline(in, ligne);
	size_t nbEdges = std::stoi(ligne);

	for (size_t i = 0; i < nbNodes; i++) {
		std::getline(in, ligne, ',');
		unsigned color = std::stoi(ligne);
		std::getline(in, ligne, ',');
		int degree = std::stoi(ligne);
		std::getline(in, ligne, ',');
		std::string name = ligne;
		std::getline(in, ligne, ',');
		int x = std::stoi(ligne);
		std::getline(in, ligne, ',');
		int y = std::stoi(ligne);
		CNode node{ name,x,y };
		Color maCouleur=Color(color);
		node.SetColor(maCouleur);
		std::getline(in, ligne, ',');

		std::getline(in, ligne, ',');

	}
	
	

	return graph;
}