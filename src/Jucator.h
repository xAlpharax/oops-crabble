// src/Jucator.h
#ifndef JUCATOR_H
#define JUCATOR_H

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Cuvant.h"
#include <unordered_set>
#include "Tile.h"

class PungaLitere;
class TablaScrabble;

class Jucator {
public:
    Jucator(const std::string& nume);
    const std::string& getNume() const;
    int getScor() const;
    void adaugaScor(int puncte);
    bool joacaCuvant(Cuvant cuvant, TablaScrabble& tabla);
    void schimbaLitere(PungaLitere& punga);
    void adaugaLitera(char litera);
    void scoateLitera(char litera);
    bool areLiterele(const std::string& cuvant) const;
    std::vector<char>& getSuport();
    std::vector<std::string> sugereazaCuvinte(const std::unordered_set<std::string>& dictionar) const;

    void initializeTiles(float startX, float startY, float tileSize, float tileSpacing);
    void drawTiles(sf::RenderWindow& window) const;
    Tile* getTileAt(sf::Vector2f point);
    void removeTile(Tile* tile);
    std::vector<Tile>& getTiles();
    void resetTilesPositions(float startX, float startY, float tileSize, float tileSpacing);


private:
    std::string nume;
    std::vector<char> suport;
    int scor;
    std::vector<Tile> tiles;
};

#endif
