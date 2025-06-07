#include "Bullet.h"

void Bullet::LoadBullet(const string& path)
{
	if (!E_texture.loadFromFile(path))
	{
		cout << "Failed to load!" << endl;
		return;
	}

	E_sprite.setTexture(E_texture);
}

int Bullet::GetDamage()
{
	return damage;
}

void Bullet::SetBullet(Vector2f& pos, Enemy* ememyTarget)
{
	position = pos;
	targetEnemy = ememyTarget;

	E_sprite.setPosition(position);
}

Enemy* Bullet::GetTargetEnemy()
{
	return targetEnemy;
}

bool Bullet::Collide(float& deltaTime)
{
	if (targetEnemy == nullptr)
		return false;

	Vector2f direction = targetEnemy->GetPosition() - position;
	float distance = sqrt(direction.x * direction.x + direction.y * direction.y);

	if (distance < 5.f)
	{
		return true;
	}

	Vector2f movement(0.f, 0.f);

	if (distance > 0.f)
	{
		position += (direction / distance) * speed * deltaTime;
	}

	E_sprite.setPosition(position);

	return false;
}


void Bullet::Draw(RenderWindow& window)
{
	window.draw(E_sprite);
}
