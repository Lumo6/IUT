#include <stdio.h> // Fonctions d’entree / sortie (printf, scanf,...)
#include <stdlib.h> // Fonctions d’allocation, aléatoire, conversion,...(malloc, free, rand, ...)
int main(int argc, char* argv[])
{
	int i;
	int max = rand() % 500;
	int total = 0;
	for (i = 0; i < max; ++i)
		if (i % 2)
			total += i;
	printf("%i", total);
	return total;
}
