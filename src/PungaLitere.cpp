#include "PungaLitere.h"
#include <algorithm>
#include <random>
#include <iostream>

PungaLitere::PungaLitere() {
    // Initialize the bag with the standard Scrabble letter distribution.
    // Romanian distribution (adjust counts as needed)
     // A - 9, B - 2, C - 5, D - 4, E - 10, F - 2, G - 2, H - 2, I - 9, J - 1, L - 4, M - 3,
    // N - 6, O - 6, P - 3, R - 6, S - 6, T - 6, U - 5, V - 2, X - 1, Z - 1, Blank - 2

    std::vector<std::pair<char, int>> distributie = {
        {'A', 9}, {'B', 2}, {'C', 5}, {'D', 4}, {'E', 10}, {'F', 2}, {'G', 2},
        {'H', 2}, {'I', 9}, {'J', 1}, {'L', 4}, {'M', 3}, {'N', 6}, {'O', 6},
        {'P', 3}, {'R', 6}, {'S', 6}, {'T', 6}, {'U', 5}, {'V', 2}, {'X', 1},
        {'Z', 1}
    };

    for (const auto& pereche : distributie) {
        for (int i = 0; i < pereche.second; ++i) {
            litere.push_back(pereche.first);
        }
    }

    // Initialize the random number generator.
    std::random_device rd;
    generator.seed(rd());
}

void PungaLitere::distribuieLitere(std::vector<char>& suport, int numarLitere) {
    if (litere.empty()) {
        return; // Bag is empty
    }
    // Shuffle only if there are enough letters remaining.  Avoids issues
    // with std::shuffle and empty/small ranges.
     if (litere.size() > 1) {
        std::shuffle(litere.begin(), litere.end(), generator);
    }

    // Distribute letters, removing them from the bag.
    for (int i = 0; i < numarLitere; ++i) {
        if (!litere.empty()) {
            suport.push_back(litere.back());
            litere.pop_back();
        } else {
            break; // Stop if the bag becomes empty
        }
    }
}

void PungaLitere::inlocuiesteLitere(std::vector<char>& suport) {
    // Return the player's letters to the bag.
    for (char litera : suport) {
        litere.push_back(litera);
    }
    suport.clear();

     if (litere.size() > 1) {
        std::shuffle(litere.begin(), litere.end(), generator);
    }
    // Draw new letters.
    distribuieLitere(suport, 7); // Assuming 7 is the hand size
}
bool PungaLitere::isEmpty() const
{
    return litere.empty();
}
int PungaLitere::getNumarLitereRamase() const
{
    return litere.size();
}
