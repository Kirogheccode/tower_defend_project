#include "Game.h"

Game::Game(const string& config)
{
	init(config);
}

void Game::init(const string& path)
{
	ifstream readconfig(path);
	string line;

	// Reading window config
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

	// Reading bullet config
	while (getline(readconfig, line)) {
		if (line.empty() || line[0] == '#') continue;
		istringstream iss(line);
		iss >>m_bulletConfig.tag >> m_bulletConfig.filepath >> m_bulletConfig.damage >> m_bulletConfig.speed;

		for (int i = 0; i < 50; i++)
		{
			auto entity = m_entities.addEntity(m_bulletConfig.tag);
			entity->cMovement = make_shared<CMovement>(m_bulletConfig.speed);
			entity->cSet = make_shared<CSet>(m_bulletConfig.filepath, Vector2u(1, 1), 0.3f, 0);
			entity->cSet->isDynamic = true;
			entity->cDamage = make_shared<CDamage>(m_bulletConfig.damage);
		}
		break;
	}

	// Rading enemy config && Pre-loaded enemies
	while (getline(readconfig, line)) {
		if (line.empty() || line[0] == '#') continue;
		istringstream iss(line);
		iss >> m_enemyType1Config.tag >> m_enemyType1Config.filepath >> m_enemyType1Config.hp >> m_enemyType1Config.speed >> m_enemyType1Config.money;

		int amount;
		iss >> amount;

		for (int i = 0; i < amount; i++)
		{
			auto entity = m_entities.addEntity(m_enemyType1Config.tag);
			entity->cSet = make_shared<CSet>(m_enemyType1Config.filepath, Vector2u(10, 1), 0.3f, 0);
			entity->cHealth = make_shared<CHealth>(m_enemyType1Config.hp);
			entity->cMovement = make_shared<CMovement>(m_enemyType1Config.speed);
			entity->cMoney = make_shared<CMoney>(m_enemyType1Config.hp);
		}

		break;
	}

	while (getline(readconfig, line)) {
		if (line.empty() || line[0] == '#') continue;
		istringstream iss(line);
		iss >> m_enemyType2Config.tag >> m_enemyType2Config.filepath >> m_enemyType2Config.hp >> m_enemyType2Config.speed >> m_enemyType2Config.money;

		int amount;
		iss >> amount;

		for (int i = 0; i < amount; i++)
		{
			auto entity = m_entities.addEntity(m_enemyType2Config.tag);
			entity->cSet = make_shared<CSet>(m_enemyType2Config.filepath, Vector2u(8, 1), 0.3f, 0);
			entity->cHealth = make_shared<CHealth>(m_enemyType2Config.hp);
			entity->cMovement = make_shared<CMovement>(m_enemyType2Config.speed);
			entity->cMoney = make_shared<CMoney>(m_enemyType2Config.hp);
		}

		break;
	}

	while (getline(readconfig, line)) {
		if (line.empty() || line[0] == '#') continue;
		istringstream iss(line);
		iss >> m_enemyType3Config.tag >> m_enemyType3Config.filepath >> m_enemyType3Config.hp >> m_enemyType3Config.speed >> m_enemyType3Config.money;

		int amount;
		iss >> amount;

		for (int i = 0; i < amount; i++)
		{
			auto entity = m_entities.addEntity(m_enemyType3Config.tag);
			entity->cSet = make_shared<CSet>(m_enemyType3Config.filepath, Vector2u(9, 1), 0.3f, 0);
			entity->cHealth = make_shared<CHealth>(m_enemyType3Config.hp);
			entity->cMovement = make_shared<CMovement>(m_enemyType3Config.speed);
			entity->cMoney = make_shared<CMoney>(m_enemyType3Config.hp);
		}

		break;
	}

	while (getline(readconfig, line)) {
		if (line.empty() || line[0] == '#') continue;
		istringstream iss(line);
		string skip;
		int wave, mapIndex, type1, type2, type3;

		iss >> skip >> wave >> mapIndex >> type1 >> type2 >> type3;

		m_waveConfigs[mapIndex][wave - 1] = { type1 , type2 , type3 };
	}

	readconfig.close();
	vector<Vector2f> towerPlace{
		Vector2f(420,185),
		Vector2f(120,538),
		Vector2f(662,384),
		Vector2f(963,420),
		Vector2f(603,589),
		Vector2f(1020,594),
		Vector2f(1561,178),
		Vector2f(1679,415),
		Vector2f(385,508),
		Vector2f(253,800),
		Vector2f(177,181),
		Vector2f(719,181),
		Vector2f(1322,181),
		Vector2f(479,809),
		Vector2f(1261,924)
	};

	// Pre-loaded backgrounds and buttons
	auto entity = m_scenes[AppState::MainMenu].addEntity("MainMenu");
	entity->cSet = make_shared<CSet>("IMGS/mainMenu.png");

	entity = m_scenes[AppState::Map1].addEntity("Map1");
	entity->cSet = make_shared<CSet>("IMGS/map2.png");
	for (int i = 0; i < 15; i++)
	{
		entity = m_scenes[AppState::Map1].addEntity("Base");
		entity->cSet = make_shared<CSet>("IMGS/Base.png");
		entity->cPosition = make_shared<CPosition>(towerPlace[i]);
		entity->active(true);
	}


	entity = m_scenes[AppState::Map1].addEntity("SelectButton");
	entity->cSet = make_shared<CSet>("IMGS/TowerSelectButton.png");
	entity->cPosition = make_shared<CPosition>(Vector2f(1820, 980));
	entity->cInput = make_shared<CInput>([this]()
		{

			m_state1 = AppState::TowerSelect;
		},
		[entity]()
		{

			entity->cSet->sprite.setColor(Color(200, 200, 200));
		},
		[entity]()
		{
			entity->cSet->sprite.setColor(Color(255, 255, 255));
		}
	);
	entity = m_scenes[AppState::TowerSelect].addEntity("SelectingBar");
	entity->cSet = make_shared<CSet>("IMGS/SelectingBar1.png");
	entity->cPosition = make_shared<CPosition>(Vector2f(1720, 0));

	entity = m_scenes[AppState::TowerSelect].addEntity("Tower1Button");
	entity->cSet = make_shared<CSet>("IMGS/Tower1Button.png");
	entity->cPosition = make_shared<CPosition>(Vector2f(1735, 30));
	entity->cInput = make_shared<CInput>([this]()
		{
			m_selected = "Tower1";
			m_state2 = AppState::TowerPlace;
		},
		[entity]()
		{
			entity->cSet->sprite.setColor(Color(200, 200, 200));
		},
		[entity]()
		{
			entity->cSet->sprite.setColor(Color(255, 255, 255));
		}
	);

	entity = m_scenes[AppState::TowerSelect].addEntity("Tower2Button");
	entity->cSet = make_shared<CSet>("IMGS/Tower2Button.png");
	entity->cPosition = make_shared<CPosition>(Vector2f(1825, 30));
	entity->cInput = make_shared<CInput>([this]()
		{
			m_selected = "Tower2";
			m_state2 = AppState::TowerPlace;
		},
		[entity]()
		{

			entity->cSet->sprite.setColor(Color(200, 200, 200));
		},
		[entity]()
		{
			entity->cSet->sprite.setColor(Color(255, 255, 255));
		}
	);

	entity = m_scenes[AppState::MainMenu].addEntity("PlayButton");
	entity->cSet = make_shared<CSet>("IMGS/play.png");
	entity->cPosition = make_shared<CPosition>(Vector2f(1100, 500));
	entity->cInput = make_shared<CInput>([this]()
		{
			m_mapindex = 0;
			m_state = AppState::Map1;
		},
		[entity]()
		{
			entity->cSet->sprite.setColor(Color(200, 200, 200));
		},
		[entity]()
		{
			entity->cSet->sprite.setColor(Color(255, 255, 255));
		}
	);

	entity = m_scenes[AppState::MainMenu].addEntity("SettingButton");
	entity->cSet = make_shared<CSet>("IMGS/exit.png");
	entity->cPosition = make_shared<CPosition>(Vector2f(1100, 700));
	entity->cInput = make_shared<CInput>([this]()
		{
			m_mapindex = 1;
			m_state = AppState::Map2;
		},
		[entity]()
		{
			entity->cSet->sprite.setColor(Color(200, 200, 200));
		},
		[entity]()
		{
			entity->cSet->sprite.setColor(Color(255, 255, 255));
		}
	);
}

