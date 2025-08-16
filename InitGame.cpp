#include "Game.h"

// --- Hàm game chính ---
Game::Game(const string& config)
{
	init(config);
}

void Game::clearFile(const string& fileName)
{
	ofstream file(fileName, ios::out | ios::trunc);
	if (!file) {
		cout << "Error opening file\n";
	}
	file.close();
	string map_name = "Map" + to_string(m_mapindex + 1);
	for (auto& e : m_scenes[AppState::LoadGame].getEntities())
	{
		if (e->tag() == map_name)
		{
			if (e->cText)
				e->cText = nullptr;
			break;
		}
	}
}

void Game::sChangeCursor(string tag)
{
	for (auto& entity : m_entities.getEntities("Cursor"))
	{
		if (entity->tag() == tag)
		{
			entity->active(true);
			m_window.setMouseCursorVisible(false);
			break;
		}
	}
}


// --- Đọc file config.txt ---
void Game::init(const string& path)
{
	ifstream readconfig(path);
	string line;

	// ================================================================================ CẤU HÌNH CỬA SỔ ================================================================================
	{
		while (getline(readconfig, line)) {
			if (line.empty() || line[0] == '#') continue;
			istringstream iss(line);
			string window_name;
			iss >> window_name >> m_windowConfig.width >> m_windowConfig.height >> m_windowConfig.fps >> m_windowConfig.fullscreen;
			Uint32 style = m_windowConfig.fullscreen ? Style::Fullscreen : Style::Default;
			m_window.create(VideoMode(m_windowConfig.width, m_windowConfig.height), window_name, style);
			m_window.setFramerateLimit(m_windowConfig.fps);
			m_cursorImage.loadFromFile("IMGS/GUI/ChillCursor.png");
			if (cursor.loadFromPixels(m_cursorImage.getPixelsPtr(), m_cursorImage.getSize(), sf::Vector2u(0, 0))) {
				m_window.setMouseCursor(cursor);
			}
			break;
		}
	}

	// ================================================================================ ĐẠN ================================================================================
	// --- Loại 1
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
				entity->cSpriteScale = make_shared<CSpriteScale>(m_bullet01Config.Sscale);

				auto& sprite = entity->cSet->sprite;
				sprite.setScale(m_bullet01Config.Sscale, m_bullet01Config.Sscale);
				sprite.setOrigin(sprite.getLocalBounds().width / 2.f, (sprite.getLocalBounds().height / 2.f));
			}
			break;
		}
	}

	// --- Loại 2
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
				entity->cSpriteScale = make_shared<CSpriteScale>(m_bullet02Config.Sscale);

				auto& sprite = entity->cSet->sprite;
				sprite.setScale(m_bullet02Config.Sscale, m_bullet02Config.Sscale);
				sprite.setOrigin(sprite.getLocalBounds().width / 2.f, (sprite.getLocalBounds().height / 2.f));
			}
			break;
		}
	}

	//--- Loai 3 
	{
		while (getline(readconfig, line)) {
			if (line.empty() || line[0] == '#') continue;
			istringstream iss(line);
			iss >> m_bullet03Config.tag >> m_bullet03Config.filepath >> m_bullet03Config.damage >> m_bullet03Config.speed >> m_bullet03Config.Bscale >> m_bullet03Config.Sscale;

			for (int i = 0; i < 50; i++)
			{
				auto entity = m_entities.addEntity(m_bullet03Config.tag);
				entity->cMovement = make_shared<CMovement>(m_bullet03Config.speed);
				entity->cSet = make_shared<CSet>(m_bullet03Config.filepath, Vector2u(4, 1), 0.1f, 0);
				entity->cSet->isDynamic = true;
				entity->cDamage = make_shared<CDamage>(m_bullet03Config.damage);
				entity->cBoundaryScale = make_shared<CBoundaryScale>(m_bullet03Config.Bscale);
				entity->cSpriteScale = make_shared<CSpriteScale>(m_bullet03Config.Sscale);

				auto& sprite = entity->cSet->sprite;
				sprite.setScale(m_bullet03Config.Sscale, m_bullet03Config.Sscale);
				sprite.setOrigin(sprite.getLocalBounds().width / 2.f, (sprite.getLocalBounds().height / 2.f) + 20.0);
			}
			break;
		}
	}

	// loai 4
	{
		while (getline(readconfig, line)) {
			if (line.empty() || line[0] == '#') continue;
			istringstream iss(line);
			iss >> m_bullet04Config.tag >> m_bullet04Config.filepath >> m_bullet04Config.damage >> m_bullet04Config.speed >> m_bullet04Config.Bscale >> m_bullet04Config.Sscale;

			for (int i = 0; i < 50; i++)
			{
				auto entity = m_entities.addEntity(m_bullet04Config.tag);
				entity->cMovement = make_shared<CMovement>(m_bullet04Config.speed);
				entity->cSet = make_shared<CSet>(m_bullet04Config.filepath, Vector2u(1, 1), 0.5f, 0);
				entity->cSet->isDynamic = true;
				entity->cDamage = make_shared<CDamage>(m_bullet04Config.damage);
				entity->cBoundaryScale = make_shared<CBoundaryScale>(m_bullet04Config.Bscale);
				entity->cSpriteScale = make_shared<CSpriteScale>(m_bullet04Config.Sscale);

				auto& sprite = entity->cSet->sprite;
				sprite.setScale(m_bullet04Config.Sscale, m_bullet04Config.Sscale);
				sprite.setOrigin(sprite.getLocalBounds().width / 2.f, (sprite.getLocalBounds().height / 2.f));
			}
			break;
		}
	}

	// loai 5
	{
		while (getline(readconfig, line)) {
			if (line.empty() || line[0] == '#') continue;
			istringstream iss(line);
			iss >> m_bullet05Config.tag >> m_bullet05Config.filepath >> m_bullet05Config.damage >> m_bullet05Config.speed >> m_bullet05Config.Bscale >> m_bullet05Config.Sscale;

			for (int i = 0; i < 50; i++)
			{
				auto entity = m_entities.addEntity(m_bullet05Config.tag);
				entity->cMovement = make_shared<CMovement>(m_bullet05Config.speed);
				entity->cSet = make_shared<CSet>(m_bullet05Config.filepath, Vector2u(4, 1), 0.1f, 0);
				entity->cSet->isDynamic = true;
				entity->cDamage = make_shared<CDamage>(m_bullet05Config.damage);
				entity->cBoundaryScale = make_shared<CBoundaryScale>(m_bullet05Config.Bscale);
				entity->cSpriteScale = make_shared<CSpriteScale>(m_bullet06Config.Sscale);


				auto& sprite = entity->cSet->sprite;
				sprite.setScale(m_bullet05Config.Sscale, m_bullet05Config.Sscale);
				sprite.setOrigin(sprite.getLocalBounds().width / 2.f, (sprite.getLocalBounds().height / 2.f));
			}
			break;
		}
	}

	//Loai 6
	{
		while (getline(readconfig, line)) {
			if (line.empty() || line[0] == '#') continue;
			istringstream iss(line);
			iss >> m_bullet06Config.tag >> m_bullet06Config.filepath >> m_bullet06Config.damage >> m_bullet06Config.speed >> m_bullet06Config.Bscale >> m_bullet06Config.Sscale;

			for (int i = 0; i < 50; i++)
			{
				auto entity = m_entities.addEntity(m_bullet06Config.tag);
				entity->cMovement = make_shared<CMovement>(m_bullet06Config.speed);
				entity->cSet = make_shared<CSet>(m_bullet06Config.filepath, Vector2u(4, 1), 0.1f, 0);
				entity->cSet->isDynamic = true;
				entity->cDamage = make_shared<CDamage>(m_bullet06Config.damage);
				entity->cBoundaryScale = make_shared<CBoundaryScale>(m_bullet06Config.Bscale);
				entity->cSpriteScale = make_shared<CSpriteScale>(m_bullet06Config.Sscale);

				auto& sprite = entity->cSet->sprite;
				sprite.setScale(m_bullet06Config.Sscale, m_bullet06Config.Sscale);
				sprite.setOrigin(sprite.getLocalBounds().width / 2.f, (sprite.getLocalBounds().height / 2.f));
			}
			break;
		}
	}

	// ================================================================================ QUÁI ================================================================================
	// --- Loại 1
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
				sprite.setOrigin(sprite.getLocalBounds().width/2.f, (sprite.getLocalBounds().height / 2.f));
			}

			break;
		}
	}

	// --- Loại 2
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
				sprite.setOrigin((sprite.getLocalBounds().width / 2.f), (sprite.getLocalBounds().height / 2.f) + 8);
			}

			break;
		}
	}

	// --- Loại 3
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
				sprite.setOrigin((sprite.getLocalBounds().width / 2.f) - 5, (sprite.getLocalBounds().height / 2.f));
			}

			break;
		}
	}

	// ================================================================================ THÁP ================================================================================
	// --- Loại 1
	{
		while (getline(readconfig, line))
		{
			if (line.empty() || line[0] == '#') continue;
			istringstream iss(line);
			Vector2u imgCount;
			float switchTime, range, cooldown;
			int amount;
			iss >> m_towerType1Config.tag >> m_towerType1Config.filepath >> imgCount.x >> imgCount.y >> switchTime >> m_towerType1Config.range >> m_towerType1Config.cooldown >> amount >> m_towerType1Config.cost >> m_towerType1Config.Sscale;

			for (int i = 0; i < amount; i++)
			{
				auto entity = m_entities.addEntity(m_towerType1Config.tag);
				entity->cSet = make_shared<CSet>(m_towerType1Config.filepath, imgCount, switchTime, 0);
				entity->cCooldown = make_shared<CCooldown>(m_towerType1Config.cooldown);
				entity->cLevel = make_shared<CLevel>(0);
				entity->cMoney = make_shared<CMoney>(m_towerType1Config.cost);
				entity->cBound = make_shared<CBound>(m_towerType1Config.range);
				entity->cWeapon = make_shared<CWeapon>(m_bullet01Config.tag);
				auto& sprite = entity->cSet->sprite;
				sprite.setScale(m_towerType1Config.Sscale, m_towerType1Config.Sscale);
				sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height - 20);

				entity->cInput = make_shared<CInput>(
					[entity]() { entity->cInput->isChoosing = true; },
					[entity]() { entity->cSet->sprite.setColor(Color(200, 200, 200)); },
					[entity]() { entity->cSet->sprite.setColor(Color(255, 255, 255)); }
				);
			}

			auto entity = m_entities.addEntity("Cursor01");
			entity->cSet = make_shared<CSet>("IMGS/TowerImages/Tower1_icon.png", Vector2u(1, 1), 0.5f, 0);
			auto& sprite = entity->cSet->sprite;
			sprite.setScale(1.f, 1.f);
			sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height - 20);

			break;
		}
	}

	// --- Loại 2
	{
		while (getline(readconfig, line))
		{
			if (line.empty() || line[0] == '#') continue;
			istringstream iss(line);
			Vector2u imgCount;
			float switchTime, range, cooldown;
			int amount;
			iss >> m_towerType2Config.tag >> m_towerType2Config.filepath >> imgCount.x >> imgCount.y >> switchTime >> m_towerType2Config.range >> m_towerType2Config.cooldown >> amount >> m_towerType2Config.cost >> m_towerType2Config.Sscale;

			for (int i = 0; i < amount; i++)
			{
				auto entity = m_entities.addEntity(m_towerType2Config.tag);
				entity->cSet = make_shared<CSet>(m_towerType2Config.filepath, imgCount, switchTime, 0);
				entity->cCooldown = make_shared<CCooldown>(m_towerType2Config.cooldown);
				entity->cLevel = make_shared<CLevel>(0);
				entity->cMoney = make_shared<CMoney>(m_towerType2Config.cost);
				entity->cBound = make_shared<CBound>(m_towerType2Config.range);
				entity->cWeapon = make_shared<CWeapon>(m_bullet02Config.tag);
				auto& sprite = entity->cSet->sprite;
				sprite.setScale(m_towerType2Config.Sscale, m_towerType2Config.Sscale);
				sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height - 20);

				entity->cInput = make_shared<CInput>(
					[entity]() { entity->cInput->isChoosing = true; },
					[entity]() { entity->cSet->sprite.setColor(Color(200, 200, 200)); },
					[entity]() { entity->cSet->sprite.setColor(Color(255, 255, 255)); }
				);
			}

			auto entity = m_entities.addEntity("Cursor02");
			entity->cSet = make_shared<CSet>("IMGS/TowerImages/Tower2_icon.png", Vector2u(1, 1), 0.5f, 0);
			auto& sprite = entity->cSet->sprite;
			sprite.setScale(1.f, 1.f);
			sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height - 20);

			break;
		}
	}

	// --- Loại 3
	{
		while (getline(readconfig, line))
		{
			if (line.empty() || line[0] == '#') continue;
			istringstream iss(line);
			Vector2u imgCount;
			float switchTime, range, cooldown;
			int amount;
			iss >> m_towerType3Config.tag >> m_towerType3Config.filepath >> imgCount.x >> imgCount.y >> switchTime >> m_towerType3Config.range >> m_towerType3Config.cooldown >> amount >> m_towerType3Config.cost >> m_towerType3Config.Sscale;

			for (int i = 0; i < amount; i++)
			{
				auto entity = m_entities.addEntity(m_towerType3Config.tag);
				entity->cSet = make_shared<CSet>(m_towerType3Config.filepath, imgCount, switchTime, 0);
				entity->cCooldown = make_shared<CCooldown>(m_towerType3Config.cooldown);
				entity->cLevel = make_shared<CLevel>(0);
				entity->cMoney = make_shared<CMoney>(m_towerType3Config.cost);
				entity->cBound = make_shared<CBound>(m_towerType3Config.range);
				entity->cWeapon = make_shared<CWeapon>(m_bullet03Config.tag);
				auto& sprite = entity->cSet->sprite;
				sprite.setScale(m_towerType3Config.Sscale, m_towerType3Config.Sscale);
				sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height - 20);

				entity->cInput = make_shared<CInput>(
					[entity]() { entity->cInput->isChoosing = true; },
					[entity]() { entity->cSet->sprite.setColor(Color(200, 200, 200)); },
					[entity]() { entity->cSet->sprite.setColor(Color(255, 255, 255)); }
				);
			}

			auto entity = m_entities.addEntity("Cursor03");
			entity->cSet = make_shared<CSet>("IMGS/TowerImages/Tower3_icon.png", Vector2u(1, 1), 0.5f, 0);
			auto& sprite = entity->cSet->sprite;
			sprite.setScale(0.5f, 0.5f);
			sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height - 20);

			break;
		}
	}

	// --- Loại 4
	{
		while (getline(readconfig, line))
		{
			if (line.empty() || line[0] == '#') continue;
			istringstream iss(line);
			Vector2u imgCount;
			float switchTime, range, cooldown;
			int amount;
			iss >> m_towerType4Config.tag >> m_towerType4Config.filepath >> imgCount.x >> imgCount.y >> switchTime >> m_towerType4Config.range >> m_towerType4Config.cooldown >> amount >> m_towerType4Config.cost >> m_towerType4Config.Sscale;

			for (int i = 0; i < amount; i++)
			{
				auto entity = m_entities.addEntity(m_towerType4Config.tag);
				entity->cSet = make_shared<CSet>(m_towerType4Config.filepath, imgCount, switchTime, 0);
				entity->cCooldown = make_shared<CCooldown>(m_towerType4Config.cooldown);
				entity->cLevel = make_shared<CLevel>(0);
				entity->cMoney = make_shared<CMoney>(m_towerType4Config.cost);
				entity->cBound = make_shared<CBound>(m_towerType4Config.range);
				entity->cWeapon = make_shared<CWeapon>(m_bullet04Config.tag);
				auto& sprite = entity->cSet->sprite;
				sprite.setScale(m_towerType4Config.Sscale, m_towerType4Config.Sscale);
				sprite.setOrigin(sprite.getLocalBounds().width / 2.f, (sprite.getLocalBounds().height / 2.f) + 20.0);

				entity->cInput = make_shared<CInput>(
					[entity]() { entity->cInput->isChoosing = true; },
					[entity]() { entity->cSet->sprite.setColor(Color(200, 200, 200)); },
					[entity]() { entity->cSet->sprite.setColor(Color(255, 255, 255)); }
				);
			}

			auto entity = m_entities.addEntity("Cursor04");
			entity->cSet = make_shared<CSet>("IMGS/TowerImages/Tower4_icon.png", Vector2u(1, 1), 0.5f, 0);
			auto& sprite = entity->cSet->sprite;
			sprite.setScale(1.2f, 1.2f);
			sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height - 20);
			break;
		}
	}

	// --- Loại 5
	{
		while (getline(readconfig, line))
		{
			if (line.empty() || line[0] == '#') continue;
			istringstream iss(line);
			Vector2u imgCount;
			float switchTime, range, cooldown;
			int amount;
			iss >> m_towerType5Config.tag >> m_towerType5Config.filepath >> imgCount.x >> imgCount.y >> switchTime >> m_towerType5Config.range >> m_towerType5Config.cooldown >> amount >> m_towerType5Config.cost >> m_towerType5Config.Sscale;

			for (int i = 0; i < amount; i++)
			{
				auto entity = m_entities.addEntity(m_towerType5Config.tag);
				entity->cSet = make_shared<CSet>(m_towerType5Config.filepath, imgCount, switchTime, 0);
				entity->cCooldown = make_shared<CCooldown>(m_towerType5Config.cooldown);
				entity->cLevel = make_shared<CLevel>(0);
				entity->cMoney = make_shared<CMoney>(m_towerType5Config.cost);
				entity->cBound = make_shared<CBound>(m_towerType5Config.range);
				entity->cWeapon = make_shared<CWeapon>(m_bullet05Config.tag);
				auto& sprite = entity->cSet->sprite;
				sprite.setScale(m_towerType5Config.Sscale, m_towerType5Config.Sscale);
				sprite.setOrigin(sprite.getLocalBounds().width / 2.f, (sprite.getLocalBounds().height / 2.f) + 20.0);

				entity->cInput = make_shared<CInput>(
					[entity]() { entity->cInput->isChoosing = true; },
					[entity]() { entity->cSet->sprite.setColor(Color(200, 200, 200)); },
					[entity]() { entity->cSet->sprite.setColor(Color(255, 255, 255)); }
				);
			}

			auto entity = m_entities.addEntity("Cursor05");
			entity->cSet = make_shared<CSet>("IMGS/TowerImages/Tower5_icon.png", Vector2u(1, 1), 0.5f, 0);
			auto& sprite = entity->cSet->sprite;
			sprite.setScale(1.4f, 1.4f);
			sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height - 20);

			break;
		}
	}

	// --- Loại 6
	{
		while (getline(readconfig, line))
		{
			if (line.empty() || line[0] == '#') continue;
			istringstream iss(line);
			Vector2u imgCount;
			float switchTime, range, cooldown;
			int amount;
			iss >> m_towerType6Config.tag >> m_towerType6Config.filepath >> imgCount.x >> imgCount.y >> switchTime >> m_towerType6Config.range >> m_towerType6Config.cooldown >> amount >> m_towerType6Config.cost >> m_towerType6Config.Sscale;

			for (int i = 0; i < amount; i++)
			{
				auto entity = m_entities.addEntity(m_towerType6Config.tag);
				entity->cSet = make_shared<CSet>(m_towerType6Config.filepath, imgCount, switchTime, 0);
				entity->cCooldown = make_shared<CCooldown>(m_towerType6Config.cooldown);
				entity->cLevel = make_shared<CLevel>(0);
				entity->cMoney = make_shared<CMoney>(m_towerType6Config.cost);
				entity->cBound = make_shared<CBound>(m_towerType6Config.range);
				entity->cWeapon = make_shared<CWeapon>(m_bullet06Config.tag);
				auto& sprite = entity->cSet->sprite;
				sprite.setScale(m_towerType6Config.Sscale, m_towerType6Config.Sscale);
				sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height - 20);

				entity->cInput = make_shared<CInput>(
					[entity]() { entity->cInput->isChoosing = true; },
					[entity]() { entity->cSet->sprite.setColor(Color(200, 200, 200)); },
					[entity]() { entity->cSet->sprite.setColor(Color(255, 255, 255)); }
				);
			}

			auto entity = m_entities.addEntity("Cursor06");
			entity->cSet = make_shared<CSet>("IMGS/TowerImages/Tower6_icon.png", Vector2u(1, 1), 0.5f, 0);
			auto& sprite = entity->cSet->sprite;
			sprite.setScale(0.5f, 0.5f);
			sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height - 20);

			break;
		}
	}

	// ================================================================================ WAVE ================================================================================
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

	// ================================================================================ EFFECT ================================================================================
	{
		for (int i = 0; i < 10; i++)
		{
			auto entity = m_entities.addEntity("Tornado");
			entity->cMovement = make_shared<CMovement>(300);
			entity->cSet = make_shared<CSet>("IMGS/Effects/tornadoMoving.png", Vector2u(5, 1), 0.2f, 0);
			entity->cBoundaryScale = make_shared<CBoundaryScale>(100);
			entity->cDamage = make_shared<CDamage>(100);
			entity->cPosition = make_shared<CPosition>(Vector2f(0, 0));
			
			auto& sprite = entity->cSet->sprite;
			sprite.setScale(0.8f, 0.8f);
			sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height - 60);
		}
	}


	loadFontText();
	initUIFlow();
	loadHeartCoinText();
	loadGuideText();
	loadTowerUpgradeInfo();
	loadTowerPirce();
	loadWaveText();
	initStoryScene();
	loadStoryFromFile("story.txt");
}


