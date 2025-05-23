#include <SFML/Graphics.hpp>
#include <iostream>

#include "screen.h"

using namespace std;
using namespace sf;

int main()
{
    RenderWindow window(sf::VideoMode(1920, 1080), "Tower Defense", sf::Style::Default);

    Screen main_menu("IMGS/Menu_Screen_Temp.png");
    Button play_button("IMGS/play.png", "IMGS/play.png");
    Button setting_button("IMGS/setting.png", "IMGS/setting.png");
    Button exit_button("IMGS/exit.png", "IMGS/exit.png");

    Screen setting_menu("IMGS/setting_menu.png");
    Button back_button("IMGS/back.png", "IMGS/back.png");

    setting_menu.setSpriteRect(64, 64, 3, 3);
    
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
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

                if (setting_button.handleinput(mousePos))
                    currentState = SETTINGS_MENU;

                if (back_button.handleinput(mousePos))
                    currentState = MAIN_MENU;
            }
        }

        window.clear();

        if (currentState == MAIN_MENU) 
        {
            main_menu.draw(0, 0, window);
            play_button.draw(1100, 300, window);
            setting_button.draw(1100, 450, window);
            exit_button.draw(1100, 600, window);
        }
        else if (currentState == SETTINGS_MENU) 
        {
            main_menu.draw(0, 0, window);
            setting_menu.draw(600, 600, window);
            back_button.draw(0, 0, window);
        }

        window.display();
    }

    return 0;
}