void Game::run()
{
	Clock clock;

	while (m_running)
	{
		float dt = clock.restart().asSeconds();

		sMovement(dt);
		sRender(dt);
		sUserInput();
		TowerAttack();
		sCollision();

		if (m_state == AppState::Map1 || m_state == AppState::Map2 || m_state == AppState::Map3)
		{
			sCheckWaveFinished();
			sSpawnWave(dt);
		}

		m_currentFrame++;
	}
}

void Game::sRender(float& deltaTime)
{
	m_window.clear();

	for (auto& e : m_scenes[m_state].getEntites())
	{
		if (e->cSet && e->cPosition)
			e->cSet->sprite.setPosition(e->cPosition->position);

		if (e->cSet->isDynamic)
		{
			sAnimation(e, deltaTime);
		}
		if (e->tag() == "Base")
		{
			if (e->isActive())
				m_window.draw(e->cSet->sprite);
		}
		else
			m_window.draw(e->cSet->sprite);
	}

	if (m_state1 == AppState::TowerSelect)
	{
		for (auto& e : m_scenes[m_state1].getEntites())
		{
			if (e->cSet && e->cPosition)
				e->cSet->sprite.setPosition(e->cPosition->position);

			m_window.draw(e->cSet->sprite);
		}
	}

	for (auto& e : m_entities.getEntites())
	{
		if (e->isActive())
		{
			if (e->cSet->isDynamic)
			{
				sAnimation(e, deltaTime);
			}

			m_window.draw(e->cSet->sprite);
		} 
	}

	m_window.display();
}

