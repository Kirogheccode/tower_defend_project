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
	float speed = 0;
	unsigned int currentPathindex = 0;

	vector<Vector2f> starting_pos = { Vector2f(500.f, 500.f),           //Starting position for map 1
								  Vector2f(500.f, 500.f),			    //Starting position for map 2
								  Vector2f(500.f, 500.f),			    //Starting position for map 3
								  Vector2f(500.f, 500.f)			    //Starting position for map 4
	};

	vector<vector<Vector2f>> paths = { {Vector2f(0.f, 500.f),     //Cordination for map1
										Vector2f(600.f, 500.f),
										Vector2f(600.f, 700.f),
										Vector2f(1200.f, 700.f),
										Vector2f(1200.f, 400.f),
										Vector2f(1920.f, 400.f)},

										{Vector2f(0.f, 500.f),     //Cordination for map2
										Vector2f(600.f, 500.f),
										Vector2f(600.f, 700.f),
										Vector2f(1200.f, 700.f),
										Vector2f(1200.f, 400.f),
										Vector2f(1920.f, 400.f)},

										{Vector2f(0.f, 500.f),     //Cordination for map3
										Vector2f(600.f, 500.f),
										Vector2f(600.f, 700.f),
										Vector2f(1200.f, 700.f),
										Vector2f(1200.f, 400.f),
										Vector2f(1920.f, 400.f)},

										{Vector2f(0.f, 500.f),     //Cordination for map4
										Vector2f(600.f, 500.f),
										Vector2f(600.f, 700.f),
										Vector2f(1200.f, 700.f),
										Vector2f(1200.f, 400.f),
										Vector2f(1920.f, 400.f) }
	};

	CMovement() {}
	CMovement(const float& v)
		: speed(v) {}
};

struct CPosition
{
	Vector2f postion;

	CPosition() {}
	CPosition(const Vector2f& A) : postion(A) {}
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

	CSet(const string& filepath) //For static entitiy (background,...)
	{
		if (!texture.loadFromFile(filepath))
		{
			cout << "Error! Can't load filepath" << endl;
			return;
		}

		sprite.setTexture(texture);
		if (sprite.getTextureRect().width == 0 || sprite.getTextureRect().height == 0)
		{
			cout << "Error! Can't load sprite" << endl;
			return;
		}
	}

	CSet(const string& filepath, const Vector2u& ImgCount, const float& switchTime, const int& row) //For dynamic entitiy
	{
		if (!texture.loadFromFile(filepath))
		{
			cout << "Error! Can't load filepath" << endl;
			return;
		}

		sprite.setTexture(texture);
		if (sprite.getTextureRect().width == 0 || sprite.getTextureRect().height == 0)
		{
			cout << "Error! Can't load sprite" << endl;
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

struct CCollision {};