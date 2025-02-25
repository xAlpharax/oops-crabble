// src/JocScrabble.cpp
#include "JocScrabble.h"
#include <iostream>
#include <sstream>
#include <algorithm>

// Constants for UI elements and game parameters
namespace Constants {
    const float TileSize = 40.0f;
    const float TileSpacing = 9.0f;
    const float RackStartY = 609.0f;
    const float RackStartX = 9.0f;
    const float ScoreDisplayStartY = 650.0f;
    const float ScoreDisplaySpacing = 20.0f;
    const float ButtonWidth = 100.0f;
    const float ButtonHeight = 40.0f;
    const float ButtonStartY = 9.0f; // Buttons at the top
    const float ButtonStartX = 650.0f; // Buttons moved to the right side
    const float ButtonSpacingY = 50.0f; // Vertical spacing for buttons on the right
    const float SuggestionStartX = 600.0f;
    const float SuggestionStartY = 202.0f;
    const float SuggestionSpacing = 20.0f;
    const int MaxSuggestionsDisplayed = 20;
    const int FontSizeSmall = 18;
    const int FontSizeMedium = 20;
    const int FontSizeLarge = 24;
    const sf::Color ButtonColor = sf::Color::Blue;
    const sf::Color ButtonTextColor = sf::Color::White;
    const sf::Color SuggestionTextColor = sf::Color::Yellow;
    const sf::Color ScoreTextColor = sf::Color::White;
    const sf::Color CurrentWordTextColor = sf::Color::White;
    const float CurrentWordTextStartX = 352.0f; // Start X for current word text on the right
    const float CurrentWordTextStartY = 650.0f; // Y position for current word text, adjusted on right
    const float MessageTextStartX = 352.0f; // Start X for message text on the right
    const float MessageTextStartY = 670.0f; // Y position for message text, adjusted on right
}

JocScrabble::JocScrabble(int numarJucatori) :
    jucatorCurentIndex(0),
    numarJucatori(numarJucatori),
    gameOver(false),
    draggedTile(nullptr),
    tileSize(Constants::TileSize)
{
    if (!font.loadFromFile("Inconsolata-Regular.ttf")) {
        std::cerr << "Eroare la incarcarea fontului!" << std::endl;
        exit(1);
    }
    initializeUI();
    currentWordText.setFont(font);
    currentWordText.setCharacterSize(Constants::FontSizeMedium);
    currentWordText.setFillColor(Constants::CurrentWordTextColor);
    currentWordText.setPosition(Constants::CurrentWordTextStartX, Constants::CurrentWordTextStartY); // Position updated to right
    messageText.setFont(font);
    messageText.setCharacterSize(Constants::FontSizeMedium);
    messageText.setFillColor(Constants::ScoreTextColor);
    messageText.setPosition(Constants::MessageTextStartX, Constants::MessageTextStartY); // Position updated to right
}

void JocScrabble::adaugaJucator(const std::string& nume) {
    if (jucatori.size() < numarJucatori) {
        jucatori.emplace_back(nume);
    }
}

void JocScrabble::incepeJoc() {
    for (auto& jucator : jucatori) {
        pungaLitere.distribuieLitere(jucator.getSuport(), 7);
        jucator.initializeTiles(Constants::RackStartX, Constants::RackStartY, tileSize, Constants::TileSpacing);
    }
    updateMessage("Incepe jocul! Jucatorul " + jucatori[jucatorCurentIndex].getNume() + " este primul.");
}

void JocScrabble::afiseazaScoruri(sf::RenderWindow& window) const {
    int startY = Constants::ScoreDisplayStartY;
    int spacing = Constants::ScoreDisplaySpacing;
    for (size_t i = 0; i < jucatori.size(); ++i) {
        sf::Text text(jucatori[i].getNume() + ": " + std::to_string(jucatori[i].getScor()), font, Constants::FontSizeMedium);
        text.setFillColor(Constants::ScoreTextColor);
        text.setPosition(10, startY + i * spacing);
        window.draw(text);
    }
}

