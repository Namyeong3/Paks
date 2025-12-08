#include "Label.h"

Label::Label(float x, float y, float w, float h, sf::Font& font, std::string text, sf::Color colour)
    : Button(x, y, w, h, font, text, colour)
{
    // Labels don’t change colour or respond to hover/click
    // So no extra behaviour needed
}
