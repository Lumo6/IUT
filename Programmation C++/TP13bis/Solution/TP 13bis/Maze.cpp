/*!
 * \file "Maze.cpp"
 * Définition de la classe CMaze
 * 
 * Copyright (c) 2015 by Benjamin ALBOUY-KISSI
 *
 * \todo Définissez la classe CMaze dans le fichier Maze.cpp
 */
//Solution
#include "maze.h"
#include <LibGraph2.h>
#include <string>

using namespace LibGraph2;
using namespace std;

CMaze::CMaze()
{
  //Initialise les positions des cases
  for (size_t x = 0; x < m_maze.size(); ++x)
    for (size_t y = 0; y < m_maze[0].size(); ++y)
      m_maze[x][y] = CCase{ (int)x, (int)y };

  //La case de sortie est la case dans le coin inférieur droit du labyrinthe
  m_pExitCase = &m_maze[m_maze.size() - 1][m_maze[0].size() - 1];
  //La case de départ est la case dans le coin supérieur gauche du labyrinthe
  m_pStartCase = &m_maze[0][0];
  m_lstPath.push_back(m_pStartCase);
  //La case de départ est donc visitée
  m_pStartCase->visit();


  //Initialise les connections des cases du labyrinthe
  /* Labyrinthe : 
   ___________ 
  |_ _   _| | |
  |  _| |     |
  |  _ _ _| | |
  | |_    |_|_|
  |_____|_____|
  */
  //Initialisation des connections à l'aide d'une chaîne de caractère :
  //  les indices de caractères pairs (0, 2, ...) correspondent à la connexion vers le bas : " " = connection, "_" = pas de connection
  //  les indices de caractères impairs (1, 3, ...) correspondent à la connexion vers la droite : " " = connection, "|" = pas de connection
  string strMaze = "_ _   _| | |"
                   "  _| |     |"
                   "  _ _ _| | |"
                   " |_    |_|_|"
                   "_ _ _|_ _ _|";
  /*string strMaze = "_  |"
                   "_ _|";*/

  auto carIt = strMaze.begin();
  for (size_t y = 0; y < m_maze[0].size(); ++y)
    for (size_t x = 0; x < m_maze.size(); ++x)
    {
      char car = *carIt;
      if (*carIt == ' ')
        connectToBottomCase(m_maze[x][y]);
      carIt++;
      if (*carIt == ' ')
        connectToRightCase(m_maze[x][y]);
      carIt++;
    }
}

void CMaze::step()
{
  //Case courante = dernière case du chemin
  CCase* pCurCase = m_lstPath.back();

  //Evacue le cas trivial où la case courante est la case d'arrivée -> rien à faire
  if (pCurCase == m_pExitCase)
    return;

  //Case à ajouter (à rechercher par la suite)
  CCase* pCaseToAdd = nullptr;

  //Tente d'ajouter une case au chemin en testant dans l'ordre la case de droite, du haut, de gauche et du base de la case courante.
  // Pour pouvoir ajouter la case, elle doit ne pas avoir été préalablement visitée
  if (pCurCase->getRightCase() && !pCurCase->getRightCase()->isVisited())
    pCaseToAdd = pCurCase->getRightCase();
  else if (pCurCase->getTopCase() && !pCurCase->getTopCase()->isVisited())
    pCaseToAdd = pCurCase->getTopCase();
  else if (pCurCase->getLeftCase() && !pCurCase->getLeftCase()->isVisited())
    pCaseToAdd = pCurCase->getLeftCase();
  else if (pCurCase->getBottomCase() && !pCurCase->getBottomCase()->isVisited())
    pCaseToAdd = pCurCase->getBottomCase();

  //Si aucune case n'a été trouvée, alors la case courante est un cul de sac, il faut la marquer comme un mauvais chemin puis la supprimer du chemin
  if (!pCaseToAdd)
  {
    m_lstPath.pop_back();
    pCurCase->badWay();
  }
  else //ajoute la nouvelle case au chemin
  {
    m_lstPath.push_back(pCaseToAdd);
    pCaseToAdd->visit();
  }
}

//Fin Solution