#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Button {
public:
    sf::RectangleShape shape;
    sf::Text label;

    Button(float x, float y, float w, float h, sf::Font& font, std::string text, sf::Color color);
    bool isHovered(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};

class ButtonList {
private:
    std::vector<Button> buttons;

public:
    void addButton(Button btn);
    void draw(sf::RenderWindow& window);
    int getClickedButtonIndex(sf::RenderWindow& window);
};