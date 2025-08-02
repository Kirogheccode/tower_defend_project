#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>
#include <ctime>
using namespace std;
using namespace sf;

// Tiền 
struct CMoney {
	int money = 0;
	CMoney() {}
	CMoney(const int& m) : money(m) {}
};


// Máu
struct CHealth {
	int hp = 0;
	CHealth() {}
	CHealth(const int& h) : hp(h) {}
};


// Level nâng cấp của tower
struct CLevel {
	int levelindex = 0;
	CLevel() {}
	CLevel(const int& h) : levelindex(h) {}
};


// Di chuyển của quái: bao gồm tốc độ, vị trí hiện tại, và đường đi theo từng map
struct CMovement {
	float speed = 0.f;
	unsigned int currentPathindex = 0;
	Vector2f velocity = { 0.f, 0.f };
	unsigned int pathIndex = 0;

	vector<Vector2f> starting_pos = {	// Vị trí bắt đầu cho từng map
		{1165.f, 1580.f}, { -500.f, 500.f }, { 1252.f, 1575.f }, { 0.f, 500.f }
	};

	// Đường đi cho mỗi map (có thể có nhiều đường)
	vector<vector<vector<Vector2f>>> paths = {
		{ // Map 1
			{ {1165.f,880.f}, {940.f,880.f}, {940.f,730.f}, {285.f,730.f}, {285.f,330.f}, {1770.f,330.f}, {1770.f,0.f} }
		},
		{ // Map 2
			{ {465.f,500.f}, {465.f,385.f}, {715.f,385.f}, {715.f,220.f}, {1265.f,220.f}, {1265.f,580.f}, {955.f,580.f}, {955.f,890.f}, {1560.f,890.f}, {1560.f,265.f} }
		},
		{ // Map 3
			{ {1252.f,755.f}, {1055.f,755.f}, {1055.f,330.f}, {770.f,330.f}, {770.f,550.f}, {300.f,550.f}, {300.f,90.f} }
		},
		{ // Map 4
			{ {600.f,500.f}, {600.f,700.f}, {1200.f,700.f}, {1200.f,400.f}, {1920.f,400.f} },      // path 0
			{ {600.f,500.f}, {600.f,700.f}, {1000.f,600.f}, {1200.f,400.f}, {1920.f,400.f} }       // path 1
		}
	};

	CMovement() = default;
	explicit CMovement(const float& v) : speed(v) {}
};


// Thời gian hệ thống thực tại
struct CTime {
	time_t now;
	tm local;

	CTime() {
		now = time(0);
		localtime_s(&local, &now);
	}
};


// Vị tr
struct CPosition {
	Vector2f position;
	CPosition() {}
	CPosition(const Vector2f& A) : position(A) {}
};


// Hiển thị hình ảnh (sprite)
struct CSet {
	Texture texture;
	Sprite sprite;

	Vector2u ImgCount;
	Vector2u CurrImg;
	bool isDynamic = false;
	int row = 0;

	float totalTime = 0.0f;
	float switchTime = 0.0f;
	IntRect uvRect;

	// Static sprite (không hoạt ảnh)
	CSet(const string& filepath) {
		if (!texture.loadFromFile(filepath)) {
			cout << "Error! Can't load filepath" << endl;
			return;
		}
		sprite.setTexture(texture);
		if (sprite.getTextureRect().width == 0 || sprite.getTextureRect().height == 0) {
			cout << "Error! Can't load sprite" << endl;
			return;
		}
	}

	// Dynamic sprite (có hoạt ảnh)
	CSet(const string& filepath, const Vector2u& ImgCount, const float& switchTime, const int& row) {
		if (!texture.loadFromFile(filepath)) {
			cout << "Error! Can't load filepath" << endl;
			return;
		}
		sprite.setTexture(texture);
		this->ImgCount = ImgCount;
		this->switchTime = switchTime;
		this->row = row;
		isDynamic = true;
		CurrImg.x = 0;
		uvRect.width = texture.getSize().x / float(ImgCount.x);
		uvRect.height = texture.getSize().y / float(ImgCount.y);
		sprite.setOrigin(uvRect.width / 2.f, uvRect.height / 2.f);
		sprite.setTextureRect(uvRect);
	}
};


