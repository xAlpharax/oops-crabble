// src/Main.cpp
#include "JocScrabble.h"
#include <iostream>
#include <limits>

int main() {
    int numarJucatori;

    std::cout << "Introduceti numarul de jucatori (2-4): ";
    while (!(std::cin >> numarJucatori) || numarJucatori < 2 || numarJucatori > 4) {
        std::cout << "Input invalid. Introduceti un numar intre 2 si 4: ";
        std::cin.clear(); //clear bad input flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    JocScrabble joc(numarJucatori);

    for (int i = 0; i < numarJucatori; ++i) {
        std::string numeJucator;
        std::cout << "Introduceti numele jucatorului " << i + 1 << ": ";
        std::getline(std::cin, numeJucator);
        joc.adaugaJucator(numeJucator);
    }

    joc.run();

    return 0;
}
