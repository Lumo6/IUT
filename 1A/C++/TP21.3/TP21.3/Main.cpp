#include "stdafx.h"

#include "fonctions.h"
#include "templates.h"

#include <chrono>
#include <iostream>
#include <algorithm>
using namespace std;
using namespace std::chrono;


int _tmain(int argc, _TCHAR* argv[])
{
#ifdef WIN32
    SetConsoleOutputCP(65001);
#endif
    high_resolution_clock::time_point start;
    high_resolution_clock::duration duration;
    high_resolution_clock::duration duration_for;
    unsigned long long fac = 0;
    const unsigned int n = 6;
    unsigned long long nbRepet = 0;

    //Affiche la précision des mesures.
    cout << "Résolution des mesures temporelles : " << (double)ratio_divide<high_resolution_clock::period, nano>::num / ratio_divide<high_resolution_clock::period, nano>::den << " nanoseconde(s)" << '\n';

    //Mesure du temps d'une boucle
    cout << "Initialisation des mesures..." << '\n';
    start = high_resolution_clock::now();
    for (nbRepet = 0; (duration_for = high_resolution_clock::now() - start) <= seconds(3); nbRepet++);
    duration_for = duration_for / (nbRepet - 1);

    //Mesure du temps du calcul par version itérative
    cout << "Mesure de la version iterative..." << '\n';
    start = high_resolution_clock::now();
    for (nbRepet = 0; (duration = high_resolution_clock::now() - start) <= seconds(3); nbRepet++)
        fac = factorial_it(n);
    cout << "Calcul de F" << n << " par version iterative = " << fac << " en " << nanoseconds((duration / (nbRepet - 1) - duration_for)).count() << " nanosecondes." << '\n';

    //Mesure du temps du calcul par version récursive
    cout << "Mesure de la version recursive..." << '\n';
    start = high_resolution_clock::now();
    for (nbRepet = 0; (duration = high_resolution_clock::now() - start) <= seconds(3); nbRepet++)
        fac = factorial_rec(n);
    cout << "Calcul de F" << n << " par version recursive = " << fac << " en " << nanoseconds((duration / (nbRepet != 1 ? (nbRepet - 1) : 1) - duration_for)).count() << " nanosecondes." << '\n';

    //Mesure du temps du calcul par version préprocesseur
    cout << "Mesure de la version preprocesseur..." << '\n';
    start = high_resolution_clock::now();
    for (nbRepet = 0; (duration = high_resolution_clock::now() - start) <= seconds(3); nbRepet++)
        fac = factorial<n>;
    cout << "Calcul de F" << n << " par preprocesseur = " << fac << " en " << nanoseconds((duration / (nbRepet - 1) - duration_for)).count() << " nanosecondes." << '\n';
    return 0;
}