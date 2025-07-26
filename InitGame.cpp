#include "Game.h"

// --- Hàm game chính ---
Game::Game(const string& config)
{
	init(config);
}

void clearFile(std::string fileName)
{
	std::ofstream file(fileName, std::ios::out | std::ios::trunc);
	if (!file) {
		std::cout << "Error opening file\n";
	}
	file.close();
}


// --- Đọc file config.txt ---
void Game::init(const string& path)
{
	ifstream readconfig(path);
	string line;

	// --- Đọc config window
	{
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
	}

	// ===================== ĐẠN =====================

	// --- Đọc config đạn loại 1
	{
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
	}

	// --- Đọc config đạn loại 2
	{
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
	}

	// ===================== QUÁI =====================

	// --- Đọc config quái loại 1
	{
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
	}

	// --- Đọc config quái loại 2
	{
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
				sprite.setOrigin(sprite.getLocalBounds().width / 2.f, (sprite.getLocalBounds().height / 2.f));
			}

			break;
		}
	}

	// --- Đọc config quái loại 3
	{
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
				sprite.setOrigin(sprite.getLocalBounds().width / 2.f, (sprite.getLocalBounds().height / 2.f));
			}

			break;
		}
	}

	// ===================== THÁP =====================

	// --- Đọc config tháp loại 1
	{
		while (getline(readconfig, line))
		{
			if (line.empty() || line[0] == '#') continue;
			istringstream iss(line);
			Vector2u imgCount;
			float switchTime, range, cooldown;
			int amount;
			iss >> m_towerType1Config.tag >> m_towerType1Config.filepath >> imgCount.x >> imgCount.y >> switchTime >> range >> cooldown >> amount >> m_towerType1Config.cost;

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
	}

	// --- Đọc config tháp loại 2
	{
		while (getline(readconfig, line))
		{
			if (line.empty() || line[0] == '#') continue;
			istringstream iss(line);
			Vector2u imgCount;
			float switchTime, range, cooldown;
			int amount;
			iss >> m_towerType2Config.tag >> m_towerType2Config.filepath >> imgCount.x >> imgCount.y >> switchTime >> range >> cooldown >> amount >> m_towerType2Config.cost;;

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
	}

	// --- Đọc config tháp loại 3
	{
		while (getline(readconfig, line))
		{
			if (line.empty() || line[0] == '#') continue;
			istringstream iss(line);
			Vector2u imgCount;
			float switchTime, range, cooldown;
			int amount;
			iss >> m_towerType3Config.tag >> m_towerType3Config.filepath >> imgCount.x >> imgCount.y >> switchTime >> range >> cooldown >> amount >> m_towerType3Config.cost;;

			for (int i = 0; i < amount; i++)
			{
				auto entity = m_entities.addEntity(m_towerType3Config.tag);
				entity->cSet = make_shared<CSet>(m_towerType3Config.filepath, imgCount, switchTime, 0);
				entity->cCooldown = make_shared<CCooldown>(cooldown);
				entity->cBound = make_shared<CBound>(range);
				entity->cWeapon = make_shared<CWeapon>("Bullet01");
				auto& sprite = entity->cSet->sprite;
				sprite.setScale(0.5, 0.5);
				sprite.setOrigin(sprite.getLocalBounds().width / 2.f, (sprite.getLocalBounds().height / 2.f) + 60.0);
			}
			break;
		}
	}

	// --- Đọc config tháp loại 4
	{
		while (getline(readconfig, line))
		{
			if (line.empty() || line[0] == '#') continue;
			istringstream iss(line);
			Vector2u imgCount;
			float switchTime, range, cooldown;
			int amount;
			iss >> m_towerType4Config.tag >> m_towerType4Config.filepath >> imgCount.x >> imgCount.y >> switchTime >> range >> cooldown >> amount >> m_towerType4Config.cost;;

			for (int i = 0; i < amount; i++)
			{
				auto entity = m_entities.addEntity(m_towerType4Config.tag);
				entity->cSet = make_shared<CSet>(m_towerType4Config.filepath, imgCount, switchTime, 0);
				entity->cCooldown = make_shared<CCooldown>(cooldown);
				entity->cBound = make_shared<CBound>(range);
				entity->cWeapon = make_shared<CWeapon>("Bullet01");
				auto& sprite = entity->cSet->sprite;
				sprite.setOrigin(sprite.getLocalBounds().width / 2.f, (sprite.getLocalBounds().height / 2.f) + 20.0);
			}
			break;
		}
	}

	// --- Đọc config tháp loại 5
	{
		while (getline(readconfig, line))
		{
			if (line.empty() || line[0] == '#') continue;
			istringstream iss(line);
			Vector2u imgCount;
			float switchTime, range, cooldown;
			int amount;
			iss >> m_towerType5Config.tag >> m_towerType5Config.filepath >> imgCount.x >> imgCount.y >> switchTime >> range >> cooldown >> amount >> m_towerType5Config.cost;

			for (int i = 0; i < amount; i++)
			{
				auto entity = m_entities.addEntity(m_towerType5Config.tag);
				entity->cSet = make_shared<CSet>(m_towerType5Config.filepath, imgCount, switchTime, 0);
				entity->cCooldown = make_shared<CCooldown>(cooldown);
				entity->cBound = make_shared<CBound>(range);
				entity->cWeapon = make_shared<CWeapon>("Bullet01");
				auto& sprite = entity->cSet->sprite;
				sprite.setOrigin(sprite.getLocalBounds().width / 2.f, (sprite.getLocalBounds().height / 2.f) + 20.0);
			}
			break;
		}
	}

	// --- Đọc config tháp loại 6
	{
		while (getline(readconfig, line))
		{
			if (line.empty() || line[0] == '#') continue;
			istringstream iss(line);
			Vector2u imgCount;
			float switchTime, range, cooldown;
			int amount;
			iss >> m_towerType6Config.tag >> m_towerType6Config.filepath >> imgCount.x >> imgCount.y >> switchTime >> range >> cooldown >> amount >> m_towerType6Config.cost;;

			for (int i = 0; i < amount; i++)
			{
				auto entity = m_entities.addEntity(m_towerType6Config.tag);
				entity->cSet = make_shared<CSet>(m_towerType6Config.filepath, imgCount, switchTime, 0);
				entity->cCooldown = make_shared<CCooldown>(cooldown);
				entity->cBound = make_shared<CBound>(range);
				entity->cWeapon = make_shared<CWeapon>("Bullet02");
				auto& sprite = entity->cSet->sprite;
				sprite.setScale(0.5, 0.5);
				sprite.setOrigin(sprite.getLocalBounds().width / 2.f, (sprite.getLocalBounds().height / 2.f) + 80.0);
			}
			break;
		}
	}

	// ===================== WAVE =====================

	// --- Đọc config từng wave
	{
		while (getline(readconfig, line)) {
			if (line.empty() || line[0] == '#') continue;
			istringstream iss(line);
			string skip;
			int wave, mapIndex, type1, type2, type3;

			iss >> skip >> wave >> mapIndex >> type1 >> type2 >> type3;

			m_waveConfigs[mapIndex][wave - 1] = { type1 , type2 , type3 };
		}
	}


	readconfig.close();

	initUIFlow();
	loadHeartCoin();
	loadFontText();
}


// --- Load những thứ cần thiết cho game ---
void Game::loadHeartCoin()
{
	// --- Khởi tạo máu người chơi
	for (int i = 0; i < 5; i++)
	{
		auto entity = m_scenes[AppState::GamePlay].addEntity("Heart");
		entity->cSet = make_shared<CSet>("IMGS/GUI/Heart.png");
		entity->cBoundaryScale = make_shared<CBoundaryScale>(0.1);
		entity->active(true);
		auto& sprite = entity->cSet->sprite;
		sprite.setScale(entity->cBoundaryScale->scale, entity->cBoundaryScale->scale);
		entity->cPosition = make_shared<CPosition>(Vector2f(i * sprite.getGlobalBounds().width, 0));
	}


	// --- Khởi tạo tiền
	auto coin = m_scenes[AppState::GamePlay].addEntity("Coin");
	coin->cSet = make_shared<CSet>("IMGS/GUI/Coin.png");
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
}

void Game::loadFontText()
{
	// -- Khởi tạo font chữ
	if (!m_font.loadFromFile("IMGS/Fonts/ARCADECLASSIC.ttf")) {
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

	if (!m_constructTower.loadFromFile("SOUNDS/Constructing.mp3"))
	{
		cout << "Error: Could not load construct sound file.\n";
	}

	if (!m_error.loadFromFile("SOUNDS/Error.mp3"))
	{
		cout << "Error: Could not load error sound file.\n";
	}

	m_inputLabel.setFont(m_font);
	m_inputLabel.setCharacterSize(24);
	m_inputLabel.setFillColor(Color::Black);
	m_inputLabel.setString("Enter your name");
	m_inputLabel.setPosition(500, 250);

	m_inputText.setFont(m_font);
	m_inputText.setCharacterSize(24);
	m_inputText.setFillColor(Color::Yellow);
	m_inputText.setPosition(500, 300);


	// -- Hiển thị giá tiền cho từng tháp
	auto Tower1Cost = m_scenes[AppState::TowerSelect].addEntity("Tower1Cost");
	Tower1Cost->cText = make_shared<CText>(m_towerType1Config.cost);
	Tower1Cost->cText->text.setFont(m_font);
	Tower1Cost->cText->text.setPosition(Vector2f(1760, 110));
	Tower1Cost->cText->text.setCharacterSize(20);
	Tower1Cost->cText->text.setFillColor(sf::Color::Yellow);

	auto Tower2Cost = m_scenes[AppState::TowerSelect].addEntity("Tower2Cost");
	Tower2Cost->cText = make_shared<CText>(m_towerType2Config.cost);
	Tower2Cost->cText->text.setFont(m_font);
	Tower2Cost->cText->text.setPosition(Vector2f(1850, 110));
	Tower2Cost->cText->text.setCharacterSize(20);
	Tower2Cost->cText->text.setFillColor(sf::Color::Yellow);

	auto Tower3Cost = m_scenes[AppState::TowerSelect].addEntity("Tower3Cost");
	Tower3Cost->cText = make_shared<CText>(m_towerType3Config.cost);
	Tower3Cost->cText->text.setFont(m_font);
	Tower3Cost->cText->text.setPosition(Vector2f(1760, 260));
	Tower3Cost->cText->text.setCharacterSize(20);
	Tower3Cost->cText->text.setFillColor(sf::Color::Yellow);

	auto Tower4Cost = m_scenes[AppState::TowerSelect].addEntity("Tower4Cost");
	Tower4Cost->cText = make_shared<CText>(m_towerType4Config.cost);
	Tower4Cost->cText->text.setFont(m_font);
	Tower4Cost->cText->text.setPosition(Vector2f(1850, 260));
	Tower4Cost->cText->text.setCharacterSize(20);
	Tower4Cost->cText->text.setFillColor(sf::Color::Yellow);

	auto Tower5Cost = m_scenes[AppState::TowerSelect].addEntity("Tower5Cost");
	Tower5Cost->cText = make_shared<CText>(m_towerType5Config.cost);
	Tower5Cost->cText->text.setFont(m_font);
	Tower5Cost->cText->text.setPosition(Vector2f(1760, 410));
	Tower5Cost->cText->text.setCharacterSize(20);
	Tower5Cost->cText->text.setFillColor(sf::Color::Yellow);

	auto Tower6Cost = m_scenes[AppState::TowerSelect].addEntity("Tower6Cost");
	Tower6Cost->cText = make_shared<CText>(m_towerType6Config.cost);
	Tower6Cost->cText->text.setFont(m_font);
	Tower6Cost->cText->text.setPosition(Vector2f(1850, 410));
	Tower6Cost->cText->text.setCharacterSize(20);
	Tower6Cost->cText->text.setFillColor(sf::Color::Yellow);


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
	numEntity->cText = make_shared<CText>(to_string(m_currentWave));
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
}

void Game::initUIFlow()
{
	// -- Chọn map
	{
		ifstream readMapBase("MapBase.txt");
		string line;

		string tag, filepath;
		Vector2f Base;
		int base_amount{};


		// Map 1
		auto entity = m_scenes[AppState::Map1].addEntity("Map1");
		entity->cSet = make_shared<CSet>("IMGS/Maps/map1.png");

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


		// Map 2
		entity = m_scenes[AppState::Map2].addEntity("Map2");
		entity->cSet = make_shared<CSet>("IMGS/Maps/map2.png");

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


		// Map 3
		entity = m_scenes[AppState::Map3].addEntity("Map3");
		entity->cSet = make_shared<CSet>("IMGS/Maps/map3.png");
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


		// Map 4
		entity = m_scenes[AppState::Map4].addEntity("Map4");
		entity->cSet = make_shared<CSet>("IMGS/Maps/map4.png");
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

			entity = m_scenes[AppState::Map4].addEntity(tag);
			entity->cSet = make_shared<CSet>(filepath);
			entity->cPosition = make_shared<CPosition>(Base);
			entity->active(true);
		}
		readMapBase.close();

		// -- OptionMenu --
		{

			entity = m_scenes[AppState::OptionMenu].addEntity("OptionBoard");
			entity->cSet = make_shared<CSet>("IMGS/GUI/optionBoard.png");
			entity->cPosition = make_shared<CPosition>(Vector2f(m_windowConfig.width / 2.f, m_windowConfig.height / 2.f));
			entity->cSet->sprite.setOrigin(entity->cSet->sprite.getLocalBounds().width / 2.f, entity->cSet->sprite.getLocalBounds().height / 2.f);

			entity = m_scenes[AppState::OptionMenu].addEntity("Title");
			entity->cText = make_shared<CText>("OPTIONS");
			entity->cText->text.setFont(m_font);
			entity->cText->text.setCharacterSize(60);
			entity->cText->text.setFillColor(Color::Black);
			entity->cText->text.setPosition(Vector2f(839, 273));

			entity = m_scenes[AppState::OptionMenu].addEntity("Resume");
			entity->cSet = make_shared<CSet>("IMGS/Buttons/play.png");
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
			entity->cSet = make_shared<CSet>("IMGS/Buttons/setting.png");
			entity->cPosition = make_shared<CPosition>(Vector2f(839, 539));
			entity->cSet->sprite.setScale(0.6f, 0.6f);
			entity->cInput = make_shared<CInput>([this]()
				{
					//sSaveGame();
					queueSave();
					std::this_thread::sleep_for(std::chrono::milliseconds(50));
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
			entity->cSet = make_shared<CSet>("IMGS/Buttons/quit.png");
			entity->cPosition = make_shared<CPosition>(Vector2f(839, 672));
			entity->cSet->sprite.setScale(0.6f, 0.6f);
			entity->cInput = make_shared<CInput>([this]()
				{
					prev_state = m_state;
					m_state = AppState::PlayMenu;
					game_state = AppState::Dummy;
					m_state1 = AppState::Dummy;
					m_playerName.clear();
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
		}


		// Khởi tạo các chức năng trong game - GamePlay
		entity = m_scenes[AppState::GamePlay].addEntity("OptionSetting");
		entity->cSet = make_shared<CSet>("IMGS/Buttons/Option.png");
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
		entity->cSet = make_shared<CSet>("IMGS/Buttons/Gear.png");
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
		entity->cSet = make_shared<CSet>("IMGS/Buttons/towerSelectButton.png");
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
		entity->cSet = make_shared<CSet>("IMGS/GUI/selectingTower.png");
		entity->cPosition = make_shared<CPosition>(Vector2f(1720, 0));

		entity = m_scenes[AppState::TowerSelect].addEntity("Tower1Button");
		entity->cSet = make_shared<CSet>("IMGS/TowerImages/Tower1Button.png");
		entity->cPosition = make_shared<CPosition>(Vector2f(1735, 30));
		entity->cInput = make_shared<CInput>([this]()
			{
				m_selected = "Tower1";
				m_state2 = AppState::TowerPlace;
				m_cost = m_towerType1Config.cost;
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
		entity->cSet = make_shared<CSet>("IMGS/TowerImages/Tower2Button.png");
		entity->cPosition = make_shared<CPosition>(Vector2f(1825, 30));
		entity->cInput = make_shared<CInput>([this]()
			{
				m_selected = "Tower2";
				m_state2 = AppState::TowerPlace;
				m_cost = m_towerType2Config.cost;
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

		entity = m_scenes[AppState::TowerSelect].addEntity("Tower3Button");
		entity->cSet = make_shared<CSet>("IMGS/TowerImages/Tower3Button.png");
		entity->cPosition = make_shared<CPosition>(Vector2f(1735, 180));
		entity->cInput = make_shared<CInput>([this]()
			{
				m_selected = "Tower3";
				m_state2 = AppState::TowerPlace;
				m_cost = m_towerType3Config.cost;
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

		entity = m_scenes[AppState::TowerSelect].addEntity("Tower4Button");
		entity->cSet = make_shared<CSet>("IMGS/TowerImages/Tower4Button.png");
		entity->cPosition = make_shared<CPosition>(Vector2f(1825, 180));
		entity->cInput = make_shared<CInput>([this]()
			{
				m_selected = "Tower4";
				m_state2 = AppState::TowerPlace;
				m_cost = m_towerType4Config.cost;
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

		entity = m_scenes[AppState::TowerSelect].addEntity("Tower5Button");
		entity->cSet = make_shared<CSet>("IMGS/TowerImages/Tower5Button.png");
		entity->cPosition = make_shared<CPosition>(Vector2f(1735, 330));
		entity->cInput = make_shared<CInput>([this]()
			{
				m_selected = "Tower5";
				m_state2 = AppState::TowerPlace;
				m_cost = m_towerType5Config.cost;
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

		entity = m_scenes[AppState::TowerSelect].addEntity("Tower6Button");
		entity->cSet = make_shared<CSet>("IMGS/TowerImages/Tower6Button.png");
		entity->cPosition = make_shared<CPosition>(Vector2f(1825, 330));
		entity->cInput = make_shared<CInput>([this]()
			{
				m_selected = "Tower6";
				m_state2 = AppState::TowerPlace;
				m_cost = m_towerType6Config.cost;
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
		entity = m_scenes[AppState::TowerSelect].addEntity("Spatula");
		entity->cSet = make_shared<CSet>("IMGS/GUI/Spatula.png");
		entity->cPosition = make_shared<CPosition>(Vector2f(1795, 480));
		entity->cInput = make_shared<CInput>([this]()
			{
				m_selected = "DeleteTower";
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
		bg->cSet = make_shared<CSet>("IMGS/Background/MainMenu.jpg");
		bg->cPosition = make_shared<CPosition>(Vector2f(0, 0));

		auto play = m_scenes[AppState::MainMenu].addEntity("Play");
		play->cSet = make_shared<CSet>("IMGS/Buttons/play.png");
		play->cPosition = make_shared<CPosition>(Vector2f(800, 425));
		play->cSet->sprite.setScale(0.55f, 0.55f);
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
		settingsButton->cSet = make_shared<CSet>("IMGS/Buttons/setting.png");
		settingsButton->cPosition = make_shared<CPosition>(Vector2f(1150, 400));
		settingsButton->cSet->sprite.setScale(0.55f, 0.55f);
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
		exit->cSet = make_shared<CSet>("IMGS/Buttons/quit.png");
		exit->cPosition = make_shared<CPosition>(Vector2f(1500, 400));
		exit->cSet->sprite.setScale(0.55f, 0.55f);
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
		bg->cSet = make_shared<CSet>("IMGS/Background/playchoose.jpg");
		bg->cPosition = make_shared<CPosition>(Vector2f(0, 0));

		auto newGameButton = m_scenes[AppState::PlayMenu].addEntity("New");
		newGameButton->cSet = make_shared<CSet>("IMGS/GUI/dark.png");
		newGameButton->cPosition = make_shared<CPosition>(Vector2f(212, 628));
		newGameButton->cInput = make_shared<CInput>([this]()
			{
				m_playerName.clear();
				clearFile("map1.txt");
				clearFile("map2.txt");
				clearFile("map3.txt");
				clearFile("map4.txt");
				std::cout << "File content cleared successfully\n";
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
		loadGame->cSet = make_shared<CSet>("IMGS/GUI/dark.png");
		loadGame->cPosition = make_shared<CPosition>(Vector2f(1515, 628));
		loadGame->cInput = make_shared<CInput>([this]()
			{
				m_typingName = false;
				m_state = AppState::LoadGame;
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
		back->cSet = make_shared<CSet>("IMGS/Buttons/back.png");
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


	// -- LoadGame --
	{
		auto bg = m_scenes[AppState::LoadGame].addEntity("BG");
		bg->cSet = make_shared<CSet>("IMGS/Background/mainmenu.jpg");
		bg->cPosition = make_shared<CPosition>(Vector2f(0, 0));

		auto back = m_scenes[AppState::LoadGame].addEntity("Back");
		back->cSet = make_shared<CSet>("IMGS/Buttons/back.png");
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

		auto map1 = m_scenes[AppState::LoadGame].addEntity("Map1");
		map1->cSet = make_shared<CSet>("IMGS/Maps/map1.png");
		map1->cPosition = make_shared<CPosition>(Vector2f(358, 267));
		map1->cSet->sprite.setScale(0.25f, 0.25f);
		map1->cInput = make_shared<CInput>([this]()
			{
				m_mapindex = 0;
				m_state = AppState::Map1;
				fileForSave = "map1.txt";
				sLoadGame();
				game_state = AppState::GamePlay;
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

		auto map2 = m_scenes[AppState::LoadGame].addEntity("Map2");
		map2->cSet = make_shared<CSet>("IMGS/Maps/map2.png");
		map2->cPosition = make_shared<CPosition>(Vector2f(1040, 267));
		map2->cSet->sprite.setScale(0.25f, 0.25f);
		map2->cInput = make_shared<CInput>([this]()
			{
				m_mapindex = 1;
				m_state = AppState::Map2;
				fileForSave = "map2.txt";
				sLoadGame();
				game_state = AppState::GamePlay;
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

		auto map3 = m_scenes[AppState::LoadGame].addEntity("Map3");
		map3->cSet = make_shared<CSet>("IMGS/Maps/map3.png");
		map3->cPosition = make_shared<CPosition>(Vector2f(358, 651));
		map3->cSet->sprite.setScale(0.25f, 0.25f);
		map3->cInput = make_shared<CInput>([this]()
			{
				m_mapindex = 2;
				m_state = AppState::Map3;
				fileForSave = "map3.txt";
				sLoadGame();
				game_state = AppState::GamePlay;
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

		auto map4 = m_scenes[AppState::LoadGame].addEntity("Map4");
		map4->cSet = make_shared<CSet>("IMGS/Maps/map4.png");
		map4->cPosition = make_shared<CPosition>(Vector2f(1040, 651));
		map4->cSet->sprite.setScale(0.25f, 0.25f);
		map4->cInput = make_shared<CInput>([this]()
			{
				m_mapindex = 3;
				m_state = AppState::Map4;
				fileForSave = "map4.txt";
				sLoadGame();
				game_state = AppState::GamePlay;
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
	}


	// -- SettingsMenu (Pop-up) --
	{

		auto panel = m_scenes[AppState::SettingsMenu].addEntity("SettingsPanel");
		panel->cSet = make_shared<CSet>("IMGS/GUI/settingmenu.png");
		panel->cPosition = make_shared<CPosition>(Vector2f(m_windowConfig.width / 2.f, m_windowConfig.height / 2.f));
		panel->cSet->sprite.setOrigin(panel->cSet->sprite.getLocalBounds().width / 2.f, panel->cSet->sprite.getLocalBounds().height / 2.f);
		panel->cSet->sprite.setScale(1.5f, 1.5f);

		Vector2f panelCenter = panel->cPosition->position;
		float row1_y = panelCenter.y - 25.f;
		float row2_y = panelCenter.y + 50.f;
		float icon_x = panelCenter.x - 170.f;
		float slider_x = panelCenter.x + 50.f;

		auto musicIcon = m_scenes[AppState::SettingsMenu].addEntity("MusicIcon");
		musicIcon->cSet = make_shared<CSet>("IMGS/Buttons/music_on.png");
		musicIcon->cPosition = make_shared<CPosition>(Vector2f(icon_x, row1_y));
		musicIcon->cSet->sprite.setOrigin(musicIcon->cSet->sprite.getLocalBounds().width / 2.f, musicIcon->cSet->sprite.getLocalBounds().height / 2.f);
		musicIcon->cSet->sprite.setScale(0.1f, 0.1f);
		musicIcon->cInput = make_shared<CInput>([this, musicIcon]() {
			m_musicMuted = !m_musicMuted;
			musicIcon->cSet->texture.loadFromFile(m_musicMuted ? "IMGS/Buttons/music_off.png" : "IMGS/Buttons/music_on.png");
			updateAudioSettings();
			});

		auto musicSliderEntity = m_scenes[AppState::SettingsMenu].addEntity("MusicSlider");
		musicSliderEntity->cSlider = make_shared<CSlider>(&m_musicVolume, Vector2f(slider_x, row1_y), "IMGS/GUI/Slider.png", "IMGS/GUI/SlidingBar.png");

		auto sfxIcon = m_scenes[AppState::SettingsMenu].addEntity("SfxIcon");
		sfxIcon->cSet = make_shared<CSet>("IMGS/Buttons/sfx_on.png");
		sfxIcon->cPosition = make_shared<CPosition>(Vector2f(icon_x, row2_y));
		sfxIcon->cSet->sprite.setOrigin(sfxIcon->cSet->sprite.getLocalBounds().width / 2.f, sfxIcon->cSet->sprite.getLocalBounds().height / 2.f);
		sfxIcon->cSet->sprite.setScale(0.1f, 0.1f);
		sfxIcon->cInput = make_shared<CInput>([this, sfxIcon]() {
			m_sfxMuted = !m_sfxMuted;
			sfxIcon->cSet->texture.loadFromFile(m_sfxMuted ? "IMGS/Buttons/sfx_off.png" : "IMGS/Buttons/sfx_on.png");
			});

		auto sfxSliderEntity = m_scenes[AppState::SettingsMenu].addEntity("SfxSlider");
		sfxSliderEntity->cSlider = make_shared<CSlider>(&m_sfxVolume, Vector2f(slider_x, row2_y), "IMGS/GUI/Slider.png", "IMGS/GUI/SlidingBar.png");

		auto back = m_scenes[AppState::SettingsMenu].addEntity("Back");
		back->cSet = make_shared<CSet>("IMGS/Buttons/back.png");
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
		aboutButton->cSet = make_shared<CSet>("IMGS/Buttons/aboutus.png");
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
		rulesButton->cSet = make_shared<CSet>("IMGS/Buttons/rules.png");
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
		panel->cSet = make_shared<CSet>("IMGS/GUI/About.png");
		panel->cPosition = make_shared<CPosition>(Vector2f(m_windowConfig.width / 2.f, m_windowConfig.height / 2.f));
		panel->cSet->sprite.setOrigin(panel->cSet->sprite.getLocalBounds().width / 2.f, panel->cSet->sprite.getLocalBounds().height / 2.f);
		panel->cSet->sprite.setScale(1.5f, 1.5f);


		auto backBtn = m_scenes[AppState::AboutUs].addEntity("BackAbout");
		backBtn->cSet = make_shared<CSet>("IMGS/Buttons/back.png");
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
		panel->cSet = make_shared<CSet>("IMGS/GUI/GameRules.png");
		panel->cPosition = make_shared<CPosition>(Vector2f(m_windowConfig.width / 2.f, m_windowConfig.height / 2.f));
		panel->cSet->sprite.setOrigin(panel->cSet->sprite.getLocalBounds().width / 2.f, panel->cSet->sprite.getLocalBounds().height / 2.f);
		panel->cSet->sprite.setScale(1.5f, 1.5f);

		auto backBtn = m_scenes[AppState::Rules].addEntity("BackRules");
		backBtn->cSet = make_shared<CSet>("IMGS/Buttons/back.png");
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
		bg->cSet = make_shared<CSet>("IMGS/Background/MapSelect.jpg");
		bg->cPosition = make_shared<CPosition>(Vector2f(0, 0));

		auto map1 = m_scenes[AppState::MapSelect].addEntity("Map1");
		map1->cSet = make_shared<CSet>("IMGS/GUI/globe.png");
		map1->cPosition = make_shared<CPosition>(Vector2f(317, 390));
		map1->cSet->sprite.setScale(1.0f, 1.0f);
		map1->cInput = make_shared<CInput>([this]()
			{
				m_mapindex = 0;
				m_state = AppState::Map1;
				game_state = AppState::GamePlay;
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
		map2->cSet = make_shared<CSet>("IMGS/GUI/globe.png");
		map2->cPosition = make_shared<CPosition>(Vector2f(25, 337));
		map2->cSet->sprite.setScale(1.125f, 1.125f);
		map2->cInput = make_shared<CInput>([this]()
			{
				m_mapindex = 1;
				m_state = AppState::Map2;
				game_state = AppState::GamePlay;
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
		map3->cSet = make_shared<CSet>("IMGS/GUI/globe.png");
		map3->cPosition = make_shared<CPosition>(Vector2f(1297, 390));
		map3->cSet->sprite.setScale(1.0f, 1.0f);
		map3->cInput = make_shared<CInput>([this]()
			{
				m_mapindex = 2;
				m_state = AppState::Map3;
				game_state = AppState::GamePlay;
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
		map4->cSet = make_shared<CSet>("IMGS/GUI/globe.png");
		map4->cPosition = make_shared<CPosition>(Vector2f(1557, 337));
		map4->cSet->sprite.setScale(1.125f, 1.125f);
		map4->cInput = make_shared<CInput>([this]()
			{
				m_mapindex = 3;
				m_state = AppState::Map4;
				game_state = AppState::GamePlay;
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
		back->cSet = make_shared<CSet>("IMGS/Buttons/back.png");
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
