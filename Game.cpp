#include "Game.h"

Game::Game(const string& config)
{
	init(config);
}

void Game::init(const string& path)
{
	ifstream readconfig(path);
	string line;

	while (getline(readconfig, line)) {
		if (line.empty() || line[0] == '#') continue;
		istringstream iss(line);
		string window_name;
		unsigned int width, height;
		int fps, fullscreen;
		iss >> window_name >> width >> height >> fps >> fullscreen;
		Uint32 style = fullscreen ? Style::Fullscreen : Style::Default;
		m_window.create(VideoMode(width, height), window_name, style);
		m_window.setFramerateLimit(fps);
		break;
	}

	while (getline(readconfig, line)) {
		if (line.empty() || line[0] == '#') continue;
		istringstream iss(line);
		iss >> m_bulletConfig.filepath >> m_bulletConfig.damage >> m_bulletConfig.speed;
		break;
	}

	while (getline(readconfig, line)) {
		if (line.empty() || line[0] == '#') continue;
		istringstream iss(line);
		iss >> m_enemyType1Config.filepath >> m_enemyType1Config.hp >> m_enemyType1Config.speed >> m_enemyType1Config.money;
		break;
	}

	while (getline(readconfig, line)) {
		if (line.empty() || line[0] == '#') continue;
		istringstream iss(line);
		iss >> m_enemyType2Config.filepath >> m_enemyType2Config.hp >> m_enemyType2Config.speed >> m_enemyType2Config.money;
		break;
	}

	while (getline(readconfig, line)) {
		if (line.empty() || line[0] == '#') continue;
		istringstream iss(line);
		iss >> m_enemyType3Config.filepath >> m_enemyType3Config.hp >> m_enemyType3Config.speed >> m_enemyType3Config.money;
		break;
	}

	auto entity = m_scenes[AppState::MainMenu].addEntity("MainMenu");
	entity->cSet = make_shared<CSet>("IMGS/mainMenu.png");

	entity = m_scenes[AppState::MainMenu].addEntity("PlayButton");
	entity->cSet = make_shared<CSet>("IMGS/play.png");
	entity->cPosition = make_shared<CPosition>(Vector2f(1100, 500));
}

void Game::run()
{
	Clock clock;

	while (m_running)
	{
		float dt = clock.restart().asSeconds();

		sRender();
		sUserInput();

		m_currentFrame++;
	}
}

void Game::setPause(bool paused)
{
	//
}

void Game::sRender()
{
	m_window.clear();

	for (auto& e : m_scenes[m_state].getEntites())
	{
		if (e->cSet && e->cPosition)
			e->cSet->sprite.setPosition(e->cPosition->postion);

		m_window.draw(e->cSet->sprite);
	}

	m_window.display();
}

void Game::sEnemyType1Spawner()
{
	auto entity = m_scenes[AppState::Game].addEntity("EnemyType1");
	entity->cHealth = make_shared<CHealth>(m_enemyType1Config.hp);
	entity->cMovement = make_shared<CMovement>(m_enemyType1Config.speed);
	entity->cSet = make_shared<CSet>("IMGS/Skeleton_01_White_Walk.png", Vector2u(10, 1), 0.3f, 0);

	m_lastEnemySpawnTime = m_currentFrame;
}

void Game::sEnemyType2Spawner()
{
	auto entity = m_scenes[AppState::Game].addEntity("EnemyType3");
	entity->cHealth = make_shared<CHealth>(m_enemyType2Config.hp);
	entity->cMovement = make_shared<CMovement>(m_enemyType2Config.speed);
	entity->cSet = make_shared<CSet>("IMGS/Skeleton_01_White_Walk.png", Vector2u(10, 1), 0.3f, 0);

	m_lastEnemySpawnTime = m_currentFrame;
}

void Game::sEnemyType3Spawner()
{
	auto entity = m_scenes[AppState::Game].addEntity("EnemyType3");
	entity->cHealth = make_shared<CHealth>(m_enemyType3Config.hp);
	entity->cMovement = make_shared<CMovement>(m_enemyType3Config.speed);
	entity->cSet = make_shared<CSet>("IMGS/Skeleton_01_White_Walk.png", Vector2u(10, 1), 0.3f, 0);

	m_lastEnemySpawnTime = m_currentFrame;
}

void Game::sUserInput()
{
	Event event;


	Vector2f mousePos = Vector2f(sf::Mouse::getPosition(m_window));

	if (event.type == Event::Closed)
	{
		m_running = false;
	}

	for (auto& state : m_scenes)
	{
		state.second.update();
	}
}

void Game::sCollision()
{
	//
}

void Game::spawnEnemy()
{
	//
}

void Game::spawnBullet(shared_ptr<Entity> entity, const Vector2f& enemy_pos)
{
	//
}