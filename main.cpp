#include <SFML/Graphics.hpp>
#include <iostream>

#include "screen.h"

using namespace std;
using namespace sf;

int main()
{
    RenderWindow window(sf::VideoMode(1920, 1080), "Tower Defense", sf::Style::Default);

    Screen menu(1024, 576, "IMGS/Menu_Screen_Temp.png");
    Button play_button(300, 80, "IMGS/play.png", "IMGS/play.png");
    Button setting_button(300, 80, "IMGS/setting.png", "IMGS/setting.png");
    Button exit_button(300, 80, "IMGS/exit.png", "IMGS/exit.png");

    Screen setting_menu(1400, 800, "IMGS/setting_menu.png");
    Button back_button(50, 50, "IMGS/back.png", "IMGS/back.png");

    setting_menu.setSpriteRect(64, 64, 4, 4);
    
    enum AppState {
        MAIN_MENU,
        SETTINGS_MENU,
        GAME_PLAY
    };

    AppState currentState = MAIN_MENU;

    while (window.isOpen())
    {
        Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

            if (setting_button.handleinput(mousePos))
            {
                currentState = SETTINGS_MENU;
            }

            if (back_button.handleinput(mousePos))
            {
                currentState = MAIN_MENU;
            }
        }

        window.clear();

        if (currentState == MAIN_MENU) 
        {
            menu.draw(0, 0, window);
            play_button.draw(1100, 300, window);
            setting_button.draw(1100, 450, window);
            exit_button.draw(1100, 600, window);
        }
        else if (currentState == SETTINGS_MENU) 
        {
            back_button.draw(0, 0, window);
        }

        window.display();
    }

    return 0;
}