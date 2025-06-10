#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Entity.h"
#include "EntityManager.h"

using namespace std;
using namespace sf;

struct BulletConfig { string filepath; int damage; float speed; };			//Damage, 
struct EnemyType1Config { string filepath; int hp; float speed; };			//Health, speed, 
struct EnemyType2Config { string filepath; int hp; float speed; };			//Health, speed,
struct EnemyType3Config { string filepath;  int hp; float speed; };			//Health, speed,
struct TowerType1Config {};
struct TowerType3Config {};
struct TowerType2Config {};

class Game
{
	RenderWindow m_window;
	EntityManager m_entities;

	BulletConfig m_bulletConfig;
	EnemyType1Config m_enemyType1Config;
	EnemyType2Config m_enemyType2Config;
	EnemyType3Config m_enemyType3Config;
	TowerType1Config m_towerType1Config;
	TowerType2Config m_towerType2Config;
	TowerType3Config m_towerType3Config;

	int m_score = 0;
	int m_currentFrame = 0;
	int m_lastEnemySpawnTime = 0;

	bool m_paused = false;
	bool m_running = true;

	void init(const string& config);
	void setPause(bool paused);

	//void sMovement(int mapIndex, float& deltaTime);										//System: Movement update
	void sRenderMenu();																		//System: Render / Drawing menus
	void sRenderEnemy();																	//System: Render / Drawing enemies
	//void sAnimation(shared_ptr<Entity>& entity, float& deltaTime);						//System: Animation
	void sEnemyType1Spawner();																//System: Spawn Enemey Type 1
	void sEnemyType2Spawner();																//System: Spawn Enemey Type 2
	void sEnemyType3Spawner();																//System: Spawn Enemey Type 3																
	void sUserInput();																		//System: User input
	void sCollision();																		//System: Collisions

	void spawnEnemy();															
	void spawnBullet(shared_ptr<Entity> entity, const Vector2f& enemy_pos);

public:
	Game(const string& config);
	void run();
};