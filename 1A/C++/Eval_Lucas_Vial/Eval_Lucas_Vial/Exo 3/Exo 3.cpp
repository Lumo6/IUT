#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>
#include <vector>
#include <sstream>
#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32

int main()
{
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif // _WIN32

    int c = 0;
    std::cout << "Choisir le fichier 1 ou 2.";
    std::cin >> c;
    if (c == 1) {
        std::vector<std::string> entetes;
        std::ifstream fichierIn("inputUTF8_1.csv");
        if (!fichierIn.is_open())
        {
            std::cerr << "Erreur lors de l'ouverture du fichier." << std::endl;
            return 1;
        }

        std::string Mot;

        // Lire la première ligne pour obtenir les entêtes
        if (std::getline(fichierIn, Mot))
        {
            std::istringstream entetesStream(Mot);
            std::string ligne;
            while (std::getline(entetesStream, ligne, ','))
            {
                entetes.push_back(ligne);
            }
            entetes.push_back("Moyenne");
        }
        else
        {
            std::cerr << "Le fichier est vide." << std::endl;
            fichierIn.close();
            return 1;
        }


        for (const auto& cat : entetes)
        {
            std::cout << std::setw(20) << cat;
        }
        std::cout << std::endl;

        const float Nbnotes = 2.0;
        const int taille = 3;

        std::vector<std::vector<std::string>> etudiants;
        std::vector<std::vector<std::string>> notess;
        std::string ligne;

        while (std::getline(fichierIn, ligne))
        {
            std::istringstream ligneStream(ligne);
            std::vector<std::string> etudiant;
            std::vector<std::string> note;
            std::string info;
            int notes[taille];
            for (int i = 0; i < Nbnotes; i++) {
                notes[i] = 0;
            }
            if (std::getline(ligneStream, info, ','))
            {
                etudiant.push_back(info);
            }
            if (std::getline(ligneStream, info, ','))
            {
                etudiant.push_back(info);
            }
            for (int i = 0; i < Nbnotes; i++) {
                if (std::getline(ligneStream, info, ','))
                {
                    note.push_back(info);
                    notes[i] = std::stod(info);
                }
            }
            double moy = 0;
            for (int i = 0; i < Nbnotes; i++) {
                moy += notes[i];
            }
            moy = moy / Nbnotes;
            std::string moys = std::to_string(moy);
            note.push_back(moys);
            etudiants.push_back(etudiant);
            notess.push_back(note);
        }
        fichierIn.close();

        for (int i = 0; i < etudiants.size(); i++) {
            for (int j = 0; j < 2; j++) {
                std::cout << std::setw(20) << etudiants[i][j];
            }
            for (int j = 0; j < Nbnotes + 1; j++) {
                std::cout << std::setw(19) << notess[i][j];
            }
            std::cout << std::endl;
        }

        std::ofstream fichierOut("outputUTF8_1.csv");
        if (fichierOut.is_open())
        {

            for (int i = 0; i < entetes.size(); i++) {
                fichierOut << entetes[i];
            }
            fichierOut << std::endl;
            for (int i = 0; i < etudiants.size(); i++) {
                for (int j = 0; j < 2; j++) {
                    fichierOut << etudiants[i][j];
                    fichierOut << ",";
                }
                for (int j = 0; j < Nbnotes + 1; j++) { //nombre de notes + moyenne = Nbnotes + 1 colomne dans le tableau
                    fichierOut << notess[i][j];
                    if (j != notess[i].size() - 1) {
                        fichierOut << ",";
                    }
                }
                fichierOut << std::endl;
            }
        }
        else
        {
            std::cerr << "Erreur lors de l'ouverture du fichier de sortie." << std::endl;
            return 1;
        }

    }
else if (c == 2) {
    std::vector<std::string> entetes;
    std::ifstream fichierIn("inputUTF8_2.csv");
    if (!fichierIn.is_open())
    {
        std::cerr << "Erreur lors de l'ouverture du fichier." << std::endl;
        return 1;
    }

    std::string Mot;

    // Lire la première ligne pour obtenir les entêtes
    if (std::getline(fichierIn, Mot))
    {
        std::istringstream entetesStream(Mot);
        std::string ligne;
        while (std::getline(entetesStream, ligne, ','))
        {
            entetes.push_back(ligne);
        }
        entetes.push_back("Moyenne");
    }
    else
    {
        std::cerr << "Le fichier est vide." << std::endl;
        fichierIn.close();
        return 1;
    }


    for (const auto& cat : entetes)
    {
        std::cout << std::setw(20) << cat;
    }
    std::cout << std::endl;

    const float Nbnotes = 3.0;
    const int taille = 3;

    std::vector<std::vector<std::string>> etudiants;
    std::vector<std::vector<std::string>> notess;
    std::string ligne;

    while (std::getline(fichierIn, ligne))
    {
        std::istringstream ligneStream(ligne);
        std::vector<std::string> etudiant;
        std::vector<std::string> note;
        std::string info;
        int notes[taille];
        for (int i = 0; i < Nbnotes; i++) {
            notes[i] = 0;
        }
        if (std::getline(ligneStream, info, ','))
        {
            etudiant.push_back(info);
        }
        if (std::getline(ligneStream, info, ','))
        {
            etudiant.push_back(info);
        }
        for (int i = 0; i < Nbnotes; i++) {
            if (std::getline(ligneStream, info, ','))
            {
                note.push_back(info);
                notes[i] = std::stod(info);
            }
        }
        double moy = 0;
        for (int i = 0; i < Nbnotes; i++) {
            moy += notes[i];
        }
        moy = moy / Nbnotes;
        std::string moys = std::to_string(moy);
        note.push_back(moys);
        etudiants.push_back(etudiant);
        notess.push_back(note);
    }
    fichierIn.close();

    for (int i = 0; i < etudiants.size(); i++) {
        for (int j = 0; j < 2; j++) {
            std::cout << std::setw(20) << etudiants[i][j];
        }
        for (int j = 0; j < Nbnotes + 1; j++) {
            std::cout << std::setw(19) << notess[i][j];
        }
        std::cout << std::endl;
    }

    std::ofstream fichierOut("outputUTF8_2.csv");
    if (fichierOut.is_open())
    {

        for (int i = 0; i < entetes.size(); i++) {
            fichierOut << entetes[i];
        }
        fichierOut << std::endl;
        for (int i = 0; i < etudiants.size(); i++) {
            for (int j = 0; j < 2; j++) {
                fichierOut << etudiants[i][j];
                fichierOut << ",";
            }
            for (int j = 0; j < Nbnotes + 1; j++) { //nombre de notes + moyenne = Nbnotes + 1 colomne dans le tableau
                fichierOut << notess[i][j];
                if (j != notess[i].size() - 1) {
                    fichierOut << ",";
                }
            }
            fichierOut << std::endl;
        }
        std::cout << notess[1].size() - 1;
    }
    else
    {
        std::cerr << "Erreur lors de l'ouverture du fichier de sortie." << std::endl;
        return 1;
    }

    }
 else {
     std::cout << "Vous n'avez pas choisis entre 1 et 2, le programme se ferme.";
    }
    return 0;

}