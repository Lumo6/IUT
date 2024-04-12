/*!\file
 * \brief D�finition de la classe CVecteur2D
 * \author Benjamin ALBOUY-KISSI
 */
#include "vecteur2D.h"

#include <math.h>
#include <iostream>

 /*!\param x Abscisse du vecteur
  * \param y Abscisse du vecteur
  * \remark Il n'y a pas de constructeur par d�faut, uniquement pour vous emb�ter !
  */
CVecteur2D::CVecteur2D(double x, double y)
{
  m_dX = x;
  m_dY = y;
}

//!\return La norme du vecteur
double CVecteur2D::Norm() const
{
  return sqrt(m_dX*m_dX + m_dY*m_dY);
}

//!\return L'orientation du vecteur
double CVecteur2D::Orientation() const
{
  return atan2(m_dY, m_dX);
}

/*!\param norm La nouvelle norme du vecteur.
 *
 * Seule la norme du vecteur est modifi�e, son orientation reste inchang�e.
 */
void CVecteur2D::setNorm(double norm)
{
  double orient = Orientation();
  m_dX = norm * cos(orient);
  m_dY = norm * sin(orient);
}

/*!\param orient La nouvelle orientation du vecteur en radians.
 *
 * Seule l'orientation du vecteur est modifi�e, sa norme reste inchang�e.
 */
void CVecteur2D::setOrientation(double orient)
{
  double norm = Norm();
  m_dX = norm * cos(orient);
  m_dY = norm * sin(orient);
}


//Op�rateurs unaires
//!\return Retourne le vecteur oppos�
CVecteur2D CVecteur2D::operator -() const
{
  return CVecteur2D{ -m_dX, -m_dY };
}



//Op�rateurs de comparaison
#if __cpp_impl_three_way_comparison >= 201907L

std::partial_ordering CVecteur2D::operator<=>(const CVecteur2D& v) const
{
  return Norm() <=> v.Norm();
}

#else

//!\return \c true ou \c false
//!\param[in] v Vecteur � comparer
bool CVecteur2D::operator==(const CVecteur2D& v) const
{
  if (m_dX == v.m_dX && m_dY == v.m_dY)
    return true;
  else
    return false;
}

//!\return \c true ou \c false
//!\param[in] v Vecteur � comparer
bool CVecteur2D::operator!=(const CVecteur2D& v) const
{
  return !(*this == v);
}

//!\return \c true ou \c false
//!\param[in] v Vecteur � comparer
//!\remark La comparaison se fait sur la norme des vecteurs
bool CVecteur2D::operator>(const CVecteur2D& v) const
{
  if (Norm() > v.Norm())
    return true;
  return false;
}

//!\return \c true ou \c false
//!\param[in] v Vecteur � comparer
//!\remark La comparaison se fait sur la norme des vecteurs
bool CVecteur2D::operator<(const CVecteur2D& v) const
{
  if (Norm() < v.Norm())
    return true;
  return false;
}

//!\return \c true ou \c false
//!\param[in] v Vecteur � comparer
//!\remark La comparaison se fait sur la norme des vecteurs
bool CVecteur2D::operator>=(const CVecteur2D& v) const
{
  return !((*this) < v);
}

//!\return \c true ou \c false
//!\param[in] v Vecteur � comparer
//!\remark La comparaison se fait sur la norme des vecteurs
bool CVecteur2D::operator<=(const CVecteur2D& v) const
{
  return !((*this) > v);
}

#endif


//Op�rateurs arithm�tiques avec affectation
//!\return Le r�sultat de l'op�ration
//!\param[in] v op�rande de droite
CVecteur2D & CVecteur2D::operator+=(const CVecteur2D & v)
{
  m_dX += v.m_dX;  m_dY += v.m_dY;
  return *this;
}

//!\return Le r�sultat de l'op�ration
//!\param[in] v op�rande de droite
CVecteur2D & CVecteur2D::operator-=(const CVecteur2D & v)
{
  m_dX -= v.m_dX;  m_dY -= v.m_dY;
  return *this;
}

//!\return Le r�sultat de l'op�ration
//!\param[in] dScal op�rande de droite
CVecteur2D & CVecteur2D::operator*=(double dScal)
{
  m_dX *= dScal;  m_dY *= dScal;
  return *this;
}

//!\return Le r�sultat de l'op�ration
//!\param[in] dScal op�rande de droite
CVecteur2D & CVecteur2D::operator/=(double dScal)
{
  m_dX /= dScal;  m_dY /= dScal;
  return *this;
}



//Op�rateurs arithm�tiques
//!\return Le r�sultat de l'op�ration
//!\param[in] v op�rande de droite
CVecteur2D CVecteur2D::operator+(const CVecteur2D & v) const
{
  CVecteur2D retour = *this;
  retour += v;
  return retour;
}


//!\return Le r�sultat de l'op�ration
//!\param[in] v op�rande de droite
CVecteur2D CVecteur2D::operator-(const CVecteur2D& v) const
{
  CVecteur2D retour = *this;
  retour -= v;
  return retour;
}

//!\return Le r�sultat de l'op�ration
//!\param[in] dScal op�rande de droite
CVecteur2D CVecteur2D::operator*(double dScal) const
{
  CVecteur2D retour = *this;
  retour *= dScal;
  return retour;
}

//!\return Le r�sultat de l'op�ration
//!\param[in] dScal op�rande de droite
CVecteur2D CVecteur2D::operator/(double dScal) const
{
  CVecteur2D retour = *this;
  retour /= dScal;
  return retour;
}


//Op�rateur de sortie vers flux
//!\return le flux modifi�
//!\param[in,out] out flux o� sortir le vecteur
//!\param[in] v le vecteur � sortir
std::ostream& operator<<(std::ostream& out, const CVecteur2D& v)
{
  out << "(" << v.X() << ", " << v.Y() << ")";
  return out;
}