void Game::sUserInput()
{
	Event event;

	Vector2f mousePos = m_window.mapPixelToCoords(Mouse::getPosition(m_window));
	while (m_window.pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			m_running = false;
		}
		// Check if left mouse is pressed
		if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
		{
			if (m_state1 == AppState::Dummy)
			{
				for (auto& e : m_scenes[m_state].getEntites())
				{
					if (e->cSet && e->cInput)
					{
						FloatRect bounds = e->cSet->sprite.getGlobalBounds();

						if (bounds.contains(mousePos))
						{
							e->cInput->onClick();
						}
					}
				}
			}
			else
			{
				if (m_state2 == AppState::TowerPlace)
				{
					bool isValid = false;
					for (auto& e : m_scenes[m_state].getEntites())
					{
						if (e->tag() == "Base" && e->isActive())
						{
							FloatRect bounds = e->cSet->sprite.getGlobalBounds();
							if (bounds.contains(mousePos))
							{
								e->active(false);
								isValid = true;
								break;
							}
						}
					}
					if (isValid)
					{
						if (m_selected == "Tower1")
						{
							auto entity = m_scenes[m_state].addEntity(m_selected);
							entity->cSet = make_shared<CSet>("IMGS/BloodMoonTower/Tower1.png", Vector2u(11, 1), 0.3f, 0);
							entity->cCooldown = make_shared<CCooldown>(1.0f);
							entity->cBound = make_shared<CBound>(1000.0f);
							entity->cPosition = make_shared<CPosition>(mousePos);
							entity->active(true);
						}
						else if (m_selected == "Tower2")
						{
							auto entity = m_scenes[m_state].addEntity(m_selected);
							entity->cSet = make_shared<CSet>("IMGS/BloodMoonTower/Tower2.png", Vector2u(8, 1), 0.3f, 0);
							entity->cCooldown = make_shared<CCooldown>(1.0f);
							entity->cBound = make_shared<CBound>(1000.0f);
							entity->cPosition = make_shared<CPosition>(mousePos);
							entity->active(true);
						}
					}
					m_state2 = AppState::Dummy;
				}
				else
				{
					bool isOutSide = true;
					for (auto& e : m_scenes[m_state1].getEntites())
					{
						if (e->cSet)
						{
							FloatRect bounds = e->cSet->sprite.getGlobalBounds();

							if (bounds.contains(mousePos))
							{
								if (e->cInput)
								{
									e->cInput->onClick();
								}
								isOutSide = false;
							}
						}
					}
					if (isOutSide)
						m_state1 = AppState::Dummy;
				}
			}
		}
	}

	// Hover detection
	if (m_state1 == AppState::Dummy)
	{
		for (auto& e : m_scenes[m_state].getEntites())
		{
			if (e->cSet && e->cInput)
			{
				FloatRect bounds = e->cSet->sprite.getGlobalBounds();
				bool Hovering = bounds.contains(mousePos);

				if (Hovering && !e->cInput->isHovered && e->cInput->onHover)
				{
					e->cInput->onHover();
				}
				else if (!Hovering && e->cInput->isHovered && e->cInput->offHover)
				{
					e->cInput->offHover();
				}

				e->cInput->isHovered = Hovering;
			}
		}
	}
	else
	{
		if (m_state2 == AppState::Dummy)
		{
			for (auto& e : m_scenes[m_state1].getEntites())
			{
				if (e->cSet && e->cInput)
				{
					FloatRect bounds = e->cSet->sprite.getGlobalBounds();
					bool Hovering = bounds.contains(mousePos);

					if (Hovering && !e->cInput->isHovered && e->cInput->onHover)
					{
						e->cInput->onHover();
					}
					else if (!Hovering && e->cInput->isHovered && e->cInput->offHover)
					{
						e->cInput->offHover();
					}

					e->cInput->isHovered = Hovering;
				}
			}
		}
	}
}

