#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <functional>
#include <string>
#include <list>

#include "Entity.h"
#include "EntityManager.h"
#include "MathSupport.h"

using namespace std;
using namespace sf;

class EntityManager; // Forward declaration

enum class SpawnStage {
	None,
	Type1,
	Type2,
	Type3,
	Done
};

enum class AppState {
	Dummy,			// Dummy
	MainMenu,       // Menu chính
	PlayMenu,       // new game, load game
	NameInput,      // pop-up nhập tên
	SettingsMenu,   // Pop-up cài đặt
	OptionMenu,     // Pop-up lựa chọn
	AboutUs,
	Rules,
	LoadGame,
	MapSelect,      // Màn hình chọn map/độ khó
	Map1,
	Map2,
	Map3,
	Map4,
	GamePlay,       // Các chức năng trong game
	TowerSelect,	// Chọn tháp 
	TowerPlace,		// Đặt tháp
	PauseMenu       // Pop-up tạm dừng
};

struct WindowConfig { unsigned int width; unsigned int height; int fps; int fullscreen; };

struct BulletConfig { string tag; string filepath; int damage; float speed; float Bscale; float Sscale; };

struct EnemyType1Config { string tag; string filepath; int hp; float speed; int money; float Bscale; float Sscale; };
struct EnemyType2Config { string tag; string filepath; int hp; float speed; int money; float Bscale; float Sscale; };
struct EnemyType3Config { string tag; string filepath; int hp; float speed; int money; float Bscale; float Sscale; };

struct TowerType1Config { string tag; string filepath; };
struct TowerType2Config { string tag; string filepath; };
struct TowerType3Config { string tag; string filepath; };
struct TowerType4Config { string tag; string filepath; };
struct TowerType5Config { string tag; string filepath; };
struct TowerType6Config { string tag; string filepath; };

struct WaveConfig {
	int enemyType1Count = 0;
	int enemyType2Count = 0;
	int enemyType3Count = 0;
};

struct SaveGame
{
	string fileName;
	AppState m_save;
	int mapIndex;
};

class Game
{
	RenderWindow m_window;
	View m_view;

	Clock m_clock;
	Clock m_waveClock;

	WindowConfig m_windowConfig;
	BulletConfig m_bullet01Config;
	BulletConfig m_bullet02Config;

	EnemyType1Config m_enemyType1Config;
	EnemyType2Config m_enemyType2Config;
	EnemyType3Config m_enemyType3Config;

	TowerType1Config m_towerType1Config;
	TowerType2Config m_towerType2Config;
	TowerType3Config m_towerType3Config;
	TowerType4Config m_towerType4Config;
	TowerType5Config m_towerType5Config;
	TowerType6Config m_towerType6Config;

	map<int, map<int, WaveConfig>> m_waveConfigs;                                           // m_waveConfigs[map index][wave] = { type1, type2, type3 };

	SpawnStage m_spawnStage = SpawnStage::None;
	float m_spawnTimer = 5.f;

	float m_spawnDelay = 5.f; 
	float m_spawningTimer = 0.f;
	float m_spawningDelay = 0.8f;
	float m_waveDisplayDuration = 2.0f;

	int m_spawnedType1 = 0;
	int m_spawnedType2 = 0;
	int m_spawnedType3 = 0;

	map<AppState, EntityManager> m_scenes;

	AppState m_state = AppState::MainMenu;
	AppState m_state1 = AppState::Dummy;	 												// For tower selecting
	AppState m_state2 = AppState::Dummy;													// For tower placing
	AppState prev_state = AppState::Dummy;
	AppState game_state = AppState::Dummy;

	EntityManager m_entities;
	string m_selected = "";

	int m_currentWave = -1;                                                                 // Keep track of current wave
	int m_mapindex = 0;                                                                     // Default testing - Need to add option to choose map_index
	int m_coin = 1000;
	int m_currentFrame = 0;

	Font m_font;
	Text m_inputLabel;
	Text m_inputText;
	string m_playerName;
	bool m_typingName = false;

	Music m_backgroundMusic;
	float m_musicVolume = 50.0f;
	bool m_musicMuted = false;

	float m_sfxVolume = 80.0f;
	bool m_sfxMuted = false;

	SoundBuffer m_clickBuffer;
	SoundBuffer m_constructTower;

	list<Sound> m_activeSounds;

	bool m_showWaveText = false;
	bool m_setting = false;
	bool m_paused = false;
	bool m_running = true;
	bool m_finishWave = false;                                                              

	void init(const string& config);
	void loadHeartCoin();
	void loadFontText();
	void initUIFlow();

	void sMovement(float& deltaTime);										                // System: Movement update
	void sRender(float& deltaTime);															// System: Render / Drawing enemies and menus		
	void sAnimation(shared_ptr<Entity>& entity, float& deltaTime);						    // System: Animation													
	void sUserInput();																		// System: User input
	void sReset();

	void updateAudioSettings();

	void sSpawnWave(float& deltaTime);
	void sCheckWaveFinished();
	bool spawnEnemyType(int type, float& deltaTime);

	void DeactivateEnemy(Entity&);
	void DeactivateBullet(Entity&);
	void DeactivateTower(Entity&);

	void onResize(const sf::Event::SizeEvent& size);

	void sSaveGame();
	void sLoadGame();
	void sAddGameSave();
	vector<SaveGame> loadGames;
	int m_loadIndex = -1;

public:
	Game(const string& config);
	void run();

	void Shoot(Entity&);			// Check for collision
	void TowerAttack();				// Check for collision with enemy and attack
	void sCollision();				// Check for collision between two entities

	void playSfx(const sf::SoundBuffer& buffer, sf::Vector2f position = { -1, -1 });
};