// src/JocScrabble.h
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
    void mutaJucator();
    void finalizeazaJoc();
    void adaugaJucator(const std::string& nume);
    void run();
    void afiseazaScoruri(sf::RenderWindow& window) const;
    void afiseazaSugestii(sf::RenderWindow& window, const std::vector<std::string>& sugestii) const;

    struct Button {
        sf::RectangleShape shape;
        sf::Text label;
        std::function<void()> onClick;

        Button(const std::string& text, const sf::Font& font, sf::Vector2f position, sf::Vector2f size, std::function<void()> action);
        void draw(sf::RenderWindow& window) const;
        bool isClicked(sf::Vector2f mousePos);
    private:
        void centerTextInButton();
    };


private:
    TablaScrabble tablaScrabble;
    PungaLitere pungaLitere;
    std::vector<Jucator> jucatori;
    int jucatorCurentIndex;
    int numarJucatori;
    bool gameOver;
    sf::Font font;
    std::string inputCuvant;
    std::vector<std::string> sugestiiCurente;
    bool afiseazaSugestiiFlag = false;

    Tile* draggedTile;
    sf::Vector2f dragOffset;
    float tileSize;

    std::vector<Button> buttons;
    sf::Text currentWordText;
    sf::Text messageText;

    void initializeUI();
    void handleMouseClick(sf::Vector2f mousePos);
    void handleMouseRelease(sf::Vector2f mousePos);
    void placeTileOnBoard(Tile* tile, int boardX, int boardY);
    bool canPlaceTile(int boardX, int boardY);
    void updateCurrentWordDisplay();
    void clearBoardAndTiles();
    void nextTurn();
    void processInput(sf::Event& event);
    void updateGame();
    void renderGame(sf::RenderWindow& window);
    bool allPlayersPassed();

    std::vector<std::pair<int, int>> placedTilesThisTurn;
    bool verificaPlasareCuvant();
    Cuvant construiesteCuvant();
    std::string construiesteStringCuvant(bool isHorizontal);
    bool esteOrizontal() const;
    void finalizeazaMutare(int wordLength);
    void updateMessage(const std::string& message);
    void toggleSugestii();
    void startDraggingTile(Tile* tile, sf::Vector2f mousePos);
    bool isValidBoardPosition(int x, int y) const;
    void returnTileToRack();
    void stopDraggingTile();
    bool isAdjacentToExistingTile(int boardX, int boardY);
    void schimbaLitereCurentJucator();
};

namespace Constants {
    extern const float TileSize;
    extern const float TileSpacing;
    extern const float RackStartY;
    extern const float RackStartX;
    extern const float ScoreDisplayStartY;
    extern const float ScoreDisplaySpacing;
    extern const float ButtonWidth;
    extern const float ButtonHeight;
    extern const float ButtonStartY; // Buttons at the top
    extern const float ButtonStartX; // Buttons moved to the right side
    extern const float ButtonSpacingY; // Vertical spacing for buttons on the right
    extern const float SuggestionStartX;
    extern const float SuggestionStartY;
    extern const float SuggestionSpacing;
    extern const int MaxSuggestionsDisplayed;
    extern const int FontSizeSmall;
    extern const int FontSizeMedium;
    extern const int FontSizeLarge;
    extern const sf::Color ButtonColor;
    extern const sf::Color ButtonTextColor;
    extern const sf::Color SuggestionTextColor;
    extern const sf::Color ScoreTextColor;
    extern const sf::Color CurrentWordTextColor;
    extern const float CurrentWordTextStartX; // Start X for current word text on the right
    extern const float CurrentWordTextStartY; // Y position for current word text, adjusted on right
    extern const float MessageTextStartX; // Start X for message text on the right
    extern const float MessageTextStartY; // Y position for message text, adjusted on right
}


#endif
