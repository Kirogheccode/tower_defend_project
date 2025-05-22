#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    /* sf::RenderWindow window(sf::VideoMode({ 200, 200 }), "SFML works!");
     sf::CircleShape shape(100.f);
     shape.setFillColor(sf::Color::Green);

     while (window.isOpen())
     {
         sf::Event event;
         while (window.pollEvent(event))
         {
             if (event.type == event.Closed)
                 window.close();
         }

         window.clear();
         window.draw(shape);
         window.display();
     }*/
    sf::RenderWindow window(sf::VideoMode(1024, 576), "Tower Defense - SFML 2.6.2", sf::Style::Default);

    //access to image and font
    enum class AppState { MainMenu, SettingsMenu };
    AppState currentState = AppState::MainMenu;


    sf::Texture mainMenu_texture;
    if (!mainMenu_texture.loadFromFile("IMGS\\Menu_Screen_Temp.png")) {
        std::cerr << "no image.\n";
        return -1;
    }
    sf::Sprite mainMenuSprite(mainMenu_texture);


    sf::Texture settingsMenu_Texture;
    if (!settingsMenu_Texture.loadFromFile("IMGS\\background.png")) {
        std::cerr << "no setting background.\n";
        return -1;
    }
    sf::Sprite settingsMenuSprite(settingsMenu_Texture);



    sf::Texture backTexture;
    if (!backTexture.loadFromFile("IMGS\\back.png")) {
        std::cerr << "no Back buton.\n";
        return -1;
    }
    sf::Sprite backButton(backTexture);
    backButton.setPosition(50.f, 50.f);


    //sf::Font font;
     //if (!font.loadFromFile("C:\\Users\\tklin\\source\\repos\\tower_defend_project\\IMGS\\arial.ttf")) {
     //    std::cerr << "no font.\n";
     //    return -1;
     //}


     //add button pictures
    sf::Texture startTexture;
    if (!startTexture.loadFromFile("IMGS\\play.png")) {
        std::cerr << "no Start.\n";
        return -1;
    }
    sf::Sprite startButton(startTexture);
    startButton.setPosition(650.f, 150.f);

    sf::Texture settingTexture;
    if (!settingTexture.loadFromFile("IMGS\\setting.png")) {
        std::cerr << "no Settings.\n";
        return -1;
    }
    sf::Sprite settingButton(settingTexture);
    settingButton.setPosition(650.f, 300.f);

    sf::Texture exitTexture;
    if (!exitTexture.loadFromFile("IMGS\\exit.png")) {
        std::cerr << "no Exit.\n";
        return -1;
    }
    sf::Sprite exitButton(exitTexture);
    exitButton.setPosition(650.f, 450.f);


    //open game console and check the mouse
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            //check if the button is pressed
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    if (currentState == AppState::MainMenu) {
                        if (startButton.getGlobalBounds().contains(mousePos)) {
                            std::cout << "Start button clicked!" << std::endl;
                        }
                        else if (settingButton.getGlobalBounds().contains(mousePos)) {
                            std::cout << "Setting button clicked!" << std::endl;
                            currentState = AppState::SettingsMenu;
                        }
                        else if (exitButton.getGlobalBounds().contains(mousePos)) {
                            std::cout << "Exit button clicked!" << std::endl;
                            window.close();
                        }
                    }
                    else if (currentState == AppState::SettingsMenu) {
                        if (backButton.getGlobalBounds().contains(mousePos)) {
                            std::cout << "Back button clicked!" << std::endl;
                            currentState = AppState::MainMenu;
                        }
                    }
                }
            }
        }


        //mouse interacts with button
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (startButton.getGlobalBounds().contains(mousePos)) {
            startButton.setColor(sf::Color(200, 200, 255));
            startButton.setScale(1.1f, 1.1f);
        }
        else {
            startButton.setColor(sf::Color::White);
            startButton.setScale(1.0f, 1.0f);
        }

        if (settingButton.getGlobalBounds().contains(mousePos)) {
            settingButton.setColor(sf::Color(200, 200, 255));
            settingButton.setScale(1.1f, 1.1f);
        }
        else {
            settingButton.setColor(sf::Color::White);
            settingButton.setScale(1.0f, 1.0f);
        }

        if (exitButton.getGlobalBounds().contains(mousePos)) {
            exitButton.setColor(sf::Color(200, 200, 255));
            exitButton.setScale(1.1f, 1.1f);
        }
        else {
            exitButton.setColor(sf::Color::White);
            exitButton.setScale(1.0f, 1.0f);
        }
        if (currentState == AppState::SettingsMenu) {
            if (backButton.getGlobalBounds().contains(mousePos)) {
                backButton.setColor(sf::Color(200, 200, 255));
                backButton.setScale(1.1f, 1.1f);
            }
            else {
                backButton.setColor(sf::Color::White);
                backButton.setScale(1.0f, 1.0f);
            }
        }

        //draw button and display
        if (currentState == AppState::MainMenu) {
            window.draw(mainMenuSprite);
            window.draw(startButton);
            window.draw(settingButton);
            window.draw(exitButton);
        }
        else if (currentState == AppState::SettingsMenu) {
            window.draw(settingsMenuSprite);
            window.draw(backButton);
        }
        window.display();
    }
    return 0;


}