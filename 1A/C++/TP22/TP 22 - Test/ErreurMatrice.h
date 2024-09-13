/*!
 * \file  "ErreurMatrice.h"
 *
 * \brief Déclaration de la classe CErreurMatrice.
 *
 * \author Benjamin ALBOUY-KISSI
 * \date 2016
 *
 * \todo Déclarer dans le fichier ErreurMatrice.h la classe CErreurMatrice
 */
#ifndef ERREURMATRICE_H
#define ERREURMATRICE_H

#include <string>
#include <iostream>

class CErreurMatrice
{
private:
    int codeErreur;
    std::string fonctionErreur;

public:
    CErreurMatrice(int code, const std::string& fonction)
        : codeErreur(code), fonctionErreur(fonction) {}

    int getCodeErreur() const { return codeErreur; }

    const std::string& getFonctionErreur() const { return fonctionErreur; }

    
};

std::ostream& operator<<(std::ostream& os, CErreurMatrice err )
{
    switch (err.getCodeErreur()) {
    case 1: {
        os << "Erreur " << err.getCodeErreur() << " dans la fonction " << err.getFonctionErreur()<<", vous essayez de lire une case en dehors de la matrice !";
        break;
    }
    case 2: {
        os << "Erreur " << err.getCodeErreur() << " dans la fonction " << err.getFonctionErreur() << ", vous essayez de faire interagir 3 matrice de taille incompatible !";
        break;
    }
    default: {
        os << "Erreur " << err.getCodeErreur() << " dans la fonction " << err.getFonctionErreur() << ", vous etes un génis car cette erreur n'est pas implémenté  !";
        break;
    }
    }
    
    return os;
}
#endif
