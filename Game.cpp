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
	while (getline(readconfig, line)) 
	{
		if (line.empty() || line[0] == '#') continue;
		istringstream iss(line);
		iss >> m_bulletConfig.filepath >> m_bulletConfig.damage >> m_bulletConfig.speed;
		int amount;
		iss >> amount;
		for (int i = 0; i < amount; i++)
		{
			auto entity = m_entities.addEntity(m_bulletConfig.tag);
			entity->cSet = make_shared<CSet>(m_bulletConfig.filepath, Vector2u(10, 1), 0.3f, 0);
			entity->cMovement = make_shared<CMovement>(m_bulletConfig.speed);
		}
		
		break;
	}

	// Rading enemy config && Pre-loaded enemies
	while (getline(readconfig, line)) 
	{
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

	while (getline(readconfig, line)) 
	{
		if (line.empty() || line[0] == '#') continue;
		istringstream iss(line);
		iss >> m_enemyType2Config.tag >> m_enemyType2Config.filepath >> m_enemyType2Config.hp >> m_enemyType2Config.speed >> m_enemyType2Config.money;
		

		int amount;
		iss >> amount;

		for (int i = 0; i < amount; i++)
		{
			auto entity = m_entities.addEntity(m_enemyType2Config.tag);
			entity->cSet = make_shared<CSet>(m_enemyType2Config.filepath, Vector2u(10, 1), 0.3f, 0);
			entity->cHealth = make_shared<CHealth>(m_enemyType2Config.hp);
			entity->cMovement = make_shared<CMovement>(m_enemyType2Config.speed);
			entity->cMoney = make_shared<CMoney>(m_enemyType2Config.hp);
		}
		 
		break;
	}

	while (getline(readconfig, line)) 
	{
		if (line.empty() || line[0] == '#') continue;
		istringstream iss(line);
		iss >> m_enemyType3Config.tag >> m_enemyType3Config.filepath >> m_enemyType3Config.hp >> m_enemyType3Config.speed >> m_enemyType3Config.money;
		

		int amount;
		iss >> amount;

		for (int i = 0; i < amount; i++)
		{
			auto entity = m_entities.addEntity(m_enemyType3Config.tag);
			entity->cSet = make_shared<CSet>(m_enemyType3Config.filepath, Vector2u(10, 1), 0.3f, 0);
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
		break;
	}

	readconfig.close();

	// Pre-loaded backgrounds and buttons
	auto entity = m_scenes[AppState::MainMenu].addEntity("MainMenu");
	entity->cSet = make_shared<CSet>("IMGS/mainMenu.png");

	entity = m_scenes[AppState::Map1].addEntity("Map1");
	entity->cSet = make_shared<CSet>("IMGS/map1.png");

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

		if (m_state == AppState::Map1 || m_state == AppState::Map2 || m_state == AppState::Map3)
		{
			sCheckWaveFinished();
			sSpawnWave(dt);
		}

		m_currentFrame++;
	}
}

