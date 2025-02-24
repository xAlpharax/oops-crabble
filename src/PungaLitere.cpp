// src/PungaLitere.cpp
#include "PungaLitere.h"
#include <algorithm>
#include <random>
#include <iostream>

PungaLitere::PungaLitere() {
    // Romanian Scrabble letter distribution
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

    std::random_device rd;
    generator.seed(rd());
}

void PungaLitere::distribuieLitere(std::vector<char>& suport, int numarLitere) {
    if (litere.empty()) {
        return;
    }
    if (litere.size() > 1) {
        std::shuffle(litere.begin(), litere.end(), generator);
    }

    for (int i = 0; i < numarLitere; ++i) {
        if (!litere.empty()) {
            suport.push_back(litere.back());
            litere.pop_back();
        } else {
            break;
        }
    }
}

void PungaLitere::inlocuiesteLitere(std::vector<char>& suport) {
    for (char litera : suport) {
        litere.push_back(litera);
    }
    suport.clear();

    if (litere.size() > 1) {
        std::shuffle(litere.begin(), litere.end(), generator);
    }
    distribuieLitere(suport, 7);
}

bool PungaLitere::isEmpty() const {
    return litere.empty();
}

int PungaLitere::getNumarLitereRamase() const {
    return litere.size();
}