// --- Load những thứ cần thiết cho game ---
void Game::loadHeartCoinText()
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
	moneyText->cText->text.setFillColor(Color::Yellow);
	moneyText->cText->text.setPosition(Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height));
}

void Game::loadTowerUpgradeInfo()
{
	// -- Hiển thị thông tin tháp
	auto Rect = m_scenes[AppState::GamePlay].addEntity("rectangle");
	Rect->cBound = make_shared<CBound>(FloatRect{ 10, 320, 265, 220 });

	auto towerName = m_scenes[AppState::GamePlay].addEntity("towerName");
	towerName->cText = make_shared<CText>("");
	towerName->cText->text.setFont(m_font);
	towerName->cText->text.setPosition(Vector2f(20, 330));
	towerName->cText->text.setCharacterSize(40);
	towerName->cText->text.setFillColor(sf::Color::Magenta);

	auto towerLevel = m_scenes[AppState::GamePlay].addEntity("towerLevel");
	towerLevel->cText = make_shared<CText>("");
	towerLevel->cText->text.setFont(m_font);
	towerLevel->cText->text.setPosition(Vector2f(170, 330));
	towerLevel->cText->text.setCharacterSize(20);
	towerLevel->cText->text.setFillColor(sf::Color::Yellow);

	auto towerDamage = m_scenes[AppState::GamePlay].addEntity("towerDamage");
	towerDamage->cText = make_shared<CText>("");
	towerDamage->cText->text.setFont(m_font);
	towerDamage->cText->text.setPosition(Vector2f(20, 380));
	towerDamage->cText->text.setCharacterSize(20);
	towerDamage->cText->text.setFillColor(sf::Color::White);

	auto towerCooldown = m_scenes[AppState::GamePlay].addEntity("towerCooldown");
	towerCooldown->cText = make_shared<CText>("");
	towerCooldown->cText->text.setFont(m_font);
	towerCooldown->cText->text.setPosition(Vector2f(20, 410));
	towerCooldown->cText->text.setCharacterSize(20);
	towerCooldown->cText->text.setFillColor(sf::Color::White);

	auto towerRange = m_scenes[AppState::GamePlay].addEntity("towerRange");
	towerRange->cText = make_shared<CText>("");
	towerRange->cText->text.setFont(m_font);
	towerRange->cText->text.setPosition(Vector2f(20, 440));
	towerRange->cText->text.setCharacterSize(20);
	towerRange->cText->text.setFillColor(sf::Color::White);

	auto sellButton = m_scenes[AppState::GamePlay].addEntity("sellButton");
	sellButton->cText = make_shared<CText>("");
	sellButton->cText->text.setFont(m_font);
	sellButton->cText->text.setPosition(Vector2f(20, 480));
	sellButton->cText->text.setCharacterSize(20);
	sellButton->cText->text.setFillColor(sf::Color::Red);
	sellButton->cInput = make_shared<CInput>(
		[this]() {
			m_clickedTower = true;
		},
		[sellButton]() {
			sellButton->cText->text.setStyle(Text::Bold);
		},
		[sellButton]() {
			sellButton->cText->text.setStyle(Text::Regular);
		}
	);

	auto upgradeButton = m_scenes[AppState::GamePlay].addEntity("upgradeButton");
	upgradeButton->cText = make_shared<CText>("");
	upgradeButton->cText->text.setFont(m_font);
	upgradeButton->cText->text.setPosition(Vector2f(150, 480));
	upgradeButton->cText->text.setCharacterSize(20);
	upgradeButton->cText->text.setFillColor(sf::Color::Green);
	upgradeButton->cInput = make_shared<CInput>(
		[this]() {
			m_clickedTower = true;
		},
		[upgradeButton]() {
			upgradeButton->cText->text.setStyle(Text::Bold);
		},
		[upgradeButton]() {
			upgradeButton->cText->text.setStyle(Text::Regular);
		}
	);

	// --- Thông số nâng cấp tiếp theo
	auto towerDamageNext = m_scenes[AppState::GamePlay].addEntity("towerDamageNext");
	towerDamageNext->cText = make_shared<CText>("");
	towerDamageNext->cText->text.setFont(m_font);
	towerDamageNext->cText->text.setPosition(Vector2f(170, 380));
	towerDamageNext->cText->text.setCharacterSize(20);
	towerDamageNext->cText->text.setFillColor(sf::Color::Green);

	auto towerCooldownNext = m_scenes[AppState::GamePlay].addEntity("towerCooldownNext");
	towerCooldownNext->cText = make_shared<CText>("");
	towerCooldownNext->cText->text.setFont(m_font);
	towerCooldownNext->cText->text.setPosition(Vector2f(170, 410));
	towerCooldownNext->cText->text.setCharacterSize(20);
	towerCooldownNext->cText->text.setFillColor(sf::Color::Green);

	auto towerRangeNext = m_scenes[AppState::GamePlay].addEntity("towerRangeNext");
	towerRangeNext->cText = make_shared<CText>("");
	towerRangeNext->cText->text.setFont(m_font);
	towerRangeNext->cText->text.setPosition(Vector2f(170, 440));
	towerRangeNext->cText->text.setCharacterSize(20);
	towerRangeNext->cText->text.setFillColor(sf::Color::Green);
}

