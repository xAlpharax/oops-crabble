// src/Tile.cpp
#include "Tile.h"

Tile::Tile(char litera, float x, float y, float size) : litera(litera), dragging(false), size(size), placedOnBoard(false) {
    shape.setSize(sf::Vector2f(size, size));
    shape.setFillColor(sf::Color::Yellow);
    shape.setOutlineThickness(1);
    shape.setOutlineColor(sf::Color::Black);
    shape.setPosition(x, y);
}

void Tile::draw(sf::RenderWindow& window) const {
    window.draw(shape);

    if (litera != ' ') {
        sf::Font font;
        if (!font.loadFromFile("Inconsolata-Regular.ttf")) {
            return;
        }
        sf::Text text(std::string(1, litera), font, size / 2);
        text.setFillColor(sf::Color::Black);
        centerTextInTile(text);
        window.draw(text);
    }
}

void Tile::centerTextInTile(sf::Text& text) const {
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f,
                   textBounds.top + textBounds.height / 2.0f);
    text.setPosition(shape.getPosition().x + size / 2.0f,
                     shape.getPosition().y + size / 2.0f);
}

void Tile::setPosition(float x, float y) {
    shape.setPosition(x, y);
}

sf::Vector2f Tile::getPosition() const {
    return shape.getPosition();
}

char Tile::getLetter() const {
    return litera;
}

void Tile::setLetter(char litera) {
    this->litera = litera;
}

bool Tile::isDragging() const {
    return dragging;
}

void Tile::setDragging(bool dragging) {
    this->dragging = dragging;
}

bool Tile::contains(sf::Vector2f point) const {
    return shape.getGlobalBounds().contains(point);
}

void Tile::setSize(float size) {
    this->size = size;
    shape.setSize(sf::Vector2f(size, size));
}

float Tile::getSize() const {
    return size;
}

bool Tile::isPlacedOnBoard() const {
    return placedOnBoard;
}

void Tile::setPlacedOnBoard(bool placed) {
    placedOnBoard = placed;
}

bool Tile::isPlaced() const {
    return placedOnBoard;
}

void Tile::setPlaced(bool placed)
{
    placedOnBoard = placed;
}
