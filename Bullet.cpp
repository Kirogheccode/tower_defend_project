#include "Bullet.h"
#include "Enemy.h"
#include "MathSupport.h"
#include <iostream>
#include <vector>


Bullet::Bullet(float x, float y, const sf::Texture& texture, int damage, float speed) 
	:Entity(PhysicsData::Type::Dynamic)
{
	SetCirclePhysics(5.0f);
	SetPosition({ x,y });
	SetTexture(texture);
	SetScale({ 0.5f,0.5f });
	SetOrigin({ 2.5f,2.5f });
	m_iDamage = damage;
	m_fSpeed = speed;
}

int Bullet::GetDamage() const
{
	return m_iDamage;
}

float Bullet::GetSpeed() const
{
	return m_fSpeed;
}

	// Check for collision with an enemy
	// circle vs rectangle
void Bullet::OnCollision(Enemy& target)
{
	// find the clostest point on the rectangle to the circle (limited by the rectangle edges)
	float fClosestX = std::clamp((*this).GetPosition().x, (*this).GetPosition().x - target.GetPhysicsData().m_fWidth / 2, target.GetPosition().x + target.GetPhysicsData().m_fWidth / 2);
	float fClosestY = std::clamp((*this).GetPosition().y, target.GetPosition().y - target.GetPhysicsData().m_fHeight / 2, target.GetPosition().y + target.GetPhysicsData().m_fHeight / 2);

	sf::Vector2f vClosestPoint(fClosestX, fClosestY);
	sf::Vector2f vCircleToClosestPoint = vClosestPoint - (*this).GetPosition();

	float fDistance = MathSupport::Length(vCircleToClosestPoint);

	// in case of collision
	if (fDistance < (*this).GetPhysicsData().m_fRadius)
	{
		m_bDeletionRequested = true; // mark the bullet for deletion
		target.SetHealth(target.GetHealth() - m_iDamage); // reduce the enemy health
		target.Update(); // update the enemy state
	}
}