// Vùng va chạm (boundary) để xử lý phạm vi, collision,...
struct CBound {
	enum shapeType { Circle, Rectangle } shape = Rectangle;
	sf::CircleShape circle;
	sf::RectangleShape rectangle;
	float radius = 0;
	FloatRect rect;

	// Hình tròn
	CBound(float r) : radius(r), shape(Circle) {
		circle.setRadius(radius);
		circle.setOrigin(radius, radius);
		circle.setFillColor(sf::Color(0, 0, 0, 40));
	}

	// Hình chữ nhật
	CBound(const FloatRect& r) : rect(r), shape(Rectangle) {
		rectangle.setSize({ rect.width, rect.height });
		rectangle.setPosition(rect.left, rect.top);
		rectangle.setFillColor(sf::Color(255, 255, 255, 20));
	}
};


// Scale vùng va chạm
struct CBoundaryScale {
	float scale = 1.0f;
	CBoundaryScale() {}
	CBoundaryScale(float r) : scale(r) {}
};


// Scale hình ảnh (sprite)
struct CSpriteScale {
	float scale = 1.0f;
	CSpriteScale() {}
	CSpriteScale(float r) : scale(r) {}
};


// Xử lý input
struct CInput {
	function<void()> onClick;
	function<void()> onHover;
	function<void()> offHover;
	bool isChoosing = false;
	bool isHovered = false;

	CInput() = default;
	CInput(function<void()> clickFunc, function<void()> hoverFunc = nullptr, function<void()> unhoverFunc = nullptr)
		: onClick(clickFunc), onHover(hoverFunc), offHover(unhoverFunc) {
	}
};


// Sát thương 
struct CDamage {
	int damage = 0;
	CDamage() = default;
	CDamage(const int& d) : damage(d) {}
};


// Tốc độ bắn và thời gian cooldown
struct CCooldown {
	Time cooldownDuration;
	Clock shootClock;
	CCooldown(float seconds) : cooldownDuration(sf::seconds(seconds)) {}
};


// Slider để điều chỉnh thông số
struct CSlider {
	Texture trackTexture, handleTexture;
	Sprite track, handle;
	float* valueToControl = nullptr;
	bool isDragging = false;

	CSlider(float* valuePtr, Vector2f position, const string& handlePath, const string& trackPath) {
		valueToControl = valuePtr;
		handleTexture.loadFromFile(handlePath);
		trackTexture.loadFromFile(trackPath);
		track.setTexture(trackTexture);
		handle.setTexture(handleTexture);
		track.setOrigin(trackTexture.getSize().x / 2.f, trackTexture.getSize().y / 2.f);
		track.setPosition(position);
		handle.setOrigin(handleTexture.getSize().x / 2.f, handleTexture.getSize().y / 2.f);
		updateHandlePosition();
	}

	void updateHandlePosition() {
		if (!valueToControl) return;
		float percent = *valueToControl / 100.f;
		float trackLeft = track.getPosition().x - trackTexture.getSize().x / 2.f;
		float newX = trackLeft + (trackTexture.getSize().x * percent);
		handle.setPosition(newX, track.getPosition().y);
	}

	void updateValueFromHandle(float mouseX) {
		if (!valueToControl) return;
		float trackLeft = track.getPosition().x - trackTexture.getSize().x / 2.f;
		float trackRight = track.getPosition().x + trackTexture.getSize().x / 2.f;
		mouseX = std::max(trackLeft, std::min(mouseX, trackRight));
		float percent = (mouseX - trackLeft) / trackTexture.getSize().x;
		*valueToControl = percent * 100.f;
		updateHandlePosition();
	}
};


// Loại đạn mà tower đang dùng (dựa vào tag)
struct CWeapon {
	string tag;

	CWeapon() {}
	CWeapon(const string& A) { tag = A; }
};


// Hiển thị văn bản lên màn hình
struct CText {
	Text text;
	CText() {}
	CText(const string& A) { text.setString(A); }
	CText(const int& A) { text.setString(to_string(A)); }
	CText(const float& A) { text.setString(to_string(A)); }
};
