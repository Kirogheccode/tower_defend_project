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
	sf::Vector2f velocity = { 0.f, 0.f }; // Add this!

	vector<Vector2f> starting_pos = { Vector2f(1150.f, 1080.f),				//Starting position for map 1
								      Vector2f(0.f, 500.f),					//Starting position for map 2
								      Vector2f(0.f, 500.f),					//Starting position for map 3
								      Vector2f(0.f, 500.f)					//Starting position for map 4
	};

	vector<vector<Vector2f>> paths = { {Vector2f(1150.f, 1080.f),     //Cordination for map1
										Vector2f(1150.f, 880.f),
										Vector2f(940.f, 880.f),
										Vector2f(940.f, 730.f),
										Vector2f(285.f, 730.f),
										Vector2f(285.f, 330.f),
										Vector2f(1770.f, 330.f),
										Vector2f(1770.f, 0.f)},

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
	CBound(float r) : radius(r), shape(Circle) {} // Constructor for Circle shape (one parameter)
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
	CDamage() = default;
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

struct CSlider {
	sf::RectangleShape track;
	sf::RectangleShape handle;
	float* valueToControl = nullptr;
	bool isDragging = false;

	CSlider(float* valuePtr, sf::Vector2f position, sf::Vector2f trackSize) {
		valueToControl = valuePtr;

		// Thiết lập thanh trượt
		track.setSize(trackSize);
		track.setOrigin(trackSize.x / 2.f, trackSize.y / 2.f);
		track.setPosition(position);
		track.setFillColor(sf::Color(50, 50, 50)); // Màu xám tối

		// Thiết lập nút kéo
		handle.setSize({ 20.f, trackSize.y * 2.f }); // Nút kéo cao hơn thanh trượt một chút
		handle.setOrigin(handle.getSize().x / 2.f, handle.getSize().y / 2.f);
		handle.setFillColor(sf::Color(150, 150, 150)); // Màu xám sáng

		// Đặt vị trí ban đầu của nút kéo dựa trên giá trị âm lượng
		updateHandlePosition();
	}

	// Cập nhật vị trí của nút kéo dựa trên giá trị âm lượng
	void updateHandlePosition() {
		if (!valueToControl) return;
		float percent = *valueToControl / 100.f; // Chuyển giá trị (0-100) thành tỷ lệ (0.0-1.0)
		float trackLeft = track.getPosition().x - track.getSize().x / 2.f;
		float newX = trackLeft + (track.getSize().x * percent);
		handle.setPosition(newX, track.getPosition().y);
	}

	// Cập nhật giá trị âm lượng dựa trên vị trí của nút kéo
	void updateValueFromHandle(float mouseX) {
		if (!valueToControl) return;
		float trackLeft = track.getPosition().x - track.getSize().x / 2.f;
		float trackRight = track.getPosition().x + track.getSize().x / 2.f;

		// Giới hạn vị trí chuột trong phạm vi thanh trượt
		mouseX = std::max(trackLeft, std::min(mouseX, trackRight));

		float percent = (mouseX - trackLeft) / track.getSize().x;
		*valueToControl = percent * 100.f;

		updateHandlePosition(); // Cập nhật lại vị trí handle cho chính xác
	}
};
