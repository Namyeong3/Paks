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

    string stories_list[] = { "Forest" , "Bus" , "Story 3" };

    for (int i = 0; i < 3; i++) {
        std::string& story = stories_list[i];

        buttons.addButton(Button(100, 200 + 80 * i, 200, 50, font, story, sf::Color::Red));
    }
}

StoryMenu::StoryMenu(sf::Font& f) : font(f) { // <--- Fixes C2530
    showingConsequence = false;

    // Initialize the styles
    situationText.setFont(font);
    situationText.setCharacterSize(60);
    situationText.setFillColor(sf::Color::White);

    consequenceText.setFont(font);
    consequenceText.setCharacterSize(30);
    consequenceText.setFillColor(sf::Color::Yellow);
}

// 2. Set Situation (The Choice Screen)
void StoryMenu::setSituation(const Situation& sit) {
    showingConsequence = false;

    // Set Main Word
    situationText.setString(sit.situation);

    // Center the text (Assuming 800x600 screen)
    sf::FloatRect textRect = situationText.getLocalBounds();
    situationText.setOrigin(textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f);
    situationText.setPosition(400, 200);

    // Set Options
    optionsTexts.clear();
    float startY = 350;

    for (size_t i = 0; i < sit.reactions.size(); ++i) {
        sf::Text opt;
        opt.setFont(font);
        opt.setString(sit.reactions[i].label);
        opt.setCharacterSize(30);
        opt.setFillColor(sf::Color::Cyan);

        // Center option
        sf::FloatRect optRect = opt.getLocalBounds();
        opt.setOrigin(optRect.left + optRect.width / 2.0f,
            optRect.top + optRect.height / 2.0f);
        opt.setPosition(400, startY + (i * 50));

        optionsTexts.push_back(opt);
    }
}

// 3. Set Consequence (The Result Screen)
void StoryMenu::setConsequence(const std::string& text) {
    showingConsequence = true;
    consequenceText.setString(text);

    // Center the text
    sf::FloatRect textRect = consequenceText.getLocalBounds();
    consequenceText.setOrigin(textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f);
    consequenceText.setPosition(400, 300);
}

// 4. Draw
void StoryMenu::draw(sf::RenderWindow& window) {
    if (showingConsequence) {
        window.draw(consequenceText);
    }
    else {
        window.draw(situationText);
        for (const auto& txt : optionsTexts) {
            window.draw(txt);
        }
    }
}

// 5. Input Handling
int StoryMenu::getClicked(sf::RenderWindow& window) {
    // If reading a result, clicks don't select options
    if (showingConsequence) return -1;

    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    for (size_t i = 0; i < optionsTexts.size(); ++i) {
        if (optionsTexts[i].getGlobalBounds().contains(mousePosF)) {
            return static_cast<int>(i);
        }
    }
    return -1;
}


AchievementsMenu::AchievementsMenu(sf::Font& font) {
    // Add a menu title for Debug Mode
    if (debug_mode)
        labels.emplace_back(Label(100, 20, 300, 50, font, "DEBUG: ACHIEVEMENTS MENU", sf::Color::White));
}

AboutMenu::AboutMenu(sf::Font& font) {
    // Add a menu title for Debug Mode
    if (debug_mode)
        labels.emplace_back(Label(100, 20, 300, 50, font, "DEBUG: ABOUT MENU", sf::Color::White));
}

PauseMenu::PauseMenu(sf::Font& font) {
    // Add a menu title for Debug Mode
    if (debug_mode)
        labels.emplace_back(Label(100, 20, 300, 50, font, "DEBUG: PAUSE MENU", sf::Color::White));
    
    // 0
    buttons.addButton(Button(100, 300, 200, 50, font, "Menu", sf::Color::Red));

    // 1
    buttons.addButton(Button(100, 400, 200, 50, font, "Stories", sf::Color::Red));

    // 2
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