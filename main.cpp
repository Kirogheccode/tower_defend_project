#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include "screen.h"
#include "button.h"
#include "sound.h"

using namespace sf;

enum class AppState { MainMenu, SettingsMenu, PlayMenu };

int main() {
    RenderWindow window(VideoMode(1024, 576), "Tower Defense - SFML");
    AppState state = AppState::MainMenu;

    SoundManager soundManager;

    // Load sound effects and background music
    soundManager.loadSound("click", "SOUNDS/hover.ogg");
    soundManager.playMusic("SOUNDS/bgmusic.wav");  // bat dau phat nhac nen

    // Backgrounds
    Screen mainBg(1024, 576, "IMGS/Menu_Screen_Temp.png");
    Screen settingBg(1024, 576, "IMGS/background.png");
    Screen playBg(1024, 576, "IMGS/Menu_Screen_Temp.png");

    // Buttons for main menu
    Button playButton("IMGS/play.png", 600, 150);
    Button settingButton("IMGS/setting.png", 600, 300);
    Button exitButton("IMGS/exit.png", 600, 450);

    // Buttons for other menus
    Button backButton("IMGS/back.png", 0, 0);
    Button loadGameButton("IMGS/load.png", 600, 200);
    Button newGameButton("IMGS/new.png", 600, 350);
    Button enterNameButton("IMGS/enter.png", 920, 450);

    // Font
    Font font;
    if (!font.loadFromFile("IMGS/arial.ttf")) {
        std::cerr << "Failed to load font\n";
    }

    // Name box and text
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
					soundManager.playSound("click");
                    state = AppState::PlayMenu;
                }
                else if (settingButton.isClicked(window, event)) {
					soundManager.playSound("click");
                    state = AppState::SettingsMenu;
                }
                else if (exitButton.isClicked(window, event)) {
					soundManager.playSound("click");
                    window.close();
                }
            }
            else if (state == AppState::SettingsMenu) {
                if (backButton.isClicked(window, event)) {
					soundManager.playSound("click");
                    state = AppState::MainMenu;
                }
            }
            else if (state == AppState::PlayMenu) {
                if (backButton.isClicked(window, event)) {
					soundManager.playSound("click");
                    state = AppState::MainMenu;
                    enteringName = false;
                    playerName.clear();
                }
                else if (loadGameButton.isClicked(window, event)) {
					soundManager.playSound("click");
                    // TODO: Load game logic
                }
                else if (newGameButton.isClicked(window, event)) {
					soundManager.playSound("click");
                    enteringName = true;
                    playerName.clear();
                }
                else if (enteringName && enterNameButton.isClicked(window, event)) {
					soundManager.playSound("click");
                    std::ofstream outFile("playername.txt");
                    if (outFile.is_open()) {
                        outFile << playerName;
                        outFile.close();
                        std::cout << "Player name saved: " << playerName << std::endl;
                    }
                    enteringName = false;
                }
            }

            // Handle text input
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

        // Update buttons (hover effect)
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

        // Render
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