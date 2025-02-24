// src/Jucator.cpp
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
        std::cerr << "Jucatorul " << nume << " nu are literele necesare pentru cuvantul '" << cuvant.getCuvant() << "'." << std::endl;
        return false;
    }

    if (!tabla.verificaCuvant(cuvant)) {
        std::cerr << "Cuvantul '" << cuvant.getCuvant() << "' nu este valid pe tabla." << std::endl;
        return false;
    }

    if (tabla.adaugaCuvant(cuvant)) {
        int puncte = cuvant.calculeazaScor(tabla);
        adaugaScor(puncte);
        std::cout << "Jucatorul " << nume << " a jucat cuvantul '" << cuvant.getCuvant() << "' pentru " << puncte << " puncte." << std::endl;
        return true;
    } else {
        std::cerr << "Eroare la adaugarea cuvantului pe tabla." << std::endl;
        return false;
    }
}

void Jucator::schimbaLitere(PungaLitere& punga) {
    punga.inlocuiesteLitere(suport);
    tiles.clear();
    suport.clear();
    punga.distribuieLitere(suport, 7);
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

std::vector<char>& Jucator::getSuport() {
    return suport;
}

bool Jucator::areLiterele(const std::string& cuvant) const {
    std::vector<char> tempSuport = suport;
    for (char literaCuvant : cuvant) {
        bool found = false;
        for (size_t i = 0; i < tempSuport.size(); ++i) {
            if (tempSuport[i] == literaCuvant) {
                tempSuport.erase(tempSuport.begin() + i);
                found = true;
                break;
            }
        }
        if (!found) {
            return false;
        }
    }
    return true;
}


std::vector<std::string> Jucator::sugereazaCuvinte(const std::unordered_set<std::string>& dictionar) const {
    std::vector<std::string> sugestii;
    std::string suportString(suport.begin(), suport.end());
    std::sort(suportString.begin(), suportString.end());

    for (const std::string& cuvant : dictionar) {
        if (cuvant.length() <= suport.size()) {
            std::string cuvantSortat = cuvant;
            std::sort(cuvantSortat.begin(), cuvantSortat.end());
            if (std::includes(suportString.begin(), suportString.end(), cuvantSortat.begin(), cuvantSortat.end())) {
                 if (areLiterele(cuvant))
                    sugestii.push_back(cuvant);
            }
        }
    }
    return sugestii;
}


void Jucator::initializeTiles(float startX, float startY, float tileSize, float tileSpacing) {
    tiles.clear();
    float x = startX;
    for (char litera : suport) {
        tiles.emplace_back(litera, x, startY, tileSize);
        x += tileSize + tileSpacing;
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
    auto it = std::remove_if(tiles.begin(), tiles.end(), [&](const Tile& t) {
        return &t == tile;
    });
    tiles.erase(it, tiles.end());

    for (size_t i = 0; i < suport.size(); ++i) {
        if (suport[i] == tile->getLetter()) {
            suport.erase(suport.begin() + i);
            break;
        }
    }
}


std::vector<Tile>& Jucator::getTiles() {
    return tiles;
}

void Jucator::resetTilesPositions(float startX, float startY, float tileSize, float tileSpacing) {
    float x = startX;
    for (Tile& tile : tiles) {
        tile.setPosition(x, startY);
        tile.setDragging(false);
        tile.setPlacedOnBoard(false); // Reset placed on board status
        x += tileSize + tileSpacing;
    }
}
