#include "stdafx.h"
#include "fonctions.h"

unsigned long long factorial_rec(unsigned int n)
{
  if (n == 0)
    return 1;
  if (n <= 1)
    return 1;
  return factorial_rec(n - 1) * n;
}

unsigned long long factorial_it(unsigned int n)
{
  if (n == 0)
    return 1;
  if (n == 1)
    return 1;
  unsigned long long Fn = 1;

  for (unsigned int i = 2; i <= n; ++i)
  {
    //Calcul de Fn
    Fn = Fn * i;
  }
  return Fn;
}
