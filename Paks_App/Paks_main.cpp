#include <SFML/Graphics.hpp>
#include <iostream> // For error printing

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Paks");

    // --- TEXT SETUP START ---
    sf::Font font;
    // EXACT FILENAME of the font you pasted next to the .exe
    if (!font.loadFromFile("SamsungSans-Medium.ttf")) {
        std::cerr << "Error loading font\n";
        return -1;
    }

    sf::Text text;
    text.setFont(font);
    text.setString("Hello World");
    text.setCharacterSize(50); // In pixels
    text.setFillColor(sf::Color::White);
    text.setPosition(100.f, 100.f); // Position x, y
    // --- TEXT SETUP END ---

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        // DRAW THE TEXT
        window.draw(text);

        window.display();
    }

    return 0;
}