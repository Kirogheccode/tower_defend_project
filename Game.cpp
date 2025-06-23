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
		iss >> m_bulletConfig.filepath >> m_bulletConfig.damage >> m_bulletConfig.speed;
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
			entity->cPosition = make_shared<CPosition>(entity->cMovement->starting_pos[m_mapindex]);
		}

		break;
	}

	while (getline(readconfig, line)) {
		if (line.empty() || line[0] == '#') continue;
		istringstream iss(line);
		iss >> m_enemyType2Config.tag >> m_enemyType2Config.filepath >> m_enemyType2Config.hp >> m_enemyType2Config.speed >> m_enemyType2Config.money;
		break;

		int amount;
		iss >> amount;

		for (int i = 0; i < amount; i++)
		{
			auto entity = m_entities.addEntity(m_enemyType2Config.tag);
			entity->cSet = make_shared<CSet>(m_enemyType2Config.filepath, Vector2u(10, 1), 0.3f, 0);
			entity->cHealth = make_shared<CHealth>(m_enemyType2Config.hp);
			entity->cMovement = make_shared<CMovement>(m_enemyType2Config.speed);
			entity->cMoney = make_shared<CMoney>(m_enemyType2Config.hp);
			entity->cPosition = make_shared<CPosition>(entity->cMovement->starting_pos[m_mapindex]);
		}
		 
		break;
	}

	while (getline(readconfig, line)) {
		if (line.empty() || line[0] == '#') continue;
		istringstream iss(line);
		iss >> m_enemyType3Config.tag >> m_enemyType3Config.filepath >> m_enemyType3Config.hp >> m_enemyType3Config.speed >> m_enemyType3Config.money;
		break;

		int amount;
		iss >> amount;

		for (int i = 0; i < amount; i++)
		{
			auto entity = m_entities.addEntity(m_enemyType3Config.tag);
			entity->cSet = make_shared<CSet>(m_enemyType3Config.filepath, Vector2u(10, 1), 0.3f, 0);
			entity->cHealth = make_shared<CHealth>(m_enemyType3Config.hp);
			entity->cMovement = make_shared<CMovement>(m_enemyType3Config.speed);
			entity->cMoney = make_shared<CMoney>(m_enemyType3Config.hp);
			entity->cPosition = make_shared<CPosition>(entity->cMovement->starting_pos[m_mapindex]);
		}

		break;
	}

	while (getline(readconfig, line)) {
		if (line.empty() || line[0] == '#') continue;
		istringstream iss(line);
		int wave, mapIndex, type1, type2, type3;

		iss >> wave >> mapIndex >> type1 >> type2 >> type3;

		m_waveConfigs[mapIndex][wave - 1] = { type1 , type2 , type3 };

		break;
	}

	// Pre-loaded backgrounds and buttons
	auto entity = m_scenes[AppState::MainMenu].addEntity("MainMenu");
	entity->cSet = make_shared<CSet>("IMGS/mainMenu.png");

	entity = m_scenes[AppState::Map1].addEntity("Map1");
	entity->cSet = make_shared<CSet>("IMGS/map1.png");

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
			entity->cSet->sprite.setColor(sf::Color(200, 200, 200));
		},
		[entity]()
		{
			entity->cSet->sprite.setColor(sf::Color(255, 255, 255));
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
			entity->cSet->sprite.setColor(sf::Color(200, 200, 200));
		},
		[entity]()
		{
			entity->cSet->sprite.setColor(sf::Color(255, 255, 255));
		}
	);
}

void Game::run()
{
	Clock clock;

	while (m_running)
	{
		float dt = clock.restart().asSeconds();

		sRender();
		sMovement(dt);
		sUserInput();

		if (m_state == AppState::Map1 || m_state == AppState::Map2 || m_state == AppState::Map3)
		{
			spawnWave();
		}

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

	for (auto& e : m_entities.getEntites())
	{
		if (e->isActive())
		{
			m_window.draw(e->cSet->sprite);
		}
	}

	for (auto& e : m_scenes[m_state].getEntites())
	{
		if (e->cSet && e->cPosition)
			e->cSet->sprite.setPosition(e->cPosition->position);

		m_window.draw(e->cSet->sprite);
	}

	m_window.display();
}

void Game::sUserInput()
{
	Event event;

	Vector2f mousePos = Vector2f(Mouse::getPosition(m_window));

	while (m_window.pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			m_running = false;
		}

		// Check if left mouse is pressed
		if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
		{
			for (auto& e : m_scenes[m_state].getEntites())
			{
				if (e->cSet && e->cInput)
				{
                    m_entities.update();
					FloatRect bounds = e->cSet->sprite.getGlobalBounds();

					if (bounds.contains(mousePos))
					{
						e->cInput->onClick();
					}
				}
			}
		}
	}

	// Hover detection
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

	// Update all entites
	for (auto& state : m_scenes)
	{
		state.second.update();
	}
	
	m_entities.update();
}


void Game::sCollision()
{
	//
}

void Game::spawnWave()
{
	if (m_finishWave == true)
	{
		WaveConfig& waveConfig = m_waveConfigs[m_mapindex][m_currentWave++];

		EntityVec& enemies1 = m_entities.getEntites(m_enemyType1Config.tag);
		int spawned1 = 0;

		for (auto& e : enemies1)
		{
			if (!e->isActive())
			{
				e->cPosition->position = e->cMovement->starting_pos[m_mapindex];
				e->active(true);
				if (++spawned1 >= waveConfig.enemyType1Count) break;
			}
		}

		for (int i = 0; i < waveConfig.enemyType2Count; i++)
		{
			// active = true -> Die -> active = false
		}

		for (int i = 0; i < waveConfig.enemyType3Count; i++)
		{
			// active = true -> Die -> active = false
		}
	}

	m_finishWave = false;
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
}

void Game::sMovement(float& deltaTime)
{
	for (auto& entity : m_entities.getEntites())
	{
		if (entity->isActive())
		{
			if (entity->cMovement->currentPathindex >= entity->cMovement->paths[m_mapindex].size())
				return;

				Vector2f target = entity->cMovement->paths[m_mapindex][entity->cMovement->currentPathindex];
				Vector2f direction = target - entity->cPosition->position;

				float distance = sqrt(direction.x * direction.x + direction.y * direction.y);

				if (distance < 1.f)
				{
					entity->cMovement->currentPathindex++;

					if (entity->cMovement->currentPathindex >= entity->cMovement->paths[m_mapindex].size())
					{
						// At the finish (minusHealth())
					}

					target = entity->cMovement->paths[m_mapindex][entity->cMovement->currentPathindex];
					direction = target - entity->cPosition->position;
					distance = sqrt(direction.x * direction.x + direction.y * direction.y);

				}

			Vector2f movement(0.f, 0.f);

			if (distance > 0) {
				movement = direction / distance;
			}

			entity->cPosition->position += movement * entity->cMovement->speed * deltaTime;

			sAnimation(entity, deltaTime);

			entity->cSet->sprite.setTextureRect(entity->cSet->uvRect);

			entity->cSet->sprite.setPosition(entity->cPosition->position);
		}
	}
}