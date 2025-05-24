#include <SFML/Graphics.hpp>
#include <iostream>

#include "screen.h"

enum class GameState {
    MainMenu,
    Settings
};

int main() {
    sf::RenderWindow window(sf::VideoMode(1024, 576), "Tower Defense");
    GameState gameState = GameState::MainMenu;

    MainMenu mainmenu(
        window,
        [&]() { gameState = GameState::Settings; },
        []() { std::cout << "Play clicked!\n"; },
        [&]() { window.close(); }
    );

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

            mainmenu.update(mousePos, event);
        }

        if (gameState == GameState::MainMenu)
            mainmenu.draw(0, 0, window);

        window.display();
    }

    return 0;
}