void Game::sAnimation(shared_ptr<Entity>& entity, float& deltaTime)
{
	entity->cSet->CurrImg.y = entity->cSet->row;
	entity->cSet->totalTime += deltaTime;

	if (entity->cSet->totalTime >= entity->cSet->switchTime)
	{
		entity->cSet->totalTime -= entity->cSet->switchTime;
		entity->cSet->CurrImg.x++;

		if (entity->cSet->CurrImg.x >= entity->cSet->ImgCount.x)
			entity->cSet->CurrImg.x = 0;
	}

	entity->cSet->uvRect.top = entity->cSet->CurrImg.y * entity->cSet->uvRect.height;
	entity->cSet->uvRect.left = entity->cSet->CurrImg.x * entity->cSet->uvRect.width;
	entity->cSet->sprite.setTextureRect(entity->cSet->uvRect);
}

void Game::sMovement(float& deltaTime)
{
	for (auto& entity : m_entities.getEntites())
	{
		if (!entity->isActive() || !entity->cMovement || !entity->cPosition) continue;

		//Bullet Movement 
		if (entity->tag() == "Bullet")
		{
			entity->cPosition->position += entity->cMovement->velocity * deltaTime;
			entity->cSet->sprite.setPosition(entity->cPosition->position);

			Vector2f pos = entity->cPosition->position;
			Vector2u winSize = m_window.getSize();

			if (pos.x < 0 || pos.y < 0 || pos.x > winSize.x || pos.y > winSize.y)
			{
				DeactivateBullet(*entity);
			}
		}
		//Enemy Movement 
		else if (entity->tag().find("Enemy") != std::string::npos)
		{
			// Check if the enemy has reached the end of the path.
			if (entity->cMovement->currentPathindex >= entity->cMovement->paths[m_mapindex].size())
			{
				m_health -= entity->cHealth->hp;
				DeactivateEnemy(*entity);
				continue; 
			}

			// Get the next waypoint and calculate the direction towards it.
			Vector2f target = entity->cMovement->paths[m_mapindex][entity->cMovement->currentPathindex];
			Vector2f direction = target - entity->cPosition->position;
			float distance = MathSupport::Length(direction);

			// If the enemy is very close to the waypoint, move to the next one.
			if (distance < 5.f) // Use a small threshold to prevent jittering.
			{
				entity->cMovement->currentPathindex++;
			}
			else
			{
				// Move the enemy towards the target.
				Vector2f movement = MathSupport::Normalize(direction);
				entity->cPosition->position += movement * entity->cMovement->speed * deltaTime;
			}

			// Update the enemy's sprite position to match its new logical position.
			entity->cSet->sprite.setPosition(entity->cPosition->position);
		}
	}
}

