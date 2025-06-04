#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Enemy.h"
#include "Bullet.h"

using namespace sf;
using namespace std;

class Tower
{
	vector<Bullet> bullets;
	Texture E_texture; 
	Sprite E_sprite;
	CircleShape boundary;
	Animation animation;

	Vector2f position;

	float width = 0.0f;
	float height = 0.0f;
	float delayTime = 0.0f;

	unsigned int row = 0;

public:
	void SetTower(const Vector2u& ImgCount, const float& switchTime, const unsigned int& row);

	void setPosition(Vector2f& mousePos);

	void LoadTower(const string& path);

	void Update(float& deltaTime);

	void HasEnemy(float& deltaTime, vector<Enemy>& Enemies, vector<Bullet>& spawned_bullet);

	void Draw(RenderWindow&);
};

