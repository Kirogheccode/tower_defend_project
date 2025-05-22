#include <SFML/Graphics.hpp>
#include <iostream>

#include "screen.h"

using namespace std;
using namespace sf;

int main()
{
    RenderWindow window(sf::VideoMode(1024, 576), "Tower Defense - SFML 2.6.2", sf::Style::Default);

    Screen menu(1024, 576, "IMGS/Menu_Screen_Temp.png");
    Screen play_button(300, 80, "IMGS/play.png");
    Screen setting_button(300, 80, "IMGS/setting.png");
    Screen exit_button(300, 80, "IMGS/exit.png");
    
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        menu.draw(0, 0, window);
        play_button.draw(40, 40, window);

        window.display();
    }

    return 0;
}