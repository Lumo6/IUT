/*!
 * \file "Maze.h"
 * Déclaration de la classe CMaze
 * 
 * Copyright (c) 2015 by Benjamin ALBOUY-KISSI
 *
 * \todo Déclarez la classe CMaze dans le fichier Maze.h
 */
//Solution
#pragma once

#include "case.h"
#include <array>
#include <list>

/*!
 * \brief
 * Représente le labyrinthe.
 * 
 * Le labyrinthe est composé d'un tableau de CCase à deux dimensions. L'ensemble des parcours possible dans le labyrinthe 
 * est constitué par les connexions des cases. Les cases sont connectées grâce à leur pointeurs internes.
 * 
 * \see
 * CCase
 */
class CMaze
{
public:
  using maze_t = std::array<std::array<CCase, 5>, 6>; //!<\brief Type du tableau 2D
  using path_t = std::list<CCase*>;                   //!<\brief Type du chemin

private:
  maze_t m_maze;                //!<\brief Tableau 2D des cases.
  path_t m_lstPath;             //!<\brief Chemin parcouru.
  CCase* m_pStartCase;          //!<\brief Case de départ du labyrinthe
  CCase* m_pExitCase;           //!<\brief Case de sortie du labyrinthe

  /*!\brief Connecte la case de droite
   *
   * Etablit un chemin possible entre la case passée en paramètre et la case située à sa droite.
   * 
   * \param cs Case de gauche
   * 
   * \remark La case \p cs doit être dans le labyrinthe courant
   * \see CMaze::connectToBottomCase()
   */
  void connectToRightCase(CCase& cs) { cs.setRightCase(&m_maze[cs.getPosX() + 1L][cs.getPosY()]); }
  /*!\brief Connecte la case du bas
  *
  * Etablit un chemin possible entre la case passée en paramètre et la case située en dessous d'elle.
  *
  * \param cs Case du haut
  *
  * \remark La case \p cs doit être dans le labyrinthe courant
  * \see CMaze::connectToRightCase()
  */
  void connectToBottomCase(CCase& cs) { cs.setBottomCase(&m_maze[cs.getPosX()][cs.getPosY() + 1L]); };

public:
  CMaze();  //!<\brief Initialise le labyrinthe

  void step(); //!<\brief Teste une case supplémentaire pour tenter de trouver la sortie
  const path_t& getPath() const { return m_lstPath; }     //!<\brief Retourne la liste des cases traversées le long du chemin parcouru
  const maze_t& getMaze() const { return m_maze; }        //!<\brief Retourne le tableau 2D des cases du labyrinthe
  const CCase* getStart() const { return m_pStartCase; }  //!<\brief Retourne la case de départ du labyrinthe
  const CCase* getExit()  const { return m_pExitCase; }   //!<\brief Retourne la case de sortie du labyrinthe
};

//Fin Solution