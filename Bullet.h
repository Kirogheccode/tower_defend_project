#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>

#include "Enemy.h"

using namespace std;
using namespace sf;

class Bullet
{
	Texture E_texture;
	Sprite E_sprite;

	Enemy* targetEnemy = nullptr;
	Vector2f position;

	float speed = 300.0f;
	int index = 0;

	bool avalible = false;

	int damage = 10;

public:
	void LoadBullet(const string& path);

	void SetBullet(Vector2f& pos, Enemy* targetEnemy);

	bool Collide(float& deltaTime);

	Enemy* GetTargetEnemy();

	int GetDamage();

	void Draw(RenderWindow& window);
};

