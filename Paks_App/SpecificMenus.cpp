#include "SpecificMenus.h"
#include "Globals.h"
using namespace std;

// SpecificMenus.cpp

// --- BASE LOGIC ---
void BaseMenu::draw(sf::RenderWindow& window) {
    // Draw labels first
    for (auto& l : labels)
        l.draw(window);

    buttons.draw(window);
}

int BaseMenu::getClicked(sf::RenderWindow& window) {
    return buttons.getClickedButtonIndex(window);
}

// --- CONSTRUCTORS ---

MainMenu::MainMenu(sf::Font& font) {
    // Add a menu title for Debug Mode
    if (debug_mode)
        labels.emplace_back(Label(100, 20, 300, 50, font, "DEBUG: MAIN MENU", sf::Color::White));

    // 0: Play, 1: Options, 2: Credits, 3: Exit
    buttons.addButton(Button(100, 100, 200, 50, font, "Stories", sf::Color::Blue));
    buttons.addButton(Button(100, 180, 200, 50, font, "Options", sf::Color::Green));
    buttons.addButton(Button(100, 260, 200, 50, font, "Achievements", sf::Color::Magenta));
    buttons.addButton(Button(100, 340, 200, 50, font, "About", sf::Color::Cyan));
    buttons.addButton(Button(100, 420, 200, 50, font, "Exit", sf::Color::Red));
}

OptionsMenu::OptionsMenu(sf::Font& font) {
    // Add a menu title for Debug Mode
    if (debug_mode)
        labels.emplace_back(Label(100, 20, 300, 50, font, "DEBUG: OPTIONS MENU", sf::Color::White));

    labels.emplace_back(Label(100, 20, 300, 50, font, "OPTIONS MENU", sf::Color::Black));

    // 0: Toggle Sound, 1: Back
    buttons.addButton(Button(100, 100, 300, 50, font, "Sound: ON", sf::Color::Cyan));
    buttons.addButton(Button(100, 500, 200, 50, font, "Back", sf::Color::Red));
}

CreditsMenu::CreditsMenu(sf::Font& font) {
    // Add a menu title for Debug Mode
    if (debug_mode)
        labels.emplace_back(Label(100, 20, 300, 50, font, "DEBUG: CREDITS MENU", sf::Color::White));

    // 0: Back
    buttons.addButton(Button(100, 500, 200, 50, font, "Back", sf::Color::Red));
}

StoriesMenu::StoriesMenu(sf::Font& font) {
    // Add a menu title for Debug Mode
    if (debug_mode)
        labels.emplace_back(Label(100, 20, 300, 50, font, "DEBUG: STORIES MENU", sf::Color::White));

    // 0: Back
    buttons.addButton(Button(100, 500, 200, 50, font, "Back", sf::Color::Red));
}

StoryMenu::StoryMenu(sf::Font& font) {
    // Add a menu title for Debug Mode
    if (debug_mode)
        labels.emplace_back(Label(100, 20, 300, 50, font, "DEBUG: STORY MENU", sf::Color::White));

    // 0: Back
    buttons.addButton(Button(100, 500, 200, 50, font, "Back", sf::Color::Red));
}

AchievementsMenu::AchievementsMenu(sf::Font& font) {
    // Add a menu title for Debug Mode
    if (debug_mode)
        labels.emplace_back(Label(100, 20, 300, 50, font, "DEBUG: ACHIEVEMENTS MENU", sf::Color::White));

    // 0: Back
    buttons.addButton(Button(100, 500, 200, 50, font, "Back", sf::Color::Red));
}

AboutMenu::AboutMenu(sf::Font& font) {
    // Add a menu title for Debug Mode
    if (debug_mode)
        labels.emplace_back(Label(100, 20, 300, 50, font, "DEBUG: ABOUT MENU", sf::Color::White));

    // 0: Back
    buttons.addButton(Button(100, 500, 200, 50, font, "Back", sf::Color::Red));
}

PauseMenu::PauseMenu(sf::Font& font) {
    // Add a menu title for Debug Mode
    if (debug_mode)
        labels.emplace_back(Label(100, 20, 300, 50, font, "DEBUG: ABOUT MENU", sf::Color::White));

    // 0: Back
    buttons.addButton(Button(100, 500, 200, 50, font, "Back", sf::Color::Red));
}

GameOverMenu::GameOverMenu(sf::Font& font) {
    // Add a menu title for Debug Mode
    if (debug_mode)
        labels.emplace_back(Label(100, 20, 300, 50, font, "DEBUG: GAME OVER MENU", sf::Color::White));

    // 0: Menu, 1: Quit
    buttons.addButton(Button(100, 300, 200, 50, font, "Main Menu", sf::Color::Green));
    buttons.addButton(Button(320, 300, 200, 50, font, "Quit", sf::Color::Red));
}