bool JocScrabble::allPlayersPassed() {
    return pungaLitere.isEmpty() && jucatori[jucatorCurentIndex].getSuport().empty();
}

void JocScrabble::nextTurn() {
    jucatorCurentIndex = (jucatorCurentIndex + 1) % jucatori.size();
    jucatori[jucatorCurentIndex].resetTilesPositions(Constants::RackStartX, Constants::RackStartY, tileSize, Constants::TileSpacing);
    afiseazaSugestiiFlag = false;
    sugestiiCurente.clear();
    inputCuvant.clear();
    updateCurrentWordDisplay();
    placedTilesThisTurn.clear();
    updateMessage("Este randul jucatorului " + jucatori[jucatorCurentIndex].getNume() + ".");
}

void JocScrabble::mutaJucator() {
    if (placedTilesThisTurn.empty()) {
        updateMessage("Nici o litera plasata. Randul a fost pierdut.");
        nextTurn();
        return;
    }

    if (!verificaPlasareCuvant()) {
        clearBoardAndTiles();
        return; // verificaPlasareCuvant handles message updates
    }

    Cuvant cuvantPlasat = construiesteCuvant();
    if (!jucatori[jucatorCurentIndex].joacaCuvant(cuvantPlasat, tablaScrabble)) {
        clearBoardAndTiles();
        updateMessage("Cuvant invalid. Reincearca.");
        return;
    }

    finalizeazaMutare(cuvantPlasat.getCuvant().length());
}

bool JocScrabble::verificaPlasareCuvant() {
    bool isHorizontal = esteOrizontal();
    std::sort(placedTilesThisTurn.begin(), placedTilesThisTurn.end(),
              [isHorizontal](const auto& a, const auto& b) {
                  return isHorizontal ? a.first < b.first : a.second < b.second;
              });

    std::string wordString = construiesteStringCuvant(isHorizontal);
    Cuvant cuvantTest(wordString, placedTilesThisTurn[0].first, placedTilesThisTurn[0].second,
                      isHorizontal ? Directie::Orizontal : Directie::Vertical);

    if (!cuvantTest.verificaValiditate(tablaScrabble)) {
        updateMessage("Plasare invalida a cuvantului.");
        return false;
    }
    return true;
}


Cuvant JocScrabble::construiesteCuvant() {
    bool isHorizontal = esteOrizontal();
    std::sort(placedTilesThisTurn.begin(), placedTilesThisTurn.end(),
              [isHorizontal](const auto& a, const auto& b) {
                  return isHorizontal ? a.first < b.first : a.second < b.second;
              });

    std::string wordString = construiesteStringCuvant(isHorizontal);
    return Cuvant(wordString, placedTilesThisTurn[0].first, placedTilesThisTurn[0].second,
                  isHorizontal ? Directie::Orizontal : Directie::Vertical);
}

std::string JocScrabble::construiesteStringCuvant(bool isHorizontal) {
    std::string wordString;
    int startX = placedTilesThisTurn[0].first;
    int startY = placedTilesThisTurn[0].second;

    if (isHorizontal) {
        for (int x = startX; x < TablaScrabble::BOARD_SIZE; ++x) {
            char letter = tablaScrabble.getCellLetter(x, startY);
            if (letter == ' ') break;
            wordString += letter;
        }
    } else {
        for (int y = startY; y < TablaScrabble::BOARD_SIZE; ++y) {
            char letter = tablaScrabble.getCellLetter(startX, y);
            if (letter == ' ') break;
            wordString += letter;
        }
    }
    return wordString;
}


bool JocScrabble::esteOrizontal() const {
    if (placedTilesThisTurn.empty()) return true; // Default to horizontal if no tiles

    bool isHorizontal = true;
    int firstY = placedTilesThisTurn[0].second;
    for (const auto& pos : placedTilesThisTurn) {
        if (pos.second != firstY) {
            isHorizontal = false;
            break;
        }
    }
    return isHorizontal;
}


