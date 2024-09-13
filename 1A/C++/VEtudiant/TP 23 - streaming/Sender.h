/*!
 * \file  "Sender.h"
 *
 * \brief Déclaration de la classe CSender.
 *
 * \author Benjamin ALBOUY-KISSI
 * \date   29/03/2020
 *
 */
#pragma once
#include <string>
#include <list>
#include <vector>

/*! \brief Simule un serveur de streaming
 *
 * Cette classe est utilisée pour simuler l'envoie de données en streaming. Les données sont simulées
 * par une longue chaîne de caractères découpée en paquets correspondants aux mots composant la chaîne.
 */
class CSender
{
  //!\brief Données à transférer
  const std::string m_strText = "Comment le C++ sauvera-t-il le monde ? C'est très simple. Le C++ sauvera le monde pour deux raisons. La première, c'est que le C++ est un des langages de programmation les plus performants en terme d'économie d'énergie et de ressources naturelles. Le pragmatisme de l'expression du langage vous permet de décrire des algorithmes très optimisés en terme d'espace mémoire ou de vitesse d'exécution, à l'inverse des langages de programmation dit modernes tels le java ou le C# (ne parlons pas des langages \"web\" qui ne méritent même pas d'être appelés langages de programmation). En effet la machinerie complexe permettant aux programmes écrits dans ces langages de fonctionner a un coût énorme en terme de performance. Vous devez savoir que les programmes écrits dans ces langages ne sont pas exécutés directement par le processeur, mais interprétés par une \"machine virtuelle\" se chargeant de traduire ses instructions dans le jeu d'instruction du processeur hôte. De plus, ces langages ne vous permettent pas de gérer directement la mémoire, laissant le soin à la machine virtuelle de gérer les allocations et les désallocations grâce à ce que l'on appelle un \"rammasse miette\". On ne sait pas trop quand le rammasse miette libère la mémoire des objets détruits. Le fait-il dès qu'il détecte qu'un objet n'est plus utilisé (comment le détecte-t-il ?) ou libère-t-il la mémoire lorsque les ressources de la machine hôte deviennent trop utilisées (quel seuil ?). On ne sait pas ! J'en viens donc maintenant à exprimer la deuxième raison pour laquelle le C++ va sauver le monde. Apprendre le C++ est une tâche sans fin tellement ce langage est subtil. Et cette tâche est personnelle. Donc quand on apprend le C++, on reste seul devant son ordinateur de nombreuses heures, journées voire années, limitant ainsi les contacts avec les autres êtres vivants (humains ou non), évitant de transmettre divers virus #restezchezvous. Voilà voilà, bon j'imagine que si vous lisez ça c'est que vous avez un programme qui fonctionne, donc vous êtes bien parti pour avoir une bonne note. Félicitations ! Bon je dois vous laisser maintenant...";
  std::list<std::vector<char>> m_lstPackets;                  //!< Cette liste contient le découpage en mots de la chaîne de caractères
  std::list<std::vector<char>>::const_iterator m_itCurPacket; //!< Itératuer de la liste de paquet pointant vers le prochain paquet à envoyer

public:
  //!\brief Initialise la liste de paquets à partir de la chaîne de caractères m_strText
  CSender();
  std::vector<char> SendNextPacket(size_t maxSize);
};

