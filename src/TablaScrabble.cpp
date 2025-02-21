#include "TablaScrabble.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cctype>

TablaScrabble::TablaScrabble() : tabla(15, std::vector<Celula>(15)) {
    // Initialize board (no changes here)
    tabla[0][3].setEfectSpecial(EfectSpecial::DubluLitera);
    tabla[0][11].setEfectSpecial(EfectSpecial::DubluLitera);
    tabla[2][6].setEfectSpecial(EfectSpecial::DubluLitera);
    tabla[2][8].setEfectSpecial(EfectSpecial::DubluLitera);
    tabla[3][0].setEfectSpecial(EfectSpecial::DubluLitera);
    tabla[3][7].setEfectSpecial(EfectSpecial::DubluLitera);
    tabla[3][14].setEfectSpecial(EfectSpecial::DubluLitera);
    tabla[6][2].setEfectSpecial(EfectSpecial::DubluLitera);
    tabla[6][6].setEfectSpecial(EfectSpecial::DubluLitera);
    tabla[6][8].setEfectSpecial(EfectSpecial::DubluLitera);
    tabla[6][12].setEfectSpecial(EfectSpecial::DubluLitera);
    tabla[7][3].setEfectSpecial(EfectSpecial::DubluLitera);
    tabla[7][11].setEfectSpecial(EfectSpecial::DubluLitera);
    tabla[8][2].setEfectSpecial(EfectSpecial::DubluLitera);
    tabla[8][6].setEfectSpecial(EfectSpecial::DubluLitera);
    tabla[8][8].setEfectSpecial(EfectSpecial::DubluLitera);
    tabla[8][12].setEfectSpecial(EfectSpecial::DubluLitera);
    tabla[11][0].setEfectSpecial(EfectSpecial::DubluLitera);
    tabla[11][7].setEfectSpecial(EfectSpecial::DubluLitera);
    tabla[11][14].setEfectSpecial(EfectSpecial::DubluLitera);
    tabla[12][6].setEfectSpecial(EfectSpecial::DubluLitera);
    tabla[12][8].setEfectSpecial(EfectSpecial::DubluLitera);
    tabla[14][3].setEfectSpecial(EfectSpecial::DubluLitera);
    tabla[14][11].setEfectSpecial(EfectSpecial::DubluLitera);
    tabla[1][5].setEfectSpecial(EfectSpecial::TripluLitera);
    tabla[1][9].setEfectSpecial(EfectSpecial::TripluLitera);
    tabla[5][1].setEfectSpecial(EfectSpecial::TripluLitera);
    tabla[5][5].setEfectSpecial(EfectSpecial::TripluLitera);
    tabla[5][9].setEfectSpecial(EfectSpecial::TripluLitera);
    tabla[5][13].setEfectSpecial(EfectSpecial::TripluLitera);
    tabla[9][1].setEfectSpecial(EfectSpecial::TripluLitera);
    tabla[9][5].setEfectSpecial(EfectSpecial::TripluLitera);
    tabla[9][9].setEfectSpecial(EfectSpecial::TripluLitera);
    tabla[9][13].setEfectSpecial(EfectSpecial::TripluLitera);
    tabla[13][5].setEfectSpecial(EfectSpecial::TripluLitera);
    tabla[13][9].setEfectSpecial(EfectSpecial::TripluLitera);
    tabla[1][1].setEfectSpecial(EfectSpecial::DubluCuvant);
    tabla[2][2].setEfectSpecial(EfectSpecial::DubluCuvant);
    tabla[3][3].setEfectSpecial(EfectSpecial::DubluCuvant);
    tabla[4][4].setEfectSpecial(EfectSpecial::DubluCuvant);
    tabla[10][10].setEfectSpecial(EfectSpecial::DubluCuvant);
    tabla[11][11].setEfectSpecial(EfectSpecial::DubluCuvant);
    tabla[12][12].setEfectSpecial(EfectSpecial::DubluCuvant);
    tabla[13][13].setEfectSpecial(EfectSpecial::DubluCuvant);
    tabla[1][13].setEfectSpecial(EfectSpecial::DubluCuvant);
    tabla[2][12].setEfectSpecial(EfectSpecial::DubluCuvant);
    tabla[3][11].setEfectSpecial(EfectSpecial::DubluCuvant);
    tabla[4][10].setEfectSpecial(EfectSpecial::DubluCuvant);
    tabla[13][1].setEfectSpecial(EfectSpecial::DubluCuvant);
    tabla[12][2].setEfectSpecial(EfectSpecial::DubluCuvant);
    tabla[11][3].setEfectSpecial(EfectSpecial::DubluCuvant);
    tabla[10][4].setEfectSpecial(EfectSpecial::DubluCuvant);
    tabla[7][7].setEfectSpecial(EfectSpecial::TripluCuvant);
    tabla[0][0].setEfectSpecial(EfectSpecial::TripluCuvant);
    tabla[0][7].setEfectSpecial(EfectSpecial::TripluCuvant);
    tabla[0][14].setEfectSpecial(EfectSpecial::TripluCuvant);
    tabla[7][0].setEfectSpecial(EfectSpecial::TripluCuvant);
    tabla[7][14].setEfectSpecial(EfectSpecial::TripluCuvant);
    tabla[14][0].setEfectSpecial(EfectSpecial::TripluCuvant);
    tabla[14][7].setEfectSpecial(EfectSpecial::TripluCuvant);
    tabla[14][14].setEfectSpecial(EfectSpecial::TripluCuvant);
    cuvinteJucate = loadDictionary("word-list-ro.txt");
}

