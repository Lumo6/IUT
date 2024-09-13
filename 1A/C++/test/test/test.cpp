#include "etudiant.h"

int main()
{
    etudiant ouais = { "Vial","Lucas" };
    //etudiant yo = { "Detournay" };
    etudiant salut;
    std::cout << ouais.GetNom() << " " << ouais.GetPrenom() << "\n" << salut.GetNom() << " " << salut.GetPrenom();
}
