// src/Cuvant.cpp
#include "Cuvant.h"
#include "TablaScrabble.h"
#include "Celula.h"
#include <algorithm>
#include <cctype>
#include <locale>
#include <iostream>

Cuvant::Cuvant(const std::string& cuvant, int x, int y, Directie directie) :
    litere(cuvant), x(x), y(y), directie(directie) {}

const std::string& Cuvant::getCuvant() const {
    return litere;
}

int Cuvant::getX() const {
    return x;
}

int Cuvant::getY() const {
    return y;
}

Directie Cuvant::getDirectie() const {
    return directie;
}

bool Cuvant::verificaValiditate(const TablaScrabble& tabla) const {
    int length = litere.length();
    if (x < 0 || y < 0) return false;  // Must not be negative

    // Check bounds based on direction.
    if (directie == Directie::Orizontal && x + length > TablaScrabble::BOARD_SIZE) return false;
    if (directie == Directie::Vertical && y + length > TablaScrabble::BOARD_SIZE) return false;

    bool connectsToExistingWord = tabla.isBoardEmpty(); // First word doesn't need to connect

    // Check for overlaps and connections
    for (int i = 0; i < length; ++i) {
        int currentX = (directie == Directie::Orizontal) ? x + i : x;
        int currentY = (directie == Directie::Vertical) ? y + i : y;

        if (!tabla.isCellEmpty(currentX, currentY) && tabla.getCellLetter(currentX, currentY) != litere[i]) {
            return false; // Overlap with a different letter
        }

        if (!connectsToExistingWord) {
            if (!tabla.isCellEmpty(currentX, currentY)) {
                connectsToExistingWord = true; // Overlaps with existing word
            } else {
                // Check adjacent cells for connections
                if ((currentY > 0 && !tabla.isCellEmpty(currentX, currentY - 1)) ||
                    (currentY < TablaScrabble::BOARD_SIZE - 1 && !tabla.isCellEmpty(currentX, currentY + 1)) ||
                    (currentX > 0 && !tabla.isCellEmpty(currentX - 1, currentY)) ||
                    (currentX < TablaScrabble::BOARD_SIZE - 1 && !tabla.isCellEmpty(currentX + 1, currentY))) {
                    connectsToExistingWord = true;
                }
            }
        }
    }

    // First word must cover the center cell
    if (tabla.isBoardEmpty() && !connectsToExistingWord) {
        bool centerCovered = false;
        for (int i = 0; i < length; ++i) {
            int currentX = (directie == Directie::Orizontal) ? x + i : x;
            int currentY = (directie == Directie::Vertical) ? y + i : y;
            if (currentX == TablaScrabble::CENTER_CELL_X && currentY == TablaScrabble::CENTER_CELL_Y) {
                centerCovered = true;
                break;
            }
        }
        if (!centerCovered) return false;
    }

    if (!connectsToExistingWord && !tabla.isBoardEmpty()) return false; // Must connect to existing words

    return true;
}

int Cuvant::calculeazaScor(const TablaScrabble& tabla) const {
    int scor = 0;
    int factorCuvant = 1;

    for (size_t i = 0; i < litere.length(); ++i) {
        int xPos = x + (directie == Directie::Orizontal ? i : 0);
        int yPos = y + (directie == Directie::Vertical ? i : 0);

        const Celula& celula = tabla.getCelula(xPos, yPos);
        int valoareLitera = getValoareLitera(litere[i]);

        if (celula.getEfectSpecial() == EfectSpecial::DubluLitera) {
            valoareLitera *= 2;
        } else if (celula.getEfectSpecial() == EfectSpecial::TripluLitera) {
            valoareLitera *= 3;
        }

        scor += valoareLitera;

        if (celula.getEfectSpecial() == EfectSpecial::DubluCuvant) {
            factorCuvant *= 2;
        } else if (celula.getEfectSpecial() == EfectSpecial::TripluCuvant) {
            factorCuvant *= 3;
        }
    }

    return scor * factorCuvant;
}

int Cuvant::getValoareLitera(char litera) const {
    switch (litera) {
        case 'A': case 'E': case 'I': case 'O': case 'U': case 'L': case 'N': case 'S': case 'T': case 'R':
            return 1;
        case 'D': case 'G':
            return 2;
        case 'B': case 'C': case 'M': case 'P':
            return 3;
        case 'F': case 'H': case 'V': case 'W': case 'Y':
            return 4;
        case 'K':
            return 5;
        case 'J': case 'X':
            return 8;
        case 'Q': case 'Z':
            return 10;
        default:
            return 0; // Handle blank tiles or invalid characters
    }
}
