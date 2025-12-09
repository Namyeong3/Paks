#include "StoryManager.h"
#include <iostream>
#include <filesystem>
#include <yaml-cpp/yaml.h>

namespace fs = std::filesystem;

// ---------------------------------------------------------
// Constructor
// ---------------------------------------------------------
StoryManager::StoryManager() {
    // Initialize the Random Number Generator with a hardware seed
    // This ensures the game is different every time you run it.
    std::random_device rd;
    rng = std::mt19937(rd());
}

// ---------------------------------------------------------
// 1. Load Story
// Loads all YAML files inside a specific story folder.
// ---------------------------------------------------------
void StoryManager::LoadStory(const std::string& story_name) {
    // Clear old data from memory
    situation_cache.clear();
    current_story_folder = "Stories/" + story_name;

    std::cout << "[System] Loading Story: " << story_name << "...\n";

    // check if folder exists
    if (!fs::exists(current_story_folder)) {
        std::cerr << "[Error] Story folder not found: " << current_story_folder << "\n";
        return;
    }

    // Iterate through every file in the folder
    // If we find a .yaml file, we load it.
    for (const auto& entry : fs::directory_iterator(current_story_folder)) {
        if (entry.path().extension() == ".yaml") {
            LoadFile(entry.path().string());
        }
    }

    std::cout << "[System] Story loaded. Situations in memory: " << situation_cache.size() << "\n";
}

// ---------------------------------------------------------
// Helper: Load File
// Parses the YAML and fills the Structs
// ---------------------------------------------------------
void StoryManager::LoadFile(const std::string& filepath) {
    try {
        YAML::Node file = YAML::LoadFile(filepath);

        // Loop through every "Situation" block in the file
        for (const auto& node : file) {
            Situation sit;

            // 1. Parse Basic Info
            sit.id = node["id"].as<std::string>();
            sit.situation = node["situation"].as<std::string>();

            // 2. Parse Reactions (Options)
            if (node["reactions"]) {
                for (const auto& r_node : node["reactions"]) {
                    Reaction react;
                    react.label = r_node["label"].as<std::string>();

                    // 3. Parse Consequences
                    if (r_node["consequences"]) {
                        for (const auto& c_node : r_node["consequences"]) {
                            Consequence cons;
                            cons.text = c_node["text"].as<std::string>();
                            cons.target_id = c_node["target_id"].as<std::string>();

                            // Handle Weight (Default to 1 if missing)
                            if (c_node["weight"]) {
                                cons.weight = c_node["weight"].as<int>();
                            }
                            else {
                                cons.weight = 1;
                            }

                            // 4. Handle Optional Data Map
                            // This reads your custom data like health, achievements, etc.
                            if (c_node["data"]) {
                                for (YAML::const_iterator it = c_node["data"].begin(); it != c_node["data"].end(); ++it) {
                                    std::string key = it->first.as<std::string>();
                                    std::string value = it->second.as<std::string>();
                                    cons.data[key] = value;
                                }
                            }

                            react.consequences.push_back(cons);
                        }
                    }
                    sit.reactions.push_back(react);
                }
            }

            // Save to Cache
            situation_cache[sit.id] = sit;
        }
    }
    catch (const YAML::Exception& e) {
        std::cerr << "[Error] parsing file " << filepath << ": " << e.what() << "\n";
    }
}

// ---------------------------------------------------------
// 2. Get Situation
// ---------------------------------------------------------
Situation StoryManager::GetSituation(const std::string& id) {
    // Check if the ID exists in our map
    if (situation_cache.find(id) != situation_cache.end()) {
        return situation_cache[id];
    }

    // Fallback if not found (Helps debugging)
    std::cerr << "[Warning] Situation ID not found: " << id << "\n";
    Situation error_sit;
    error_sit.id = "error";
    error_sit.situation = "ERROR: MISSING ID " + id;
    return error_sit;
}

// ---------------------------------------------------------
// 3. Get Consequence (Dice Roll)
// ---------------------------------------------------------
Consequence StoryManager::GetConsequence(const Reaction& reaction) {
    if (reaction.consequences.empty()) {
        return {}; // Return empty if nothing defined
    }

    // Algorithm: Weighted Random Selection

    // A. Calculate total weight (e.g., 4 + 1 = 5)
    int total_weight = 0;
    for (const auto& c : reaction.consequences) {
        total_weight += c.weight;
    }

    // B. Roll the dice (e.g., get a number between 1 and 5)
    std::uniform_int_distribution<int> dist(1, total_weight);
    int roll = dist(rng);

    // C. Find which bucket the roll landed in
    int current_sum = 0;
    for (const auto& c : reaction.consequences) {
        current_sum += c.weight;
        if (roll <= current_sum) {
            return c; // We found the winner
        }
    }

    // Fallback (should never be reached if logic is correct)
    return reaction.consequences.back();
}