void Game::sCheckWaveFinished()
{
	if (m_finishWave) return;

	bool allInactive = true;

	for (auto& e : m_entities.getEntites(m_enemyType1Config.tag))
	{
		if (e->isActive())
		{
			allInactive = false;
			break;
		}
	}

	for (auto& e : m_entities.getEntites(m_enemyType2Config.tag))
	{
		if (e->isActive())
		{
			allInactive = false;
			break;
		}
	}

	for (auto& e : m_entities.getEntites(m_enemyType3Config.tag))
	{
		if (e->isActive())
		{
			allInactive = false;
			break;
		}
	}

	if (allInactive)
	{
		m_currentWave++;
		cout << "Spawning wave right now" << endl;
		m_finishWave = true;
	}
}

void Game::sSpawnWave(float& deltaTime)
{
	bool Type1Finish = false;
	bool Type2Finish = false;
	bool Type3Finish = false;

	if (m_spawnStage == SpawnStage::None && m_finishWave)
	{
		m_spawnStage = SpawnStage::Type1;
		m_spawnTimer = 0.f;

		m_spawnedType1 = 0;
		m_spawnedType2 = 0;
		m_spawnedType3 = 0;
	}

	if (m_spawnStage == SpawnStage::Done)
	{
		m_spawnStage = SpawnStage::None;
		m_finishWave = false;
		return;
	}

	m_spawnTimer += deltaTime;

	if (m_spawnTimer < m_spawnDelay) return;

	if (m_spawnStage == SpawnStage::Type1)
	{
		if (spawnEnemyType(1, deltaTime))
		{
			m_spawnStage = SpawnStage::Type2;
			m_spawnTimer = 0;
		}
	}
	else if (m_spawnStage == SpawnStage::Type2)
	{
		if (spawnEnemyType(2, deltaTime))
		{
			m_spawnStage = SpawnStage::Type3;
			m_spawnTimer = 0;
		}
	}
	else if (m_spawnStage == SpawnStage::Type3)
	{
		if (spawnEnemyType(3, deltaTime))
		{
			m_spawnStage = SpawnStage::Done;
			m_spawnTimer = 0;
		}
	}
}

bool Game::spawnEnemyType(int type, float& deltaTime)
{
	WaveConfig& wave = m_waveConfigs[m_mapindex][m_currentWave];

	m_spawningTimer += deltaTime;

	if (type == 1)
	{
		if (m_spawnedType1 >= wave.enemyType1Count) return true;

		for (auto& e : m_entities.getEntites(m_enemyType1Config.tag))
		{
			if (m_spawningTimer < m_spawningDelay) return false;

			if (!e->isActive())
			{
				m_spawningTimer = 0;

				e->cPosition = make_shared<CPosition>(e->cMovement->starting_pos[m_mapindex]);
				e->active(true);
				m_spawnedType1++;
				break;
			}
		}

		return m_spawnedType1 >= wave.enemyType1Count;
	}

	else if (type == 2)
	{
		if (m_spawnedType2 >= wave.enemyType2Count) return true;

		for (auto& e : m_entities.getEntites(m_enemyType2Config.tag))
		{
			if (m_spawningTimer < m_spawningDelay) return false;

			if (!e->isActive())
			{
				m_spawningTimer = 0;

				e->cPosition = make_shared<CPosition>(e->cMovement->starting_pos[m_mapindex]);
				e->active(true);
				m_spawnedType2++;
				break;
			}
		}

		return m_spawnedType2 >= wave.enemyType2Count;
	}

	else if (type == 3)
	{
		if (m_spawnedType3 >= wave.enemyType3Count) return true;

		for (auto& e : m_entities.getEntites(m_enemyType3Config.tag))
		{
			if (m_spawningTimer < m_spawningDelay) return false;

			if (!e->isActive())
			{
				m_spawningTimer = 0;

				e->cPosition = make_shared<CPosition>(e->cMovement->starting_pos[m_mapindex]);
				e->active(true);
				m_spawnedType3++;
				break;
			}
		}

		return m_spawnedType3 >= wave.enemyType3Count;
	}

	return true;
}

