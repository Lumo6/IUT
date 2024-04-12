/*!\file
 * \brief Déclaration de la classe CVecteur2D
 * \author Benjamin ALBOUY-KISSI
 */
#pragma once

#include <string>
#include <iostream>
#if __cpp_impl_three_way_comparison >= 201907L
#include <compare>
#endif

//!\brief Classe de gestion d'un vecteur en deux dimensions
class CVecteur2D
{
  double m_dX;//!<Position en X
  double m_dY;//!<Position en Y

public:
  //!\brief Constructeur
  CVecteur2D(double x, double y);

  //!\{
  //!\name Accesseurs
  double X() const { return m_dX; }
  double Y() const { return m_dY; }
  double Norm() const;
  double Orientation() const;
  //!\}

  //!\{
  //!\name Modificateurs
  void setX(double x) { m_dX = x; }
  void setY(double y) { m_dY = y; };
  void setNorm(double norm);
  void setOrientation(double orient);
  //!\}

  //!\{
  //!\name Opérateurs unaires
  CVecteur2D operator -() const;
  CVecteur2D operator +() const { return *this; };
  //!\}

  //!\{
  //!\name Opérateurs de comparaison
#if __cpp_impl_three_way_comparison >= 201907L
  bool operator==(const CVecteur2D& v) const = default;
  std::partial_ordering operator<=>(const CVecteur2D& v) const;
#else
  bool operator==(const CVecteur2D& v) const;
  bool operator!=(const CVecteur2D& v) const;
  bool operator>(const CVecteur2D& v) const;
  bool operator<(const CVecteur2D& v) const;
  bool operator>=(const CVecteur2D& v) const;
  bool operator<=(const CVecteur2D& v) const;
#endif
  //!\}

  //!\{
  //!\name Opérateurs arithmétiques avec affectation
  CVecteur2D& operator+=(const CVecteur2D & v);
  CVecteur2D& operator-=(const CVecteur2D & v);
  CVecteur2D& operator*=(double dScal);
  CVecteur2D& operator/=(double dScal);
  //!\}

  //!\{
  //!\name Opérateurs arithmétiques
  CVecteur2D operator+(const CVecteur2D& v) const;
  CVecteur2D operator-(const CVecteur2D& v) const;
  CVecteur2D operator*(double dScal) const;
  CVecteur2D operator/(double dScal) const;
  //!\}
};

//!\brief Opérateur de sortie vers flux
std::ostream& operator<<(std::ostream& out, const CVecteur2D& v);

//!\brief Alias de type : un CPoint2D est un CVecteur2D
using CPoint2D = CVecteur2D;
