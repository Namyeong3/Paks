#pragma once
#include <string>
#include <vector>
#include <map> // Required for std::map

// 3. The Result: What happens after the choice
struct Consequence {
    std::string text;
    std::string target_id;
    int weight = 1;

    // Stores optional data like {"health": "-10", "achievement": "hero"}
    std::map<std::string, std::string> data;
};

// 2. The Choice: The button the player clicks
struct Reaction {
    std::string label;     // "Jump", "Run", "Hide"
    std::vector<Consequence> consequences;
};

// 1. The Screen: The main display
struct Situation {
    std::string id;        // Internal use: "forest_01"
    std::string situation; // Displayed: "FOREST" (The main word)
    std::vector<Reaction> reactions;
};