std::string TablaScrabble::toUpper(const std::string& s) const {
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c){ return std::toupper(c); });
    return result;
}

std::unordered_set<std::string> TablaScrabble::loadDictionary(const std::string& filename) {
    std::unordered_set<std::string> dictionary;
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string word;
        while (std::getline(file, word)) {
            dictionary.insert(toUpper(word));
        }
        file.close();
    } else {
        std::cerr << "Nu s-a putut deschide fisierul cu dictionarul: " << filename << std::endl;
        exit(1);
    }
    return dictionary;
}

bool TablaScrabble::adaugaCuvant(const Cuvant& cuvant) {
    if (!verificaCuvant(cuvant)) {
        return false;
    }
    int length = cuvant.getCuvant().length();
    for (int i = 0; i < length; ++i) {
        int x = cuvant.getX();
        int y = cuvant.getY();
        if (cuvant.getDirectie() == Directie::Orizontal) {
            x += i;
        } else {
            y += i;
        }
        tabla[y][x].setLitera(cuvant.getCuvant()[i]);
    }
    return true;
}

bool TablaScrabble::isBoardEmpty() const {
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            if (tabla[i][j].getLitera() != ' ') {
                return false;
            }
        }
    }
    return true;
}
bool TablaScrabble::verificaCuvant(const Cuvant& cuvant) const {
    // 1. Check if the main word is in the dictionary.
    std::string upperCuvant = toUpper(cuvant.getCuvant());
    if (cuvinteJucate.find(upperCuvant) == cuvinteJucate.end()) {
        std::cerr << "Cuvantul '" << cuvant.getCuvant() << "' nu este in dictionar." << std::endl;
        return false;
    }

    // 2. Check board-specific rules (Cuvant's internal checks).
    if (!cuvant.verificaValiditate(*this)) {
        std::cerr << "Plasare invalida (reguli interne ale cuvantului)." << std::endl;
        return false;
    }

    // --- Use a temporary board for checking ---
    std::vector<std::vector<Celula>> tempTabla = tabla;

    // --- TEMPORARILY place letters on the temporary board for cross-word checking ---
    int length = cuvant.getCuvant().length();
    for (int i = 0; i < length; ++i) {
        int x = cuvant.getX();
        int y = cuvant.getY();
        if (cuvant.getDirectie() == Directie::Orizontal) {
            x += i;
        } else {
            y += i;
        }
        // Place on the temporary board
        tempTabla[y][x].setLitera(cuvant.getCuvant()[i]);
    }

    // 3. Check for cross-words (using the temporary board)
    bool validCrossWords = true;
    for (int i = 0; i < length; ++i) {
        int currentX = (cuvant.getDirectie() == Directie::Orizontal) ? cuvant.getX() + i : cuvant.getX();
        int currentY = (cuvant.getDirectie() == Directie::Vertical) ? cuvant.getY() + i : cuvant.getY();

        // Check BOTH horizontal and vertical cross-words for EACH letter
        std::string horizontalWord;
        int startX = currentX;
        while (startX > 0 && tempTabla[currentY][startX - 1].getLitera() != ' ') startX--;
        while (startX < 15 && tempTabla[currentY][startX].getLitera() != ' ') {
            horizontalWord += tempTabla[currentY][startX].getLitera();
            startX++;
        }
        if (horizontalWord.length() > 1 && cuvinteJucate.find(toUpper(horizontalWord)) == cuvinteJucate.end()) {
            std::cerr << "Cuvantul orizontal format '" << horizontalWord << "' nu este valid." << std::endl;
            validCrossWords = false;
            break;
        }

        std::string verticalWord;
        int startY = currentY;
        while (startY > 0 && tempTabla[startY - 1][currentX].getLitera() != ' ') startY--;
        while (startY < 15 && tempTabla[startY][currentX].getLitera() != ' ') {
            verticalWord += tempTabla[startY][currentX].getLitera();
            startY++;
        }
        if (verticalWord.length() > 1 && cuvinteJucate.find(toUpper(verticalWord)) == cuvinteJucate.end()) {
            std::cerr << "Cuvantul vertical format '" << verticalWord << "' nu este valid." << std::endl;
            validCrossWords = false;
            break;
        }
    }

    return validCrossWords;
}

