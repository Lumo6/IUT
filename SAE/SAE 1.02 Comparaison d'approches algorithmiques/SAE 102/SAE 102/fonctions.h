/**
 * \file fonctions.h
 *
 * Déclaration des fonctions fournies.
 */
#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <array>


using tabfonc = std::vector<int>(*)(size_t);
using tabtri = size_t(*)(std::vector<int>&);

//!\brief Crée un tableau aléatoire
std::vector<int> initTabAleat(size_t N);

//!\brief Crée un tableau presque trié
std::vector<int> initTabPresqueTri(size_t N);

//!\brief Crée un tableau presque trié au début
std::vector<int> initTabPresqueTriDeb(size_t N);

//!\brief Crée un tableau presque trié à la fin
std::vector<int> initTabPresqueTriFin(size_t N);

//!\brief Crée un tableau presque trié entre le début et la fin
std::vector<int> initTabPresqueTriDebFin(size_t N);

//!\brief Vérifie qu'un tableau est correctement trié
void verifTri(const std::vector<int>& tab, const std::string& algoName = {});

size_t TriParSelection(std::vector<int>& tab);

size_t TriABulles(std::vector<int>& tab);

size_t TriABullesOpt(std::vector<int>&);

size_t TriPeigne(std::vector<int>&);

size_t TriRapide(std::vector<int>&,int,int);

size_t TriRapide(std::vector<int>& tab);

size_t triAleatoire(std::vector<int>& tab);

size_t triCocktail(std::vector<int>& tab);

size_t triShell(std::vector<int>& tab);

size_t triInsertion(std::vector<int>& tab);

size_t triPairImpair(std::vector<int>& tab);