void JocScrabble::finalizeazaMutare(int wordLength) {
    Cuvant cuvantPlasat = construiesteCuvant();
    int scorMutare = cuvantPlasat.calculeazaScor(tablaScrabble);
    jucatori[jucatorCurentIndex].adaugaScor(scorMutare);

    std::stringstream ss;
    ss << "Cuvantul '" << cuvantPlasat.getCuvant() << "' a fost plasat pentru " << scorMutare << " puncte.";
    updateMessage(ss.str());


    for (const auto& pos : placedTilesThisTurn) {
        for (auto& tile : jucatori[jucatorCurentIndex].getTiles()) {
            if (tile.getLetter() == tablaScrabble.getCellLetter(pos.first, pos.second) && !tile.isPlaced()) {
                jucatori[jucatorCurentIndex].removeTile(&tile);
                tile.setPlaced(true); // Mark tile as placed
                break;
            }
        }
    }

    pungaLitere.distribuieLitere(jucatori[jucatorCurentIndex].getSuport(), wordLength);
    jucatori[jucatorCurentIndex].initializeTiles(Constants::RackStartX, Constants::RackStartY, tileSize, Constants::TileSpacing);
    nextTurn();
}


void JocScrabble::finalizeazaJoc() {
    gameOver = true;
    int maxScore = -1;
    std::string winnerName = "";
    for (const auto& jucator : jucatori) {
        if (jucator.getScor() > maxScore) {
            maxScore = jucator.getScor();
            winnerName = jucator.getNume();
        }
    }
    std::stringstream ss;
    ss << "Jocul s-a terminat! Castigatorul este " << winnerName
       << " cu scorul " << maxScore << " puncte!";
    updateMessage(ss.str());
}

void JocScrabble::processInput(sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
            handleMouseClick(mousePos);
        }
    } else if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Left && draggedTile) {
            sf::Vector2f mousePos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
            handleMouseRelease(mousePos);
        }
    } else if (event.type == sf::Event::MouseMoved) {
        if (draggedTile) {
            draggedTile->setPosition(event.mouseMove.x - dragOffset.x, event.mouseMove.y - dragOffset.y);
            updateCurrentWordDisplay();
        }
    }
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Tab) {
            toggleSugestii();
        }
    }
}

void JocScrabble::handleMouseClick(sf::Vector2f mousePos) {
    for (auto& button : buttons) {
        if (button.isClicked(mousePos)) {
            button.onClick();
            return;
        }
    }
    Tile* clickedTile = jucatori[jucatorCurentIndex].getTileAt(mousePos);
    if (clickedTile) {
        startDraggingTile(clickedTile, mousePos);
    }
}

void JocScrabble::startDraggingTile(Tile* tile, sf::Vector2f mousePos) {
    draggedTile = tile;
    dragOffset = mousePos - draggedTile->getPosition();
    draggedTile->setDragging(true);
}


void JocScrabble::updateGame() {
    if (pungaLitere.isEmpty() && jucatori[jucatorCurentIndex].getSuport().empty()) {
        finalizeazaJoc();
    }
}

void JocScrabble::renderGame(sf::RenderWindow& window) {
    tablaScrabble.deseneaza(window);
    jucatori[jucatorCurentIndex].drawTiles(window);
    afiseazaScoruri(window);
    window.draw(currentWordText);
    window.draw(messageText);
    if (afiseazaSugestiiFlag) {
        afiseazaSugestii(window, sugestiiCurente);
    }
    for (const auto& button : buttons) {
        button.draw(window);
    }
}

void JocScrabble::run() {
    sf::RenderWindow window(sf::VideoMode(800, 750), "Scrabble");
    incepeJoc();
    while (window.isOpen() && !gameOver) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            processInput(event);
        }
        updateGame();
        window.clear();
        renderGame(window);
        window.display();
    }
    finalizeazaJoc(); // Call finalizeGame one last time to display the final message
}

