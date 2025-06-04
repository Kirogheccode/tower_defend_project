#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Animation.h"

using namespace sf;
using namespace std;

class Enemy
{
	Texture E_texture;
	Sprite E_sprite;
	Animation animation;

	int hp = 100;
	unsigned int row = 0;
	float speed = 1.0f;

	Vector2f position;
	size_t currentTargetIndex = 0;

	float width = 0;
	float height = 0;

public:
	void SetEnemy(const Vector2u& ImgCount, const float& switchTime, const int& HP, const float& speed, const unsigned int& row, const bool& inverted);

	void SetHealth(int remain);

	int GetHealth();

	void LoadEnemy(const string& Path);

	void Update(float& deltaTime, vector<Vector2f>& Path);

	Vector2f GetPosition();

	void Draw(RenderWindow&);
};

//bool faceRight;
