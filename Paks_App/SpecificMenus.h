#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h" // <--- THIS IS THE FIX. YOU NEED THIS LINE.

class BaseMenu {
public:
    ButtonList buttons;

    void draw(sf::RenderWindow& window);
    int getClicked(sf::RenderWindow& window);
};

class MainMenu : public BaseMenu {
public:
    MainMenu(sf::Font& font);
};

class OptionsMenu : public BaseMenu {
public:
    OptionsMenu(sf::Font& font);
};

class CreditsMenu : public BaseMenu {
public:
    CreditsMenu(sf::Font& font);
};

class GameOverMenu : public BaseMenu {
public:
    GameOverMenu(sf::Font& font);
};