#pragma once

// --- Thư viện chuẩn & SFML ---
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <list>
#include <thread>
#include <chrono>
#include <mutex>
#include <ctime>
#include <functional>

#include "Entity.h"
#include "EntityManager.h"
#include "MathSupport.h"

using namespace std;
using namespace sf;

// --- Forward declarations ---
class EntityManager;


// --- Enum định nghĩa các trạng thái ---
enum class SpawnStage { None, Type1, Type2, Type3, Done };


enum class AppState {
	Dummy,
	MainMenu,
	PlayMenu,
	NameInput,
	SettingsMenu,
	OptionMenu,
	AboutUs,
	Rules,
	LoadGame,
	MapSelect,
	Map1, Map2, Map3, Map4,
	GamePlay,
	TowerSelect,
	TowerPlace,
	PauseMenu,
	TowerInfo
};


// --- Cấu hình cơ bản ---
struct WindowConfig { unsigned int width; unsigned int height; int fps; int fullscreen; };
struct BulletConfig { string tag; string filepath; int damage; float speed; float Bscale; float Sscale; };
struct EnemyType1Config { string tag; string filepath; int hp; float speed; int money; float Bscale; float Sscale; };
struct EnemyType2Config { string tag; string filepath; int hp; float speed; int money; float Bscale; float Sscale; };
struct EnemyType3Config { string tag; string filepath; int hp; float speed; int money; float Bscale; float Sscale; };
struct TowerType1Config { string tag; string filepath; int cost; float cooldown; float range; };
struct TowerType2Config { string tag; string filepath; int cost; float cooldown; float range; };
struct TowerType3Config { string tag; string filepath; int cost; float cooldown; float range; };
struct TowerType4Config { string tag; string filepath; int cost; float cooldown; float range; };
struct TowerType5Config { string tag; string filepath; int cost; float cooldown; float range; };
struct TowerType6Config { string tag; string filepath; int cost; float cooldown; float range; };
struct WaveConfig { int enemyType1Count = 0, enemyType2Count = 0, enemyType3Count = 0; };


struct SaveGame {
	string fileName;
	AppState m_save;
	int mapIndex;
};


// --- Class Game chính ---
class Game {
	// --- Window & thời gian ---
	RenderWindow m_window;
	View m_view;
	Clock m_clock;
	Clock m_waveClock;


	// --- Cấu hình ---
	WindowConfig m_windowConfig;
	BulletConfig m_bullet01Config, m_bullet02Config;
	EnemyType1Config m_enemyType1Config;
	EnemyType2Config m_enemyType2Config;
	EnemyType3Config m_enemyType3Config;
	TowerType1Config m_towerType1Config;
	TowerType2Config m_towerType2Config;
	TowerType3Config m_towerType3Config;
	TowerType4Config m_towerType4Config;
	TowerType5Config m_towerType5Config;
	TowerType6Config m_towerType6Config;


	// --- Wave ---
	map<int, map<int, WaveConfig>> m_waveConfigs;
	SpawnStage m_spawnStage = SpawnStage::None;
	float m_spawnTimer = 3.f;
	float m_spawnDelay = 3.f;
	float m_spawningTimer = 0.f;
	float m_spawningDelay = 0.6f;
	float m_waveDisplayDuration = 2.0f;
	float dt = 0;
	int m_spawnedType1 = 0, m_spawnedType2 = 0, m_spawnedType3 = 0;
	int m_currentWave = -1;
	bool m_showWaveText = false, m_finishWave = false;


	// --- Game state ---
	map<AppState, EntityManager> m_scenes;
	AppState m_state = AppState::MainMenu;
	AppState m_state1 = AppState::Dummy; // chọn tháp
	AppState m_state2 = AppState::Dummy; // đặt tháp
	AppState prev_state = AppState::Dummy;
	AppState game_state = AppState::Dummy;


	// --- Entities ---
	EntityManager m_entities;
	string m_selected = "";
	float m_refund = 0.6f;
	int m_cost = 0;
	int m_mapindex = 0;
	int m_coin = 1000;
	int m_currentFrame = 0;
	vector<float> m_multiplies = { 1, 1.2, 1.4, 1.6 };


	// --- Âm thanh ---
	Music m_backgroundMusic;
	Music m_mapSelect;
	map<int, Music> m_mapMusic;
	float m_musicVolume = 50.f;
	bool m_musicMuted = false;
	float m_sfxVolume = 80.f;
	bool m_sfxMuted = false;
	SoundBuffer m_clickBuffer, m_constructTower, m_error, m_collide;
	list<Sound> m_activeSounds;


	// --- Font ---
	Font m_font;


	// --- Cờ trạng thái ---
	bool m_setting = false;
	bool m_paused = false;
	bool m_running = true;
	bool m_clickedTower = false;
	int m_speedup = 1;


	// --- Save game ---
	string fileForSave = "";
	mutex saveMutex;
	ofstream writePlayer;


	// --- Hàm khởi tạo ---
	void init(const string& config);
	void loadHeartCoinText();
	void loadTowerUpgradeInfo();
	void loadGuideText();
	void loadTowerPirce();
	void loadWaveText();
	void loadFontText();
	void initUIFlow();


	// --- Hệ thống ---
	void sRender(float& dt);
	void sMovement(float& dt);
	void sAnimation(shared_ptr<Entity>& entity, float& dt);
	void sUserInput();
	void sReset();
	void sSpawnWave(float& dt);
	void sCheckWaveFinished();
	bool spawnEnemyType(int type, float& dt);
	void sCollision();


	// --- Tháp (Tower) ---
	void RemoveTower(Entity& tower);
	void UpgradeTower(Entity& tower);
	void TowerAttack();
	void Shoot(Entity& tower);


	// --- Âm thanh ---
	void playSfx(const sf::SoundBuffer& buffer, sf::Vector2f pos = { -1, -1 });
	void updateAudioSettings();
	void playMapMusic(int mapIdx);
	void updateMusicState();


	// --- Save/load ---
	void sSaveGame();
	void sLoadGame();
	void queueSave();
	void startWriting(const string& filename);
	void stopWriting();


	// --- Tiện ích ---
	Vector2f getWindowSize() const;
	bool isOutOfBounds(const Entity& e, float margin = 50.0f);
	bool isFileEmpty(const string& filename);


	// --- Reset dữ liệu ---
	void DeactivateEnemy(Entity& enemy);
	void DeactivateTower(Entity& tower);
	void DeactivateBullet(Entity& bullet);

public:
	Game(const string& config);
	void run();
};
