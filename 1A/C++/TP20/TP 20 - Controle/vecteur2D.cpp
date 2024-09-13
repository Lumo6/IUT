/// \file
/// \brief Définition de la classe CVecteur2D
/// \author Benjamin ALBOUY-KISSI
#include "StdAfx.h"
#include "vecteur2D.h"
#include <math.h>
#include <iostream>
using namespace std;

/// \param x Abscisse du vecteur
/// \param y Abscisse du vecteur
CVecteur2D::CVecteur2D(double x, double y)
{
  m_dX = x;
  m_dY = y;
}

/// \return La norme du vecteur
double CVecteur2D::Norm() const
{
  return sqrt(m_dX*m_dX + m_dY*m_dY);
}

/// \return L'orientation du vecteur
double CVecteur2D::Orientation() const
{
  return atan2(m_dY, m_dX);
}

/// \param norm La nouvelle norme du vecteur.
/// 
/// Seule la norme du vecteur est modifiée, son orientation reste inchangée.
void CVecteur2D::setNorm(double norm)
{
  double orient = Orientation();
  m_dX = norm * cos(orient);
  m_dY = norm * sin(orient);
}

/// \param orient La nouvelle orientation du vecteur en radians.
/// 
/// Seule l'orientation du vecteur est modifiée, sa norme reste inchangée.
void CVecteur2D::setOrientation(double orient)
{
  double norm = Norm();
  m_dX = norm * cos(orient);
  m_dY = norm * sin(orient);
}


//Opérateurs unaires
/// \return Retourne le vecteur opposé
CVecteur2D CVecteur2D::operator -() const
{
  return CVecteur2D{ -m_dX, -m_dY };
}



//Opérateurs de comparaison
/// \return \c true ou \c false
/// \param[in] v Vecteur à comparer
bool CVecteur2D::operator==(const CVecteur2D& v) const
{
  if (m_dX == v.m_dX && m_dY == v.m_dY)
    return true;
  else
    return false;
}

/// \return \c true ou \c false
/// \param[in] v Vecteur à comparer
bool CVecteur2D::operator!=(const CVecteur2D& v) const
{
  return !(*this == v);
}

/// \return \c true ou \c false
/// \param[in] v Vecteur à comparer
/// \remark La comparaison se fait sur la norme des vecteurs
bool CVecteur2D::operator>(const CVecteur2D& v) const
{
  if (Norm() > v.Norm())
    return true;
  return false;
}

/// \return \c true ou \c false
/// \param[in] v Vecteur à comparer
/// \remark La comparaison se fait sur la norme des vecteurs
bool CVecteur2D::operator<(const CVecteur2D& v) const
{
  if (Norm() < v.Norm())
    return true;
  return false;
}

/// \return \c true ou \c false
/// \param[in] v Vecteur à comparer
/// \remark La comparaison se fait sur la norme des vecteurs
bool CVecteur2D::operator>=(const CVecteur2D& v) const
{
  return !((*this) < v);
}

/// \return \c true ou \c false
/// \param[in] v Vecteur à comparer
/// \remark La comparaison se fait sur la norme des vecteurs
bool CVecteur2D::operator<=(const CVecteur2D& v) const
{
  return !((*this) > v);
}



//Opérateurs arithmétiques avec affectation
/// \return Le résultat de l'opération
/// \param[in] v opérande de droite
CVecteur2D & CVecteur2D::operator+=(const CVecteur2D & v)
{
  m_dX += v.m_dX;  m_dY += v.m_dY;
  return *this;
}

/// \return Le résultat de l'opération
/// \param[in] v opérande de droite
CVecteur2D & CVecteur2D::operator-=(const CVecteur2D & v)
{
  m_dX -= v.m_dX;  m_dY -= v.m_dY;
  return *this;
}

/// \return Le résultat de l'opération
/// \param[in] dScal opérande de droite
CVecteur2D & CVecteur2D::operator*=(double dScal)
{
  m_dX *= dScal;  m_dY *= dScal;
  return *this;
}

/// \return Le résultat de l'opération
/// \param[in] dScal opérande de droite
CVecteur2D & CVecteur2D::operator/=(double dScal)
{
  m_dX /= dScal;  m_dY /= dScal;
  return *this;
}



//Opérateurs arithmétiques
/// \return Le résultat de l'opération
/// \param[in] v opérande de droite
CVecteur2D CVecteur2D::operator+(const CVecteur2D & v) const
{
  CVecteur2D retour = *this;
  retour += v;
  return retour;
}


/// \return Le résultat de l'opération
/// \param[in] v opérande de droite
CVecteur2D CVecteur2D::operator-(const CVecteur2D& v) const
{
  CVecteur2D retour = *this;
  retour -= v;
  return retour;
}

/// \return Le résultat de l'opération
/// \param[in] dScal opérande de droite
CVecteur2D CVecteur2D::operator*(double dScal) const
{
  CVecteur2D retour = *this;
  retour *= dScal;
  return retour;
}

/// \return Le résultat de l'opération
/// \param[in] dScal opérande de droite
CVecteur2D CVecteur2D::operator/(double dScal) const
{
  CVecteur2D retour = *this;
  retour /= dScal;
  return retour;
}


//Opérateur de sortie vers flux
/// \return le flux modifié
/// \param[in,out] out flux où sortir le vecteur
/// \param[in] v le vecteur à sortir
ostream& operator<<(ostream& out, const CVecteur2D& v)
{
  out << "(" << v.X() << ", " << v.Y() << ")";
  return out;
}
