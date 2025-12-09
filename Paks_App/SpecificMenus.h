#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Label.h"
#include "StoryData.h"

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

class StoryMenu { // You can remove ": public BaseMenu" if you don't need it, or keep it.
private:
    sf::Font& font;

    // New Variables for the Game
    sf::Text situationText;       // The big word (e.g. "FOREST")
    sf::Text consequenceText;     // The result text (e.g. "You tripped.")
    std::vector<sf::Text> optionsTexts; // The list of clickables

    bool showingConsequence;      // State flag

public:
    StoryMenu(sf::Font& font);

    // Replaces updateStoryLabels
    void setSituation(const Situation& sit);
    void setConsequence(const std::string& text);

    void draw(sf::RenderWindow& window);
    int getClicked(sf::RenderWindow& window);
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