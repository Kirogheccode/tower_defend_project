#include <SFML/Graphics.hpp>
#include <iostream>

#include "screen.h"

using namespace std;
using namespace sf;

// ==================== [SCREEN] ====================

Screen::Screen(const string& filepath)
{
    if (!texture.loadFromFile(filepath))
    {
        std::cout << "Failed to load screen texture: " << filepath << std::endl;
        return;
    }

    sprite.setTexture(texture);
}

void Screen::setRect(float frame_width, float frame_height, int column, int row)
{
    sprite.setTextureRect(IntRect(
        static_cast<int>(column * frame_width),
        static_cast<int>(row * frame_height),
        static_cast<int>(frame_width),
        static_cast<int>(frame_height)
    ));
}

void Screen::draw(float x, float y, RenderWindow& window)
{
    sprite.setPosition(x, y);

    window.draw(sprite);
}


// ==================== [Button] ====================

Button::Button(const string& filepath)
    :Screen("")
{
    if (!texture.loadFromFile(filepath))
    {
        cout << "Failed to load screen png" << endl;
        return;
    }

    sprite.setTexture(texture);
}

void Button::draw(float x, float y, RenderWindow& window)
{
	sprite.setPosition(x, y);

	window.draw(sprite);
}

void Button::setAction(std::function<void()> action) {
    onClick = action;
}

void Button::handleinput(Vector2f& mousePos, const Event& event)
{
    if (sprite.getGlobalBounds().contains(mousePos)) {
        sprite.setColor(sf::Color(200, 200, 200));
        sprite.setScale(1.05f, 1.05f);

        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
        {
            onClick();
        }
    }
    else {
        sprite.setColor(sf::Color::White);
        sprite.setScale(1.f, 1.f);
    }
}


// ==================== [MainMenu] ====================

MainMenu::MainMenu(RenderWindow& window, function<void()> goToSettings, function<void()> onPlay, function<void()> onExit)
    :Screen(""),
    window(window),
    background("IMGS/Menu_Screen_Temp.png"),
    playButton("IMGS/play.png"),
    settingsButton("IMGS/setting.png"),
    exitButton("IMGS/exit.png")
{
    playButton.setAction(onPlay);
    settingsButton.setAction(goToSettings);
    exitButton.setAction(onExit);
}

void MainMenu::update(Vector2f& mousePos, const Event& event)
{
    playButton.handleinput(mousePos, event);
    settingsButton.handleinput(mousePos, event);
    exitButton.handleinput(mousePos, event);
}

void MainMenu::draw(float x, float y, RenderWindow& window)
{
    background.draw(0, 0, window);
    playButton.draw(580, 150, window);
    settingsButton.draw(580, 300, window);
    exitButton.draw(580, 450, window);
}