void Game::Shoot(Entity& tower)
{
	if (!tower.cTarget) { return; }

	for (auto& bullet : m_entities.getEntites("Bullet"))
	{
		if (!bullet->isActive())
		{
			bullet->cPosition = make_shared<CPosition>(tower.cPosition->position);

			bullet->cSet->sprite.setPosition(tower.cPosition->position);

			bullet->active(true);

			sf::Vector2f direction = tower.cTarget->cPosition->position - tower.cPosition->position;
			sf::Vector2f normalized_direction = MathSupport::Normalize(direction);
			bullet->cMovement->velocity = normalized_direction * m_bulletConfig.speed;

			break;
		}
	}
}

void Game::TowerAttack()
{
	for (auto& curTower : m_scenes[m_state].getEntites("Tower"))
	{

		if (curTower->isActive() && curTower->cCooldown->shootClock.getElapsedTime().asSeconds() >= curTower->cCooldown->cooldownDuration.asSeconds())
		{
			std::shared_ptr<Entity> closestEnemy = nullptr;
			float minDistance = curTower->cBound->radius;

			for (auto& enemy : m_entities.getEntites("Enemy"))
			{
				if (enemy->isActive())
				{
					float distance = MathSupport::Length(enemy->cPosition->position - curTower->cPosition->position);
					if (distance < minDistance)
					{
						minDistance = distance;
						closestEnemy = enemy;
					}
				}
			}

			if (closestEnemy)
			{
				// Fire and reset cooldown
				curTower->cTarget = closestEnemy;
				Shoot(*curTower);
				curTower->cCooldown->shootClock.restart();
			}
		}
	}
}

void Game::DeactivateEnemy(Entity& enemy)
{
	if (!enemy.isActive())
	{
		return;
	}

	enemy.active(false);

	if (enemy.cHealth)
	{
		if (enemy.tag() == "EnemyType1")
		{
			enemy.cHealth->hp = 100;// to be config
		}
		else if (enemy.tag() == "EnemyType2")
		{
			enemy.cHealth->hp = 100; // to be config 
		}
		else if (enemy.tag() == "EnemyType3")
		{
			enemy.cHealth->hp = 110; // to be config
		}
	}

	if (enemy.cMovement)
	{
		enemy.cMovement->currentPathindex = 0;
	}

	//optional
	if (enemy.cPosition)
	{
		enemy.cPosition->position = sf::Vector2f(-100, -100);
	}
}

void Game::DeactivateTower(Entity& tower)
{
	if (!tower.isActive())
		return;

	// Deactivate the tower
	tower.active(false);

	// Reset position if needed (optional)
	if (tower.cPosition)
		tower.cPosition->position = sf::Vector2f(-100.f, -100.f); // Off-screen or default position

	// Reset target
	if (tower.cTarget)
		tower.cTarget = nullptr;

	// Reset cooldown timer
	if (tower.cCooldown)
		tower.cCooldown->shootClock.restart(); // Or set to zero elapsed time

}

void Game::DeactivateBullet(Entity& bullet)
{
	if (!bullet.isActive())
		return;

	// Deactivate the bullet
	bullet.active(false);

	// Reset position off-screen or to a default location
	if (bullet.cPosition)
		bullet.cPosition->position = sf::Vector2f(-100.f, -100.f);
}

bool collisionDetection(const Entity& entity1, const Entity& entity2)
{
	if (!entity1.cSet || !entity2.cSet) return false;
	FloatRect bounds1 = entity1.cSet->sprite.getGlobalBounds();
	FloatRect bounds2 = entity2.cSet->sprite.getGlobalBounds();
	return bounds1.intersects(bounds2);
}

void Game::sCollision()
{
	for (auto& cur : m_entities.getEntites("Enemy"))
	{
		if (!cur->isActive()) continue;
		
		for (auto& bullet : m_entities.getEntites("Bullet"))
		{
			if (!bullet->isActive()) continue;
			if(collisionDetection(*cur, *bullet))
			{
				if (cur->cHealth)
				{
					cur->cHealth->hp -= bullet->cDamage->damage;
					if (cur->cHealth->hp <= 0)
					{
						m_money += cur->cMoney->money;
						DeactivateEnemy(*cur);
					}
				}
				DeactivateBullet(*bullet);
			}
		}
	}
}
