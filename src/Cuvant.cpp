#include "Cuvant.h"
#include "TablaScrabble.h"
#include "Celula.h"
#include <algorithm>
#include <cctype>
#include <locale>

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
    if (x < 0 || y < 0) return false;  //Must not be negative

    // Check bounds based on direction.
    if (directie == Directie::Orizontal && x + length > 15) return false;
    if (directie == Directie::Vertical && y + length > 15) return false;

    bool connects = tabla.isBoardEmpty(); // If the board is empty, we don't need to connect.

    // Check for overlap and collect newly formed words.
    for (int i = 0; i < length; ++i) {
        int currentX = (directie == Directie::Orizontal) ? x + i : x;
        int currentY = (directie == Directie::Vertical) ? y + i : y;

        // Check if the cell is occupied by a *different* letter.
        if (!tabla.isCellEmpty(currentX, currentY) &&
            tabla.getCellLetter(currentX, currentY) != litere[i]) {
            return false;
        }
        // Check for adjacency to existing letters.
        if (!connects)
        {
            if (!tabla.isCellEmpty(currentX, currentY))
            {
                connects = true; // It overlaps with existing letters
            }
            else
            {
                 // Check adjacent cells (up, down, left, right).
                if (currentY > 0 && !tabla.isCellEmpty(currentX, currentY - 1)) connects = true;
                if (currentY < 14 && !tabla.isCellEmpty(currentX, currentY + 1)) connects = true;
                if (currentX > 0 && !tabla.isCellEmpty(currentX - 1, currentY)) connects = true;
                if (currentX < 14 && !tabla.isCellEmpty(currentX + 1, currentY)) connects = true;
            }
        }
    }

    //The first word MUST go through the center
    if(tabla.isBoardEmpty() && !connects)
    {
        bool centerCovered = false;
        for (int i = 0; i < length; i++)
        {
            int currentX = (directie == Directie::Orizontal) ? x + i : x;
            int currentY = (directie == Directie::Vertical) ? y + i : y;
            if (currentX == 7 && currentY == 7)
                centerCovered = true;
        }
        if(!centerCovered)
            return false;
    }

    if (!connects) return false; // Must connect if not the first word.

    return true; // All checks passed.
}

int Cuvant::calculeazaScor(const TablaScrabble& tabla) const {
  int scor = 0;
    int factorCuvant = 1;

    for (size_t i = 0; i < litere.length(); ++i) {
        int xPos = x;
        int yPos = y;

        if (directie == Directie::Orizontal) {
            xPos += i;
        } else {
            yPos += i;
        }

        const Celula& celula = tabla.getCelula(xPos, yPos);
        int valoareLitera = 0; // You'll need a function to get letter values.
        switch (litere[i]) {
            // Assign point values to each letter (this is a simplified example)
            case 'A': case 'E': case 'I': case 'O': case 'U': case 'L': case 'N': case 'S': case 'T': case 'R':
                valoareLitera = 1; break;
            case 'D': case 'G':
                valoareLitera = 2; break;
            case 'B': case 'C': case 'M': case 'P':
                valoareLitera = 3; break;
            case 'F': case 'H': case 'V': case 'W': case 'Y':
                valoareLitera = 4; break;
            case 'K':
                valoareLitera = 5; break;
            case 'J': case 'X':
                valoareLitera = 8; break;
            case 'Q': case 'Z':
                valoareLitera = 10; break;
            default:
                valoareLitera = 0; // Handle blank tiles or invalid characters
        }


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
