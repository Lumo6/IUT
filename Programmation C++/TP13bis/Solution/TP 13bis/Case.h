/*!
 * \file "Case.h"
 * Déclaration de la classe CCase
 * 
 * Copyright (c) 2015 by Benjamin ALBOUY-KISSI
 *
 * \todo Déclarez la classe CCase dans le fichier Case.h
 */
//Solution
#pragma once

/*!
 * \brief
 * Représente une case du labyrinthe.
 * 
 * Chaque case est connectée aux cases adjacentes si le passage est possible de l'une à l'autre.
 * 
 */
class CCase
{
private:
  int m_x = -1;             //!<\brief	Abscisse de la case
  int m_y = -1;             //!<\brief	Ordonnée de la case
  bool m_bVisited = false;  //!<\brief	La case a-t-elle été visitée ?
  bool m_bBadWay = false;   //!<\brief	La case est-elle un mauvais chemin ?

  CCase* m_pRightCase = nullptr;  //!<\brief Pointeur vers la case de droite si un passage est possible, nullptr sinon
  CCase* m_pTopCase = nullptr;    //!<\brief Pointeur vers la case du haut si un passage est possible, nullptr sinon
  CCase* m_pLeftCase = nullptr;   //!<\brief Pointeur vers la case de gauche si un passage est possible, nullptr sinon
  CCase* m_pBottomCase = nullptr; //!<\brief Pointeur vers la case du bas si un passage est possible, nullptr sinon

public:
  /*!\brief Constructeur
   * 
   * \param x Abscisse de la position de la case
   * \param y Ordonnée de la position de la case
   *
   * \remark Les valeurs (-1, -1) signifient que la case est à une position non initialisée.
   */
  CCase(int x = -1, int y = -1) { m_x = x; m_y = y; }
  void setRightCase(CCase* pCase);  //!<\brief Définit la case de droite
  void setTopCase(CCase* pCase);    //!<\brief Définit la case du haut
  void setLeftCase(CCase* pCase);   //!<\brief Définit la case de gauche
  void setBottomCase(CCase* pCase); //!<\brief Définit la case du bas

  const CCase* getRightCase()  const { return m_pRightCase; }  //!<\brief Retourne la case de droite ou nullptr si aucun pasage n'est possible
  const CCase* getTopCase()    const { return m_pTopCase; }    //!<\brief Retourne la case du haut ou nullptr si aucun pasage n'est possible
  const CCase* getLeftCase()   const { return m_pLeftCase; }   //!<\brief Retourne la case de gauche ou nullptr si aucun pasage n'est possible
  const CCase* getBottomCase() const { return m_pBottomCase; } //!<\brief Retourne la case du bas ou nullptr si aucun pasage n'est possible
  CCase* getRightCase()  { return m_pRightCase; }  //!<\brief Retourne la case de droite ou nullptr si aucun pasage n'est possible
  CCase* getTopCase()    { return m_pTopCase; }    //!<\brief Retourne la case du haut ou nullptr si aucun pasage n'est possible
  CCase* getLeftCase()   { return m_pLeftCase; }   //!<\brief Retourne la case de gauche ou nullptr si aucun pasage n'est possible
  CCase* getBottomCase() { return m_pBottomCase; } //!<\brief Retourne la case du bas ou nullptr si aucun pasage n'est possible

  void visit() { m_bVisited = true; }     //!<\brief Définit la case comme étant visitée
  bool isVisited() const { return m_bVisited; } //!<\brief Retourne true si la case a été visitée, false sinon

  void badWay() { m_bBadWay = true; }     //!<\brief Définit la case comme étant un mauvais chemin
  bool isBadWay() const { return m_bBadWay; }   //!<\brief Retourne true si la case est un mauvais chemin, false sinon

  int getPosX() const { return m_x; }  //!<\brief Retourne l'abscisse de la position de la case
  int getPosY() const { return m_y; }  //!<\brief Retourne l'ordonnée de la position de la case
};

//Fin Solution