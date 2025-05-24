#include "Enemy.h"


Enemy::Enemy(float x, float y, const sf::Texture& texture, int health, int damage, float speed) 
		:Entity(PhysicsData::Type::Dynamic)
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

void Enemy::Update()
{
	if (m_bDeletionRequested)
	return;
}


