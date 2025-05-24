#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>

using namespace std;
using namespace sf;

class Screen
{
public:
	Sprite sprite;
	Texture texture;

	Screen(const string& filepath);

	virtual void setRect(float frame_width, float frame_height, int column, int row);

	virtual void draw(float x, float y, RenderWindow& window);
};

class Button : public::Screen
{
private:
	bool isHovered = false;
	function<void()> onClick = nullptr;

public:
	Button(const string& filepath);

	void draw(float x, float y, RenderWindow& window);

	void setAction(std::function<void()> action);

	void handleinput(Vector2f& mousePos,const Event& event);
};

class MainMenu : public::Screen
{
private:
	RenderWindow& window;

	Screen background;

	Button playButton;
	Button settingsButton;
	Button exitButton;
public:
	MainMenu(RenderWindow &window, function<void()> goToSettings, function<void()> onPlay, function<void()> onExit);

	void update(Vector2f& mousePos, const Event& event);

	void draw(float x, float y, RenderWindow& window) override;
};