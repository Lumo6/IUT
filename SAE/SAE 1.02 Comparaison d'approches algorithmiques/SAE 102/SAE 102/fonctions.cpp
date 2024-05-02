/**
 * \file fonctions.cpp
 * 
 * Définition des fonctions fournies.
 */
#include "fonctions.h"
#include <iostream>
#include <random>

/**
 * Crée un tableau d'entiers dont tous les éléments sont choisis aléatoirement.
 * 
 * Un tel tableau peut par exemple être 30968 28073 31177 2882 6140 17999 13828 20039 2310 24865.
 * 
 * \param[in] N taille du tableau
 * \return le tableau initialisé
 */
std::vector<int> initTabAleat(size_t N)
{
  std::vector<int> tab(N);
  for (auto& val : tab)
    val = rand();
  return tab;
}

/**
 * Crée un tableau d'entiers presque triés. Chaque élément est quasiment à sa place définitive, échangé éventuellement d'une place.
 * 
 * Un tel tableau peut par exemple être 1 3 2 4 6 5 8 7 9 10.
 *
 * \param[in] N taille du tableau
 * \return le tableau initialisé
 */
std::vector<int> initTabPresqueTri(size_t N)
{
  std::vector<int> tab(N);
  for (int i = 0; i < N; i++)
    tab[i] = i;
  for (int i = 0; i < N-1; i++)
  {
    if (rand() % 2 == 0)
    {
      std::swap(tab[i], tab[i + 1]);
      ++i;
    }
  }
  return tab;
}

/**
 * Crée un tableau d'entiers presque triés. Seuls le premier et le deuxième élément sont échangés.
 *
 * Un tel tableau peut par exemple être 2 1 3 4 5 6 7 8 9 10.
 *
 * \param[in] N taille du tableau
 * \return le tableau initialisé
 */
std::vector<int> initTabPresqueTriDeb(size_t N)
{
  std::vector<int> tab(N);
  for (int i = 0; i < N; i++)
    tab[i] = i;
  std::swap(tab[0], tab[1]);
  return tab;
}

/**
 * Crée un tableau d'entiers presque triés. Seuls le dernier et l'avant dernier élément sont échangés.
 *
 * Un tel tableau peut par exemple être 1 2 3 4 5 6 7 8 10 9.
 *
 * \param[in] N taille du tableau
 * \return le tableau initialisé
 */
std::vector<int> initTabPresqueTriFin(size_t N)
{
  std::vector<int> tab(N);
  for (int i = 0; i < N; i++)
    tab[i] = i;
  std::swap(tab[N - 1], tab[N - 2]);
  return tab;
}

/**
 * Crée un tableau d'entiers presque triés. Seuls le premier et le dernier élément sont échangés.
 *
 * Un tel tableau peut par exemple être 10 2 3 4 5 6 7 8 9 1.
 *
 * \param[in] N taille du tableau
 * \return le tableau initialisé
 */
std::vector<int> initTabPresqueTriDebFin(size_t N)
{
  std::vector<int> tab(N);
  for (int i = 0; i < N; i++)
    tab[i] = i;
  std::swap(tab[N - 1], tab[0]);
  return tab;
}

/**
 * Vérifie qu'un tableau est correctement trié. Si le tableau est mal trié, un message d'erreur est
 * affiché sur le flux d'erreur et le programme est terminé.
 * 
 * \param[in] tab Le tableau à vérifier
 * \param[in] algoName Le nom de l'algorithme de tri qui a été utilisé. Ce paramètre est optionnel.
 */
void verifTri(const std::vector<int>& tab, const std::string& algoName)
{
  const size_t taille = tab.size();
  for (size_t i = 1; i < taille; i++)
  {
    if (tab[i - 1] > tab[i])
    {
      std::cerr << "Erreur dans le tri " << algoName << (algoName.empty() ? "!" : " !") << '\n';
      exit(EXIT_FAILURE);
    }
  }
}


size_t TriParSelection(std::vector<int>& tab) {

    int n = tab.size();
    size_t NbrComp=0;
    for (size_t i = 0; i < n; i++) {
        int min = i;

        for (size_t j = i+1; j < n; j++) {
            NbrComp++;
            if (tab[j] < tab[min]) {
                min = j;
            }
            
        }

        if (min != i) {
            std::swap(tab[i], tab[min]);
        }
    }
    return NbrComp;
}

size_t TriABulles(std::vector<int>& tab) {
    size_t NbrComp = 0;
    for (size_t i = (tab.size()) - 1; i > 0; i--) {
        for (size_t j = 0; j < i; j++) {
            NbrComp++;
            if (tab[j + 1] < tab[j]) {
                int temp = tab[j + 1];
                tab[j + 1] = tab[j];
                tab[j] = temp;
            }
        }
    }
    return NbrComp;
}

