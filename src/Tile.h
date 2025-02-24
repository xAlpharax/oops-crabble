// src/Tile.h
#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>

class Tile {
public:
    Tile(char litera = ' ', float x = 0.0f, float y = 0.0f, float size = 30.0f);

    void draw(sf::RenderWindow& window) const;
    void setPosition(float x, float y);
    sf::Vector2f getPosition() const;
    char getLetter() const;
    void setLetter(char litera);
    bool isDragging() const;
    void setDragging(bool dragging);
    bool contains(sf::Vector2f point) const;
    void setSize(float size);
    float getSize() const;
    bool isPlacedOnBoard() const;
    void setPlacedOnBoard(bool placed);
    bool isPlaced() const;
    void setPlaced(bool placed);


private:
    char litera;
    sf::RectangleShape shape;
    bool dragging;
    float size;
    bool placedOnBoard;
    void centerTextInTile(sf::Text& text) const;
};

#endif
