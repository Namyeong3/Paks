#include <SFML/Graphics.hpp>
#include "SpecificMenus.h"

// Added CREDITS and GAMEOVER to the state list
enum AppState { MENU, OPTIONS, CREDITS, GAME, GAMEOVER };

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Paks");
    sf::Font font;
    if (!font.loadFromFile("SamsungSans-Medium.ttf")) return -1;

    // Instantiate all menus
    MainMenu mMain(font);
    OptionsMenu mOptions(font);
    CreditsMenu mCredits(font);
    GameOverMenu mGameOver(font);

    AppState currentState = MENU;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            // --- CLICK HANDLING ---
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {

                if (currentState == MENU) {
                    int id = mMain.getClicked(window);
                    if (id == 0) currentState = GAME;
                    if (id == 1) currentState = OPTIONS;
                    if (id == 2) currentState = CREDITS;
                    if (id == 3) window.close();
                }
                else if (currentState == OPTIONS) {
                    if (mOptions.getClicked(window) == 1) currentState = MENU;
                }
                else if (currentState == CREDITS) {
                    if (mCredits.getClicked(window) == 0) currentState = MENU;
                }
                else if (currentState == GAMEOVER) {
                    int id = mGameOver.getClicked(window);
                    if (id == 0) currentState = MENU;
                    if (id == 1) window.close();
                }
            }

            // --- KEYBOARD SHORTCUTS ---
            if (event.type == sf::Event::KeyPressed) {
                // Press K in game to simulate dying
                if (currentState == GAME && event.key.code == sf::Keyboard::K) {
                    currentState = GAMEOVER;
                }
                // Press ESC in game to Pause/Menu
                if (currentState == GAME && event.key.code == sf::Keyboard::Escape) {
                    currentState = MENU;
                }
            }
        }

        window.clear(sf::Color::Black);

        // --- DRAWING ---
        if (currentState == MENU)     mMain.draw(window);
        if (currentState == OPTIONS)  mOptions.draw(window);
        if (currentState == CREDITS)  mCredits.draw(window);
        if (currentState == GAMEOVER) mGameOver.draw(window);

        if (currentState == GAME) {
            // Simple placeholder for the game
            sf::Text t;
            t.setFont(font);
            t.setString("Game Running... Press 'K' to Die.");
            t.setPosition(50, 300);
            window.draw(t);
        }
        
        window.display();
    }
    return 0;
}