size_t TriABullesOpt(std::vector<int>& tab) {
    size_t NbrComp = 0;
    for (size_t i = (tab.size()) - 1; i > 0; i--) {
        bool tri = true;
        for (size_t j = 0; j < i; j++) {
            NbrComp++;
            if (tab[j + 1] < tab[j]) {
                int temp = tab[j+1];
                tab[j + 1] = tab[j];
                tab[j] = temp;
                tri = false;
            }
        }
        if (tri)break;
    }
    return NbrComp;
}

size_t TriPeigne(std::vector<int>& tab) {
    size_t NbrIt=0;
    size_t intervalle = tab.size();
    bool echange = false;
    do{
        intervalle = static_cast<int>(intervalle / 1.3);
        if (intervalle < 1) {
            intervalle = 1;
        }
        
        size_t i = 0;
        echange = false;

        do {
            NbrIt++;
            if (tab[i] > tab[i + intervalle]) {
                size_t temp = tab[i];
                tab[i] = tab[i + intervalle];
                tab[i + intervalle] = temp;
                echange = true;
            }
            i++;
        } while (i < tab.size() - intervalle);


    } while (intervalle > 1 || echange);
    return NbrIt;
}

size_t TriRapide(std::vector<int>& tab, int debut, int fin) {
    unsigned int nb_comparaisons = 0;

    if (debut < fin) {
        int milieu = debut + (fin - debut) / 2;
        int pivot = tab[milieu];
        int i = debut;
        int j = fin;
        while (i <= j) {
            while (tab[i] < pivot) {
                i++;
                nb_comparaisons++;
            }
            while (tab[j] > pivot) {
                j--;
                nb_comparaisons++;
            }

            if (i <= j) {
                std::swap(tab[i], tab[j]);
                i++;
                j--;
            }
        }
        nb_comparaisons += TriRapide(tab, debut, j);
        nb_comparaisons += TriRapide(tab, i, fin);
    }
    return nb_comparaisons;
}

size_t TriRapide(std::vector<int>& tab) {
    int nb_comparaison = TriRapide(tab, 0, tab.size() - 1);
    return nb_comparaison;
}

// Fonction pour trier de manière aléatoire un tableau
size_t triAleatoire(std::vector<int>& tab) {
    std::random_device rd;
    std::mt19937 gen(rd());
    int NbrIt = 0;

    while (!std::is_sorted(tab.begin(), tab.end())) {
        std::shuffle(tab.begin(), tab.end(), gen);
        NbrIt = NbrIt + 1;
    }
    return NbrIt;
}


size_t triCocktail(std::vector<int>& tab) {
    bool echange = true;
    int debut = 0;
    int fin = tab.size() - 1;
    int NbrIt = 0;

    while (echange) {
        echange = false;
        for (int i = debut; i < fin; ++i) {
            NbrIt = NbrIt + 1;
            if (tab[i] > tab[i + 1]) {
                std::swap(tab[i], tab[i + 1]);
                echange = true;
            }
        }

        fin = fin - 1;

        for (int i = fin; i >= debut; --i) {
            NbrIt = NbrIt + 1;
            if (tab[i] > tab[i + 1]) {
                std::swap(tab[i], tab[i + 1]);
                echange = true;
            }
        }
        debut = debut + 1;
    }
    return NbrIt;
}

size_t triInsertion(std::vector<int>& tab) {
    int NbrIt = 0;
    for (size_t i = 1; i < tab.size(); ++i) {
        int x = tab[i];
        int j = i;
        while (j > 0 && tab[j - 1] > x) {
            tab[j] = tab[j - 1];
            --j;
            NbrIt = NbrIt + 1;
        }
        tab[j] = x;
    }
    return NbrIt;
}

size_t triPairImpair(std::vector<int>& tab) {
    size_t nb_comparaison = 0;
    bool trie = false;

    while (!trie) {
        trie = true;
        for (size_t i = 0; i < tab.size() - 1; i += 2) {
            nb_comparaison++;
            if (tab[i] > tab[i + 1]) {
                std::swap(tab[i], tab[i + 1]);
                trie = false;
            }
        }
        for (size_t i = 1; i < tab.size() - 1; i += 2) {
            nb_comparaison++;
            if (tab[i] > tab[i + 1]) {
                std::swap(tab[i], tab[i + 1]);
                trie = false;
            }
        }
    }

    return nb_comparaison;
}

size_t triShell(std::vector<int>& tab) {
    size_t nb_comparaison = 0;
    size_t n = tab.size();
    for (int esp = n / 2; esp > 0; esp /= 2) {
        for (int i = esp; i < n; ++i) {
            int temp = tab[i];
            int j;
            for (j = i; j >= esp && tab[j - esp] > temp; j -= esp) {
                tab[j] = tab[j - esp];
                nb_comparaison++;
            }

            tab[j] = temp;
        }
    }

    return nb_comparaison;
}