#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h" // <--- THIS IS THE FIX. YOU NEED THIS LINE.
#include "Label.h"

// SpecificMenus.h

class BaseMenu {
public:
    ButtonList buttons;
    std::vector<Label> labels;

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

class StoriesMenu : public BaseMenu {
public:
    StoriesMenu(sf::Font& font);
};

class StoryMenu : public BaseMenu {
public:
    StoryMenu(sf::Font& font);
};

class PauseMenu : public BaseMenu {
public:
    PauseMenu(sf::Font& font);
};

class AchievementsMenu : public BaseMenu {
public:
    AchievementsMenu(sf::Font& font);
};

class AboutMenu : public BaseMenu {
public:
    AboutMenu(sf::Font& font);
};