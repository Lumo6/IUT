#include "etudiant.h"

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    char elem = 't';
    std::vector<etudiant> promo;
    while (elem != 'q') {
        std::cout << "'a' : Ajouter étudiant" << std::endl
            << "'s' : Supprimer étudiant" << std::endl
            << "'p' : Affiche la promotion" << std::endl
            << "'q' : Quitter" << std::endl
            << "Votre choix : ";
        std::cin >> elem;
        switch (elem) {
        case 'a': {
            std::string nom, prenom;
            short j, m, y;
            std::cout << "Entrez le nom, le prénom puis la date de naissance." << std::endl;
            std::cin >> nom >> prenom >> j>> m >> y;
            CDate dateR = {j,m,y};
            promo.push_back(etudiant{ nom, prenom, dateR});
            break;
        }
        case 's': {
            std::string nom;
            std::cout << "Choisir le nom de l'etudiant à supprimer." << std::endl;
            std::cin >> nom;
            for (int i = 0; i < promo.size();i++) {
                if (promo[i].verifnom(nom)) {
                    promo.erase(promo.begin()+i);
                }
            }
            break;
        }
        case 'p': {;
            std::sort(promo.begin(), promo.end(), [](etudiant & a, etudiant & b) -> bool
                { return a.getnom() < b.getnom(); });
            for (auto element : promo) {
                element.Affichertexte();
            }
            break;
        }
        case 'q': {
            break;
        }
        default: {
            std::cout << "Choisissez un caractère correcte" << std::endl;
        }
        }
    }
}
