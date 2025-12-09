#pragma once
#include <string>
#include <map>
#include <random>
#include "StoryData.h" // Include the structs above

class StoryManager {
private:
    // Memory: Stores loaded situations to avoid re-reading files constantly
    std::map<std::string, Situation> situation_cache;

    // State: Which story folder are we currently reading?
    std::string current_story_folder;

    // Logic: The random number generator for probabilities
    std::mt19937 rng;

    // Internal Helper: Loads a specific file (e.g. "Start.yaml") from the folder
    void LoadFile(const std::string& filename);

public:
    // Constructor: Sets up the RNG
    StoryManager();

    // 1. Start a new story (sets the folder path)
    void LoadStory(const std::string& story_name);

    // 2. Retrieve a situation by its ID (e.g., "forest_start")
    Situation GetSituation(const std::string& id);

    // 3. Calculate the outcome of a reaction (handles the dice roll)
    Consequence GetConsequence(const Reaction& reaction);
};