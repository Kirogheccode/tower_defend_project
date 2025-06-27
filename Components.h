#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>

using namespace std;
using namespace sf;

struct CMoney
{
	int money = 0;

	CMoney() {}
	CMoney(const int& m)
	{
		money = m;
	}
};

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

	vector<Vector2f> starting_pos = { Vector2f(0.f, 500.f),					//Starting position for map 1
								      Vector2f(0.f, 500.f),					//Starting position for map 2
								      Vector2f(0.f, 500.f),					//Starting position for map 3
								      Vector2f(0.f, 500.f)					//Starting position for map 4
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
	Vector2f position;

	CPosition() {}
	CPosition(const Vector2f& A) : position(A) {}
};

struct CBound
{
	enum shapeType { Circle, Rectangle } shape = Rectangle; // Default shape is Rectangle
	float radius = 0; // For Circle shape
	FloatRect rect; // For Rectangle shape
};

struct CSet
{
	Texture texture;
	Sprite sprite;

	Vector2u ImgCount;
	Vector2u CurrImg;

	bool isDynamic = false;

	int row = 0;

	float totalTime = 0.0f;
	float switchTime = 0.0f;

	IntRect uvRect;

	CSet() {}

	CSet(const string& filepath) // For static entitiy (background,...)
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

	CSet(const string& filepath, const Vector2u& ImgCount, const float& switchTime, const int& row) // For dynamic entitiy
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

		totalTime = 0.0f;
		CurrImg.x = 0;

		uvRect.width = texture.getSize().x / float(ImgCount.x);
		uvRect.height = texture.getSize().y / float(ImgCount.y);

		isDynamic = true;
		this->row = row;
		sprite.setOrigin( (texture.getSize().x / ImgCount.x) / 2.f, (texture.getSize().y / ImgCount.y) / 2.f);

		sprite.setTextureRect(uvRect);
	}
};

struct CInput
{
	function<void()> onClick;
	function<void()> onHover;
	function<void()> offHover;

	bool isHovered = false;

	CInput() = default;
	CInput(function<void()> clickFunc,
		function<void()> hoverFunc = nullptr,
		function<void()> unhoverFunc = nullptr)
		: onClick(clickFunc), onHover(hoverFunc), offHover(unhoverFunc) {
	}
};

struct CState
{
	bool isActive = false;
	CState() = default;
};

struct CDamage
{
	int damage;
	CDamage() {};
	CDamage(const int& d)
	{
		damage = d;
	}
};

struct CCooldown
{
	sf::Time cooldownDuration; // The total time between shots
	sf::Clock shootClock;      // A persistent clock to track the cooldown

	// Constructor to set the cooldown
	CCooldown(float seconds) : cooldownDuration(sf::seconds(seconds)) {}
};

//struct CTarget
//{
//	Entity* target = nullptr; // Pointer to the target entity
//};
//
//struct CSourceTower
//{
//	Entity* source = nullptr; // Pointer to the entity that created this entity (e.g., a tower that spawned a bullet)
//};
