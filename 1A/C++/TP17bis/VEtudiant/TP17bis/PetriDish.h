#pragma once
#include <vector>
#include <memory>
#include "Cell.h"

/*!
 * \brief Gère une boîte de Petri.
 * 
 * Une boîte de Petri consiste en une collection à deux dimensions de cellules CCell. La boîte de Petri
 * simule le [jeu de la vie](https://fr.wikipedia.org/wiki/Jeu_de_la_vie) par appels succesif de la fonction
 * Update().
 */
class CPetriDish
{
  /// \todo Modifiez la ligne suivante pour définir l'alias petri_collection vers une collection de cellules.
  /// Vous devez choisir un type de collection pertinant et également réfléchir au type des éléments contenus.
  using petri_collection = std::vector<std::vector<std::shared_ptr<CCell>>>;
  petri_collection m_cells;
public:
  //!\brief Crée la boîte de Petri en fixant sa taille
  CPetriDish(size_t size);

  //!\brief Retourne la taille de la boîte de Petri
  size_t Size() const { 
    /// \todo Modifiez la ligne suivante pour retourner correctement la taille de la boîte de Petri.
    return m_cells.size();
  }


  //!\brief Force une cellule à être vivante
  void ForceAlive(size_t i, size_t j);

  //!\brief Force une cellule à être morte
  void ForceDead(size_t i, size_t j);

  //!\brief Verifie si une cellule est vivante
  bool IsAlive(size_t i, size_t j);

  //!\brief Met à jour l'état de chaque cellule selon les règles du jeu
  void Update();

  std::shared_ptr<CCell> operator() (size_t i, size_t j) { return m_cells[i][j]; };

private:
  //!\brief Supprime toutes les cellules mourantes
  void CleanMe();
  //!\brief Compte le nombre de cellules voisines vivantes
  unsigned int NbAliveNeighboors(const petri_collection& snapshot, size_t i, size_t j) const;
  //!\brief Crée une copie mémoire des données des cellules
  petri_collection CreateSnapshot() const;

  
};