void JocScrabble::afiseazaSugestii(sf::RenderWindow& window, const std::vector<std::string>& sugestii) const {
    int startX = Constants::SuggestionStartX;
    int startY = Constants::SuggestionStartY;
    int spacing = Constants::SuggestionSpacing;
    for (size_t i = 0; i < std::min((int)sugestii.size(), Constants::MaxSuggestionsDisplayed); ++i) {
        sf::Text text(sugestii[i], font, Constants::FontSizeSmall);
        text.setFillColor(Constants::SuggestionTextColor);
        text.setPosition(startX, startY + i * spacing);
        window.draw(text);
    }
}

JocScrabble::Button::Button(const std::string& text, const sf::Font& font, sf::Vector2f position, sf::Vector2f size, std::function<void()> action)
    : onClick(action)
{
    shape.setSize(size);
    shape.setPosition(position);
    shape.setFillColor(Constants::ButtonColor);
    shape.setOutlineThickness(1);
    shape.setOutlineColor(sf::Color::White);

    label.setFont(font);
    label.setString(text);
    label.setCharacterSize(Constants::FontSizeMedium);
    label.setFillColor(Constants::ButtonTextColor);
    centerTextInButton();
}

void JocScrabble::Button::centerTextInButton() {
    sf::FloatRect textBounds = label.getLocalBounds();
    label.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    label.setPosition(shape.getPosition().x + shape.getSize().x / 2.0f, shape.getPosition().y + shape.getSize().y / 2.0f);
}


void JocScrabble::Button::draw(sf::RenderWindow& window) const {
    window.draw(shape);
    window.draw(label);
}

bool JocScrabble::Button::isClicked(sf::Vector2f mousePos) {
    return shape.getGlobalBounds().contains(mousePos);
}

void JocScrabble::initializeUI() {
    float buttonStartY = Constants::ButtonStartY;
    float buttonStartX = Constants::ButtonStartX;
    float buttonSpacing = Constants::ButtonSpacingY;

    buttons.emplace_back("Submit", font, sf::Vector2f(buttonStartX, buttonStartY), sf::Vector2f(Constants::ButtonWidth, Constants::ButtonHeight), [this]() {
        mutaJucator();
    });
    buttonStartY += buttonSpacing;
    buttons.emplace_back("Exchange", font, sf::Vector2f(buttonStartX, buttonStartY), sf::Vector2f(Constants::ButtonWidth, Constants::ButtonHeight), [this]() {
        schimbaLitereCurentJucator();
    });
    buttonStartY += buttonSpacing;
    buttons.emplace_back("Clear", font, sf::Vector2f(buttonStartX, buttonStartY), sf::Vector2f(Constants::ButtonWidth, Constants::ButtonHeight), [this]() {
        clearBoardAndTiles();
    });
    buttonStartY += buttonSpacing;
    buttons.emplace_back("Pass", font, sf::Vector2f(buttonStartX, buttonStartY), sf::Vector2f(Constants::ButtonWidth, Constants::ButtonHeight), [this]() {
        nextTurn();
    });
}

void JocScrabble::schimbaLitereCurentJucator() {
    jucatori[jucatorCurentIndex].schimbaLitere(pungaLitere);
    jucatori[jucatorCurentIndex].initializeTiles(Constants::RackStartX, Constants::RackStartY, tileSize, Constants::TileSpacing);
    nextTurn();
    clearBoardAndTiles();
    updateMessage("Litere schimbate. Randul a fost pierdut.");
}


void JocScrabble::clearBoardAndTiles() {
    for (int y = 0; y < TablaScrabble::BOARD_SIZE; ++y) {
        for (int x = 0; x < TablaScrabble::BOARD_SIZE; ++x) {
            tablaScrabble.clearCell(x, y);
        }
    }
    jucatori[jucatorCurentIndex].resetTilesPositions(Constants::RackStartX, Constants::RackStartY, tileSize, Constants::TileSpacing);
    inputCuvant.clear();
    updateCurrentWordDisplay();
    placedTilesThisTurn.clear();
    for (auto& tile : jucatori[jucatorCurentIndex].getTiles()) {
        tile.setPlaced(false); // Reset placed status when clearing board
    }
    updateMessage("Tabla a fost stearsa.");
}

