#pragma once
#include "Enemy.h"

void Enemy::SetEnemy(const Vector2u& ImgCount, const float& switchTime, const int& hp, const float& speed, const unsigned int& row, const bool& inverted)
{
	//ImgCount.x = numbers of columns
	//ImgCount.y = numbers of rows

	this->speed = speed;
	this->row  = row;
	this->hp = hp;

	animation.setAnimation(&E_texture, ImgCount, switchTime);
	E_sprite.setTexture(E_texture);

	if (!inverted) E_sprite.scale(Vector2f(1.0, 1.0));
	else E_sprite.scale(Vector2f(-1.0, 1.0));

	E_sprite.setPosition(Vector2f(0.0f, 500.0));
	position = Vector2f(0.0f, 500.0);

	width = E_texture.getSize().x / float(ImgCount.x);
	height = E_texture.getSize().y / float(ImgCount.y);
}

int Enemy::GetHealth()
{
	return hp;
}

void Enemy::Update(float& deltaTime, vector<Vector2f>& path) {
	if (currentTargetIndex >= path.size())
		return;

	Vector2f target = path[currentTargetIndex];
	Vector2f direction = target - position;

	float distance = sqrt(direction.x * direction.x + direction.y * direction.y);

	if (distance < 1.f) {
		currentTargetIndex++;
		if (currentTargetIndex >= path.size()) {
			// At the finish (minusHealth())
			return;
		}

		target = path[currentTargetIndex];
		direction = target - position;
		distance = sqrt(direction.x * direction.x + direction.y * direction.y);
	}

	Vector2f movement(0.f, 0.f);

	if (distance > 0) {
		movement = direction / distance; //Movement is simply direction vector
	}

	position += movement * speed * deltaTime;

	animation.Update(row, deltaTime);

	E_sprite.setTextureRect(animation.uvRect);

	E_sprite.setPosition(position);
}

void Enemy::SetHealth(int remain)
{
	hp = remain;
}

void Enemy::Draw(RenderWindow& window)
{
	window.draw(E_sprite);
}

Vector2f Enemy::GetPosition()
{
	return position;
}

void Enemy::LoadEnemy(const string& Path)
{
	if (!E_texture.loadFromFile(Path))
	{
		cout << "Failed to load!" << endl;
		return;
    }
}
