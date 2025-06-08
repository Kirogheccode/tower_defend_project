#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

struct CHealth
{
	int hp = 0;

	CHealth() {};
	CHealth(const int& h)
	{
		hp = h;
	}
};

struct CMovement
{
	Vector2f position = { 0, 0 };
	float speed = 0;
	unsigned int currentPathindex = 0;

	vector<vector<Vector2f>> paths = { {Vector2f(0.f, 500.f),     //Cordinate for map1
										Vector2f(600.f, 500.f),
										Vector2f(600.f, 700.f),
										Vector2f(1200.f, 700.f),
										Vector2f(1200.f, 400.f),
										Vector2f(1920.f, 400.f)},

										{Vector2f(0.f, 500.f),     //Cordinate for map2
										Vector2f(600.f, 500.f),
										Vector2f(600.f, 700.f),
										Vector2f(1200.f, 700.f),
										Vector2f(1200.f, 400.f),
										Vector2f(1920.f, 400.f)},

										{Vector2f(0.f, 500.f),     //Cordinate for map3
										Vector2f(600.f, 500.f),
										Vector2f(600.f, 700.f),
										Vector2f(1200.f, 700.f),
										Vector2f(1200.f, 400.f),
										Vector2f(1920.f, 400.f)},

										{Vector2f(0.f, 500.f),     //Cordinate for map4
										Vector2f(600.f, 500.f),
										Vector2f(600.f, 700.f),
										Vector2f(1200.f, 700.f),
										Vector2f(1200.f, 400.f),
										Vector2f(1920.f, 400.f)}
	};

	CMovement() {}
	CMovement(const Vector2f& p, const float& v)
		: position(p), speed(v) {}
};

struct CSet
{
	Texture texture;
	Sprite sprite;

	Vector2u ImgCount;
	Vector2u CurrImg;

	float totalTime = 0.0f;
	float switchTime = 0.0f;

	IntRect uvRect;

	int row = 0;

	CSet() {}
	CSet(const string& filepath, const Vector2u& ImgCount, float& switchTime, const int& row)
	{
		if (!texture.loadFromFile(filepath))
		{
			cout << "Error! Can't load filepath" << endl;
			return;
		}

		sprite.setTexture(texture);
		if (sprite.getTextureRect().width == 0 || sprite.getTextureRect().height == 0)
		{
			cout << "Error! Can't load filepath" << endl;
			return;
		}

		this->ImgCount = ImgCount;
		this->switchTime = switchTime;
		this->row = row;

		totalTime = 0.0f;
		CurrImg.x = 0;

		uvRect.width = texture.getSize().x / float(ImgCount.x);
		uvRect.height = texture.getSize().y / float(ImgCount.y);
	}
};