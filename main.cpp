
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "screen.h"
using namespace sf;

enum class AppState { MainMenu, SettingsMenu, PlayMenu };

int main() {
    RenderWindow window(VideoMode(1024, 576), "Tower Defense - SFML");
    AppState state = AppState::MainMenu;

    Screen mainBg(1024, 576, "IMGS/Menu_Screen_Temp.png");
    Screen settingBg(1024, 576, "IMGS/background.png");
    Screen playBg(1024, 576, "IMGS/Menu_Screen_Temp.png");

    Button playButton("IMGS/play.png", 600, 150);
    Button settingButton("IMGS/setting.png", 600, 300);
    Button exitButton("IMGS/exit.png", 600, 450);
    Button backButton("IMGS/back.png", 0, 0);

    Button loadGameButton("IMGS/load.png", 600, 200);
    Button newGameButton("IMGS/new.png", 600, 350);
    Button enterNameButton("IMGS/enter.png", 920, 450);

    Font font;
    if (!font.loadFromFile("IMGS/arial.ttf")) {
        std::cerr << "Failed to load font\n";
    }

    RectangleShape nameBox(Vector2f(300, 50));
    nameBox.setPosition(600, 450);
    nameBox.setFillColor(Color(255, 255, 255, 200));
    nameBox.setOutlineColor(Color::Black);
    nameBox.setOutlineThickness(2);

    Text playerNameText;
    playerNameText.setFont(font);
    playerNameText.setCharacterSize(24);
    playerNameText.setFillColor(Color::Black);
    playerNameText.setPosition(610, 455);

    std::string playerName;
    bool enteringName = false;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (state == AppState::MainMenu) {
                if (playButton.isClicked(window, event)) {
                    state = AppState::PlayMenu;
                }
                else if (settingButton.isClicked(window, event)) {
                    state = AppState::SettingsMenu;
                }
                else if (exitButton.isClicked(window, event)) {
                    window.close();
                }
            }
            else if (state == AppState::SettingsMenu) {
                if (backButton.isClicked(window, event)) {
                    state = AppState::MainMenu;
                }
            }
            else if (state == AppState::PlayMenu) {
                if (backButton.isClicked(window, event)) {
                    state = AppState::MainMenu;
                    enteringName = false;
                    playerName.clear();
                }
                else if (loadGameButton.isClicked(window, event)) {
                    // TODO: Handle load game
                }
                else if (newGameButton.isClicked(window, event)) {
                    enteringName = true;
                    playerName.clear();
                }
                else if (enteringName && enterNameButton.isClicked(window, event)) {
                    std::ofstream outFile("playername.txt");
                    if (outFile.is_open()) {
                        outFile << playerName;
                        outFile.close();
                        std::cout << "Player name saved: " << playerName << std::endl;
                    }
                    enteringName = false;
                }
            }

            if (enteringName && event.type == Event::TextEntered) {
                if (event.text.unicode == '\b') {
                    if (!playerName.empty()) playerName.pop_back();
                }
                else if (event.text.unicode < 128 && playerName.size() < 20) {
                    playerName += static_cast<char>(event.text.unicode);
                }
                playerNameText.setString(playerName);
            }
        }

        if (state == AppState::MainMenu) {
            playButton.update(window);
            settingButton.update(window);
            exitButton.update(window);
        }
        else if (state == AppState::SettingsMenu) {
            backButton.update(window);
        }
        else if (state == AppState::PlayMenu) {
            backButton.update(window);
            loadGameButton.update(window);
            newGameButton.update(window);
            if (enteringName) enterNameButton.update(window);
        }

        window.clear();

        if (state == AppState::MainMenu) {
            mainBg.draw(0, 0, window);
            playButton.draw(window);
            settingButton.draw(window);
            exitButton.draw(window);
        }
        else if (state == AppState::SettingsMenu) {
            settingBg.draw(0, 0, window);
            backButton.draw(window);
        }
        else if (state == AppState::PlayMenu) {
            playBg.draw(0, 0, window);
            loadGameButton.draw(window);
            newGameButton.draw(window);
            backButton.draw(window);
            if (enteringName) {
                window.draw(nameBox);
                window.draw(playerNameText);
                enterNameButton.draw(window);
            }
        }

        window.display();
    }

    return 0;
}
