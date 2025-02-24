#include "JocScrabble.h"
#include <iostream>
#include <sstream>

JocScrabble::JocScrabble(int numarJucatori) :
    jucatorCurent(0),
    numarJucatori(numarJucatori),
    gameOver(false),
    draggedTile(nullptr),
    tileSize(40.0f)
{
    if (!font.loadFromFile("Inconsolata-Regular.ttf")) {
        std::cerr << "Eroare la incarcarea fontului!" << std::endl;
        exit(1);
    }
    initializeUI();
    currentWordText.setFont(font);
    currentWordText.setCharacterSize(20);
    currentWordText.setFillColor(sf::Color::White);
    currentWordText.setPosition(10, 550);
}

void JocScrabble::adaugaJucator(const std::string& nume) {
    if (jucatori.size() < numarJucatori) {
        jucatori.emplace_back(nume);
    }
}

void JocScrabble::incepeJoc() {
    for (auto& jucator : jucatori) {
        punga.distribuieLitere(jucator.getSuport(), 7);
        jucator.initializeTiles(10, 600, tileSize);
    }
}

void JocScrabble::afiseazaScoruri(sf::RenderWindow& window) const {
    int startY = 650;
    int spacing = 30;
    for (size_t i = 0; i < jucatori.size(); ++i) {
        sf::Text text(jucatori[i].getNume() + ": " + std::to_string(jucatori[i].getScor()), font, 20);
        text.setFillColor(sf::Color::White);
        text.setPosition(10, startY + i * spacing);
        window.draw(text);
    }
}

bool JocScrabble::allPlayersPassed() {
    return punga.isEmpty() && jucatori[jucatorCurent].getSuport().empty();
}

void JocScrabble::nextTurn() {
    jucatorCurent = (jucatorCurent + 1) % jucatori.size();
    jucatori[jucatorCurent].resetTilesPositions(10, 600, tileSize);
    afiseazaSugestiiFlag = false;
    sugestiiCurente.clear();
    inputCuvant.clear();
    updateCurrentWordDisplay();
    placedTilesThisTurn.clear();
}

void JocScrabble::mutaJucator() {
    if (placedTilesThisTurn.empty()) {
        std::cout << "No tiles placed." << std::endl;
        return;
    }

    // Determine word direction
    bool isHorizontal = true;
    int firstY = placedTilesThisTurn[0].second;
    for (const auto& pos : placedTilesThisTurn) {
        if (pos.second != firstY) {
            isHorizontal = false;
            break;
        }
    }

    // Sort placed tiles by position
    std::sort(placedTilesThisTurn.begin(), placedTilesThisTurn.end(),
        [isHorizontal](const auto& a, const auto& b) {
            return isHorizontal ? a.first < b.first : a.second < b.second;
        });

    // Build word
    std::string wordString;
    int startX = placedTilesThisTurn[0].first;
    int startY = placedTilesThisTurn[0].second;

    if (isHorizontal) {
        for (int x = startX; x < 15; x++) {
            char letter = tabla.getCellLetter(x, startY);
            if (letter == ' ') break;
            wordString += letter;
        }
    } else {
        for (int y = startY; y < 15; y++) {
            char letter = tabla.getCellLetter(startX, y);
            if (letter == ' ') break;
            wordString += letter;
        }
    }

    Cuvant cuvant(wordString, startX, startY,
                  isHorizontal ? Directie::Orizontal : Directie::Vertical);

    if (jucatori[jucatorCurent].joacaCuvant(cuvant, tabla)) {
        // Word is valid, update game state
        for (auto& pos : placedTilesThisTurn) {
            for (auto& tile : jucatori[jucatorCurent].getTiles()) {
                if (tile.getLetter() == tabla.getCellLetter(pos.first, pos.second)) {
                    jucatori[jucatorCurent].removeTile(&tile);
                    break;
                }
            }
        }

        punga.distribuieLitere(jucatori[jucatorCurent].getSuport(), wordString.length());
        jucatori[jucatorCurent].initializeTiles(10, 600, tileSize);
        nextTurn();
    } else {
        // Word is invalid, clear the board
        clearBoardAndTiles();
    }
}

