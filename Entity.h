#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

#include "EntityManager.h"
#include "Components.h"
#include "MathSupport.h"

using namespace std;
using namespace sf;

class EntityManager;

class Entity
{
	friend class EntityManager;
	size_t m_id = 0;
	string m_tag = "default";
	bool m_active = false;

public:
	Entity(const string& tag, const size_t& id);

	shared_ptr<CHealth> cHealth;
	shared_ptr<CMovement> cMovement;
	shared_ptr<CSet> cSet;
	shared_ptr<CPosition> cPosition;
	shared_ptr<CInput> cInput;
	shared_ptr<CMoney> cMoney;
	shared_ptr<CBound> cBound;
	shared_ptr<CDamage> cDamage;
	shared_ptr<CCooldown> cCooldown;
	shared_ptr<Entity> cTarget; //nearest enemies or leader enemy 
	shared_ptr<Entity> cSource;
	shared_ptr<CSlider> cSlider;
	shared_ptr<CWeapon> cWeapon;
	shared_ptr<CBoundaryScale> cBoundaryScale;
	shared_ptr<CSpriteScale> cSpriteScale;

	bool isActive() const;
	const string& tag() const;
	const size_t& id() const;
	void active(const bool&);
	void destroy();

	sf::Vector2f GetPosition();
	sf::Texture GetTexture();
	sf::FloatRect GetRect();
	float GetRadius();
	
	void MotionProcess(Entity&, sf::Vector2f);
	bool ReadyShoot();
};