void Game::setPause(bool paused)
{
	//
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

	/*Vector2f mousePos = Vector2f(Mouse::getPosition(m_window));*/
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
					if (m_selected == "Tower1")
					{
						auto entity = m_scenes[m_state].addEntity(m_selected);
						entity->cSet = make_shared<CSet>("IMGS/BloodMoonTower/Tower1.png", Vector2u(11, 1), 0.3f, 0);
						entity->cPosition = make_shared<CPosition>(mousePos);
					}
					else if (m_selected == "Tower2")
					{
						auto entity = m_scenes[m_state].addEntity(m_selected);
						entity->cSet = make_shared<CSet>("IMGS/BloodMoonTower/Tower2.png", Vector2u(8, 1), 0.3f, 0);
						entity->cPosition = make_shared<CPosition>(mousePos);
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



void Game::TowerShoot()
{
	for (auto& curTower : m_entities.getEntites("Tower"))
	{
		if (curTower->isActive() && curTower->ReadyShoot())
		{
			for (auto& bullet : m_entities.getEntites("Bullet"))
			{
				if (!bullet->isActive())
				{
					bullet->cPosition = make_shared<CPosition>(curTower->cPosition->position);
					bullet->cMovement = make_shared<CMovement>(m_bulletConfig.speed);
					bullet->cSet = make_shared<CSet>(m_bulletConfig.filepath, Vector2u(10, 1), 0.3f, 0);
					bullet->cSet->sprite.setPosition(bullet->cPosition->position);
					bullet->active(true);

					sf::Vector2f tour = curTower->cTarget->cPosition->position - curTower->cPosition->position;

					// Set bullet velocity to fixed direction times speed
					bullet->cMovement->speed = MathSupport::Length(tour) * m_bulletConfig.speed; 
				}

			}
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
	if (m_spawnStage == SpawnStage::None && m_finishWave)
	{
		m_spawnStage = SpawnStage::Type1;
		m_spawnTimer = 0.f;
	}

	if (m_spawnStage == SpawnStage::Done)
	{
		m_spawnStage = SpawnStage::None;
		m_finishWave = false;
		return;
	}

	m_spawnTimer += deltaTime;

	if (m_spawnTimer < m_spawnDelay) return;

	m_spawnTimer = 0.f;

	if (m_spawnStage == SpawnStage::Type1)
	{
		spawnEnemyType(1);
		m_spawnStage = SpawnStage::Type2;
	}
	else if (m_spawnStage == SpawnStage::Type2)
	{
		spawnEnemyType(2);
		m_spawnStage = SpawnStage::Type3;
	}
	else if (m_spawnStage == SpawnStage::Type3)
	{
		spawnEnemyType(3);
		m_spawnStage = SpawnStage::Done;
		m_currentWave++;
	}
}

void Game::spawnEnemyType(int type)
{
	WaveConfig& waveConfig = m_waveConfigs[m_mapindex][m_currentWave];

	if (type == 1)
	{
		int count = 0;
		for (auto& e : m_entities.getEntites(m_enemyType1Config.tag))
		{
			if (!e->isActive())
			{
				e->cPosition = make_shared<CPosition>(e->cMovement->starting_pos[m_mapindex]);
				e->active(true);
				if (++count >= waveConfig.enemyType1Count) break;
			}
		}
	}
	else if (type == 2)
	{
		int count = 0;
		for (auto& e : m_entities.getEntites(m_enemyType2Config.tag))
		{
			if (!e->isActive())
			{
				e->cPosition = make_shared<CPosition>(e->cMovement->starting_pos[m_mapindex]);
				e->active(true);
				if (++count >= waveConfig.enemyType2Count) break;
			}
		}
	}
	else if (type == 3)
	{
		int count = 0;
		for (auto& e : m_entities.getEntites(m_enemyType3Config.tag))
		{
			if (!e->isActive())
			{
				e->cPosition = make_shared<CPosition>(e->cMovement->starting_pos[m_mapindex]);
				e->active(true);
				if (++count >= waveConfig.enemyType3Count) break;
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
		if (entity->isActive())
		{
			if (entity->cMovement->currentPathindex >= entity->cMovement->paths[m_mapindex].size())
				continue;

			Vector2f target = entity->cMovement->paths[m_mapindex][entity->cMovement->currentPathindex];
			Vector2f direction = target - entity->cPosition->position;

			float distance = sqrt(direction.x * direction.x + direction.y * direction.y);

			if (distance < 1.f)
			{
				entity->cMovement->currentPathindex++;

				if (entity->cMovement->currentPathindex >= entity->cMovement->paths[m_mapindex].size())
				{
					m_health -= entity->cHealth->hp;
					continue; 
				}

				target = entity->cMovement->paths[m_mapindex][entity->cMovement->currentPathindex];
				direction = target - entity->cPosition->position;
				distance = sqrt(direction.x * direction.x + direction.y * direction.y);
			}

			Vector2f movement(0.f, 0.f);
			if (distance > 0)
				movement = direction / distance;

			entity->cPosition->position += movement * entity->cMovement->speed * deltaTime;

			sAnimation(entity, deltaTime);

			entity->cSet->sprite.setTextureRect(entity->cSet->uvRect);
			entity->cSet->sprite.setPosition(entity->cPosition->position);
		}
	}
}