void Game::loadGuideText()
{
	// --- Hiển thị độ khó cho từng map
	auto easyText = m_scenes[AppState::MapSelect].addEntity("easyText");
	easyText->cText = make_shared<CText>("EASY");
	easyText->cText->text.setFont(m_font);
	easyText->cText->text.setPosition(Vector2f(280, 400));
	easyText->cText->text.setCharacterSize(40);
	easyText->cText->text.setFillColor(Color::Green);

	auto mediumText = m_scenes[AppState::MapSelect].addEntity("mediumText");
	mediumText->cText = make_shared<CText>("MEDIUM");
	mediumText->cText->text.setFont(m_font);
	mediumText->cText->text.setPosition(Vector2f(65, 380));
	mediumText->cText->text.setCharacterSize(40);
	mediumText->cText->text.setFillColor(Color::Yellow);

	auto hardText = m_scenes[AppState::MapSelect].addEntity("hardText");
	hardText->cText = make_shared<CText>("HARD");
	hardText->cText->text.setFont(m_font);
	hardText->cText->text.setPosition(Vector2f(1525, 410));
	hardText->cText->text.setCharacterSize(40);
	hardText->cText->text.setFillColor(Color::Red);

	auto extremeText = m_scenes[AppState::MapSelect].addEntity("extremeText");
	extremeText->cText = make_shared<CText>("EXTREME");
	extremeText->cText->text.setFont(m_font);
	extremeText->cText->text.setPosition(Vector2f(1707, 370));
	extremeText->cText->text.setCharacterSize(40);
	extremeText->cText->text.setFillColor(Color::Black);

	// --- Hiển thị chỉ dẫn
	auto chooseMap = m_scenes[AppState::PlayMenu].addEntity("chooseMap");
	chooseMap->cText = make_shared<CText>("CHOOSE MAP");
	chooseMap->cText->text.setFont(m_font);
	chooseMap->cText->text.setPosition(Vector2f(135, 510));
	chooseMap->cText->text.setCharacterSize(40);
	chooseMap->cText->text.setFillColor(Color::White);

	auto loadGame = m_scenes[AppState::PlayMenu].addEntity("loadGame");
	loadGame->cText = make_shared<CText>("LOAD GAME");
	loadGame->cText->text.setFont(m_font);
	loadGame->cText->text.setPosition(Vector2f(1515, 520));
	loadGame->cText->text.setCharacterSize(40);
	loadGame->cText->text.setFillColor(Color::White);

	auto catalog = m_scenes[AppState::PlayMenu].addEntity("showCatalog");
	catalog->cText = make_shared<CText>("CATALOG");
	catalog->cText->text.setFont(m_font);
	catalog->cText->text.setPosition(Vector2f(863, 535));
	catalog->cText->text.setCharacterSize(40);
	catalog->cText->text.setFillColor(Color::White);
}

