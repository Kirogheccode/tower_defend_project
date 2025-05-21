#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Screen
{
private:
	Texture texture;

public:
	Screen(float width, float height, string filepath);

	void draw(RenderWindow& window);

	~Screen();
};