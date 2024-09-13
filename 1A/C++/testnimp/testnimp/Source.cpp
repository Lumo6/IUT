#include <iostream>

int main() {
	std::cout << "Please enter the size of the streaming buffer: ";
	size_t nEntry;
	std::cin >> nEntry;
	size_t nSize = 1;
	while (nEntry > nSize) {
		nSize << 1;
	}
	std::cout << nSize;
}