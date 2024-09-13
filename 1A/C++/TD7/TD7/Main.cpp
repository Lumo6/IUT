#include "CTab.h"

int main() {
	//CTab tab;

	CTab<double,5> tab;

	CTab<int,5> tab2;

	for (auto* p = tab.begin(); p != tab.end(); p++) {
		*p = p - tab.begin() + 1.1;
	}
	std::cout << tab;

	tab2 = tab;
	std::cout << tab2;
	return 0;
}