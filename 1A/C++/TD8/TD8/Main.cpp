#include "CVecteur.h"

int main() {
	try {
		CVecteur<double> vec;
		vec.resize(3);
		for (size_t i = 0; i < vec.size(); i++) {
			vec[i] = i * 1.0;
		}
		CVecteur<double> vec2;
		vec2.resize(3);
		for (size_t i = 0; i < vec2.size(); i++) {
			vec2[i] = i * 1.0;
		}
		CVecteur<double> vec3;
		vec3.resize(4);
		for (size_t i = 0; i < vec3.size(); i++) {
			vec3[i] = i * 1.0;
		}
		std::cout << vec <<"\n";
		std::cout << vec2 << "\n";
		std::cout << vec3 << "\n";

		CVecteur<double> vec4 = vec + vec2;
		std::cout << vec4 << "\n";
		CVecteur<double> vec5 = vec - vec2;
		std::cout << vec5 << "\n";
		/*CVecteur<double> vec6 = vec + vec3;
		std::cout << vec6 << "\n";
		CVecteur<double> vec7 = vec - vec3;
		std::cout << vec7 << "\n";*/
		std::cout << "Choisir une case du tableau de taille : " << vec.size() << ".\n";
		size_t n;
		std::cin >> n;
		std::cout << vec[n];


	}
	catch (int n) {
		switch (n) {
		case 0: {
			std::cerr << "Indice hors limite\n";
			break;
		}
		case 1: {
			std::cerr << "Paramètre incorrect\n";
			break;
		}
		case 2: {
			std::cerr << "Les tailles ne correspondent pas\n";
			break;
		}
		case 3: {
			std::cerr << "?\n";
			break;
		}
		default: {
			std::cerr << "Ah bon!\n";
			break;
		}
		}
	}
}