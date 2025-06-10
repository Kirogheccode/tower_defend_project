#include "Game.h"

Game::Game(const string& config)
{
	init(config);
}

void Game::init(const string& path)
{
	ifstream readconfig(path);

	//Reading window info
	string window_name;
	unsigned int width = 0;
	unsigned int height = 0;
	int frame_limits = 0;
	bool fullscreen_mode = 0;

	readconfig >> window_name >> width >> height >> frame_limits >> fullscreen_mode;

	Uint32 style = fullscreen_mode ? Style::Fullscreen : Style::Default;

	m_window.create(VideoMode(width, height), window_name, style);
	m_window.setFramerateLimit(frame_limits);

	//Reading bullet info
	readconfig >> m_bulletConfig.filepath >> m_bulletConfig.damage >> m_bulletConfig.speed;

	//Reading Enemy type 1
	readconfig >> m_enemyType1Config.filepath >> m_enemyType1Config.hp >> m_enemyType1Config.speed;

	//Reading Enemy type 2
	readconfig >> m_enemyType2Config.filepath >> m_enemyType2Config.hp >> m_enemyType2Config.speed;

	//Reading Enemy type 2
	readconfig >> m_enemyType3Config.filepath >> m_enemyType3Config.hp >> m_enemyType3Config.speed;

	auto entity = m_entities.addEntity("MainMenu");
	entity->cSet = make_shared<CSet>("main_menu.png");
}

void Game::run()
{
	while (m_running)
	{
		sRenderMenu();

		m_currentFrame++;
	}
}

void Game::setPause(bool paused)
{
	//
}

//void Game::spawnEnemy();

//void Game::sAnimation(shared_ptr<Entity>& entity, float& deltaTime)
//{
//	auto entities = m_entities.getEntites("Enemy");
//
//	entity->cSet->CurrImg.y = entity->cSet->row;
//	entity->cSet->totalTime += deltaTime;
//
//	if (entity->cSet->totalTime >= entity->cSet->switchTime)
//	{
//		entity->cSet->totalTime -= entity->cSet->switchTime;
//		entity->cSet->CurrImg.x++;
//
//		if (entity->cSet->CurrImg.x >= entity->cSet->ImgCount.x)
//			entity->cSet->CurrImg.x = 0;
//	}
//
//	entity->cSet->uvRect.top = entity->cSet->CurrImg.y * entity->cSet->uvRect.height;
//	entity->cSet->uvRect.left = entity->cSet->CurrImg.x * entity->cSet->uvRect.width;
//}
//
//void Game::sMovement(int mapIndex, float& deltaTime)
//{
//auto entities = m_entities.getEntites("Enemy");
//
//	for (auto& entity : entities)
//	{
//		if (entity->cMovement->currentPathindex >= entity->cMovement->paths[mapIndex].size())
//			return;
//
//		Vector2f target = entity->cMovement->paths[mapIndex][entity->cMovement->currentPathindex];
//		Vector2f direction = target - entity->cMovement->position;
//
//		float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
//
//		if (distance < 1.f) {
//			entity->cMovement->currentPathindex++;
//			if (entity->cMovement->currentPathindex >= entity->cMovement->paths[mapIndex].size()) {
//				// At the finish (minusHealth())
//			}
//
//			target = entity->cMovement->paths[mapIndex][entity->cMovement->currentPathindex];
//			direction = target - entity->cMovement->position;
//			distance = sqrt(direction.x * direction.x + direction.y * direction.y);
//		}
//
//		Vector2f movement(0.f, 0.f);
//
//		if (distance > 0) {
//			movement = direction / distance;
//		}
//
//		entity->cMovement->position += movement * entity->cMovement->speed * deltaTime;
//
//		sAnimation(entity, deltaTime);
//
//		entity->cSet->sprite.setTextureRect(entity->cSet->uvRect);
//
//		entity->cSet->sprite.setPosition(entity->cMovement->position);
//	}
//}

void Game::sRenderMenu()
{
	auto entities = m_entities.getEntites("MainMenu");

	for (auto& entity : entities) 
	{
		m_window.draw(entity->cSet->sprite);
	}
}

void Game::sRenderEnemy()
{
	//
}

void Game::sEnemyType1Spawner()
{
	auto entity = m_entities.addEntity("EnemyType1");
	entity->cHealth = make_shared<CHealth>(m_enemyType1Config.hp);
	entity->cMovement = make_shared<CMovement>(m_enemyType1Config.speed);
	entity->cSet = make_shared<CSet>("Skeleton_01_White_Walk.png", Vector2u(10, 1), 0.3f, 0);

	m_lastEnemySpawnTime = m_currentFrame;
}

void Game::sEnemyType2Spawner()
{
	auto entity = m_entities.addEntity("EnemyType3");
	entity->cHealth = make_shared<CHealth>(m_enemyType2Config.hp);
	entity->cMovement = make_shared<CMovement>(m_enemyType2Config.speed);
	entity->cSet = make_shared<CSet>("Skeleton_01_White_Walk.png", Vector2u(10, 1), 0.3f, 0);

	m_lastEnemySpawnTime = m_currentFrame;
}

void Game::sEnemyType3Spawner()
{
	auto entity = m_entities.addEntity("EnemyType3");
	entity->cHealth = make_shared<CHealth>(m_enemyType3Config.hp);
	entity->cMovement = make_shared<CMovement>(m_enemyType3Config.speed);
	entity->cSet = make_shared<CSet>("Skeleton_01_White_Walk.png", Vector2u(10, 1), 0.3f, 0);

	m_lastEnemySpawnTime = m_currentFrame;
}

void Game::sUserInput()
{
	//
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