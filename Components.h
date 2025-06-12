#pragma once

#include "ComponentManager.h"
#include "ComponentsArray.h"
#include <bitset>


namespace cmpAux
{
	const int MAX_ENTITIES = 4000;
	using eID = std::uint32_t;
	using Signature = std::bitset<MAX_ENTITIES>;
	using ComponentType = std::uint8_t; // Component ID
	using EventId = std::uint32_t;
	const ComponentType MAX_COMPONENTS = 32;
}

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

	vector<Vector2f> position = { Vector2f(500.f, 500.f),         //Starting position for map 1
								  Vector2f(500.f, 500.f),         //Starting position for map 2
								  Vector2f(500.f, 500.f),         //Starting position for map 3
								  Vector2f(500.f, 500.f)          //Starting position for map 4
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
		: speed(v) {
	}
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
			cout << "Error! Can't load filepath" << endl;
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

struct CAnimation
{
	float speed = 0.0f;
	float totalTime = 0.0f;
	float switchTime = 0.0f;
	Vector2u ImgCount;
	Vector2u CurrImg;
	IntRect uvRect;
	int row = 0;
	CAnimation() {}
	CAnimation(const Vector2u& ImgCount, const float& switchTime, const int& row)
		: ImgCount(ImgCount), switchTime(switchTime), row(row) {
		totalTime = 0.0f;
		CurrImg.x = 0;
	}
};

struct CPosition
{
	Vector2f position = Vector2f(0.f, 0.f);
	CPosition() {}
	CPosition(const Vector2f& pos)
		: position(pos) {}
};

struct CVelocity
{
	Vector2f velocity = Vector2f(0.f, 0.f);
	CVelocity() {}
	CVelocity(const Vector2f& vel)
		: velocity(vel) {}
};

 