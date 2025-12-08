#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Label.h"

class BaseMenu {
protected:
    sf::Text menuText;
    public:
        ButtonList buttons;
        std::vector<Label> labels;

        void draw(sf::RenderWindow& window);
        int getClicked(sf::RenderWindow& window);
};