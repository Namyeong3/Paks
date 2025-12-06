#include "SpecificMenus.h"

// --- BASE LOGIC ---
void BaseMenu::draw(sf::RenderWindow& window) {
    buttons.draw(window);
}

int BaseMenu::getClicked(sf::RenderWindow& window) {
    return buttons.getClickedButtonIndex(window);
}

// --- CONSTRUCTORS ---

MainMenu::MainMenu(sf::Font& font) {
    // 0: Play, 1: Options, 2: Credits, 3: Exit
    buttons.addButton(Button(100, 100, 200, 50, font, "Play Game", sf::Color::Blue));
    buttons.addButton(Button(100, 180, 200, 50, font, "Options", sf::Color::Green));
    buttons.addButton(Button(100, 260, 200, 50, font, "Credits", sf::Color::Magenta));
    buttons.addButton(Button(100, 340, 200, 50, font, "Exit", sf::Color::Red));
}

OptionsMenu::OptionsMenu(sf::Font& font) {
    // 0: Toggle Sound, 1: Back
    buttons.addButton(Button(100, 100, 300, 50, font, "Sound: ON", sf::Color::Cyan));
    buttons.addButton(Button(100, 500, 200, 50, font, "Back", sf::Color::Red));
}

CreditsMenu::CreditsMenu(sf::Font& font) {
    // 0: Back
    buttons.addButton(Button(100, 500, 200, 50, font, "Back", sf::Color::Red));
}

GameOverMenu::GameOverMenu(sf::Font& font) {
    // 0: Menu, 1: Quit
    buttons.addButton(Button(100, 300, 200, 50, font, "Main Menu", sf::Color::Green));
    buttons.addButton(Button(320, 300, 200, 50, font, "Quit", sf::Color::Red));
}