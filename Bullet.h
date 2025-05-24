#pragma once
#include "Entity.h"
#include "Enemy.h"
#include "MathSupport.h"
#include <iostream>
#include <vector>

class Bullet :
    public Entity
{
private:
	int m_iDamage;
	float m_fSpeed;
	sf::Sprite m_sBulletSprite;

public:
	Bullet(float x, float y, const sf::Texture& texture, int damage, float speed) :
		Entity(PhysicsData::Type::Dynamic) {};

	int GetDamage() const
	{
		return m_iDamage;
	}

	float GetSpeed() const
	{
		return m_fSpeed;
	}

	void OnCollision(Enemy&); //check for collision with an enemy
};

