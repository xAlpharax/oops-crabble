// Fisier: PungaLitere.cpp
#include "PungaLitere.h"
#include <algorithm>
#include <random>

// Constructor implicit
PungaLitere::PungaLitere() {
    // Inițializarea punga cu litere (exemplu: distribuție standard Scrabble)
    litere = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
              'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    // Shuffle the letters
    std::shuffle(litere.begin(), litere.end(), std::mt19937{std::random_device{}()});
}

// Distribuie litere către un jucător
void PungaLitere::distribuieLitere(std::vector<char>& suport) {
    // Implementarea logicii pentru a distribui litere către un jucător
}

// Înlocuiește literele unui jucător
void PungaLitere::inlocuiesteLitere(std::vector<char>& suport) {
    // Implementarea logicii pentru a înlocui literele unui jucător
}