void Game::loadTowerPirce()
{
	// --- Hiển thị giá mua cho từng tháp khi chọn tháp
	auto Tower1Cost = m_scenes[AppState::TowerSelect].addEntity("Tower1Cost");
	Tower1Cost->cText = make_shared<CText>(m_towerType1Config.cost);
	Tower1Cost->cText->text.setFont(m_font);
	Tower1Cost->cText->text.setPosition(Vector2f(1760, 110));
	Tower1Cost->cText->text.setCharacterSize(20);
	Tower1Cost->cText->text.setFillColor(Color::Yellow);

	auto Tower2Cost = m_scenes[AppState::TowerSelect].addEntity("Tower2Cost");
	Tower2Cost->cText = make_shared<CText>(m_towerType2Config.cost);
	Tower2Cost->cText->text.setFont(m_font);
	Tower2Cost->cText->text.setPosition(Vector2f(1850, 110));
	Tower2Cost->cText->text.setCharacterSize(20);
	Tower2Cost->cText->text.setFillColor(Color::Yellow);

	auto Tower3Cost = m_scenes[AppState::TowerSelect].addEntity("Tower3Cost");
	Tower3Cost->cText = make_shared<CText>(m_towerType3Config.cost);
	Tower3Cost->cText->text.setFont(m_font);
	Tower3Cost->cText->text.setPosition(Vector2f(1760, 260));
	Tower3Cost->cText->text.setCharacterSize(20);
	Tower3Cost->cText->text.setFillColor(Color::Yellow);

	auto Tower4Cost = m_scenes[AppState::TowerSelect].addEntity("Tower4Cost");
	Tower4Cost->cText = make_shared<CText>(m_towerType4Config.cost);
	Tower4Cost->cText->text.setFont(m_font);
	Tower4Cost->cText->text.setPosition(Vector2f(1850, 260));
	Tower4Cost->cText->text.setCharacterSize(20);
	Tower4Cost->cText->text.setFillColor(Color::Yellow);

	auto Tower5Cost = m_scenes[AppState::TowerSelect].addEntity("Tower5Cost");
	Tower5Cost->cText = make_shared<CText>(m_towerType5Config.cost);
	Tower5Cost->cText->text.setFont(m_font);
	Tower5Cost->cText->text.setPosition(Vector2f(1760, 410));
	Tower5Cost->cText->text.setCharacterSize(20);
	Tower5Cost->cText->text.setFillColor(Color::Yellow);

	auto Tower6Cost = m_scenes[AppState::TowerSelect].addEntity("Tower6Cost");
	Tower6Cost->cText = make_shared<CText>(m_towerType6Config.cost);
	Tower6Cost->cText->text.setFont(m_font);
	Tower6Cost->cText->text.setPosition(Vector2f(1850, 410));
	Tower6Cost->cText->text.setCharacterSize(20);
	Tower6Cost->cText->text.setFillColor(Color::Yellow);

	auto GachaCost = m_scenes[AppState::TowerSelect].addEntity("GachaCost");
	GachaCost->cText = make_shared<CText>(5000);
	GachaCost->cText->text.setFont(m_font);
	GachaCost->cText->text.setPosition(Vector2f(1800,615));
	GachaCost->cText->text.setCharacterSize(20);
	GachaCost->cText->text.setFillColor(Color::Yellow);
}