void JocScrabble::finalizeazaJoc() {
    int maxScore = -1;
    std::string winner = "";
    for (const auto& jucator : jucatori) {
        if (jucator.getScor() > maxScore) {
            maxScore = jucator.getScor();
            winner = jucator.getNume();
        }
    }
    std::cout << "Jocul s-a terminat! Castigatorul este " << winner
              << " cu scorul " << maxScore << std::endl;
}

void JocScrabble::processInput(sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
            for (auto& button : buttons) {
                if (button.isClicked(mousePos)) {
                    button.onClick();
                    return;
                }
            }
            Tile* clickedTile = jucatori[jucatorCurent].getTileAt(mousePos);
            if (clickedTile) {
                draggedTile = clickedTile;
                dragOffset = mousePos - draggedTile->getPosition();
                draggedTile->setDragging(true);
            }
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
            afiseazaSugestiiFlag = !afiseazaSugestiiFlag;
            if (afiseazaSugestiiFlag) {
                sugestiiCurente = jucatori[jucatorCurent].sugereazaCuvinte(tabla.getSet());
            } else {
                sugestiiCurente.clear();
            }
        }
    }
}

void JocScrabble::updateGame() {}

void JocScrabble::renderGame(sf::RenderWindow& window) {
    tabla.deseneaza(window);
    jucatori[jucatorCurent].drawTiles(window);
    afiseazaScoruri(window);
    window.draw(currentWordText);
    if (afiseazaSugestiiFlag) {
        afiseazaSugestii(window, sugestiiCurente);
    }
    for (const auto& button : buttons) {
        button.draw(window);
    }
}

void JocScrabble::run() {
    sf::RenderWindow window(sf::VideoMode(800, 700), "Scrabble");
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
    if (gameOver) {
        finalizeazaJoc();
    }
}

void JocScrabble::afiseazaSugestii(sf::RenderWindow& window, const std::vector<std::string>& sugestii) const {
    int startX = 600;
    int startY = 300;
    int spacing = 25;
    for (size_t i = 0; i < sugestii.size(); ++i) {
        sf::Text text(sugestii[i], font, 18);
        text.setFillColor(sf::Color::Cyan);
        text.setPosition(startX, startY + i * spacing);
        window.draw(text);
        if (i > 15) break;
    }
}

JocScrabble::Button::Button(const std::string& text, const sf::Font& font, sf::Vector2f position, sf::Vector2f size, std::function<void()> action)
    : onClick(action)
{
    shape.setSize(size);
    shape.setPosition(position);
    shape.setFillColor(sf::Color::Blue);
    shape.setOutlineThickness(1);
    shape.setOutlineColor(sf::Color::White);

    label.setFont(font);
    label.setString(text);
    label.setCharacterSize(20);
    label.setFillColor(sf::Color::White);
    sf::FloatRect textBounds = label.getLocalBounds();
    label.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    label.setPosition(position.x + size.x / 2.0f, position.y + size.y / 2.0f);
}

void JocScrabble::Button::draw(sf::RenderWindow& window) const {
    window.draw(shape);
    window.draw(label);
}

bool JocScrabble::Button::isClicked(sf::Vector2f mousePos) {
    return shape.getGlobalBounds().contains(mousePos);
}

void JocScrabble::initializeUI() {
    buttons.emplace_back("Submit", font, sf::Vector2f(600, 100), sf::Vector2f(100, 40), [this]() {
        mutaJucator();
    });
    buttons.emplace_back("Exchange", font, sf::Vector2f(600, 150), sf::Vector2f(100, 40), [this]() {
        jucatori[jucatorCurent].schimbaLitere(punga);
        jucatori[jucatorCurent].initializeTiles(10, 600, tileSize);
        nextTurn();
        clearBoardAndTiles();
    });
    buttons.emplace_back("Clear", font, sf::Vector2f(600, 200), sf::Vector2f(100, 40), [this]() {
        clearBoardAndTiles();
    });
}

