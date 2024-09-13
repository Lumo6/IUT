#include <stdio.h> // Fonctions d’entree / sortie (printf, scanf,...)
#include <stdlib.h> // Fonctions d’allocation, aléatoire, conversion,...(malloc, free, rand, ...)
int main(int argc, char* argv[])
{
	int j=0;
	float total = 0;
	int cnt = 0;
	while (cnt != 15) {
		bool flag = false;
		if (j == 0 || j == 1)
			flag = 1;
		for (size_t i = 2; i <= j / 2; ++i) {

			// if j is divisible by i, then j is not prime
			// change flag to 1 for non-prime number
			if (j % i == 0) {
				flag = 1;
				break;
			}
		}
		if (!flag) {
			if (total == 0) {
				total = j;
				cnt++;
			}
			else {
				total *= j;
				cnt++;
			}
		}
		j++;
	}
	printf("%f", total);
	return total;
}

