#ifndef JOC_SCRABBLE_H
#define JOC_SCRABBLE_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "TablaScrabble.h"
#include "PungaLitere.h"
#include "Jucator.h"
#include "Tile.h"
#include <functional>

class JocScrabble {
public:
    JocScrabble(int numarJucatori);
    void incepeJoc();
    void mutaJucator(); // Will be significantly changed
    void finalizeazaJoc();
    void adaugaJucator(const std::string& nume);
    void run();
    void afiseazaScoruri(sf::RenderWindow& window) const;
    void afiseazaSugestii(sf::RenderWindow& window, const std::vector<std::string>& sugestii) const;

    // --- UI Elements ---
    struct Button {
        sf::RectangleShape shape;
        sf::Text label;
        std::function<void()> onClick; // Function to call when clicked

        Button(const std::string& text, const sf::Font& font, sf::Vector2f position, sf::Vector2f size, std::function<void()> action);
        void draw(sf::RenderWindow& window) const;
        bool isClicked(sf::Vector2f mousePos);
    };


private:
    TablaScrabble tabla;
    PungaLitere punga;
    std::vector<Jucator> jucatori;
    int jucatorCurent;
    int numarJucatori;
    bool gameOver;
    bool inputState; // Might not be needed anymore
    sf::Font font;
    std::string inputCuvant; // Keep for displaying formed word
    int inputX; // No longer needed
    int inputY; // No longer needed
    Directie inputDirectie; // No longer needed
    std::vector<std::string> sugestiiCurente;
    bool afiseazaSugestiiFlag = false;

    // --- Drag-and-Drop ---
    Tile* draggedTile;
    sf::Vector2f dragOffset;
    float tileSize;

    // --- UI ---
    std::vector<Button> buttons;
    sf::Text currentWordText; // Display the word being formed
    void initializeUI();
    void handleMousePress(sf::Vector2f mousePos);
    void handleMouseRelease(sf::Vector2f mousePos);
    void placeTileOnBoard(Tile* tile, int boardX, int boardY);
    bool canPlaceTile(int boardX, int boardY, char letter);
    void updateCurrentWordDisplay(); // Update the displayed word
    void clearBoardAndTiles(); // Function to clear tiles placed on the board
    void nextTurn(); // Go to the next turn

    void processInput(sf::Event& event);
    void updateGame();
    void renderGame(sf::RenderWindow& window);
    bool allPlayersPassed();

    // --- NEW: Track Placed Tiles ---
    std::vector<std::pair<int, int>> placedTilesThisTurn;
};

#endif
