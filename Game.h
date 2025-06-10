#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Entity.h"
#include "EntityManager.h"

using namespace std;
using namespace sf;

struct BulletConfig { int damage; float speed; }; //Damage, 
struct EnemyType1Config { int HP; float speed; }; //Health, speed, 
struct EnemyType2Config { int HP; float speed; }; //Health, speed,
struct EnemyType3Config { int HP; float speed; }; //Health, speed,

class Game
{
	RenderWindow m_window;
	EntityManager m_entities;

	BulletConfig m_bulletConfig;
	EnemyType1Config m_enemyType1Config;
	EnemyType2Config m_enemyType2Config;
	EnemyType3Config m_enemyType3Config;

	int m_score = 0;
	int m_currentFrame = 0;
	int m_lastEnemySpawnTime = 0;

	bool m_paused = false;
	bool m_running = true;

	void init(const string& config);
	void setPause(bool paused);

	void sMovement(); //System: Movement update
	void sRender(); //System:: Render / Drawing
	void sEnemySpawner(); //System:: Spawns Enemies;
	void sCollision(); //System:: Collisions

	void run();
	void spawnEnemy();
	void spawnBullet(shared_ptr<Entity> entity, const Vector2f& enemy_pos);

public:
	Game(const string& config);
};