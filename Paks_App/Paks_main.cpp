#include <SFML/Graphics.hpp>
#include "SpecificMenus.h"
#include "Globals.h"
#include "StoryManager.h"
using namespace std;

// Paks_main.cpp

enum AppState { MENU, STORY, STORIES, OPTIONS, ACHIEVEMENTS, ABOUT, PAUSE, GAME, GAMEOVER };

int main() {

    // Debug Mode
    bool debug_mode = true;
    if (debug_mode)
        cout << "===========\nDebug Mode\n===========\n\n";

    sf::RenderWindow window(sf::VideoMode(800, 600), "Paks");

    if (!globalFont.loadFromFile("SamsungSans-Medium.ttf"))
        return -1;

    if (!boldFont.loadFromFile("SamsungSans-Bold.ttf"))
        return -1;

    if (!lightFont.loadFromFile("SamsungSans-Light.ttf"))
        return -1;

    // Instantiate all menus
    MainMenu mMain(globalFont);
    StoryMenu mStory(globalFont);
    StoriesMenu mStories(globalFont);
    OptionsMenu mOptions(globalFont);
    AchievementsMenu mAchievements(globalFont);
    AboutMenu mAbout(globalFont);
    PauseMenu mPause(globalFont);
    GameOverMenu mGameOver(globalFont);

    // Setup the Story Engine
    StoryManager engine;
    Situation currentSituation;
    Consequence currentConsequence;
    bool waitingForContinue = false; // Logic flag

    AppState currentState = MENU;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            // --- CLICK HANDLING ---
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {

                if (currentState == MENU) {
                    int id = mMain.getClicked(window);
                    if (id == 0) currentState = STORIES;
                    if (id == 1) currentState = OPTIONS;
                    if (id == 2) currentState = ACHIEVEMENTS;
                    if (id == 3) currentState = ABOUT;
                    if (id == 4) window.close();
                }
                else if (currentState == STORIES) {
                    int id = mStories.getClicked(window);
                    if (id != -1) {
                        // Housekeeping: Automate these buttons
                        
                        // 3. Load the specific story based on ID
                        string storyFolder = "Forest"; // Default
                        if (id == 1) storyFolder = "Bus";
                        if (id == 2) storyFolder = "HauntedHouse";

                        engine.LoadStory(storyFolder);

                        // 4. Get the first situation (Ensure your YAML has a standard start ID)
                        currentSituation = engine.GetSituation("start");

                        // Update the GUI
                        mStory.setSituation(currentSituation);
                        waitingForContinue = false;

                        currentState = STORY;
                    }
                }
                else if (currentState == STORY) {

                    // CASE A: We just showed the result text (Consequence).
                    // Any click moves us to the NEXT situation.
                    if (waitingForContinue) {
                        // Load the target ID from the previous consequence
                        if (currentConsequence.target_id == "game_over") {
                            currentState = GAMEOVER;
                        }
                        else {
                            currentSituation = engine.GetSituation(currentConsequence.target_id);
                            mStory.setSituation(currentSituation);
                            waitingForContinue = false; // Back to choosing options
                        }
                    }
                    // CASE B: We are choosing an option (Reaction).
                    else {
                        int choiceIndex = mStory.getClicked(window); // Returns 0, 1, 2...

                        if (choiceIndex != -1 && choiceIndex < currentSituation.reactions.size()) {
                            // 1. Get the chosen reaction data
                            Reaction chosen = currentSituation.reactions[choiceIndex];

                            // 2. Calculate the outcome (RNG)
                            currentConsequence = engine.GetConsequence(chosen);

                            // 3. Update GUI to show text ("You fell!")
                            mStory.setConsequence(currentConsequence.text);

                            // 4. Handle Optional Data (Stats/Achievements)
                            if (currentConsequence.data.count("achievement")) {
                                // mAchievements.unlock(currentConsequence.data["achievement"]);
                            }

                            // 5. Set flag so next click loads the new room
                            waitingForContinue = true;
                        }
                    }
                }
                else if (currentState == OPTIONS) {
                    if (mOptions.getClicked(window) == 1) currentState = MENU;
                }
                else if (currentState == ABOUT) {
                    if (mAbout.getClicked(window) == 0) currentState = MENU;
                }
                else if (currentState == GAMEOVER) {
                    int id = mGameOver.getClicked(window);
                    if (id == 0) currentState = MENU;
                    if (id == 1) window.close();
                }
                else if (currentState == PAUSE) {
                    int id = mPause.getClicked(window);
                    if (id == 0) currentState = MENU;
                    if (id == 1) currentState = STORIES;
                    if (id == 2) currentState = STORY;

                }
            }

            // --- KEYBOARD SHORTCUTS ---
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    // Press ESC in main menu to exit
                    if (currentState == MENU) {
                        window.close();
                    }
                    // Press ESC in the story menu to Pause
                    else if (currentState == STORY) {
                        currentState = PAUSE;
                    }
                    // Press ESC in the Pause menu to Resume
                    else if (currentState == PAUSE) {
                        currentState = STORY;
                    }
                    // Press ESC in a submenu to go back to submenu
                    else if (currentState != MENU && currentState != STORY && currentState != PAUSE) {
                        currentState = MENU;
                    }
                }
            }
        }

        window.clear(sf::Color::Black);

        // --- DRAWING ---
        if (currentState == MENU)     mMain.draw(window);
        if (currentState == STORY)     mStory.draw(window);
        if (currentState == STORIES)     mStories.draw(window);
        if (currentState == OPTIONS)  mOptions.draw(window);
        if (currentState == ACHIEVEMENTS)  mAchievements.draw(window);
        if (currentState == ABOUT)  mAbout.draw(window);
        if (currentState == PAUSE) mPause.draw(window);
        if (currentState == GAMEOVER) mGameOver.draw(window);
        
        window.display();
    }
    return 0;
}