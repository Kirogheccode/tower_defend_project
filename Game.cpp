#include "Game.h"

// --- Khởi tạo game ---
Game::Game(const string& config)
{
	init(config);
}

void Game::init(const string& path)
{
	ifstream readconfig(path);
	string line;


	// --- Reading window config
	while (getline(readconfig, line)) {
		if (line.empty() || line[0] == '#') continue;
		istringstream iss(line);
		string window_name;
		iss >> window_name >> m_windowConfig.width >> m_windowConfig.height >> m_windowConfig.fps >> m_windowConfig.fullscreen;
		Uint32 style = m_windowConfig.fullscreen ? Style::Fullscreen : Style::Default;
		m_window.create(VideoMode(m_windowConfig.width, m_windowConfig.height), window_name, style);
		m_window.setFramerateLimit(m_windowConfig.fps);
		break;
	}


	while (getline(readconfig, line)) {
		if (line.empty() || line[0] == '#') continue;
		istringstream iss(line);
		iss >> m_bullet01Config.tag >> m_bullet01Config.filepath >> m_bullet01Config.damage >> m_bullet01Config.speed >> m_bullet01Config.Bscale >> m_bullet01Config.Sscale;

		for (int i = 0; i < 50; i++)
		{
			auto entity = m_entities.addEntity(m_bullet01Config.tag);
			entity->cMovement = make_shared<CMovement>(m_bullet01Config.speed);
			entity->cSet = make_shared<CSet>(m_bullet01Config.filepath, Vector2u(1, 1), 0.5f, 0);
			entity->cSet->isDynamic = true;
			entity->cDamage = make_shared<CDamage>(m_bullet01Config.damage);
			entity->cBoundaryScale = make_shared<CBoundaryScale>(m_bullet01Config.Bscale);
			auto& sprite = entity->cSet->sprite;
			sprite.setScale(m_bullet01Config.Sscale, m_bullet01Config.Sscale);
			sprite.setOrigin(sprite.getLocalBounds().width / 2.f, (sprite.getLocalBounds().height / 2.f) + 20.0);
		}
		break;
	}


	while (getline(readconfig, line)) {
		if (line.empty() || line[0] == '#') continue;
		istringstream iss(line);
		iss >> m_bullet02Config.tag >> m_bullet02Config.filepath >> m_bullet02Config.damage >> m_bullet02Config.speed >> m_bullet02Config.Bscale >> m_bullet02Config.Sscale;

		for (int i = 0; i < 50; i++)
		{
			auto entity = m_entities.addEntity(m_bullet02Config.tag);
			entity->cMovement = make_shared<CMovement>(m_bullet02Config.speed);
			entity->cSet = make_shared<CSet>(m_bullet02Config.filepath, Vector2u(1, 1), 0.5f, 0);
			entity->cSet->isDynamic = true;
			entity->cDamage = make_shared<CDamage>(m_bullet02Config.damage);
			entity->cBoundaryScale = make_shared<CBoundaryScale>(m_bullet02Config.Bscale);
			auto& sprite = entity->cSet->sprite;
			sprite.setScale(m_bullet02Config.Sscale, m_bullet02Config.Sscale);
			sprite.setOrigin(sprite.getLocalBounds().width / 2.f, (sprite.getLocalBounds().height / 2.f) + 20.0);
		}
		break;
	}


	// --- Rading enemy config && Pre-loaded enemies
	while (getline(readconfig, line)) {
		if (line.empty() || line[0] == '#') continue;
		istringstream iss(line);
		iss >> m_enemyType1Config.tag >> m_enemyType1Config.filepath >> m_enemyType1Config.hp >> m_enemyType1Config.speed >> m_enemyType1Config.money >> m_enemyType1Config.Bscale >> m_enemyType1Config.Sscale;

		int amount;
		iss >> amount;

		for (int i = 0; i < amount; i++)
		{
			auto entity = m_entities.addEntity(m_enemyType1Config.tag);
			entity->cSet = make_shared<CSet>(m_enemyType1Config.filepath, Vector2u(10, 1), 0.3f, 0);
			entity->cHealth = make_shared<CHealth>(m_enemyType1Config.hp);
			entity->cMovement = make_shared<CMovement>(m_enemyType1Config.speed);
			entity->cMoney = make_shared<CMoney>(m_enemyType1Config.money);
			entity->cBoundaryScale = make_shared<CBoundaryScale>(m_enemyType1Config.Bscale);
			entity->cSpriteScale = make_shared<CSpriteScale>(m_enemyType1Config.Sscale);

			auto& sprite = entity->cSet->sprite;
			sprite.setScale(1.2f, 1.2f);
			sprite.setOrigin(sprite.getLocalBounds().width / 2.f, (sprite.getLocalBounds().height / 2.f) + 20.0);
		}

		break;
	}


	while (getline(readconfig, line)) {
		if (line.empty() || line[0] == '#') continue;
		istringstream iss(line);
		iss >> m_enemyType2Config.tag >> m_enemyType2Config.filepath >> m_enemyType2Config.hp >> m_enemyType2Config.speed >> m_enemyType2Config.money >> m_enemyType2Config.Bscale >> m_enemyType2Config.Sscale;

		int amount;
		iss >> amount;

		for (int i = 0; i < amount; i++)
		{
			auto entity = m_entities.addEntity(m_enemyType2Config.tag);
			entity->cSet = make_shared<CSet>(m_enemyType2Config.filepath, Vector2u(8, 1), 0.3f, 0);
			entity->cHealth = make_shared<CHealth>(m_enemyType2Config.hp);
			entity->cMovement = make_shared<CMovement>(m_enemyType2Config.speed);
			entity->cMoney = make_shared<CMoney>(m_enemyType2Config.money);
			entity->cBoundaryScale = make_shared<CBoundaryScale>(m_enemyType2Config.Bscale);
			entity->cSpriteScale = make_shared<CSpriteScale>(m_enemyType2Config.Sscale);

			auto& sprite = entity->cSet->sprite;
			sprite.setScale(m_enemyType2Config.Sscale, m_enemyType2Config.Sscale);
			sprite.setOrigin(sprite.getLocalBounds().width / 2.f, (sprite.getLocalBounds().height / 2.f) + 20.0);
		}

		break;
	}


	while (getline(readconfig, line)) {
		if (line.empty() || line[0] == '#') continue;
		istringstream iss(line);
		iss >> m_enemyType3Config.tag >> m_enemyType3Config.filepath >> m_enemyType3Config.hp >> m_enemyType3Config.speed >> m_enemyType3Config.money >> m_enemyType3Config.Bscale >> m_enemyType3Config.Sscale;

		int amount;
		iss >> amount;

		for (int i = 0; i < amount; i++)
		{
			auto entity = m_entities.addEntity(m_enemyType3Config.tag);
			entity->cSet = make_shared<CSet>(m_enemyType3Config.filepath, Vector2u(9, 1), 0.3f, 0);
			entity->cHealth = make_shared<CHealth>(m_enemyType3Config.hp);
			entity->cMovement = make_shared<CMovement>(m_enemyType3Config.speed);
			entity->cMoney = make_shared<CMoney>(m_enemyType3Config.money);
			entity->cBoundaryScale = make_shared<CBoundaryScale>(m_enemyType3Config.Bscale);
			entity->cSpriteScale = make_shared<CSpriteScale>(m_enemyType3Config.Sscale);

			auto& sprite = entity->cSet->sprite;
			sprite.setOrigin(sprite.getLocalBounds().width / 2.f, (sprite.getLocalBounds().height / 2.f) + 20.0);
		}

		break;
	}


	// --- Load and Initialize Tower1
	while (getline(readconfig, line))
	{
		if (line.empty() || line[0] == '#') continue;
		istringstream iss(line);
		Vector2u imgCount;
		float switchTime, range, cooldown;
		int amount;
		iss >> m_towerType1Config.tag >> m_towerType1Config.filepath >> imgCount.x >> imgCount.y >> switchTime >> range >> cooldown >> amount;

		for (int i = 0; i < amount; i++)
		{
			auto entity = m_entities.addEntity(m_towerType1Config.tag);
			entity->cSet = make_shared<CSet>(m_towerType1Config.filepath, imgCount, switchTime, 0);
			entity->cCooldown = make_shared<CCooldown>(cooldown);
			entity->cBound = make_shared<CBound>(range);
			entity->cWeapon = make_shared<CWeapon>("Bullet01");
			auto& sprite = entity->cSet->sprite;
			sprite.setOrigin(sprite.getLocalBounds().width / 2.f, (sprite.getLocalBounds().height / 2.f) + 20.0);
		}
		break;
	}


	// --- Load and Initialize Tower2
	while (getline(readconfig, line))
	{
		if (line.empty() || line[0] == '#') continue;
		istringstream iss(line);
		Vector2u imgCount;
		float switchTime, range, cooldown;
		int amount;
		iss >> m_towerType2Config.tag >> m_towerType2Config.filepath >> imgCount.x >> imgCount.y >> switchTime >> range >> cooldown >> amount;

		for (int i = 0; i < amount; i++)
		{
			auto entity = m_entities.addEntity(m_towerType2Config.tag);
			entity->cSet = make_shared<CSet>(m_towerType2Config.filepath, imgCount, switchTime, 0);
			entity->cCooldown = make_shared<CCooldown>(cooldown);
			entity->cBound = make_shared<CBound>(range);
			entity->cWeapon = make_shared<CWeapon>("Bullet02");
			auto& sprite = entity->cSet->sprite;
			sprite.setOrigin(sprite.getLocalBounds().width / 2.f, (sprite.getLocalBounds().height / 2.f) + 20.0);
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

	if (!m_font.loadFromFile("IMGS/ARCADECLASSIC.ttf")) {
		cout << "Failed to load font\n";
	}

	if (!m_backgroundMusic.openFromFile("SOUNDS/bgmusic.wav")) {
		cout << "Error: Could not load background music file.\n";
	}
	else
	{
		m_backgroundMusic.setLoop(true);
		m_backgroundMusic.play();
		updateAudioSettings();
	}

	if (!m_clickBuffer.loadFromFile("SOUNDS/hover.ogg")) {
		cout << "Error: Could not load click sound file.\n";
	}

	m_inputLabel.setFont(m_font);
	m_inputLabel.setCharacterSize(24);
	m_inputLabel.setFillColor(Color::White);
	m_inputLabel.setString("Enter your name:");
	m_inputLabel.setPosition(500, 250);

	m_inputText.setFont(m_font);
	m_inputText.setCharacterSize(24);
	m_inputText.setFillColor(Color::Yellow);
	m_inputText.setPosition(500, 300);


	// --- Khởi tạo máu người chơi
	m_health.resize(4, vector<int>(5, 1));

	for (int i = 0; i < 5; i++)
	{
		auto entity = m_scenes[AppState::GamePlay].addEntity("Heart");
		entity->cSet = make_shared<CSet>("IMGS/Heart.png");
		entity->cBoundaryScale = make_shared<CBoundaryScale>(0.1);
		auto& sprite = entity->cSet->sprite;
		sprite.setScale(entity->cBoundaryScale->scale, entity->cBoundaryScale->scale);
		entity->cPosition = make_shared<CPosition>(Vector2f(i * sprite.getGlobalBounds().width, 0));
	}


	// --- Khởi tạo tiền
	auto coin = m_scenes[AppState::GamePlay].addEntity("Coin");
	coin->cSet = make_shared<CSet>("IMGS/Coin.png");
	coin->cBoundaryScale = make_shared<CBoundaryScale>(0.1182432432432432);
	auto& sprite = coin->cSet->sprite;
	sprite.setScale(coin->cBoundaryScale->scale, coin->cBoundaryScale->scale);
	coin->cPosition = make_shared<CPosition>(Vector2f(0, sprite.getGlobalBounds().height));

	auto moneyText = m_scenes[AppState::GamePlay].addEntity("MoneyText");
	moneyText->cText = make_shared<CText>(0);
	moneyText->cText->text.setFont(m_font);
	moneyText->cText->text.setCharacterSize(50);
	moneyText->cText->text.setFillColor(sf::Color::Yellow);
	moneyText->cText->text.setPosition(Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height));


	// --- Khởi tạo WAVE text
	auto waveEntity = m_scenes[AppState::GamePlay].addEntity("WaveText");
	waveEntity->cText = make_shared<CText>("WAVE ");
	waveEntity->cText->text.setFont(m_font);
	waveEntity->cText->text.setCharacterSize(80);
	waveEntity->cText->text.setFillColor(sf::Color::Black);

	sf::FloatRect waveBounds = waveEntity->cText->text.getLocalBounds();
	waveEntity->cText->text.setOrigin(waveBounds.left + waveBounds.width / 2.f,
		waveBounds.top + waveBounds.height / 2.f);

	auto numEntity = m_scenes[AppState::GamePlay].addEntity("WaveNumber");
	numEntity->cText = make_shared<CText>(to_string(m_currentWave[m_mapindex]));
	numEntity->cText->text.setFont(m_font);
	numEntity->cText->text.setCharacterSize(80);
	numEntity->cText->text.setFillColor(sf::Color::Red);

	FloatRect numBounds = numEntity->cText->text.getLocalBounds();
	numEntity->cText->text.setOrigin(numBounds.left + numBounds.width / 2.f,
		numBounds.top + numBounds.height / 2.f);

	float totalWidth = waveBounds.width + 20 + numBounds.width;
	float centerX = m_windowConfig.width / 2.f;
	float centerY = m_windowConfig.height / 2.f;

	waveEntity->cText->text.setPosition(centerX - totalWidth / 2.f + waveBounds.width / 2.f, centerY);
	numEntity->cText->text.setPosition(waveEntity->cText->text.getPosition().x + waveBounds.width / 2.f + 20 + numBounds.width / 2.f, centerY);


	initUIFlow();
}

void Game::initUIFlow()
{
	// -- Choose map --
	{
		ifstream readMapBase("MapBase.txt");
		string line;

		string tag, filepath;
		Vector2f Base;
		int base_amount{};

		// Khởi tạo map1 
		auto entity = m_scenes[AppState::Map1].addEntity("Map1");
		entity->cSet = make_shared<CSet>("IMGS/map1.png");

		while (getline(readMapBase, line)) {
			if (line.empty() || line[0] == '#') continue;
			istringstream iss(line);
			iss >> tag >> filepath >> base_amount;
			break;
		}

		while (getline(readMapBase, line) && base_amount > 0) {
			if (line.empty() || line[0] == '#') continue;

			base_amount--;
			istringstream iss(line);
			iss >> Base.x >> Base.y;

			entity = m_scenes[AppState::Map1].addEntity(tag);
			entity->cSet = make_shared<CSet>(filepath);
			entity->cPosition = make_shared<CPosition>(Base);
			entity->active(true);
		}



		//Khởi tạo map2
		entity = m_scenes[AppState::Map2].addEntity("Map2");
		entity->cSet = make_shared<CSet>("IMGS/map2.png");

		while (getline(readMapBase, line)) {
			if (line.empty() || line[0] == '#') continue;
			istringstream iss(line);
			iss >> tag >> filepath >> base_amount;
			break;
		}

		while (getline(readMapBase, line) && base_amount > 0) {
			if (line.empty() || line[0] == '#') continue;

			base_amount--;
			istringstream iss(line);
			iss >> Base.x >> Base.y;

			entity = m_scenes[AppState::Map2].addEntity(tag);
			entity->cSet = make_shared<CSet>(filepath);
			entity->cPosition = make_shared<CPosition>(Base);
			entity->active(true);
		}
		
		//Khởi tạo map3
		entity = m_scenes[AppState::Map3].addEntity("Map3");
		entity->cSet = make_shared<CSet>("IMGS/map3.png");
		while (getline(readMapBase, line)) {
			if (line.empty() || line[0] == '#') continue;
			istringstream iss(line);
			iss >> tag >> filepath >> base_amount;
			break;
		}

		while (getline(readMapBase, line) && base_amount > 0) {
			if (line.empty() || line[0] == '#') continue;

			base_amount--;
			istringstream iss(line);
			iss >> Base.x >> Base.y;

			entity = m_scenes[AppState::Map3].addEntity(tag);
			entity->cSet = make_shared<CSet>(filepath);
			entity->cPosition = make_shared<CPosition>(Base);
			entity->active(true);
		}
		readMapBase.close();
		
		// Khởi tạo map4
		entity = m_scenes[AppState::Map4].addEntity("Map4");
		entity->cSet = make_shared<CSet>("IMGS/map4.png");

		// -- OptionMenu --
		entity = m_scenes[AppState::OptionMenu].addEntity("OptionBoard");
		entity->cSet = make_shared<CSet>("IMGS/OptionBoard.png");
		entity->cPosition = make_shared<CPosition>(Vector2f(m_windowConfig.width / 2.f, m_windowConfig.height / 2.f));
		entity->cSet->sprite.setOrigin(entity->cSet->sprite.getLocalBounds().width / 2.f, entity->cSet->sprite.getLocalBounds().height / 2.f);

		entity = m_scenes[AppState::OptionMenu].addEntity("Title");
		entity->cText = make_shared<CText>("OPTIONS");
		entity->cText->text.setFont(m_font);
		entity->cText->text.setCharacterSize(60);
		entity->cText->text.setFillColor(Color::Black);
		entity->cText->text.setPosition(Vector2f(839, 273));


		entity = m_scenes[AppState::OptionMenu].addEntity("Resume");
		entity->cSet = make_shared<CSet>("IMGS/play.png");
		entity->cPosition = make_shared<CPosition>(Vector2f(839, 406));
		entity->cSet->sprite.setScale(0.6f, 0.6f);
		entity->cInput = make_shared<CInput>([this]()
			{
				m_state1 = AppState::Dummy;
				m_paused = false;
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

		entity = m_scenes[AppState::OptionMenu].addEntity("Save");
		entity->cSet = make_shared<CSet>("IMGS/setting.png");
		entity->cPosition = make_shared<CPosition>(Vector2f(839, 539));
		entity->cSet->sprite.setScale(0.6f, 0.6f);
		entity->cInput = make_shared<CInput>([this]()
			{
				cout << "Successfully saved" << endl;
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


		entity = m_scenes[AppState::OptionMenu].addEntity("Quit");
		entity->cSet = make_shared<CSet>("IMGS/quit.png");
		entity->cPosition = make_shared<CPosition>(Vector2f(839, 672));
		entity->cSet->sprite.setScale(0.6f, 0.6f);
		entity->cInput = make_shared<CInput>([this]()
			{
				prev_state = m_state;
				m_state = AppState::MapSelect;
				game_state = AppState::Dummy;
				m_state1 = AppState::Dummy;
				sReset();
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


		// Khởi tạo các chức năng trong game - GamePlay
		entity = m_scenes[AppState::GamePlay].addEntity("OptionSetting");
		entity->cSet = make_shared<CSet>("IMGS/Option.png");
		entity->cPosition = make_shared<CPosition>(Vector2f(20, 1010));
		entity->cInput = make_shared<CInput>([this]()
			{
				m_state1 = AppState::OptionMenu;
				m_paused = true;
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


		entity = m_scenes[AppState::GamePlay].addEntity("SystemSetting");
		entity->cSet = make_shared<CSet>("IMGS/Gear.png");
		entity->cPosition = make_shared<CPosition>(Vector2f(20, 940));
		entity->cInput = make_shared<CInput>([this]()
			{
				m_setting = true;
				m_paused = true;
				m_state1 = AppState::SettingsMenu;
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


		// Khởi tạo việc chọn và đặt tháp
		entity = m_scenes[AppState::GamePlay].addEntity("SelectButton");
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
	}

	// -- MainMenu --
	{
		auto bg = m_scenes[AppState::MainMenu].addEntity("BG");
		bg->cSet = make_shared<CSet>("IMGS/mainMenu1.png");
		bg->cPosition = make_shared<CPosition>(Vector2f(0, 0));

		auto play = m_scenes[AppState::MainMenu].addEntity("Play");
		play->cSet = make_shared<CSet>("IMGS/play.png");
		play->cPosition = make_shared<CPosition>(Vector2f(1090, 485));
		play->cSet->sprite.setScale(0.85f, 0.85f);
		play->cInput = make_shared<CInput>([this]() 
			{
			m_state = (AppState::PlayMenu);
			},
			[play]()
			{
				play->cSet->sprite.setColor(Color(200, 200, 200));
			},
			[play]()
			{
				play->cSet->sprite.setColor(Color(255, 255, 255));
			}
		);

		auto settingsButton = m_scenes[AppState::MainMenu].addEntity("SettingsButton");
		settingsButton->cSet = make_shared<CSet>("IMGS/setting.png");
		settingsButton->cPosition = make_shared<CPosition>(Vector2f(1090, 680));
		settingsButton->cSet->sprite.setScale(0.85f, 0.85f);
		settingsButton->cInput = make_shared<CInput>([this]() 
			{
			m_setting = true;
			m_state1 = AppState::SettingsMenu;
			},
			[settingsButton]()
			{
				settingsButton->cSet->sprite.setColor(Color(200, 200, 200));
			},
			[settingsButton]()
			{
				settingsButton->cSet->sprite.setColor(Color(255, 255, 255));
			}
		);

		auto exit = m_scenes[AppState::MainMenu].addEntity("Exit");
		exit->cSet = make_shared<CSet>("IMGS/quit.png");
		exit->cPosition = make_shared<CPosition>(Vector2f(1090, 876));
		exit->cSet->sprite.setScale(0.85f, 0.85f);
		exit->cInput = make_shared<CInput>([this]() 
			{
			m_window.close();
			m_running = false;
			},
			[exit]()
			{
				exit->cSet->sprite.setColor(Color(200, 200, 200));
			},
			[exit]()
			{
				exit->cSet->sprite.setColor(Color(255, 255, 255));
			}
		);
	}

	// -- PlayMenu --
	{
		auto bg = m_scenes[AppState::PlayMenu].addEntity("BG");
		bg->cSet = make_shared<CSet>("IMGS/mainMenu1.png");
		bg->cPosition = make_shared<CPosition>(Vector2f(0, 0));

		auto newGameButton = m_scenes[AppState::PlayMenu].addEntity("New");
		newGameButton->cSet = make_shared<CSet>("IMGS/new.png");
		newGameButton->cPosition = make_shared<CPosition>(Vector2f(1144, 605));
		newGameButton->cInput = make_shared<CInput>([this]() 
			{
			m_playerName.clear();
			m_inputText.setString("|");
			m_typingName = true;
			},
			[newGameButton]()
			{
				newGameButton->cSet->sprite.setColor(Color(200, 200, 200));
			},
			[newGameButton]()
			{
				newGameButton->cSet->sprite.setColor(Color(255, 255, 255));
			}
		);

		auto loadGame = m_scenes[AppState::PlayMenu].addEntity("Load");
		loadGame->cSet = make_shared<CSet>("IMGS/load.png");
		loadGame->cPosition = make_shared<CPosition>(Vector2f(1144, 766));
		loadGame->cInput = make_shared<CInput>([this]() 
			{
			cout << "Load Game clicked\n";
			// sLoadGame();
			},
			[loadGame]()
			{
				loadGame->cSet->sprite.setColor(Color(200, 200, 200));
			},
			[loadGame]()
			{
				loadGame->cSet->sprite.setColor(Color(255, 255, 255));
			}
		);

		auto back = m_scenes[AppState::PlayMenu].addEntity("Back");
		back->cSet = make_shared<CSet>("IMGS/back.png");
		back->cPosition = make_shared<CPosition>(Vector2f(20, 1010));
		back->cInput = make_shared<CInput>([this]() 
			{
			 m_state = AppState::MainMenu;
			 m_typingName = false;
			},
			[back]()
			{
				back->cSet->sprite.setColor(Color(200, 200, 200));
			},
			[back]()
			{
				back->cSet->sprite.setColor(Color(255, 255, 255));
			}
		);
	}

	// -- SettingsMenu (Pop-up) --
	{

		auto panel = m_scenes[AppState::SettingsMenu].addEntity("SettingsPanel");
		panel->cSet = make_shared<CSet>("IMGS/settingmenu.png");
		panel->cPosition = make_shared<CPosition>(Vector2f(m_windowConfig.width / 2.f, m_windowConfig.height / 2.f));
		panel->cSet->sprite.setOrigin(panel->cSet->sprite.getLocalBounds().width / 2.f, panel->cSet->sprite.getLocalBounds().height / 2.f);
		panel->cSet->sprite.setScale(1.5f, 1.5f);

		Vector2f panelCenter = panel->cPosition->position;
		float row1_y = panelCenter.y - 25.f;
		float row2_y = panelCenter.y + 50.f;
		float icon_x = panelCenter.x - 170.f;
		float slider_x = panelCenter.x + 50.f;

		auto musicIcon = m_scenes[AppState::SettingsMenu].addEntity("MusicIcon");
		musicIcon->cSet = make_shared<CSet>("IMGS/music_on.png");
		musicIcon->cPosition = make_shared<CPosition>(Vector2f(icon_x, row1_y));
		musicIcon->cSet->sprite.setOrigin(musicIcon->cSet->sprite.getLocalBounds().width / 2.f, musicIcon->cSet->sprite.getLocalBounds().height / 2.f);
		musicIcon->cSet->sprite.setScale(0.1f, 0.1f);
		musicIcon->cInput = make_shared<CInput>([this, musicIcon]() {
			m_musicMuted = !m_musicMuted;
			musicIcon->cSet->texture.loadFromFile(m_musicMuted ? "IMGS/music_off.png" : "IMGS/music_on.png");
			updateAudioSettings();
			});

		auto musicSliderEntity = m_scenes[AppState::SettingsMenu].addEntity("MusicSlider");
		musicSliderEntity->cSlider = make_shared<CSlider>(&m_musicVolume, Vector2f(slider_x, row1_y),"IMGS/Slider.png","IMGS/SlidingBar.png");

		auto sfxIcon = m_scenes[AppState::SettingsMenu].addEntity("SfxIcon");
		sfxIcon->cSet = make_shared<CSet>("IMGS/sfx_on.png");
		sfxIcon->cPosition = make_shared<CPosition>(Vector2f(icon_x, row2_y));
		sfxIcon->cSet->sprite.setOrigin(sfxIcon->cSet->sprite.getLocalBounds().width / 2.f, sfxIcon->cSet->sprite.getLocalBounds().height / 2.f);
		sfxIcon->cSet->sprite.setScale(0.1f, 0.1f);
		sfxIcon->cInput = make_shared<CInput>([this, sfxIcon]() {
			m_sfxMuted = !m_sfxMuted;
			sfxIcon->cSet->texture.loadFromFile(m_sfxMuted ? "IMGS/sfx_off.png" : "IMGS/sfx_on.png");
			});

		auto sfxSliderEntity = m_scenes[AppState::SettingsMenu].addEntity("SfxSlider");
		sfxSliderEntity->cSlider = make_shared<CSlider>(&m_sfxVolume, Vector2f(slider_x, row2_y), "IMGS/Slider.png", "IMGS/SlidingBar.png");

		auto back = m_scenes[AppState::SettingsMenu].addEntity("Back");
		back->cSet = make_shared<CSet>("IMGS/back.png");
		back->cPosition = make_shared<CPosition>(Vector2f(panelCenter.x, panelCenter.y + 115.f));
		back->cSet->sprite.setOrigin(back->cSet->sprite.getLocalBounds().width / 2.f, back->cSet->sprite.getLocalBounds().height / 2.f);
		back->cInput = make_shared<CInput>([this]() 
			{
			m_setting = false;
			m_paused = false;
			m_state1 = AppState::Dummy;
			},
			[back]()
			{
				back->cSet->sprite.setColor(Color(200, 200, 200));
			},
			[back]()
			{
				back->cSet->sprite.setColor(Color(255, 255, 255));
			}
		);

		auto aboutButton = m_scenes[AppState::SettingsMenu].addEntity("AboutButton");
		aboutButton->cSet = make_shared<CSet>("IMGS/aboutus.png");
		aboutButton->cPosition = make_shared<CPosition>(Vector2f(panelCenter.x - 100.f, panelCenter.y + 115.f));
		aboutButton->cSet->sprite.setOrigin(aboutButton->cSet->sprite.getLocalBounds().width / 2.f, aboutButton->cSet->sprite.getLocalBounds().height / 2.f);
		aboutButton->cSet->sprite.setScale(4.0f, 4.0f);
		aboutButton->cInput = make_shared<CInput>([this]() {
			m_state1 = AppState::AboutUs;
			},
			[aboutButton]() {
				aboutButton->cSet->sprite.setColor(Color(200, 200, 200));
			},
			[aboutButton]() {
				aboutButton->cSet->sprite.setColor(Color(255, 255, 255));
			}
		);

		auto rulesButton = m_scenes[AppState::SettingsMenu].addEntity("RulesButton");
		rulesButton->cSet = make_shared<CSet>("IMGS/rules.png");
		rulesButton->cPosition = make_shared<CPosition>(Vector2f(panelCenter.x + 100.f, panelCenter.y + 115.f));
		rulesButton->cSet->sprite.setOrigin(rulesButton->cSet->sprite.getLocalBounds().width / 2.f, rulesButton->cSet->sprite.getLocalBounds().height / 2.f);
		rulesButton->cSet->sprite.setScale(4.0f, 4.0f);
		rulesButton->cInput = make_shared<CInput>([this]() {
			m_state1 = AppState::Rules;
			},
			[rulesButton]() {
				rulesButton->cSet->sprite.setColor(Color(200, 200, 200));
			},
			[rulesButton]() {
				rulesButton->cSet->sprite.setColor(Color(255, 255, 255));
			}
		);
	}

	// -- AboutUs (Pop-up) --
	{
		auto panel = m_scenes[AppState::AboutUs].addEntity("AboutPanel");
		panel->cSet = make_shared<CSet>("IMGS/About.png");
		panel->cPosition = make_shared<CPosition>(Vector2f(m_windowConfig.width / 2.f, m_windowConfig.height / 2.f));
		panel->cSet->sprite.setOrigin(panel->cSet->sprite.getLocalBounds().width / 2.f, panel->cSet->sprite.getLocalBounds().height / 2.f);
		panel->cSet->sprite.setScale(1.5f, 1.5f);


		auto backBtn = m_scenes[AppState::AboutUs].addEntity("BackAbout");
		backBtn->cSet = make_shared<CSet>("IMGS/back.png");
		backBtn->cPosition = make_shared<CPosition>(Vector2f(m_windowConfig.width / 2.f, m_windowConfig.height / 2.f + 200.f));
		backBtn->cInput = make_shared<CInput>([this]() 
			{
			m_state1 = AppState::SettingsMenu;
			},
			[backBtn]()
			{
				backBtn->cSet->sprite.setColor(Color(200, 200, 200));
			},
			[backBtn]()
			{
				backBtn->cSet->sprite.setColor(Color(255, 255, 255));
			}
		);
	}

	// -- Rules (Pop - up) --
	{
		auto panel = m_scenes[AppState::Rules].addEntity("RulesPanel");
		panel->cSet = make_shared<CSet>("IMGS/GameRules.png");
		panel->cPosition = make_shared<CPosition>(Vector2f(m_windowConfig.width / 2.f, m_windowConfig.height / 2.f));
		panel->cSet->sprite.setOrigin(panel->cSet->sprite.getLocalBounds().width / 2.f, panel->cSet->sprite.getLocalBounds().height / 2.f);
		panel->cSet->sprite.setScale(1.5f, 1.5f);

		auto backBtn = m_scenes[AppState::Rules].addEntity("BackRules");
		backBtn->cSet = make_shared<CSet>("IMGS/back.png");
		backBtn->cPosition = make_shared<CPosition>(Vector2f(m_windowConfig.width / 2.f, m_windowConfig.height / 2.f + 200.f));
		backBtn->cInput = make_shared<CInput>([this]() 
			{
			m_state1 = AppState::SettingsMenu;
			},
			[backBtn]()
			{
				backBtn->cSet->sprite.setColor(Color(200, 200, 200));
			},
			[backBtn]()
			{
				backBtn->cSet->sprite.setColor(Color(255, 255, 255));
			}
		);
	}

	// -- MapSelect --
	{
		auto bg = m_scenes[AppState::MapSelect].addEntity("BG");
		bg->cSet = make_shared<CSet>("IMGS/mainMenu1.png");
		bg->cPosition = make_shared<CPosition>(Vector2f(0, 0));

		auto map1 = m_scenes[AppState::MapSelect].addEntity("Map1");
		map1->cSet = make_shared<CSet>("IMGS/map1.png");
		map1->cPosition = make_shared<CPosition>(Vector2f(358, 267));
		map1->cSet->sprite.setScale(0.25f, 0.25f);
		map1->cInput = make_shared<CInput>([this]() 
			{
			m_mapindex = 0;
			m_state = AppState::Map1;
			game_state = AppState::GamePlay;

			int i = 0;
			for (auto& e : m_scenes[AppState::GamePlay].getEntities("Heart"))
			{
				e->active((bool)m_health[m_mapindex][i++]);
			}
			},
			[map1]()
			{
				map1->cSet->sprite.setColor(Color(200, 200, 200));
			},
			[map1]()
			{
				map1->cSet->sprite.setColor(Color(255, 255, 255));
			}
		);

		auto map2 = m_scenes[AppState::MapSelect].addEntity("Map2");
		map2->cSet = make_shared<CSet>("IMGS/map2.png");
		map2->cPosition = make_shared<CPosition>(Vector2f(1040, 267));
		map2->cSet->sprite.setScale(0.25f, 0.25f);
		map2->cInput = make_shared<CInput>([this]() 
			{
			m_mapindex = 1;
			m_state = AppState::Map2;
			game_state = AppState::GamePlay;

			int i = 0;
			for (auto& e : m_scenes[AppState::GamePlay].getEntities("Heart"))
			{
				e->active((bool)m_health[m_mapindex][i++]);
			}
			},
			[map2]()
			{
				map2->cSet->sprite.setColor(Color(200, 200, 200));
			},
			[map2]()
			{
				map2->cSet->sprite.setColor(Color(255, 255, 255));
			}
		);

		auto map3 = m_scenes[AppState::MapSelect].addEntity("Map3");
		map3->cSet = make_shared<CSet>("IMGS/map3.png");
		map3->cPosition = make_shared<CPosition>(Vector2f(358, 651));
		map3->cSet->sprite.setScale(0.25f, 0.25f);
		map3->cInput = make_shared<CInput>([this]() 
			{
			m_mapindex = 2;
			m_state = AppState::Map3;
			game_state = AppState::GamePlay;

			int i = 0;
			for (auto& e : m_scenes[AppState::GamePlay].getEntities("Heart"))
			{
				e->active((bool)m_health[m_mapindex][i++]);
			}
			},
			[map3]()
			{
				map3->cSet->sprite.setColor(Color(200, 200, 200));
			},
			[map3]()
			{
				map3->cSet->sprite.setColor(Color(255, 255, 255));
			}
		);

		auto map4 = m_scenes[AppState::MapSelect].addEntity("Map4");
		map4->cSet = make_shared<CSet>("IMGS/map4.png");
		map4->cPosition = make_shared<CPosition>(Vector2f(1040, 651));
		map4->cSet->sprite.setScale(0.25f, 0.25f);
		map4->cInput = make_shared<CInput>([this]() 
			{
			m_mapindex = 3;
			m_state = AppState::Map4;
			game_state = AppState::GamePlay;

			int i = 0;
			for (auto& e : m_scenes[AppState::GamePlay].getEntities("Heart"))
			{
				e->active((bool)m_health[m_mapindex][i++]);
			}
			},
			[map4]()
			{
				map4->cSet->sprite.setColor(Color(200, 200, 200));
			},
			[map4]()
			{
				map4->cSet->sprite.setColor(Color(255, 255, 255));
			}
		);


		auto back = m_scenes[AppState::MapSelect].addEntity("Back");
		back->cSet = make_shared<CSet>("IMGS/back.png");
		back->cPosition = make_shared<CPosition>(Vector2f(20, 1010));
		back->cInput = make_shared<CInput>([this]() 
			{
			m_state = AppState::PlayMenu;
			},
			[back]()
			{
				back->cSet->sprite.setColor(Color(200, 200, 200));
			},
			[back]()
			{
				back->cSet->sprite.setColor(Color(255, 255, 255));
			}
		);

	}
}

void Game::run()
{
	while (m_running)
	{
		float dt = m_clock.restart().asSeconds();

		sUserInput(); // Always process input (so you can pause/unpause)

		if (!m_paused)
		{
			sMovement(dt);
			sRender(dt);
			TowerAttack();
			sCollision();

			if (m_state == AppState::Map1 || m_state == AppState::Map2 || m_state == AppState::Map3 || m_state == AppState::Map4)
			{
				sCheckWaveFinished();
				sSpawnWave(dt);
			}
		}
		else
		{
			// Optionally, render a pause overlay here
			sRender(dt); // You may want to show a "Paused" message
		}
	}
}


// --- Vẽ hình ảnh lên màn hình ---
void Game::sRender(float& deltaTime)
{
	m_window.clear();

	// Hiển thị tổng
	for (auto& e : m_scenes[m_state].getEntities())
	{
		if (e->cSet && e->cPosition)
			e->cSet->sprite.setPosition(e->cPosition->position);

		if (e->tag() == "Base")
		{
			if (e->isActive())
				m_window.draw(e->cSet->sprite);
		}
		else
		{
			if (e->cSet)
				m_window.draw(e->cSet->sprite);
		}
	}

	if (game_state == AppState::GamePlay)
	{
		for (auto& e : m_scenes[game_state].getEntities())
		{
			if (!e->cSet || !e->cPosition)
				continue;

			e->cSet->sprite.setPosition(e->cPosition->position);

			// Nếu là trái tim (máu), chỉ vẽ nếu còn active
			if (e->tag() == "Heart")
			{
				if (e->isActive())
					m_window.draw(e->cSet->sprite);
			}
			else
			{
				// Các entity khác vẽ bình thường
				m_window.draw(e->cSet->sprite);
			}

			for (auto& e : m_scenes[AppState::GamePlay].getEntities("MoneyText"))
			{
				e->cText->text.setString(to_string(m_coin[m_mapindex]));

				if (e->cText)
					m_window.draw(e->cText->text);
			}

			if (m_showWaveText)
			{
				for (auto& e : m_scenes[AppState::GamePlay].getEntities("WaveText"))
				{
					if (e->cText)
						m_window.draw(e->cText->text);
				}
				for (auto& e : m_scenes[AppState::GamePlay].getEntities("WaveNumber"))
				{
					e->cText->text.setString(to_string(m_currentWave[m_mapindex] + 1));

					if (e->cText)
						m_window.draw(e->cText->text);
				}

				if (m_waveClock.getElapsedTime().asSeconds() > m_waveDisplayDuration)
				{
					m_showWaveText = false;
				}
			}
		}
	}

	// Hiển thị quái và đạn
	for (auto& e : m_entities.getEntities())
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

	// Hiển thị chọn tháp
	if (m_state1 != AppState::Dummy)
	{
		for (auto& e : m_scenes[m_state1].getEntities())
		{
			if (e->cSet && e->cPosition)
				e->cSet->sprite.setPosition(e->cPosition->position);

			if(e->cSet)
			   m_window.draw(e->cSet->sprite);
			if (e->cText)
				m_window.draw(e->cText->text);

			if (e->cSlider) 
			{
				m_window.draw(e->cSlider->track);
				m_window.draw(e->cSlider->handle);
			}
		}
	}

	// Hiển thị nhập tên
	if (m_typingName)
	{
		Vector2f panelCenter(m_windowConfig.width / 2.f, m_windowConfig.height / 2.f);

		m_inputLabel.setPosition(panelCenter.x, panelCenter.y - 50);
		m_inputText.setPosition(panelCenter.x, panelCenter.y);

		FloatRect textRect = m_inputLabel.getLocalBounds();
		m_inputLabel.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
		textRect = m_inputText.getLocalBounds();
		m_inputText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

		m_window.draw(m_inputLabel);
		m_window.draw(m_inputText);
	}

	m_window.display();
}


// --- Xử lý input từ người dùng ---
void Game::sUserInput()
{
	Event event;
	Vector2f mousePos = m_window.mapPixelToCoords(Mouse::getPosition(m_window));

	while (m_window.pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			m_running = false;
			m_window.close();
		}

		// --- Input cho SettingsMenu (Slider + Icon)
		if (m_state1 == AppState::SettingsMenu)
		{
			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
			{
				for (auto& e : m_scenes[m_state1].getEntities())
				{
					if (e->cSlider &&
						(e->cSlider->track.getGlobalBounds().contains(mousePos) || e->cSlider->handle.getGlobalBounds().contains(mousePos)))
					{
						e->cSlider->isDragging = true;

						if (e->tag() == "MusicSlider" && m_musicMuted)
						{
							m_musicMuted = false;
							m_scenes[m_state].getEntities("MusicIcon").front()->cSet->texture.loadFromFile("IMGS/music_on.png");
						}
						else if (e->tag() == "SfxSlider" && m_sfxMuted)
						{
							m_sfxMuted = false;
							m_scenes[m_state].getEntities("SfxIcon").front()->cSet->texture.loadFromFile("IMGS/sfx_on.png");
						}

						e->cSlider->updateValueFromHandle(mousePos.x);
						updateAudioSettings();
						break;
					}
				}
			}

			if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
			{
				for (auto& e : m_scenes[m_state1].getEntities())
				{
					if (e->cSlider && e->cSlider->isDragging)
						e->cSlider->isDragging = false;
				}
			}

			if (event.type == Event::MouseMoved)
			{
				for (auto& e : m_scenes[m_state1].getEntities())
				{
					if (e->cSlider && e->cSlider->isDragging)
					{
						e->cSlider->updateValueFromHandle(mousePos.x);
						updateAudioSettings();
					}
				}
			}
		}

		// --- Input cho NameInput (gõ tên)
		if(m_typingName)
		{
			if (event.type == Event::TextEntered)
			{
				if (event.text.unicode == '\b' && !m_playerName.empty())
				{
					m_playerName.pop_back();
				}
				else if (event.text.unicode == '\r' || event.text.unicode == '\n')
				{
					if (!m_playerName.empty())
					{
						sSaveGame();
						m_state = AppState::MapSelect;
					}
				}
				else if (event.text.unicode >= 32 && event.text.unicode < 128)
				{
					m_playerName += static_cast<char>(event.text.unicode);
				}
				m_inputText.setString(m_playerName);
			}
		}

		// --- Click chuột trái
		if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
		{
			bool clickedSlider = false;

			if (m_state == AppState::SettingsMenu)
			{
				for (auto& e : m_scenes[m_state].getEntities())
				{
					if (e->cSlider && e->cSlider->isDragging)
					{
						clickedSlider = true;
						break;
					}
				}
			}

			if (!clickedSlider)
			{
				// Ưu tiên state2 nếu đang chọn tower

				if (m_state2 == AppState::TowerPlace)
				{
					bool placed = false;

					for (auto& e : m_scenes[m_state].getEntities("Base"))
					{
						if (e->isActive() && e->cSet->sprite.getGlobalBounds().contains(mousePos))
						{
							e->active(false);
							placed = true;
							break;
						}
					}

					if (placed)
					{
						for (auto& e : m_entities.getEntities(m_selected))
						{
							if (!e->isActive())
							{
								e->active(true);
								e->cPosition = make_shared<CPosition>(mousePos);
								e->cSet->sprite.setPosition(e->cPosition->position);
								break; 
							}
						}
					}

					m_state2 = AppState::Dummy;
				}
				else
				{
					// Xử lý click cho m_state1 nếu đang hiện overlay chọn tháp

					AppState stateToHandle = m_state;
					if (m_state1 != AppState::Dummy)
						stateToHandle = m_state1;
					else if (game_state != AppState::Dummy)
						stateToHandle = game_state;

					if (stateToHandle == AppState::TowerSelect)
					{
						bool isOutSide = true;
						for (auto& e : m_scenes[stateToHandle].getEntities())
						{
							if (e->cSet && e->cSet->sprite.getGlobalBounds().contains(mousePos))
							{
								if (e->cInput)
								{
									playSfx(m_clickBuffer);
									e->cInput->onClick();
									isOutSide = false;
									break;
								}
								isOutSide = false;
							}
						}
						if (isOutSide)
							m_state1 = AppState::Dummy;
					}
					else
					{
						for (auto& e : m_scenes[stateToHandle].getEntities())
						{
							if (e->cSet && e->cInput && e->cSet->sprite.getGlobalBounds().contains(mousePos))
							{
								playSfx(m_clickBuffer);
								e->cInput->onClick();
								return;
							}
						}
					}
				}
			}
		}

		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == Keyboard::P) // or Escape
			{
				m_paused = !m_paused;
			}
		}
	}

	// --- Hover Detection
	AppState hoverState = m_state;

	if (m_state1 != AppState::Dummy && m_state2 == AppState::Dummy)
		hoverState = m_state1;
	else if (m_state2 != AppState::Dummy)
		hoverState = m_state2;
	else if (game_state != AppState::Dummy)
		hoverState = game_state;

	for (auto& e : m_scenes[hoverState].getEntities())
	{
		if (e->cSet && e->cInput)
		{
			bool hovering = e->cSet->sprite.getGlobalBounds().contains(mousePos);

			if (hovering && !e->cInput->isHovered && e->cInput->onHover)
				e->cInput->onHover();
			else if (!hovering && e->cInput->isHovered && e->cInput->offHover)
				e->cInput->offHover();

			e->cInput->isHovered = hovering;
		}
	}
}


// --- Lưu tên người chơi khi nhập ở PlayMenu ---
void Game::sSaveGame()
{
	// Thêm bước kiểm tra trùng tên
	//
	//
	//
	//
	// 
	// 
	// 
	//
	///////////////////////////////

	ofstream writePlayer(m_playerName + ".txt");

	if (writePlayer.is_open())
	{
		// Lưu wave
		writePlayer << "# Current wave index: " << "\n";
		for (int i = 0; i < m_currentWave.size(); i++)
		{
			writePlayer << m_currentWave[i] << " ";
		}
		writePlayer << "\n";


		// Lưu index của máu còn lại
		writePlayer << "# Remaining health: " << "\n";
		for (int i = 0; i < m_health.size(); i++)
		{
			for (int j = 0; j < m_health[i].size(); j++)
			{
				writePlayer << m_health[i][j] << " ";
			}
			writePlayer << "\n";
		}


		// Lưu tiền
		writePlayer << "# Money: " << "\n";
		for (int i = 0; i < m_coin.size(); i++)
		{
			writePlayer << m_coin[i] << " ";
		}
		writePlayer << "\n";


		// Lưu vị trí tháp
		writePlayer << "# Tower position" << "\n";
		for (auto& entity : m_entities.getEntities(m_towerType1Config.tag))
		{
			if (entity->isActive())
			{
				writePlayer << entity->id() << " " << entity->cPosition->position.x << " " << entity->cPosition->position.y << "\n";
			}
		}
		//
		//
		//
		//
		////////////////
	}

	m_typingName = false;
}

void Game::sLoadGame()
{
	ifstream readPlayer(m_playerName + ".txt");

	if (!readPlayer.is_open())
	{
		// Thêm hiển thị thông báo trên màn hình nếu cần
		//
		//
		//
		//
		//
		////////////////////////////////////////////////

		cout << "Can't open file or file doesn't exist!" << endl;
		return;
	}

	string line;

	while (getline(readPlayer, line)) {
		if (line.empty() || line[0] == '#') continue;
		istringstream iss(line);

		// Load màn chơi
		for (int i = 0; i < m_currentWave.size(); i++)
		{
			iss >> m_currentWave[i];
		}


		// Load máu
		for (int i = 0; i < m_health.size(); i++)
		{
			for (int j = 0; j < m_health[i].size(); j++)
			{
				iss >> m_health[i][j];
			}
		}


		// Load tiền
		for (int i = 0; i < m_coin.size(); i++)
		{
			iss >> m_coin[i];
		}


		// Đọc tháp
		//
		//
		//
		//
		//
		//////////

		break;
	}
}

// --- Reset quái, tháp và đạn khi thoát game ---
void Game::sReset()
{
	// Reset quái
	for (auto& enemy : m_entities.getEntities("Enemy"))
		DeactivateEnemy(*enemy);

	m_finishWave = true;
	m_spawnStage = SpawnStage::None;

	// Reset tháp
	for (auto& tower : m_entities.getEntities("Tower"))
		DeactivateTower(*tower);

	// Reset đạn
	for (auto& bullet : m_entities.getEntities("Bullet"))
		DeactivateBullet(*bullet);

	for (auto& base : m_scenes[prev_state].getEntities("Base"))
	{
		if (!base->isActive())
			base->active(true);
	}

	// Reset máu
	for (auto& heart : m_scenes[AppState::GamePlay].getEntities("Heart"))
	{
		if (!heart->isActive())
			heart->active(true);
	}

	// Reset wave
	m_showWaveText = false;
	m_finishWave = false;
	m_paused = false;
}


// --- Di chuyển và hoạt họa ---
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
	for (auto& entity : m_entities.getEntities())
	{
		if (!entity->isActive() || !entity->cMovement || !entity->cPosition) continue;

		// Chuyển động đạn
		if (entity->tag().find("Bullet") != std::string::npos)
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

		// Chuyển động quái
		else if (entity->tag().find("Enemy") != std::string::npos)
		{
			// Nếu như quái đi hết đường đi
			if (entity->cMovement->currentPathindex >= entity->cMovement->paths[m_mapindex].size())
			{
				auto heartvector = m_scenes[AppState::GamePlay].getEntities("Heart");
				int vecindex = 4;
				int index = static_cast<int>(heartvector.size()) - 1;

				// Tìm trái tim cuối cùng còn active
				while (index >= 0 && !heartvector[index]->isActive())
				{
					index--;
					vecindex--;
				}

				if (heartvector.size() - index == 5)
				{
					m_window.close();
					// LOSE
					//
					//
					//
					///////
				}
				else
				{
					heartvector[index]->active(false); 
					m_health[m_mapindex][vecindex] = 0;
				}

				DeactivateEnemy(*entity);
				continue; 
			}

			// Tính toán đường đi đến điểm tiếp theo
			Vector2f target = entity->cMovement->paths[m_mapindex][entity->cMovement->currentPathindex];
			Vector2f direction = target - entity->cPosition->position;
			float distance = MathSupport::Length(direction);
			

			// Kiểm tra xem nếu đủ gần điểm thì chuyển tiếp điểm khác
			if (distance < 5.f) 
			{
				entity->cMovement->currentPathindex++;
			}
			else
			{
				// Di chuyển quái đến điểm
				Vector2f movement = MathSupport::Normalize(direction);
				entity->cPosition->position += movement * entity->cMovement->speed * deltaTime;

				// Lật sprite theo hướng di chuyển
				float baseScale = 1.f;

				if (entity->cSpriteScale) baseScale = entity->cSpriteScale->scale;

				// Tính toán để dự đoán hướng quay mặt tiếp theo
				int currentIndex = entity->cMovement->currentPathindex;
				int nextIndex = currentIndex + 1;

				if (nextIndex < (int)entity->cMovement->paths[m_mapindex].size())
				{
					Vector2f currentTarget = entity->cMovement->paths[m_mapindex][currentIndex];
					Vector2f nextTarget = entity->cMovement->paths[m_mapindex][nextIndex];

					float dx = nextTarget.x - currentTarget.x;

					if (dx < -0.1f)
						entity->cSet->sprite.setScale(-baseScale, baseScale);
					else if (dx > 0.1f)
						entity->cSet->sprite.setScale(baseScale, baseScale);  
				}
				else
				{
					if (movement.x < -0.1f)
						entity->cSet->sprite.setScale(-baseScale, baseScale);
					else if (movement.x > 0.1f)
						entity->cSet->sprite.setScale(baseScale, baseScale);
				}
			}

			// Cập nhật hình ảnh và vị trí
			entity->cSet->sprite.setPosition(entity->cPosition->position);
		}
	}
}


// --- Chỉnh sửa kích thước cửa sổ ---
void Game::playSfx(const sf::SoundBuffer& buffer, sf::Vector2f position) {
	if (m_sfxMuted) return;
	m_activeSounds.remove_if([](const sf::Sound& s) { return s.getStatus() == Sound::Stopped; });
	Sound& newSound = m_activeSounds.emplace_back();
	newSound.setBuffer(buffer);
	newSound.setVolume(m_sfxVolume);
	newSound.play();
}

void Game::onResize(const sf::Event::SizeEvent& size) {
	m_view.setSize(m_windowConfig.width, m_windowConfig.height);
	m_view.setCenter(m_windowConfig.width / 2.f, m_windowConfig.height / 2.f);
	float windowRatio = static_cast<float>(size.width) / static_cast<float>(size.height);
	float viewRatio = static_cast<float>(m_windowConfig.width) / static_cast<float>(m_windowConfig.height);
	float sizeX = 1.0f, sizeY = 1.0f, posX = 0.0f, posY = 0.0f;
	if (windowRatio > viewRatio) {
		sizeX = viewRatio / windowRatio;
		posX = (1.0f - sizeX) / 2.0f;
	}
	else {
		sizeY = windowRatio / viewRatio;
		posY = (1.0f - sizeY) / 2.0f;
	}
	m_view.setViewport(sf::FloatRect(posX, posY, sizeX, sizeY));
	m_window.setView(m_view);
}


// --- Âm thanh và Xử lý sự kiện ---
void Game::updateAudioSettings() {
	if (m_musicMuted) {
		m_backgroundMusic.setVolume(0);
	}
	else {
		m_backgroundMusic.setVolume(m_musicVolume);
	}
}


// --- Spawn quái ---
void Game::sCheckWaveFinished()
{
	if (m_finishWave) return;

	bool allInactive = true;

	for (auto& e : m_entities.getEntities(m_enemyType1Config.tag))
	{
		if (e->isActive())
		{
			allInactive = false;
			break;
		}
	}

	for (auto& e : m_entities.getEntities(m_enemyType2Config.tag))
	{
		if (e->isActive())
		{
			allInactive = false;
			break;
		}
	}

	for (auto& e : m_entities.getEntities(m_enemyType3Config.tag))
	{
		if (e->isActive())
		{
			allInactive = false;
			break;
		}
	}

	if (allInactive)
	{
		m_currentWave[m_mapindex]++;
		cout << "Spawning wave right now" << endl;
		m_finishWave = true;
		m_showWaveText = true;
		m_waveClock.restart();
		sSaveGame();
	}
}

void Game::sSpawnWave(float& deltaTime)
{
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
	WaveConfig& wave = m_waveConfigs[m_mapindex][m_currentWave[m_mapindex]];

	m_spawningTimer += deltaTime;

	if (type == 1)
	{
		if (m_spawnedType1 >= wave.enemyType1Count) return true;

		for (auto& e : m_entities.getEntities(m_enemyType1Config.tag))
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

		for (auto& e : m_entities.getEntities(m_enemyType2Config.tag))
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

		for (auto& e : m_entities.getEntities(m_enemyType3Config.tag))
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


// --- Tháp bắn quái ---
void Game::Shoot(Entity& tower)
{
	if (!tower.cTarget) { return; }

	for (auto& bullet : m_entities.getEntities(tower.cWeapon->tag))
	{
		if (!bullet->isActive())
		{
			bullet->cPosition = make_shared<CPosition>(tower.cPosition->position);

			bullet->cSet->sprite.setPosition(tower.cPosition->position);
			cout << "fire\n";

			bullet->active(true);

			Vector2f direction = tower.cTarget->cPosition->position - tower.cPosition->position;
			Vector2f normalized_direction = MathSupport::Normalize(direction);

			if (tower.cWeapon->tag == "Bullet01")
				bullet->cMovement->velocity = normalized_direction * m_bullet01Config.speed;
			else if (tower.cWeapon->tag == "Bullet02")
				bullet->cMovement->velocity = normalized_direction * m_bullet02Config.speed;

			break;
		}
	}
}

void Game::TowerAttack()
{
	for (auto& curTower : m_entities.getEntities("Tower"))
	{

		if (curTower->isActive() && curTower->cCooldown->shootClock.getElapsedTime().asSeconds() >= curTower->cCooldown->cooldownDuration.asSeconds())
		{
			shared_ptr<Entity> closestEnemy = nullptr;
			float minDistance = curTower->cBound->radius;

			for (auto& enemy : m_entities.getEntities("Enemy"))
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


// --- Reset dữ liệu ---
void Game::DeactivateEnemy(Entity& enemy)
{
	if (!enemy.isActive())
	{
		return;
	}

	enemy.active(false);

	// Reset máu
	if (!enemy.cHealth)
	{
		if (enemy.tag() == "EnemyType1")
		{
			enemy.cHealth->hp = m_enemyType1Config.hp;
		}
		else if (enemy.tag() == "EnemyType2")
		{
			enemy.cHealth->hp = m_enemyType2Config.hp;
		}
		else if (enemy.tag() == "EnemyType3")
		{
			enemy.cHealth->hp = m_enemyType3Config.hp;
		}
	}

	// Reset chuyển động
	if (enemy.cMovement)
	{
		enemy.cMovement->currentPathindex = 0;
	}

	// Reset vị trí
	if (enemy.cPosition)
	{
		enemy.cPosition->position = Vector2f(-100, -100);
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
		tower.cPosition = nullptr; // Off-screen or default position

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
		bullet.cPosition->position = Vector2f(-100.f, -100.f);
}


// support collision logic 
bool isContained(const sf::FloatRect& inner, const sf::FloatRect& outer) 
{
	// Check all four corners of the inner rectangle
	return outer.contains(inner.left, inner.top) &&
		outer.contains(inner.left + inner.width, inner.top) &&
		outer.contains(inner.left, inner.top + inner.height) &&
		outer.contains(inner.left + inner.width, inner.top + inner.height);
}

FloatRect scaleRect(const FloatRect& rect, float scale = 1.0f) 
{
	float newWidth = rect.width * scale;
	float newHeight = rect.height * scale;
	float centerX = rect.left + rect.width / 2.f;
	float centerY = rect.top + rect.height / 2.f;
	return FloatRect(
		centerX - newWidth / 2.f,
		centerY - newHeight / 2.f,
		newWidth,
		newHeight
	);
}


// --- Check collision ---
bool collisionDetection(const Entity& entity1, const Entity& entity2)
{
	if (!entity1.cSet || !entity2.cSet) return false;
	FloatRect bounds1 = scaleRect(entity1.cSet->sprite.getGlobalBounds(), entity2.cBoundaryScale->scale / 100.0f);
	FloatRect bounds2 = scaleRect(entity2.cSet->sprite.getGlobalBounds(), entity2.cBoundaryScale->scale / 100.0f);
	//return bounds1.intersects(bounds2);
	return isContained(bounds1, bounds2);
}


// process collision 
void Game::sCollision()
{
	for (auto& cur : m_entities.getEntities("Enemy"))
	{
		if (!cur->isActive()) continue;

		for (auto& bullet : m_entities.getEntities("Bullet"))
		{
			if (!bullet->isActive()) continue;
			if (collisionDetection(*bullet, *cur))
			{
			std:cout << "Bump\n";
				if (cur->cHealth)
				{
					cur->cHealth->hp -= bullet->cDamage->damage;
					if (cur->cHealth->hp <= 0)
					{
						m_coin[m_mapindex] += cur->cMoney->money;
						DeactivateEnemy(*cur);
					}
				}
				DeactivateBullet(*bullet);
			}
		}
	}
}
