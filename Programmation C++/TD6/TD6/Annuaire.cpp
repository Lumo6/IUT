#include "Annuaire.h"

std::list< std::shared_ptr<Employe>> Annuaire::RechercheEmploye(std::string nom, std::string prenom)
{
    std::list< std::shared_ptr<Employe>> temp;

    for (std::shared_ptr<Employe> it : listemp)
        if (it->GetNom() == nom && it->GetPrenom() == prenom)
            temp.push_back(it);
    return temp;
}

std::list< std::shared_ptr<Etudiant>> Annuaire::RechercheEtudiant(std::string nom, std::string prenom)
{
    std::list< std::shared_ptr<Etudiant>> temp;
    for (auto& it : listetu)
        if (it->GetNom() == nom && it->GetPrenom() == prenom)
            temp.push_back(it);
    return temp;
}
