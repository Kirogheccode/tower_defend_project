#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Entity.h"
#include "EntityManager.h"

using namespace std;
using namespace sf;

enum class AppState { Dummy, MainMenu, SettingsMenu, Map1, Map2, Map3, TowerSelect, TowerPlace};

enum class SpawnStage {
	None,
	Type1,
	Type2,
	Type3,
	Done
};

struct BulletConfig { string filepath; int damage; float speed; };				

struct EnemyType1Config { string tag; string filepath; int hp; float speed; int money; };			
struct EnemyType2Config { string tag; string filepath; int hp; float speed; int money; };			
struct EnemyType3Config { string tag; string filepath; int hp; float speed; int money; };

struct TowerType1Config {};
struct TowerType3Config {};
struct TowerType2Config {};

struct WaveConfig {
	int enemyType1Count = 0;
	int enemyType2Count = 0;
	int enemyType3Count = 0;
};

class Game
{
	RenderWindow m_window;

	BulletConfig m_bulletConfig;
	EnemyType1Config m_enemyType1Config;
	EnemyType2Config m_enemyType2Config;
	EnemyType3Config m_enemyType3Config;
	TowerType1Config m_towerType1Config;
	TowerType2Config m_towerType2Config;
	TowerType3Config m_towerType3Config;

	map<int, map<int, WaveConfig>> m_waveConfigs;                                           //m_waveConfigs[map index][wave] = { type1, type2, type3 };

	SpawnStage m_spawnStage = SpawnStage::None;
	float m_spawnTimer = 0.f;
	float m_spawnDelay = 5.f; // Delay gi?a các ??t spawn

	map<AppState, EntityManager> m_scenes;
	AppState m_state = AppState::MainMenu;
	AppState m_state1 = AppState::Dummy; // For tower selecting
	AppState m_state2 = AppState::Dummy; // For tower placing

	EntityManager m_entities;
	string m_selected = "";
	int m_currentWave = 0;                                                                  // Keep track of current wave
	int m_mapindex = 0;                                                                     // Default testing - Need to add option to choose map_index
	int m_score = 0;
	int m_health = 1000;
	int m_currentFrame = 0;

	bool m_paused = false;
	bool m_running = true;
	bool m_finishWave = true;                                                               // m_finishWave = true -> spawnWave() -> m_fnishWave = false -> If all enemies die -> finishWave = true -> spawnWave() -> finishWave = false -> if all enemies die -> ... 

	void init(const string& config);
	void setPause(bool paused); 

	void sMovement(float& deltaTime);										                //System: Movement update
	void sRender(float& deltaTime);																			//System: Render / Drawing enemies and menus		
	void sAnimation(shared_ptr<Entity>& entity, float& deltaTime);						    //System: Animation													
	void sUserInput();																		//System: User input
	void sCollision();																		//System: Collision

	void sSpawnWave(float& deltaTime);
	void sCheckWaveFinished();
	void spawnEnemyType(int type);

public:
	Game(const string& config);
	void run();
};