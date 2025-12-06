#include "Button.h"

// --- BUTTON IMPLEMENTATION ---
Button::Button(float x, float y, float w, float h, sf::Font& font, std::string text, sf::Color color) {
    shape.setPosition(x, y);
    shape.setSize(sf::Vector2f(w, h));
    shape.setFillColor(color);

    label.setFont(font);
    label.setString(text);
    label.setCharacterSize(24);
    label.setFillColor(sf::Color::White);

    // Center text roughly
    label.setPosition(x + 5, y + 5);
}

bool Button::isHovered(sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::FloatRect bounds = shape.getGlobalBounds();
    return bounds.contains(static_cast<sf::Vector2f>(mousePos));
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(label);
}

// --- BUTTONLIST IMPLEMENTATION ---
void ButtonList::addButton(Button btn) {
    buttons.push_back(btn);
}

void ButtonList::draw(sf::RenderWindow& window) {
    // Loop through the list and draw each one
    for (int i = 0; i < buttons.size(); i++) {
        buttons[i].draw(window);
    }
}

int ButtonList::getClickedButtonIndex(sf::RenderWindow& window) {
    for (int i = 0; i < buttons.size(); i++) {
        if (buttons[i].isHovered(window)) {
            return i; // Return the index (0, 1, 2...) of the button clicked
        }
    }
    return -1; // Nothing clicked
}