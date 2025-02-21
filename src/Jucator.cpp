#include "Jucator.h"
#include "PungaLitere.h"
#include "TablaScrabble.h"
#include <algorithm>
#include <iostream>
#include <unordered_set>

Jucator::Jucator(const std::string& nume) : nume(nume), scor(0) {}

const std::string& Jucator::getNume() const {
    return nume;
}

int Jucator::getScor() const {
    return scor;
}

void Jucator::adaugaScor(int puncte) {
    scor += puncte;
}

bool Jucator::joacaCuvant(Cuvant cuvant, TablaScrabble& tabla) {
   if (!areLiterele(cuvant.getCuvant())) {
        std::cerr << "Jucatorul " << nume << " nu are literele necesare." << std::endl;
        return false;
    }

    if (!cuvant.verificaValiditate(tabla)) {
        std::cerr << "Cuvantul nu este valid." << std::endl;
        return false;
    }

    if (tabla.adaugaCuvant(cuvant)) {
        int puncte = cuvant.calculeazaScor(tabla);
        adaugaScor(puncte);
        return true;
    }

    return false;
}

void Jucator::schimbaLitere(PungaLitere& punga) {
    // Return the player's letters to the bag.
    for (char litera : suport) {
        punga.inlocuiesteLitere(suport);
    }
    tiles.clear(); // Clear old tiles
    suport.clear();
    punga.distribuieLitere(suport, 7); // Assuming 7 is the hand size
}

void Jucator::adaugaLitera(char litera) {
    suport.push_back(litera);
}

void Jucator::scoateLitera(char litera) {
    auto it = std::find(suport.begin(), suport.end(), litera);
    if (it != suport.end()) {
        suport.erase(it);
    }
}
std::vector<char>& Jucator::getSuport()
{
    return suport;
}

bool Jucator::areLiterele(const std::string& cuvant) const {
    std::vector<char> tempSuport = suport; // Work with a copy
    for (char litera : cuvant) {
        auto it = std::find(tempSuport.begin(), tempSuport.end(), litera);
        if (it == tempSuport.end()) {
            return false; // Letter not found
        }
        tempSuport.erase(it); // Remove the letter (to handle duplicates)
    }
    return true;
}

std::vector<std::string> Jucator::sugereazaCuvinte(const std::unordered_set<std::string>& dictionar) const {
    std::vector<std::string> sugestii;
    std::vector<char> tempSuport = suport;

    for (const std::string& cuvant : dictionar) {
        bool posibil = true;
        std::vector<char> temp = tempSuport; // Copy of player's letters

        for (char litera : cuvant) {
            auto it = std::find(temp.begin(), temp.end(), litera);
            if (it == temp.end()) {
                posibil = false;
                break;
            }
            temp.erase(it); // Remove letter *from the copy*
        }

        if (posibil) {
            sugestii.push_back(cuvant);
        }
    }
    return sugestii;
}

// --- Drag-and-Drop Implementation ---

void Jucator::initializeTiles(float startX, float startY, float tileSize) {
    tiles.clear(); // Clear any existing tiles
    float x = startX;
    for (char litera : suport) {
        tiles.emplace_back(litera, x, startY, tileSize);
        x += tileSize + 5; // Spacing between tiles
    }
}

void Jucator::drawTiles(sf::RenderWindow& window) const {
    for (const Tile& tile : tiles) {
        tile.draw(window);
    }
}

Tile* Jucator::getTileAt(sf::Vector2f point) {
    for (Tile& tile : tiles) {
        if (tile.contains(point)) {
            return &tile;
        }
    }
    return nullptr;
}

void Jucator::removeTile(Tile* tile) {
    // Find and remove the tile from the 'tiles' vector.
    auto it = std::find_if(tiles.begin(), tiles.end(), [&](const Tile& t) {
        return &t == tile;
    });
    if (it != tiles.end()) {
        tiles.erase(it);
    }
}

std::vector<Tile>& Jucator::getTiles() {
    return tiles;
}
void Jucator::resetTilesPositions(float startX, float startY, float tileSize)
{
    float x = startX;
    for (Tile& tile : tiles)
    {
        tile.setPosition(x, startY);
        tile.setDragging(false); // Reset dragging state
        x += tileSize + 5;
    }
}
