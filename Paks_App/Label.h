#pragma once
#include "Button.h"

class Label : public Button {
public:
    Label(float x, float y, float w, float h, sf::Font& font, std::string text, sf::Color colour);
};
