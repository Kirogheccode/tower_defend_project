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
	float speed = 0.f;
	unsigned int currentPathindex = 0;
	sf::Vector2f velocity = { 0.f, 0.f };

	// Starting positions for each map
	// +500f starting delay
	std::vector<sf::Vector2f> starting_pos = {
		{1165.f, 1580.f},   // Map 1
		{0.f,   500.f},     // Map 2
		{1254.f, 1277.f},   // Map 3
		{0.f,   500.f}      // Map 4
	};

	// Path coordinates for each map
	std::vector<std::vector<sf::Vector2f>> paths = {
		{   // Map 1
			{1165.f, 880.f},
			{940.f,  880.f},
			{940.f,  730.f},
			{285.f,  730.f},
			{285.f,  330.f},
			{1770.f, 330.f},
			{1770.f, 0.f}
		},
		{   // Map 2
			{600.f,  500.f},
			{600.f,  700.f},
			{1200.f, 700.f},
			{1200.f, 400.f},
			{1920.f, 400.f}
		},
		{   // Map 3
			{1254.f, 755.f},
			{1055.f, 755.f},
			{1055.f, 700.f},
			{1200.f, 400.f},
			{1920.f, 400.f}
		},
		{   // Map 4
			{600.f,  500.f},
			{600.f,  700.f},
			{1200.f, 700.f},
			{1200.f, 400.f},
			{1920.f, 400.f}
		}
	};

	CMovement() = default;
	explicit CMovement(const float& v)
		: speed(v) {
	}
};

struct CPosition
{
	Vector2f position;

	CPosition() {}
	CPosition(const Vector2f& A) : position(A) {}
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

struct CBound
{
	enum shapeType { Circle, Rectangle } shape = Rectangle; // Mặc định là Rectangle

	sf::CircleShape circle;
	sf::RectangleShape rectangle;

	float radius = 0;        // Dùng để cập nhật lại circle khi cần
	FloatRect rect;          // Dùng để cập nhật lại rectangle khi cần

	// Constructor cho hình tròn
	CBound(float r) : radius(r), shape(Circle)
	{
		circle.setRadius(radius);
		circle.setOrigin(radius, radius);
		circle.setFillColor(sf::Color(255, 255, 255, 20));
		circle.setOutlineThickness(0.f);

	}

	// Constructor cho hình chữ nhật
	CBound(const FloatRect& r) : rect(r), shape(Rectangle)
	{
		rectangle.setSize({ rect.width, rect.height });
		rectangle.setPosition(rect.left, rect.top);
		rectangle.setFillColor(sf::Color(255, 255, 255, 20));
		rectangle.setOutlineThickness(0.f);
	}
};

struct CBoundaryScale
{
	float scale;
	CBoundaryScale() : scale(1.0f) {}
	CBoundaryScale(float r) : scale(r) {}
};

struct CSpriteScale
{
	float scale;
	CSpriteScale() : scale(1.0f) {}
	CSpriteScale(float r) : scale(r) {}
};

struct CInput
{
	function<void()> onClick;
	function<void()> onHover;
	function<void()> offHover;

	bool isChoosing = false;
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
	/*sf::RectangleShape track;
	sf::RectangleShape handle;*/
	Texture trackTexture;
	Texture handleTexture;
	Sprite track;
	Sprite handle;
	float* valueToControl = nullptr;
	bool isDragging = false;

	CSlider(float* valuePtr, Vector2f position, const string& handlePath, const string& trackPath) 
	{
		valueToControl = valuePtr;


		if (!handleTexture.loadFromFile(handlePath))
		{
			cout << "Error loading handle texture" << endl;
			return;
		}
		if (!trackTexture.loadFromFile(trackPath))
		{
			cout << "Error loading track texture" << endl;
			return;
		}
		track.setTexture(trackTexture);
		handle.setTexture(handleTexture);

		// Thiết lập thanh trượt
		track.setOrigin(trackTexture.getSize().x / 2.f, trackTexture.getSize().y / 2.f);
		track.setPosition(position);
	    

		// Thiết lập nút kéo
		handle.setOrigin(handleTexture.getSize().x / 2.f, handleTexture.getSize().y / 2.f);
		

		// Đặt vị trí ban đầu của nút kéo dựa trên giá trị âm lượng
		updateHandlePosition();
	}

	// Cập nhật vị trí của nút kéo dựa trên giá trị âm lượng
	void updateHandlePosition() {
		if (!valueToControl) return;
		float percent = *valueToControl / 100.f; // Chuyển giá trị (0-100) thành tỷ lệ (0.0-1.0)
		float trackLeft = track.getPosition().x - trackTexture.getSize().x / 2.f;
		float newX = trackLeft + (trackTexture.getSize().x * percent);
		handle.setPosition(newX, track.getPosition().y);
	}

	// Cập nhật giá trị âm lượng dựa trên vị trí của nút kéo
	void updateValueFromHandle(float mouseX) {
		if (!valueToControl) return;
		float trackLeft = track.getPosition().x - trackTexture.getSize().x / 2.f;
		float trackRight = track.getPosition().x + trackTexture.getSize().x / 2.f;

		// Giới hạn vị trí chuột trong phạm vi thanh trượt
		mouseX = std::max(trackLeft, std::min(mouseX, trackRight));

		float percent = (mouseX - trackLeft) / trackTexture.getSize().x;
		*valueToControl = percent * 100.f;

		updateHandlePosition(); // Cập nhật lại vị trí handle cho chính xác
	}
};

struct CWeapon
{
	string tag;
};

struct CText
{
	sf::Text text;

	CText() {}

	CText(const string& A)
	{
		text.setString(A);
	}

	CText(const int& A)
	{
		text.setString(to_string(A));
	}

	CText(const float& A)
	{
		text.setString(to_string(A));
	}
};