void JocScrabble::handleMousePress(sf::Vector2f mousePos) {
    Tile* clickedTile = jucatori[jucatorCurent].getTileAt(mousePos);
    if (clickedTile) {
        draggedTile = clickedTile;
        dragOffset = mousePos - draggedTile->getPosition();
        draggedTile->setDragging(true);
    }
}

void JocScrabble::clearBoardAndTiles() {
    for (int y = 0; y < 15; ++y) {
        for (int x = 0; x < 15; ++x) {
            tabla.clearCell(x, y);
        }
    }

    jucatori[jucatorCurent].resetTilesPositions(10, 600, tileSize);
    inputCuvant.clear();
    updateCurrentWordDisplay();
    placedTilesThisTurn.clear();
}

void JocScrabble::handleMouseRelease(sf::Vector2f mousePos) {
    if (!draggedTile) return;

    int boardX = static_cast<int>(mousePos.x / tileSize);
    int boardY = static_cast<int>(mousePos.y / tileSize);

    if (boardX >= 0 && boardX < 15 && boardY >= 0 && boardY < 15) {
        // --- Pass the letter to canPlaceTile ---
        if (canPlaceTile(boardX, boardY, draggedTile->getLetter())) {
            placeTileOnBoard(draggedTile, boardX, boardY);
        } else {
            jucatori[jucatorCurent].resetTilesPositions(10, 600, tileSize);
        }
    } else {
        jucatori[jucatorCurent].resetTilesPositions(10, 600, tileSize);
    }

    draggedTile->setDragging(false);
    draggedTile = nullptr;
    updateCurrentWordDisplay();
}

void JocScrabble::placeTileOnBoard(Tile* tile, int boardX, int boardY) {
    if (tabla.isCellEmpty(boardX, boardY)) {
        // Just place the letter without validation
        tabla.placeLetter(boardX, boardY, tile->getLetter());
        tile->setPosition(boardX * tile->getSize(), boardY * tile->getSize());
        tile->setDragging(false);

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
}

bool JocScrabble::canPlaceTile(int boardX, int boardY, char letter) {
    // Always return false if out of bounds
    if (boardX < 0 || boardX >= 15 || boardY < 0 || boardY >= 15) {
        return false;
    }

    // If the cell is not empty, we cannot place a tile there
    if (!tabla.isCellEmpty(boardX, boardY)) {
        return false;
    }

    // If the board is empty, the tile MUST be placed in the center
    if (tabla.isBoardEmpty()) {
        return boardX == 7 && boardY == 7;
    }

    // Check for adjacency, considering the letter being placed
    bool adjacent = false;
    // Temporarily place the letter on a copy of the board for the adjacency check
    TablaScrabble tempTabla = tabla; // Create a copy of the board
    tempTabla.adaugaCuvant(Cuvant(std::string(1, letter), boardX, boardY, Directie::Orizontal)); // Temporarily add

    if (boardX > 0 && !tempTabla.isCellEmpty(boardX - 1, boardY)) adjacent = true;
    if (boardX < 14 && !tempTabla.isCellEmpty(boardX + 1, boardY)) adjacent = true;
    if (boardY > 0 && !tempTabla.isCellEmpty(boardX, boardY - 1)) adjacent = true;
    if (boardY < 14 && !tempTabla.isCellEmpty(boardX, boardY + 1)) adjacent = true;

    return adjacent;
}

void JocScrabble::updateCurrentWordDisplay() {
    std::stringstream ss;
    // Build the displayed word from placedTilesThisTurn
    for (const auto& pos : placedTilesThisTurn) {
        ss << tabla.getCellLetter(pos.first, pos.second);
    }
    currentWordText.setString("Current Word: " + ss.str());
}
