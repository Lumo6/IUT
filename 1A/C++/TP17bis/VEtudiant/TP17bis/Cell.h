#pragma once
#include <cassert>

/*!
 * \brief Gère une cellule.
 * 
 * Une cellule a à chaque instant un certain état :
 * - Nascent (=naissante) à sa création jusqu'à ce que sa fonction Adult() soit appelée
 * - Adult (=adulte)
 * - Dying (=mourante) à partir du moment où sa fonction Die() est appelée
 * 
 * Les transistions d'états ne peuvent être que :
 * - Nascent -> Adult -> Dying
 * - Nascent -> Dying
 */
class CCell
{
  enum class Stage
  {
    Nascent,
    Adult,
    Dying
  } m_Stage = Stage::Nascent;

public:
  //! Retourne \c true si la cellule est à l'état Nascent.
  bool IsNascent() const { return m_Stage == Stage::Nascent; }
  //! Retourne \c true si la cellule est à l'état Adult.
  bool IsAdult() const { return m_Stage == Stage::Adult; }
  //! Retourne \c true si la cellule est à l'état Dying.
  bool IsDying() const { return m_Stage == Stage::Dying; }
  //! Passe la cellule à l'état Adult. La cellule ne doit pas être à l'état Dying.
  void Adult() { assert(m_Stage != Stage::Dying);  m_Stage = Stage::Adult; }
  //! Passe la cellule à l'état Dying.
  void Die() { m_Stage = Stage::Dying; }
};