void Game::loadWaveText()
{
	// --- Khởi tạo WAVE text
	auto waveEntity = m_scenes[AppState::GamePlay].addEntity("WaveText");
	waveEntity->cText = make_shared<CText>("WAVE ");
	waveEntity->cText->text.setFont(m_font);
	waveEntity->cText->text.setCharacterSize(80);
	waveEntity->cText->text.setFillColor(Color::Black);

	sf::FloatRect waveBounds = waveEntity->cText->text.getLocalBounds();
	waveEntity->cText->text.setOrigin(waveBounds.left + waveBounds.width / 2.f,
		waveBounds.top + waveBounds.height / 2.f);

	auto numEntity = m_scenes[AppState::GamePlay].addEntity("WaveNumber");
	numEntity->cText = make_shared<CText>(to_string(m_currentWave));
	numEntity->cText->text.setFont(m_font);
	numEntity->cText->text.setCharacterSize(80);
	numEntity->cText->text.setFillColor(Color::Red);

	FloatRect numBounds = numEntity->cText->text.getLocalBounds();
	numEntity->cText->text.setOrigin(numBounds.left + numBounds.width / 2.f,
		numBounds.top + numBounds.height / 2.f);

	float totalWidth = waveBounds.width + 20 + numBounds.width;
	float centerX = m_windowConfig.width / 2.f;
	float centerY = m_windowConfig.height / 2.f;

	waveEntity->cText->text.setPosition(centerX - totalWidth / 2.f + waveBounds.width / 2.f, centerY);
	numEntity->cText->text.setPosition(waveEntity->cText->text.getPosition().x + waveBounds.width / 2.f + 20 + numBounds.width / 2.f, centerY - 10);

	// --- Khởi tạo wave đisplay
	auto waveDisplay = m_scenes[AppState::GamePlay].addEntity("WaveDisplay");
	waveDisplay->cText = make_shared<CText>("WAVE " + to_string(m_currentWave + 1));
	waveDisplay->cText->text.setFont(m_font);
	waveDisplay->cText->text.setCharacterSize(40);
	waveDisplay->cText->text.setFillColor(Color::Green);
	waveDisplay->cText->text.setPosition(15, 130);

	// --- Khởi tạo speed up
	auto speedup = m_scenes[AppState::GamePlay].addEntity("SpeedUp");
	speedup->cText = make_shared<CText>('x' + to_string(m_speedup));
	speedup->cText->text.setFont(m_font);
	speedup->cText->text.setCharacterSize(40);
	speedup->cText->text.setFillColor(Color::White);
	speedup->cText->text.setPosition(28, 820);
}