void JocScrabble::handleMouseRelease(sf::Vector2f mousePos) {
    if (!draggedTile) return;

    int boardX = static_cast<int>(mousePos.x / tileSize);
    int boardY = static_cast<int>(mousePos.y / tileSize);

    if (isValidBoardPosition(boardX, boardY)) {
        if (canPlaceTile(boardX, boardY)) {
            placeTileOnBoard(draggedTile, boardX, boardY);
        } else {
            returnTileToRack();
        }
    } else {
        returnTileToRack();
    }

    stopDraggingTile();
    updateCurrentWordDisplay();
}

bool JocScrabble::isValidBoardPosition(int x, int y) const {
    return x >= 0 && x < TablaScrabble::BOARD_SIZE && y >= 0 && y < TablaScrabble::BOARD_SIZE;
}


void JocScrabble::returnTileToRack() {
    jucatori[jucatorCurentIndex].resetTilesPositions(Constants::RackStartX, Constants::RackStartY, tileSize, Constants::TileSpacing);
}

void JocScrabble::stopDraggingTile() {
    draggedTile->setDragging(false);
    draggedTile = nullptr;
}


void JocScrabble::placeTileOnBoard(Tile* tile, int boardX, int boardY) {
    tablaScrabble.placeLetter(boardX, boardY, tile->getLetter());
    tile->setPosition(boardX * tileSize, boardY * tileSize);
    tile->setPlacedOnBoard(true); // Mark tile as placed on board

    bool alreadyPlaced = false;
    for (const auto& pos : placedTilesThisTurn) {
        if (pos.first == boardX && pos.second == boardY) {
            alreadyPlaced = true;
            break;
        }
    }
    if (!alreadyPlaced) {
        placedTilesThisTurn.emplace_back(boardX, boardY);
    }
    inputCuvant += tile->getLetter();
}

bool JocScrabble::canPlaceTile(int boardX, int boardY) {
    if (!isValidBoardPosition(boardX, boardY)) return false;
    if (!tablaScrabble.isCellEmpty(boardX, boardY)) return false;
    if (tablaScrabble.isBoardEmpty()) {
        return boardX == TablaScrabble::CENTER_CELL_X && boardY == TablaScrabble::CENTER_CELL_Y;
    }

    return isAdjacentToExistingTile(boardX, boardY);
}

bool JocScrabble::isAdjacentToExistingTile(int boardX, int boardY) {
    if (boardX > 0 && !tablaScrabble.isCellEmpty(boardX - 1, boardY)) return true;
    if (boardX < TablaScrabble::BOARD_SIZE - 1 && !tablaScrabble.isCellEmpty(boardX + 1, boardY)) return true;
    if (boardY > 0 && !tablaScrabble.isCellEmpty(boardX, boardY - 1)) return true;
    if (boardY < TablaScrabble::BOARD_SIZE - 1 && !tablaScrabble.isCellEmpty(boardX, boardY + 1)) return true;
    return false;
}


void JocScrabble::updateCurrentWordDisplay() {
    std::stringstream ss;
    for (const auto& pos : placedTilesThisTurn) {
        ss << tablaScrabble.getCellLetter(pos.first, pos.second);
    }
    currentWordText.setString("Cuvant curent: " + ss.str());
}

void JocScrabble::updateMessage(const std::string& message) {
    messageText.setString(message);
}

void JocScrabble::toggleSugestii() {
    afiseazaSugestiiFlag = !afiseazaSugestiiFlag;
    if (afiseazaSugestiiFlag) {
        sugestiiCurente = jucatori[jucatorCurentIndex].sugereazaCuvinte(tablaScrabble.getDictionar());
    } else {
        sugestiiCurente.clear();
    }
}
