// src/TablaScrabble.h
#ifndef TABLA_SCRABBLE_H
#define TABLA_SCRABBLE_H

#include <vector>
#include <unordered_set>
#include <string>
#include <SFML/Graphics.hpp>
#include "Celula.h"
#include "Cuvant.h"

class TablaScrabble {
public:
    TablaScrabble();
    bool adaugaCuvant(const Cuvant& cuvant);
    bool verificaCuvant(const Cuvant& cuvant) const;
    void deseneaza(sf::RenderWindow& window) const;
    bool isCellEmpty(int x, int y) const;
    char getCellLetter(int x, int y) const;
    const Celula& getCelula(int x, int y) const;
    bool isBoardEmpty() const;
    const std::unordered_set<std::string>& getDictionar() const;
    void clearCell(int x, int y);
    void placeLetter(int x, int y, char letter);
    bool isValidPosition(int x, int y) const;

    static const int BOARD_SIZE;
    static const int CENTER_CELL_X;
    static const int CENTER_CELL_Y;


private:
    std::vector<std::vector<Celula>> tabla;
    std::unordered_set<std::string> cuvinteJucate;
    std::unordered_set<std::string> loadDictionary(const std::string& filename);
    std::string toUpper(const std::string& s) const;
    void centerTextInCell(sf::Text& text, const sf::RectangleShape& cellShape) const;
    void drawEffectText(sf::RenderWindow& window, int x, int y, int cellSize) const;
};

#endif
