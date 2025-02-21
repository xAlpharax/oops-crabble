#ifndef JUCATOR_H
#define JUCATOR_H

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Cuvant.h"
#include <unordered_set>
#include "Tile.h" // Include the Tile class

class PungaLitere;
class TablaScrabble;

class Jucator {
public:
    Jucator(const std::string& nume);
    const std::string& getNume() const;
    int getScor() const;
    void adaugaScor(int puncte);
    bool joacaCuvant(Cuvant cuvant, TablaScrabble& tabla); // Keep this for final validation
    void schimbaLitere(PungaLitere& punga);
    void adaugaLitera(char litera);
    void scoateLitera(char litera);
    //void afiseazaSuport(sf::RenderWindow& window, int x, int y) const; // Remove old display
    bool areLiterele(const std::string& cuvant) const;
    std::vector<char>& getSuport(); // Keep for PungaLitere interaction
    std::vector<std::string> sugereazaCuvinte(const std::unordered_set<std::string>& dictionar) const;

    // --- Drag-and-Drop Related ---
    void initializeTiles(float startX, float startY, float tileSize); // Create Tile objects
    void drawTiles(sf::RenderWindow& window) const;
    Tile* getTileAt(sf::Vector2f point); // Find a tile at a given position
    void removeTile(Tile* tile); // Remove a tile from the rack (after placing on board)
    std::vector<Tile>& getTiles(); // Access the tiles directly
    void resetTilesPositions(float startX, float startY, float tileSize); //Added reset tile positions


private:
    std::string nume;
    std::vector<char> suport; // Still keep the char vector for letter management
    int scor;
    std::vector<Tile> tiles; // Store Tile objects for display and interaction
};

#endif
