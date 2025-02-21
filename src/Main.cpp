#include "JocScrabble.h"
#include <iostream>

int main() {
    int numarJucatori;

    std::cout << "Introduceti numarul de jucatori (2-4): ";
    std::cin >> numarJucatori;
	// Clear the input buffer
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (numarJucatori < 2 || numarJucatori > 4) {
        std::cerr << "Numar de jucatori invalid." << std::endl;
        return 1;
    }

    JocScrabble joc(numarJucatori);

    for (int i = 0; i < numarJucatori; ++i) {
        std::string numeJucator;
        std::cout << "Introduceti numele jucatorului " << i + 1 << ": ";
        std::getline(std::cin, numeJucator); // Use getline to handle spaces in names
        joc.adaugaJucator(numeJucator);
    }

    joc.run(); // Start the game loop

    return 0;
}
