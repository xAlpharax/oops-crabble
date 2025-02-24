// src/TablaScrabble.cpp
#include "TablaScrabble.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cctype>

const int TablaScrabble::BOARD_SIZE = 15;
const int TablaScrabble::CENTER_CELL_X = 7;
const int TablaScrabble::CENTER_CELL_Y = 7;

TablaScrabble::TablaScrabble() : tabla(BOARD_SIZE, std::vector<Celula>(BOARD_SIZE)) {
    // Initialize special cell effects on the board
    // Double Letter Scores (DL)
    std::vector<std::pair<int, int>> doubleLetterCoords = {
        {0, 3}, {0, 11}, {2, 6}, {2, 8}, {3, 0}, {3, 7}, {3, 14}, {6, 2}, {6, 6}, {6, 8}, {6, 12},
        {7, 3}, {7, 11}, {8, 2}, {8, 6}, {8, 8}, {8, 12}, {11, 0}, {11, 7}, {11, 14}, {12, 6}, {12, 8}, {14, 3}, {14, 11}
    };
    for (const auto& coord : doubleLetterCoords) {
        tabla[coord.first][coord.second].setEfectSpecial(EfectSpecial::DubluLitera);
    }

    // Triple Letter Scores (TL)
    std::vector<std::pair<int, int>> tripleLetterCoords = {
        {1, 5}, {1, 9}, {5, 1}, {5, 5}, {5, 9}, {5, 13}, {9, 1}, {9, 5}, {9, 9}, {9, 13}, {13, 5}, {13, 9}
    };
    for (const auto& coord : tripleLetterCoords) {
        tabla[coord.first][coord.second].setEfectSpecial(EfectSpecial::TripluLitera);
    }

    // Double Word Scores (DW)
    std::vector<std::pair<int, int>> doubleWordCoords = {
        {1, 1}, {2, 2}, {3, 3}, {4, 4}, {10, 10}, {11, 11}, {12, 12}, {13, 13},
        {1, 13}, {2, 12}, {3, 11}, {4, 10}, {13, 1}, {12, 2}, {11, 3}, {10, 4}
    };
    for (const auto& coord : doubleWordCoords) {
        tabla[coord.first][coord.second].setEfectSpecial(EfectSpecial::DubluCuvant);
    }

    // Triple Word Scores (TW)
    std::vector<std::pair<int, int>> tripleWordCoords = {
        {0, 0}, {0, 7}, {0, 14}, {7, 0}, {7, 14}, {14, 0}, {14, 7}, {14, 14}, {7, 7}
    };
    for (const auto& coord : tripleWordCoords) {
        tabla[coord.first][coord.second].setEfectSpecial(EfectSpecial::TripluCuvant);
    }

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

void TablaScrabble::placeLetter(int x, int y, char letter) {
    if (isValidPosition(x, y)) {
        tabla[y][x].setLitera(letter);
    }
}

bool TablaScrabble::adaugaCuvant(const Cuvant& cuvant) {
    if (!verificaCuvant(cuvant)) {
        return false;
    }
    int length = cuvant.getCuvant().length();
    for (int i = 0; i < length; ++i) {
        int x = cuvant.getX() + (cuvant.getDirectie() == Directie::Orizontal ? i : 0);
        int y = cuvant.getY() + (cuvant.getDirectie() == Directie::Vertical ? i : 0);
        if (isValidPosition(x,y))
            tabla[y][x].setLitera(cuvant.getCuvant()[i]);
    }
    return true;
}

bool TablaScrabble::isBoardEmpty() const {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (tabla[i][j].getLitera() != ' ') {
                return false;
            }
        }
    }
    return true;
}

bool TablaScrabble::verificaCuvant(const Cuvant& cuvant) const {
    std::string upperCuvant = toUpper(cuvant.getCuvant());
    if (cuvinteJucate.find(upperCuvant) == cuvinteJucate.end()) {
        std::cerr << "Cuvantul '" << cuvant.getCuvant() << "' nu este in dictionar." << std::endl;
        return false;
    }

    if (!cuvant.verificaValiditate(*this)) {
        std::cerr << "Plasare invalida pentru cuvantul '" << cuvant.getCuvant() << "'." << std::endl;
        return false;
    }

    return true;
}

