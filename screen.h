#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Screen
{
private:
	Texture texture;
	float width;
	float height;

public:
	Screen(float width, float height, string filepath);

	void draw(float x, float y, RenderWindow& window);

	~Screen();
};

class Button : public::Screen
{
public:
	void handleinputdraw(RenderWindow& window, Screen& new_screen);
	void handleinputback(RenderWindow& window);
};