void Game::loadFontText()
{
	// -- Khởi tạo font chữ
	if (!m_font.loadFromFile("IMGS/Fonts/ARCADECLASSIC.TTF")) {
		cout << "Failed to load font\n";
	}
	if (!m_font1.loadFromFile("IMGS/Fonts/arial.ttf"))
	{
		cout << "Failed to load font\n";
	}
	if (!m_font2.loadFromFile("IMGS/Fonts/VT323-Regular.ttf"))
	{
		cout << "Failed to load font\n";
	}
	// -- Load nhạc
	if (!m_backgroundMusic.openFromFile("SOUNDS/MainMenuMusic.mp3")) {
		cout << "Error: Could not load main menu music file.\n";
	}
	else
	{
		m_backgroundMusic.setLoop(true);
	}

	if (!m_mapSelect.openFromFile("SOUNDS/freedom.mp3")) {
		cout << "Error: Could not load map select music file.\n";
	}
	else
	{
		m_mapSelect.setLoop(true);
	}

	if (!m_mapMusic[0].openFromFile("SOUNDS/ForestBattle.mp3")) {
		cout << "Error: Could not load map 1 music file.\n";
	}
	else
	{
		m_mapMusic[0].setLoop(true);
	}

	if (!m_mapMusic[1].openFromFile("SOUNDS/DesertBattle.mp3")) {
		cout << "Error: Could not load map 1 music file.\n";
	}
	else
	{
		m_mapMusic[1].setLoop(true);
	}

	if (!m_mapMusic[2].openFromFile("SOUNDS/LavaBattle.mp3")) {
		cout << "Error: Could not load map 1 music file.\n";
	}
	else
	{
		m_mapMusic[2].setLoop(true);
	}

	if (!m_mapMusic[3].openFromFile("SOUNDS/FrozenBattle.mp3")) {
		cout << "Error: Could not load map 1 music file.\n";
	}
	else
	{
		m_mapMusic[3].setLoop(true);
	}

	if (!m_victoryMusic.openFromFile("SOUNDS/Victory.mp3")) {
		cout << "Error: Could not victory music file.\n";
	}
	else
	{
		m_victoryMusic.setLoop(true);
	}
	//"C:\Users\ASUS\source\repos\Alpha\SOUNDS\Defeat.mp3"
	if (!m_defeatMusic.openFromFile("SOUNDS/Defeat.mp3")) {
		cout << "Error: Could not defeat music file.\n";
	}
	else
	{
		m_defeatMusic.setLoop(true);
	}
	// --- Load sfx
	if (!m_clickBuffer.loadFromFile("SOUNDS/click.mp3")) {
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

	if (!m_collide.loadFromFile("SOUNDS/HitSound.mp3"))
	{
		cout << "Error: Could not load collide sound file.\n";
	}
	if (!m_sell.loadFromFile("SOUNDS/selling.mp3"))
	{
		cout << "Error: Could not load selling sound file.\n";
	}

	updateAudioSettings();
}

void Game::initUIFlow()
{
	// -- Load Map ---
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


			entity = m_scenes[AppState::OptionMenu].addEntity("Resume");
			entity->cSet = make_shared<CSet>("IMGS/Buttons/continue.png");
			entity->cPosition = make_shared<CPosition>(Vector2f(810, 391));
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
			entity->cSet = make_shared<CSet>("IMGS/Buttons/Save.png");
			entity->cPosition = make_shared<CPosition>(Vector2f(810, 544));
			entity->cInput = make_shared<CInput>([this]()
				{

					queueSave();
					this_thread::sleep_for(chrono::milliseconds(50));
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
			entity->cSet = make_shared<CSet>("IMGS/Buttons/Out.png");
			entity->cPosition = make_shared<CPosition>(Vector2f(810, 697));
			entity->cInput = make_shared<CInput>([this]()
				{
					prev_state = m_state;
					m_state = AppState::PlayMenu;
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
		}


		// --- Gameplay ---
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

		entity = m_scenes[AppState::GamePlay].addEntity("SpeedUp");
		entity->cSet = make_shared<CSet>("IMGS/Buttons/speedup1.png");
		entity->cPosition = make_shared<CPosition>(Vector2f(16, 865));
		entity->cInput = make_shared<CInput>([this]()
			{
				if (m_speedup == 1)
				{
					m_speedup = 2;
				}
				else if (m_speedup == 2)
				{
					m_speedup = 3;
				}
				else if (m_speedup == 3)
				{
					m_speedup = 1;
				}

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


		// --- Tower Select ---
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
				sChangeCursor("Cursor01");
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
				sChangeCursor("Cursor02");
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
				sChangeCursor("Cursor03");
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
				sChangeCursor("Cursor04");
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
				sChangeCursor("Cursor05");
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
				sChangeCursor("Cursor06");
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

		entity = m_scenes[AppState::TowerSelect].addEntity("DiceButton");
		entity->cSet = make_shared<CSet>("IMGS/Effects/DiceSpriteSheet2.png", Vector2u(4, 1), 0.25f, 0);

		auto& sprite = entity->cSet->sprite;
		sprite.setScale(0.8, 0.8);
		sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height - 20);
		entity->cPosition = make_shared<CPosition>(Vector2f(1820, 600));

		entity->cInput = make_shared<CInput>([this]()
			{
				sGacha();
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
		play->cPosition = make_shared<CPosition>(Vector2f(770, 450));
		play->cInput = make_shared<CInput>([this]()
			{
				playStoryBlock("intro", AppState::PlayMenu);
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
		settingsButton->cPosition = make_shared<CPosition>(Vector2f(1170, 450));
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
		exit->cPosition = make_shared<CPosition>(Vector2f(1570, 450));
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
		bg->cSet = make_shared<CSet>("IMGS/Background/playmenu.jpg");
		bg->cPosition = make_shared<CPosition>(Vector2f(0, 0));

		auto newGameButton = m_scenes[AppState::PlayMenu].addEntity("New");
		newGameButton->cSet = make_shared<CSet>("IMGS/GUI/dark1.jpg");
		newGameButton->cPosition = make_shared<CPosition>(Vector2f(209, 618));
		newGameButton->cInput = make_shared<CInput>([this]()
			{
				m_state = AppState::MapSelect;
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

		auto catalogButton = m_scenes[AppState::PlayMenu].addEntity("Catalog");
		catalogButton->cSet = make_shared<CSet>("IMGS/GUI/dark3.jpg");
		catalogButton->cPosition = make_shared<CPosition>(Vector2f(901, 641));
		catalogButton->cInput = make_shared<CInput>([this]()
			{
				m_state1 = AppState::Catalog;
				m_currentCatalog = 0;
				updateCatalogDisplay();
			},
			[catalogButton]()
			{
				catalogButton->cSet->sprite.setColor(Color(200, 200, 200));
			},
			[catalogButton]()
			{
				catalogButton->cSet->sprite.setColor(Color(255, 255, 255));
			}
		);

		auto loadGame = m_scenes[AppState::PlayMenu].addEntity("Load");
		loadGame->cSet = make_shared<CSet>("IMGS/GUI/dark2.jpg");
		loadGame->cPosition = make_shared<CPosition>(Vector2f(1563, 630));
		loadGame->cInput = make_shared<CInput>([this]()
			{
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
		back->cSet->sprite.setScale(0.2f, 0.2f);
		back->cPosition = make_shared<CPosition>(Vector2f(3, 980));
		back->cInput = make_shared<CInput>([this]()
			{
				m_state = AppState::MainMenu;
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
		back->cSet->sprite.setScale(0.2f, 0.2f);
		back->cPosition = make_shared<CPosition>(Vector2f(3, 980));
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
				fileForSave = "map1.txt";
				if (!isFileEmpty(fileForSave))
				{
					m_mapindex = 0;
					m_state = AppState::Map1;
					sLoadGame();
					game_state = AppState::GamePlay;
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
		if (!isFileEmpty("map1.txt"))
		{
			ifstream readTime1("map1.txt");
			if (readTime1.is_open())
			{
				setSaveTime(map1, readTime1);
			}
			readTime1.close();
		}

		auto map2 = m_scenes[AppState::LoadGame].addEntity("Map2");
		map2->cSet = make_shared<CSet>("IMGS/Maps/map2.png");
		map2->cPosition = make_shared<CPosition>(Vector2f(1040, 267));
		map2->cSet->sprite.setScale(0.25f, 0.25f);
		map2->cInput = make_shared<CInput>([this]()
			{
				fileForSave = "map2.txt";
				if (!isFileEmpty(fileForSave))
				{
					m_mapindex = 1;
					m_state = AppState::Map2;
					sLoadGame();
					game_state = AppState::GamePlay;
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
		if (!isFileEmpty("map2.txt"))
		{
			ifstream readTime("map2.txt");
			if (readTime.is_open())
			{
				setSaveTime(map2, readTime);
			}
			readTime.close();
		}
		auto map3 = m_scenes[AppState::LoadGame].addEntity("Map3");
		map3->cSet = make_shared<CSet>("IMGS/Maps/map3.png");
		map3->cPosition = make_shared<CPosition>(Vector2f(358, 651));
		map3->cSet->sprite.setScale(0.25f, 0.25f);
		map3->cInput = make_shared<CInput>([this]()
			{
				fileForSave = "map3.txt";
				if (!isFileEmpty(fileForSave))
				{
					m_mapindex = 2;
					m_state = AppState::Map3;
					sLoadGame();
					game_state = AppState::GamePlay;
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
		if (!isFileEmpty("map3.txt"))
		{
			ifstream readTime("map3.txt");
			if (readTime.is_open())
			{
				setSaveTime(map3, readTime);
			}
			readTime.close();
		}
		auto map4 = m_scenes[AppState::LoadGame].addEntity("Map4");
		map4->cSet = make_shared<CSet>("IMGS/Maps/map4.png");
		map4->cPosition = make_shared<CPosition>(Vector2f(1040, 651));
		map4->cSet->sprite.setScale(0.25f, 0.25f);
		map4->cInput = make_shared<CInput>([this]()
			{
				fileForSave = "map4.txt";
				if (!isFileEmpty(fileForSave))
				{
					m_mapindex = 3;
					m_state = AppState::Map4;
					sLoadGame();
					game_state = AppState::GamePlay;
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
		if (!isFileEmpty("map4.txt"))
		{
			ifstream readTime("map4.txt");
			if (readTime.is_open())
			{
				setSaveTime(map4, readTime);
			}
			readTime.close();
		}
	}


	// -- SettingsMenu (Pop-up) --
	{

		auto panel = m_scenes[AppState::SettingsMenu].addEntity("SettingsPanel");
		panel->cSet = make_shared<CSet>("IMGS/GUI/settingmenu.png");
		panel->cPosition = make_shared<CPosition>(Vector2f(m_windowConfig.width / 2.f, m_windowConfig.height / 2.f));
		panel->cSet->sprite.setOrigin(panel->cSet->sprite.getLocalBounds().width / 2.f, panel->cSet->sprite.getLocalBounds().height / 2.f);
		panel->cSet->sprite.setScale(1.5f, 1.5f);

		Vector2f panelCenter = panel->cPosition->position;
		float row1_y = panelCenter.y - 10.f;
		float row2_y = panelCenter.y + 65.f;
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
		back->cSet->sprite.setScale(0.2f, 0.2f);
		back->cPosition = make_shared<CPosition>(Vector2f(panelCenter.x, panelCenter.y + 155.f));
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
		aboutButton->cPosition = make_shared<CPosition>(Vector2f(panelCenter.x - 100.f, panelCenter.y + 155.f));
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
		rulesButton->cPosition = make_shared<CPosition>(Vector2f(panelCenter.x + 100.f, panelCenter.y + 155.f));
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
		panel->cSet->sprite.setScale(2.5f, 2.5f);


		auto backBtn = m_scenes[AppState::AboutUs].addEntity("BackAbout");
		backBtn->cSet = make_shared<CSet>("IMGS/Buttons/back.png");
		backBtn->cSet->sprite.setScale(0.2f, 0.2f);
		backBtn->cPosition = make_shared<CPosition>(Vector2f(m_windowConfig.width / 2.f, m_windowConfig.height / 2.f + 350.f));
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
		panel->cSet->sprite.setScale(2.5f, 2.5f);

		auto backBtn = m_scenes[AppState::Rules].addEntity("BackRules");
		backBtn->cSet = make_shared<CSet>("IMGS/Buttons/back.png");
		backBtn->cSet->sprite.setScale(0.2f, 0.2f);
		backBtn->cPosition = make_shared<CPosition>(Vector2f(m_windowConfig.width / 2.f, m_windowConfig.height / 2.f + 300.f));
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


	// --- Special effect pop up---

	//Effect 1 Button 
	{
		auto panel = m_scenes[AppState::Effect1].addEntity("EffectPanel");
		panel->cSet = make_shared<CSet>("IMGS/GUI/Eff1Panel.png");
		panel->cPosition = make_shared<CPosition>(Vector2f(m_windowConfig.width / 2.f, m_windowConfig.height / 2.f));
		panel->cSet->sprite.setOrigin(panel->cSet->sprite.getLocalBounds().width / 2.f, panel->cSet->sprite.getLocalBounds().height / 2.f);
		panel->cSet->sprite.setScale(0.75f, 0.75f);


		auto Eff1 = m_scenes[AppState::Effect1].addEntity("Effect1");
		Eff1->cSet = make_shared<CSet>("IMGS/Effects/RecoverEff.png");
		Eff1->cPosition = make_shared<CPosition>(Vector2f(m_windowConfig.width / 2.f - 64, m_windowConfig.height / 2.f - 128));
		Eff1->cInput = make_shared<CInput>([this]()
			{
				m_state1 = AppState::Dummy;
				m_paused = false;
				sHealthRecover(); // Effect 1 applied
			},
			[Eff1]()
			{
				Eff1->cSet->sprite.setColor(Color(200, 200, 200));
			},
			[Eff1]()
			{
				Eff1->cSet->sprite.setColor(Color(255, 255, 255));
			}
		);
	}

	//Effect 2 Button 
	{
		auto panel = m_scenes[AppState::Effect2].addEntity("EffectPanel");
		panel->cSet = make_shared<CSet>("IMGS/GUI/Eff2Panel.png");
		panel->cPosition = make_shared<CPosition>(Vector2f(m_windowConfig.width / 2.f, m_windowConfig.height / 2.f));
		panel->cSet->sprite.setOrigin(panel->cSet->sprite.getLocalBounds().width / 2.f, panel->cSet->sprite.getLocalBounds().height / 2.f);
		panel->cSet->sprite.setScale(0.75f, 0.75f);


		auto Eff2 = m_scenes[AppState::Effect2].addEntity("Effect2");
		Eff2->cSet = make_shared<CSet>("IMGS/Effects/CoinAddEff.png");
		Eff2->cPosition = make_shared<CPosition>(Vector2f(m_windowConfig.width / 2.f - 64, m_windowConfig.height / 2.f - 128));
		Eff2->cInput = make_shared<CInput>([this]()
			{
				m_state1 = AppState::Dummy;
				m_paused = false;
				m_coin *= 1.5; // Effect 2 applied
			},
			[Eff2]()
			{
				Eff2->cSet->sprite.setColor(Color(200, 200, 200));
			},
			[Eff2]()
			{
				Eff2->cSet->sprite.setColor(Color(255, 255, 255));
			}
		);
	}

	//Effect 3 Button 
	{
		auto panel = m_scenes[AppState::Effect3].addEntity("EffectPanel");
		panel->cSet = make_shared<CSet>("IMGS/GUI/Eff3Panel.png");
		panel->cPosition = make_shared<CPosition>(Vector2f(m_windowConfig.width / 2.f, m_windowConfig.height / 2.f));
		panel->cSet->sprite.setOrigin(panel->cSet->sprite.getLocalBounds().width / 2.f, panel->cSet->sprite.getLocalBounds().height / 2.f);
		panel->cSet->sprite.setScale(0.75f, 0.75f);


		auto Eff3 = m_scenes[AppState::Effect3].addEntity("Effect3");
		Eff3->cSet = make_shared<CSet>("IMGS/Effects/DeadEff.png");
		Eff3->cPosition = make_shared<CPosition>(Vector2f(m_windowConfig.width / 2.f - 64, m_windowConfig.height / 2.f - 128));
		Eff3->cInput = make_shared<CInput>([this]()
			{
				m_state1 = AppState::Dummy;
				m_paused = false;			

				for (auto& tow : m_entities.getEntities("Tower"))
				{
					if (tow->isActive())
					{
						RemoveTower(*tow);
						break;
					}
				}

				m_coin = 0; // Effect 3 applied
			},
			[Eff3]()
			{
				Eff3->cSet->sprite.setColor(Color(200, 200, 200));
			},
			[Eff3]()
			{
				Eff3->cSet->sprite.setColor(Color(255, 255, 255));
			}
		);
	}

	//Effect 4 Button 
	{
		auto panel = m_scenes[AppState::Effect4].addEntity("EffectPanel");
		panel->cSet = make_shared<CSet>("IMGS/GUI/Eff4Panel.png");
		panel->cPosition = make_shared<CPosition>(Vector2f(m_windowConfig.width / 2.f, m_windowConfig.height / 2.f));
		panel->cSet->sprite.setOrigin(panel->cSet->sprite.getLocalBounds().width / 2.f, panel->cSet->sprite.getLocalBounds().height / 2.f);
		panel->cSet->sprite.setScale(0.75f, 0.75f);

		auto Eff4 = m_scenes[AppState::Effect4].addEntity("Effect4");
		Eff4->cSet = make_shared<CSet>("IMGS/Effects/MagicEff.png");
		Eff4->cPosition = make_shared<CPosition>(Vector2f(m_windowConfig.width / 2.f - 64, m_windowConfig.height / 2.f - 128));
		Eff4->cInput = make_shared<CInput>([this]()
			{
				m_state1 = AppState::Dummy;
				m_paused = false;

				for (auto& e : m_entities.getEntities())
				{
					if (e->tag() == "Tornado" && !e->isActive())
					{
						if (m_mapindex == 3)
						{
							static random_device rd;
							static mt19937 gen(rd());
							static uniform_int_distribution<> dis(0, 3);
							e->cMovement->pathIndex = dis(gen);
						}

						auto& path = e->cMovement->paths[m_mapindex][e->cMovement->pathIndex];
						if (path.empty()) continue;

						e->active(true);
						e->cMovement->currentDes = (int)path.size() - 1;
						e->cPosition->position = path.back();
						break;
					}
				}
				// Effect 4 applied
			},
			[Eff4]()
			{
				Eff4->cSet->sprite.setColor(Color(200, 200, 200));
			},
			[Eff4]()
			{
				Eff4->cSet->sprite.setColor(Color(255, 255, 255));
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
		map1->cPosition = make_shared<CPosition>(Vector2f(253, 450));
		map1->cSet->sprite.setScale(1.0f, 1.0f);
		map1->cInput = make_shared<CInput>([this]()
			{
				m_mapindex = 0;
				clearFile("map1.txt");
				fileForSave = "map1.txt";
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
		map2->cPosition = make_shared<CPosition>(Vector2f(50, 427));
		map2->cSet->sprite.setScale(1.2f, 1.2f);
		map2->cInput = make_shared<CInput>([this]()
			{
				m_mapindex = 1;
				clearFile("map2.txt");
				fileForSave = "map2.txt";
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
		map3->cPosition = make_shared<CPosition>(Vector2f(1505, 450));
		map3->cSet->sprite.setScale(1.0f, 1.0f);
		map3->cInput = make_shared<CInput>([this]()
			{
				m_mapindex = 2;
				clearFile("map3.txt");
				fileForSave = "map3.txt";
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
		map4->cPosition = make_shared<CPosition>(Vector2f(1700, 420));
		map4->cSet->sprite.setScale(1.25f, 1.25f);
		map4->cInput = make_shared<CInput>([this]()
			{
				m_mapindex = 3;
				clearFile("map4.txt");
				fileForSave = "map4.txt";
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
		back->cSet->sprite.setScale(0.2f, 0.2f);
		back->cPosition = make_shared<CPosition>(Vector2f(3, 980));
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


// --- Load Story ---
string trimBOM(const string& line)
{
	if (line.size() >= 3 &&
		(unsigned char)line[0] == 0xEF &&
		(unsigned char)line[1] == 0xBB &&
		(unsigned char)line[2] == 0xBF)
	{
		return line.substr(3);
	}
	return line;
}

void Game::loadStoryFromFile(const string& filename)
{
	m_storyBlocks.clear();
	ifstream in(filename);
	if (!in)
	{
		cerr << "Can not open file story: " << filename << "\n";
		return;
	}

	string line, currentBlock;
	while (getline(in, line))
	{
		line = trimBOM(line);

		if (line.empty() || line[0] == '#') continue;

		if (line.front() == '[' && line.back() == ']')
		{
			currentBlock = line.substr(1, line.size() - 2);
			m_storyBlocks[currentBlock] = {};
			continue;
		}

		if (currentBlock.empty()) continue;

		size_t sep = line.find('|');
		if (sep == std::string::npos) continue;

		string img = line.substr(0, sep);
		string text = line.substr(sep + 1);
		m_storyBlocks[currentBlock].push_back({ img, text });
	}
	{
		auto entity = m_scenes[AppState::Defeat].addEntity("DefeatPanel");
		entity->cSet = make_shared<CSet>("IMGS/GUI/Defeat.png");
		entity->cPosition = make_shared<CPosition>(Vector2f(511, 257));

		auto addText = m_scenes[AppState::Defeat].addEntity("DefeatText");
		addText->cText = make_shared<CText>("The stronghold falls... but the war isn't over. Stand again! Fight again!");
		addText->cText->text.setFont(m_font2);
		addText->cText->text.setCharacterSize(40);
		addText->cText->text.setFillColor(Color::White);
		addText->cText->text.setOutlineColor(Color::Black);
		addText->cText->text.setOutlineThickness(2.f);
		addText->cText->text.setPosition(400.f, 625.f);


		entity = m_scenes[AppState::Defeat].addEntity("Exit");
		entity->cSet = make_shared<CSet>("IMGS/Buttons/exit.png");
		entity->cPosition = make_shared<CPosition>(Vector2f(688, 750));
		entity->cInput = make_shared<CInput>([this]()
			{
				prev_state = m_state;
				m_state = AppState::PlayMenu;
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

		entity = m_scenes[AppState::Defeat].addEntity("Retry");
		entity->cSet = make_shared<CSet>("IMGS/Buttons/Retry.png");
		entity->cPosition = make_shared<CPosition>(Vector2f(1076, 750));
		entity->cInput = make_shared<CInput>([this]()
			{
				prev_state = m_state;
				sReset();
				m_state1 = AppState::Dummy;
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

		entity = m_scenes[AppState::Victory].addEntity("VictoryPanel");
		entity->cSet = make_shared<CSet>("IMGS/GUI/Victory.png");
		entity->cPosition = make_shared<CPosition>(Vector2f(511, 257));

		addText = m_scenes[AppState::Victory].addEntity("VictoryText");
		addText->cText = make_shared<CText>("You held the line. You turned the tide. This war is over - because you never gave up.");
		addText->cText->text.setFont(m_font2);
		addText->cText->text.setCharacterSize(40);
		addText->cText->text.setFillColor(Color::White);
		addText->cText->text.setOutlineColor(Color::Black);
		addText->cText->text.setOutlineThickness(2.f);
		addText->cText->text.setPosition(300.f, 625.f);

		entity = m_scenes[AppState::Victory].addEntity("Exit");
		entity->cSet = make_shared<CSet>("IMGS/Buttons/exit.png");
		entity->cPosition = make_shared<CPosition>(Vector2f(688, 750));
		entity->cInput = make_shared<CInput>([this]()
			{
				prev_state = m_state;
				m_state = AppState::PlayMenu;
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

		entity = m_scenes[AppState::Victory].addEntity("Retry");
		entity->cSet = make_shared<CSet>("IMGS/Buttons/Retry.png");
		entity->cPosition = make_shared<CPosition>(Vector2f(1076, 750));
		entity->cInput = make_shared<CInput>([this]()
			{
				prev_state = m_state;
				sReset();
				m_state1 = AppState::Dummy;
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

	in.close();
}

void Game::initStoryScene()
{
	// Story
	{
		auto bg = m_scenes[AppState::StoryScene].addEntity("StoryBG");
		bg->cSet = make_shared<CSet>("IMGS/Story/cut1.jpg");
		bg->cPosition = make_shared<CPosition>(Vector2f(0.f, 0.f));
		bg->cSet->sprite.setPosition(bg->cPosition->position);
		bg->cSet->sprite.setScale(1.f, 1.f);
		bg->cSet->sprite.setOrigin(0.f, 0.f);

		auto text = m_scenes[AppState::StoryScene].addEntity("StoryText");
		text->cText = make_shared<CText>("...");
		text->cText->text.setFont(m_font2);
		text->cText->text.setCharacterSize(40);
		text->cText->text.setFillColor(sf::Color::White);
		text->cText->text.setPosition(300.f, 800.f);

		auto skipText = m_scenes[AppState::StoryScene].addEntity("SkipButton");
		skipText->cText = make_shared<CText>("SKIP");
		skipText->cText->text.setFont(m_font2);
		skipText->cText->text.setCharacterSize(36);
		skipText->cText->text.setFillColor(Color::White);
		skipText->cText->text.setPosition(1600.f, 950.f);
		skipText->cText->text.setOutlineColor(Color::Black);
		skipText->cText->text.setOutlineThickness(1.f);

		skipText->cInput = make_shared<CInput>([this]()
			{
				m_state = m_nextStateAfterStory;
			},
			[skipText]()
			{
				skipText->cText->text.setFillColor(Color::Yellow);
			},
			[skipText]()
			{
				skipText->cText->text.setFillColor(Color::White);
			});
	}

	// catalog
	{
		m_catalog = {
			{ "IMGS/Catalog/tower1.png", m_towerType1Config, Vector2u(11, 1), 0.2f},
			{ "IMGS/Catalog/tower2.png", m_towerType2Config, Vector2u(8, 1), 0.2f },
			{ "IMGS/Catalog/tower3.png", m_towerType3Config, Vector2u(13, 1), 0.2f },
			{ "IMGS/Catalog/tower4.png", m_towerType4Config, Vector2u(8, 1), 0.2f },
			{ "IMGS/Catalog/tower5.png", m_towerType5Config, Vector2u(14, 1), 0.2f },
			{ "IMGS/Catalog/tower6.png", m_towerType6Config, Vector2u(14, 1), 0.2f }
		};

		auto bg = m_scenes[AppState::Catalog].addEntity("CatalogBG");
		bg->cSet = make_shared<CSet>("IMGS/Catalog/tower1.png");
		bg->cPosition = make_shared<CPosition>(Vector2f(m_windowConfig.width / 2.f, m_windowConfig.height / 2.f));
		bg->cSet->sprite.setOrigin(bg->cSet->sprite.getLocalBounds().width / 2.f, bg->cSet->sprite.getLocalBounds().height / 2.f);
		bg->cSet->sprite.setScale(1.2f, 1.2f);

		Vector2f center = Vector2f(m_windowConfig.width / 2.f, m_windowConfig.height / 2.f);
		float x = center.x;
		float y = center.y;

		auto towerSprite = m_scenes[AppState::Catalog].addEntity("TowerSprite");
		towerSprite->cSet = make_shared<CSet>(m_catalog[0].config.filepath, m_catalog[0].imgCount, m_catalog[0].switchTime, 0);
		auto& sprite = towerSprite->cSet->sprite;
		sprite.setScale(m_catalog[0].config.Sscale, m_catalog[0].config.Sscale);
		towerSprite->cSet->isDynamic = true;
		towerSprite->cPosition = make_shared<CPosition>(Vector2f(x - 155.f, y - 20.f));
		towerSprite->cSet->sprite.setScale(2.0f, 2.0f);

		auto leftBtn = m_scenes[AppState::Catalog].addEntity("LeftButton");
		leftBtn->cSet = make_shared<CSet>("IMGS/Buttons/left.png");
		leftBtn->cPosition = make_shared<CPosition>(Vector2f(x - 475, y));
		leftBtn->cSet->sprite.setScale(1.5f, 1.5f);
		leftBtn->cInput = make_shared<CInput>([this]()
			{
				m_currentCatalog--;
				if (m_currentCatalog < 0) m_currentCatalog = m_catalog.size() - 1;
				updateCatalogDisplay();
			},
			[leftBtn]()
			{
				leftBtn->cSet->sprite.setColor(Color(200, 200, 200));
			},
			[leftBtn]()
			{
				leftBtn->cSet->sprite.setColor(Color(255, 255, 255));
			}
		);

		auto rightBtn = m_scenes[AppState::Catalog].addEntity("RightButton");
		rightBtn->cSet = make_shared<CSet>("IMGS/Buttons/right.png");
		rightBtn->cPosition = make_shared<CPosition>(Vector2f(x + 400, y));
		rightBtn->cSet->sprite.setScale(1.5f, 1.5f);
		rightBtn->cInput = make_shared<CInput>([this]()
			{
				m_currentCatalog = (m_currentCatalog + 1) % m_catalog.size();
				updateCatalogDisplay();
			},
			[rightBtn]()
			{
				rightBtn->cSet->sprite.setColor(Color(200, 200, 200));
			},
			[rightBtn]()
			{
				rightBtn->cSet->sprite.setColor(Color(255, 255, 255));
			}
		);


		auto back = m_scenes[AppState::Catalog].addEntity("Back");
		back->cSet = make_shared<CSet>("IMGS/Buttons/exit.png");
		back->cPosition = make_shared<CPosition>(Vector2f(x, y + 300));
		back->cSet->sprite.setOrigin(back->cSet->sprite.getLocalBounds().width / 2.f, back->cSet->sprite.getLocalBounds().height / 2.f);
		back->cSet->sprite.setScale(0.5f, 0.5f);
		back->cInput = make_shared<CInput>([this]()
			{
				m_currentCatalog = 0;
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
		updateCatalogDisplay();
	}
}