void TablaScrabble::deseneaza(sf::RenderWindow& window) const {
    int cellSize = 40;
    for (int y = 0; y < BOARD_SIZE; ++y) {
        for (int x = 0; x < BOARD_SIZE; ++x) {
            sf::RectangleShape shape(sf::Vector2f(cellSize, cellSize));
            shape.setOutlineThickness(1);
            shape.setOutlineColor(sf::Color::Black);
            shape.setPosition(sf::Vector2f(x * cellSize, y * cellSize));

            switch (tabla[y][x].getEfectSpecial()) {
                case EfectSpecial::Normal:         shape.setFillColor(sf::Color(200, 200, 200)); break; // Light Gray
                case EfectSpecial::DubluLitera:    shape.setFillColor(sf::Color(173, 216, 230)); break; // Light Blue
                case EfectSpecial::TripluLitera:   shape.setFillColor(sf::Color(0, 0, 255));   break; // Blue
                case EfectSpecial::DubluCuvant:    shape.setFillColor(sf::Color(255, 182, 193)); break; // Light Pink
                case EfectSpecial::TripluCuvant:   shape.setFillColor(sf::Color(255, 0, 0));   break; // Red
            }
            window.draw(shape);

            if (tabla[y][x].getLitera() != ' ') {
                sf::Font font;
                if (!font.loadFromFile("Inconsolata-Regular.ttf")) return;
                sf::Text text(std::string(1, tabla[y][x].getLitera()), font, cellSize / 2);
                text.setFillColor(sf::Color::Black);
                centerTextInCell(text, shape);
                window.draw(text);
            }
            drawEffectText(window, x, y, cellSize);
        }
    }
}

void TablaScrabble::centerTextInCell(sf::Text& text, const sf::RectangleShape& cellShape) const {
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f,
                   textBounds.top + textBounds.height / 2.0f);
    text.setPosition(cellShape.getPosition().x + cellShape.getSize().x / 2.0f,
                     cellShape.getPosition().y + cellShape.getSize().y / 2.0f);
}

void TablaScrabble::drawEffectText(sf::RenderWindow& window, int x, int y, int cellSize) const {
    if (tabla[y][x].getEfectSpecial() != EfectSpecial::Normal) {
        sf::Font font;
        if (!font.loadFromFile("Inconsolata-Regular.ttf")) return;
        std::string effectText = "";
        switch (tabla[y][x].getEfectSpecial()) {
            case EfectSpecial::DubluLitera:  effectText = "DL"; break;
            case EfectSpecial::TripluLitera: effectText = "TL"; break;
            case EfectSpecial::DubluCuvant:  effectText = "DC"; break;
            case EfectSpecial::TripluCuvant: effectText = "TC"; break;
            default: break;
        }
        sf::Text text(effectText, font, cellSize / 4);
        text.setFillColor(sf::Color::Black);
        text.setPosition(x * cellSize + cellSize/8, y * cellSize + cellSize * 0.6f); // Adjust position for better visibility
        window.draw(text);
    }
}


bool TablaScrabble::isCellEmpty(int x, int y) const {
    return isValidPosition(x, y) && tabla[y][x].esteGoala();
}

char TablaScrabble::getCellLetter(int x, int y) const {
    return isValidPosition(x, y) ? tabla[y][x].getLitera() : ' ';
}

const Celula& TablaScrabble::getCelula(int x, int y) const {
    if (!isValidPosition(x, y)) {
        return tabla[0][0]; // Return a default cell if out of bounds, handle carefully!
    }
    return tabla[y][x];
}

void TablaScrabble::clearCell(int x, int y) {
    if (isValidPosition(x, y)) {
        tabla[y][x].setLitera(' ');
    }
}
bool TablaScrabble::isValidPosition(int x, int y) const {
    return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE;
}

const std::unordered_set<std::string>& TablaScrabble::getDictionar() const {
    return cuvinteJucate;
}
