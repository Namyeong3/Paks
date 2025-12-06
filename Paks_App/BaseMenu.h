#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class BaseMenu {
protected:
    sf::Text menuText;
public:
    BaseMenu(sf::Font& font, std::string content, float yPos, sf::Color colour);
    void draw(sf::RenderWindow& window);
};