void TablaScrabble::deseneaza(sf::RenderWindow& window) const {
    int cellSize = 40;
    for (int y = 0; y < 15; ++y) {
        for (int x = 0; x < 15; ++x) {
            // --- DRAWING LOGIC HERE (moved from Celula) ---
            sf::RectangleShape shape(sf::Vector2f(cellSize, cellSize));
            shape.setOutlineThickness(1);
            shape.setOutlineColor(sf::Color::Black);
            shape.setPosition(sf::Vector2f(x * cellSize, y * cellSize));

            // Set the fill color based on the cell's effect
            switch (tabla[y][x].getEfectSpecial()) {
                case EfectSpecial::Normal:
                    shape.setFillColor(sf::Color(200, 200, 200)); // Light Gray
                    break;
                case EfectSpecial::DubluLitera:
                    shape.setFillColor(sf::Color(173, 216, 230)); // Light Blue
                    break;
                case EfectSpecial::TripluLitera:
                    shape.setFillColor(sf::Color(0, 0, 255));   // Blue
                    break;
                case EfectSpecial::DubluCuvant:
                    shape.setFillColor(sf::Color(255, 182, 193)); // Light Pink
                    break;
                case EfectSpecial::TripluCuvant:
                    shape.setFillColor(sf::Color(255, 0, 0));   // Red
                    break;
            }
            window.draw(shape);

            // Draw the letter (if any)
            if (tabla[y][x].getLitera() != ' ') {
                sf::Font font;
                if (!font.loadFromFile("Inconsolata-Regular.ttf")) {
                    return; // Handle font loading error
                }
                sf::Text text(std::string(1, tabla[y][x].getLitera()), font, cellSize / 2);
                text.setFillColor(sf::Color::Black);
                // Center the text within the cell
                sf::FloatRect textBounds = text.getLocalBounds();
                text.setOrigin(textBounds.left + textBounds.width / 2.0f,
                               textBounds.top + textBounds.height / 2.0f);
                text.setPosition(x * cellSize + cellSize / 2.0f,
                                 y * cellSize + cellSize / 2.0f);
                window.draw(text);
            }
             // Draw effect text
            if (tabla[y][x].getEfectSpecial() != EfectSpecial::Normal) {
                sf::Font font;
                if (!font.loadFromFile("Inconsolata-Regular.ttf")) {
                    return; // Handle font loading error
                }
                std::string effectText = "";
                switch (tabla[y][x].getEfectSpecial())
                {
                case EfectSpecial::Normal:
                    break;
                case EfectSpecial::DubluLitera:
                    effectText = "DL";
                    break;
                case EfectSpecial::TripluLitera:
                    effectText = "TL";
                    break;
                case EfectSpecial::DubluCuvant:
                    effectText = "DC";
                    break;
                case EfectSpecial::TripluCuvant:
                    effectText = "TC";
                    break;
                default:
                    break;
                }
                sf::Text text(effectText, font, cellSize / 4);
                text.setFillColor(sf::Color::Black);
                text.setPosition(x * cellSize, y * cellSize);
                window.draw(text);
            }
        }
    }
}

bool TablaScrabble::isCellEmpty(int x, int y) const {
    if (x < 0 || x >= 15 || y < 0 || y >= 15) {
        return false;
    }
    return tabla[y][x].esteGoala();
}

char TablaScrabble::getCellLetter(int x, int y) const {
    if (x < 0 || x >= 15 || y < 0 || y >= 15) {
        return ' ';
    }
    return tabla[y][x].getLitera();
}

const Celula& TablaScrabble::getCelula(int x, int y) const {
    if (x < 0 || x >= 15 || y < 0 || y >= 15) {
        return tabla[0][0]; // Return a reference to a valid cell
    }
    return tabla[y][x];
}

void TablaScrabble::clearCell(int x, int y) {
    if (x >= 0 && x < 15 && y >= 0 && y < 15) {
        tabla[y][x].setLitera(' ');
    }
}
