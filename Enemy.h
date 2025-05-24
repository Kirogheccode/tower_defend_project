#pragma once
#include "Entity.h"
class Enemy :
    public Entity
{
private:
	int m_iHealth;
	int m_iDamage;
	float m_fSpeed;
	int m_iPathIndex;
	sf::Sprite m_sEnemySprite;
public:
	Enemy(float x, float y, const sf::Texture& texture, int health, int damage, float speed) :
		Entity(PhysicsData::Type::Dynamic)
	{
		SetRectanglePhysics(32.0f, 32.0f);
		SetPosition({ x,y });
		SetTexture(texture);
		SetScale({ 0.5f,0.5f });
		SetOrigin({ 10.0f,10.0f });
		m_iHealth = health;
		m_iDamage = damage;
		m_fSpeed = speed;
	}

	int GetHealth() const
	{
		return m_iHealth;
	}

	void SetHealth(int health)
	{
		m_iHealth = health;
	}
	
	int GetDamage() const
	{
		return m_iDamage;
	}

	void Update()
	{
		if (m_bDeletionRequested)
			return;
	}

	void setPathIndex(int index)
	{
		m_iPathIndex = index;
	}



};

