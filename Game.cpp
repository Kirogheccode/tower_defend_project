#include "Game.h"

// --- Vẽ hình ảnh lên màn hình ---
void Game::sRender(float& deltaTime)
{
	m_window.clear();

	// Hiển thị tổng
	if (m_state == AppState::LoadGame)
	{
		Vector2f layout{10.f,10.f};
		Vector2f TinyMap{ 288.f, 162.f };
		int indent = 0;
		for (auto& e : m_scenes[m_state].getEntities())
		{
			if (e->tag() == "GameSave")
			{
				layout.x = layout.x + TinyMap.x * indent + 20.f;
				e->cPosition = make_shared<CPosition>(layout);
				indent++;
			}

			if (e->cSet && e->cPosition)
			{
				e->cSet->sprite.setPosition(e->cPosition->position);
				m_window.draw(e->cSet->sprite);
			}

		}
	}
	else
	{

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
				e->cText->text.setString(to_string(m_coin));

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
					e->cText->text.setString(to_string(m_currentWave + 1));

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
			sSaveGame();
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
						m_state = AppState::MapSelect;
						m_typingName = false;
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
					if (m_selected == "DeleteTower")
					{
						bool remove = false;

						for (auto& e : m_entities.getEntities("Tower"))
						{
							if (e->isActive() && e->cSet->sprite.getGlobalBounds().contains(mousePos))
							{
								DeactivateTower(*e);
								remove = true;
								break;
							}
						}
						if (remove)
						{
							float marginX = 10.f;
							float marginY = 10.f;
							for (auto& e : m_scenes[m_state].getEntities("Base"))
							{
								if (!e->isActive())
								{
									FloatRect bounds = e->cSet->sprite.getGlobalBounds();
									bounds.left -= marginX;
									bounds.top -= marginY;
									bounds.width += 2 * marginX;
									bounds.height += 2 * marginY;
									if (bounds.contains(mousePos))
									{
										e->active(true);
										break;
									}
								}
							}
						}
					}
					else
					{

						bool placed = false;

						for (auto& e : m_scenes[m_state].getEntities("Base"))
						{
							if (e->isActive() && e->cSet->sprite.getGlobalBounds().contains(mousePos))
							{
								e->active(false);
								placed = true;
								playSfx(m_constructTower);
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
							if (stateToHandle == AppState::LoadGame && e->tag() == "GameSave")
								m_loadIndex++;
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

// --- Thêm màn chơi được save (khi bấm save trong options) vào danh sách loadGames ---
void Game::sAddGameSave()
{
	string fileName = m_playerName + ".txt";
	loadGames.push_back({ m_playerName, m_state, m_mapindex });

	switch (m_state)
	{
	  case AppState::Map1:
		   fileName = "map1";
		   break;
	  case AppState::Map2:
		  fileName = "map2";
		  break;
	  case AppState::Map3:
		  fileName = "map3";
		  break;
	  case AppState::Map4:
		  fileName = "map4";
		  break;
	}


	auto map = m_scenes[AppState::LoadGame].addEntity("GameSave");
	map->cSet = make_shared<CSet>("IMGS/Maps/" + fileName + ".png");
	map->cSet->sprite.setScale(0.15f, 0.15f);
	map->cInput = make_shared<CInput>([this]()
		{
			sLoadGame();
			m_mapindex = loadGames[m_loadIndex].mapIndex;
			m_state = loadGames[m_loadIndex].m_save;
			m_playerName = loadGames[m_loadIndex].fileName;
			game_state = AppState::GamePlay;
			prev_state = AppState::LoadGame;
			m_loadIndex = -1;
		},
		[map]()
		{
			map->cSet->sprite.setColor(Color(200, 200, 200));
		},
		[map]()
		{
			map->cSet->sprite.setColor(Color(255, 255, 255));
		}
	);
}


// --- Lưu tên người chơi khi nhập ở PlayMenu ---
void Game::sSaveGame()
{
	if (m_playerName.empty())
		return;
	ofstream writePlayer(m_playerName + ".txt");

	if (writePlayer.is_open())
	{
		// Lưu wave
		writePlayer << "# Current wave index: " << "\n";
		writePlayer << m_currentWave << "\n";
		writePlayer << "\n";


		// Lưu index của máu còn lại
		writePlayer << "# Remaining health: " << "\n";
		for (auto& e: m_scenes[AppState::GamePlay].getEntities("Heart"))
		{
			if (e->isActive())
			{
				writePlayer << e->id() << " ";
			}
		}
		writePlayer << "\n";
		writePlayer << "\n";


		// Lưu tiền
		writePlayer << "# Money: " << "\n";
		writePlayer << m_coin << "\n";
		writePlayer << "\n";

		
		// Lưu vị trí quái
		writePlayer << "# Enemies position" << "\n";
		bool isExist = false;
		for (auto& entity : m_entities.getEntities(m_enemyType1Config.tag))
		{
			if (entity->isActive())
			{
				writePlayer << entity->cPosition->position.x << " " << entity->cPosition->position.y << " " <<  entity->cMovement->currentPathindex << " ";
				isExist = true;
			}
		}
		if (!isExist)
			writePlayer << "@";
		else
			isExist = false;
		writePlayer << "\n";
		writePlayer << "\n";

		for (auto& entity : m_entities.getEntities(m_enemyType2Config.tag))
		{
			if (entity->isActive())
			{
				writePlayer << entity->cPosition->position.x << " " << entity->cPosition->position.y << " " << entity->cMovement->currentPathindex << " ";
				isExist = true;
			}
		}
		if (!isExist)
			writePlayer << "@";
		else
			isExist = false;

		writePlayer << "\n";
		writePlayer << "\n";

		for (auto& entity : m_entities.getEntities(m_enemyType3Config.tag))
		{
			if (entity->isActive())
			{
				writePlayer << entity->cPosition->position.x << " " << entity->cPosition->position.y << " " << entity->cMovement->currentPathindex << " ";
				isExist = true;
			}
		}
		if (!isExist)
			writePlayer << "@";
		else
			isExist = false;
		writePlayer << "\n";
		writePlayer << "\n";

		// Lưu vị trí tháp
		writePlayer << "# Tower position" << "\n";
		for (auto& entity : m_entities.getEntities(m_towerType1Config.tag))
		{
			
			if (entity->isActive())
			{
				writePlayer << entity->cPosition->position.x << " " << entity->cPosition->position.y << " ";
				isExist = true;
			}
		}
		if (!isExist)
			writePlayer << "@";
		else
			isExist = false;
		writePlayer << "\n";
		writePlayer << "\n";

		for (auto& entity : m_entities.getEntities(m_towerType2Config.tag))
		{
			if (entity->isActive())
			{
				writePlayer << entity->cPosition->position.x << " " << entity->cPosition->position.y << " ";
				isExist = true;
			}
		}
		if (!isExist)
			writePlayer << "@";
		else
			isExist = false;
		writePlayer << "\n";
		writePlayer << "\n";

		for (auto& entity : m_entities.getEntities(m_towerType3Config.tag))
		{
			if (entity->isActive())
			{
				writePlayer << entity->cPosition->position.x << " " << entity->cPosition->position.y << " ";
				isExist = true;
			}
		}
		if (!isExist)
			writePlayer << "@";
		else
			isExist = false;
		writePlayer << "\n";
		writePlayer << "\n";

		for (auto& entity : m_entities.getEntities(m_towerType4Config.tag))
		{
			if (entity->isActive())
			{
				writePlayer << entity->cPosition->position.x << " " << entity->cPosition->position.y << " ";
				isExist = true;
			}
		}
		if (!isExist)
			writePlayer << "@";
		else
			isExist = false;
		writePlayer << "\n";
		writePlayer << "\n";

		for (auto& entity : m_entities.getEntities(m_towerType5Config.tag))
		{
			if (entity->isActive())
			{
				writePlayer << entity->cPosition->position.x << " " << entity->cPosition->position.y << " ";
				isExist = true;
			}
		}
		if (!isExist)
			writePlayer << "@";
		else
			isExist = false;
		writePlayer << "\n";
		writePlayer << "\n";

		for (auto& entity : m_entities.getEntities(m_towerType6Config.tag))
		{
			if (entity->isActive())
			{
				writePlayer << entity->cPosition->position.x << " " << entity->cPosition->position.y << " ";
				isExist = true;
			}
		}
		if (!isExist)
			writePlayer << "@";
		else
			isExist = false;
		writePlayer << "\n";
		writePlayer << "\n";
		writePlayer << "# Base in current map" << "\n";

		for (auto& base : m_scenes[m_state].getEntities("Base"))
		{
			writePlayer << base->isActive() << " ";
			cout << base->isActive() << " ";
		}
		if (!writePlayer)
		{
			cout << "Error writing" << endl;
		}
		cout << endl;
		writePlayer << "\n";
		writePlayer.close();
		cout << "Game saved" << endl;
	}
}

void Game::sLoadGame()
{
	
	ifstream readPlayer(loadGames[m_loadIndex].fileName + ".txt");
	cout << loadGames[m_loadIndex].fileName << endl;

	if (!readPlayer.is_open())
	{
		// Thêm hiển thị thông báo trên màn hình nếu cần
		//
		//
		//
		//
		//
		//==============================================

		cout << "Can't open file or file doesn't exist!" << endl;
		return;
	}

	string line;

	// Load wave index
	while (getline(readPlayer, line))
	{
		if (line.empty() || line[0] == '#') continue;
		istringstream iss(line);

		iss >> m_currentWave;
		break;
	}


	// Load máu người chơi
	while (getline(readPlayer, line))
	{
		if (line.empty() || line[0] == '#') continue;
		istringstream iss(line);
		int value;
		int i = 0;

		for (auto& heart : m_scenes[AppState::GamePlay].getEntities("Heart"))
		{
			if (!(iss >> value)) break;

			heart->active(true);
			i++;
		}
		break;
	}
	

	// Load tiền người chơi
	while (getline(readPlayer, line))
	{
		if (line.empty() || line[0] == '#') continue;
		istringstream iss(line);

		iss >> m_coin;
		break;
	}


	// Load quái type 1
	while (getline(readPlayer, line))
	{
		if (line.empty() || line[0] == '#') continue;
		if (line[0] == '@') break;
		istringstream iss(line);

		for (auto& enemy : m_entities.getEntities(m_enemyType1Config.tag))
		{
			float x, y;
			int index;

			if (!(iss >> x >> y >> index)) break;

			

			Vector2f pos(x, y);

			enemy->cPosition = make_shared<CPosition>(pos);
			enemy->cSet->sprite.setPosition(enemy->cPosition->position);
			enemy->active(true);

			enemy->cMovement->currentPathindex = index;
		}

		break;
	}


	// Load quái type 2
	while (getline(readPlayer, line))
	{
		if (line.empty() || line[0] == '#') continue;
		if (line[0] == '@') break;
		istringstream iss(line);

		for (auto& enemy : m_entities.getEntities(m_enemyType2Config.tag))
		{
			float x, y;
			int index;

			if (!(iss >> x >> y >> index)) break;

			

			Vector2f pos(x, y);

			enemy->cPosition = make_shared<CPosition>(pos);
			enemy->cSet->sprite.setPosition(enemy->cPosition->position);
			enemy->active(true);

			enemy->cMovement->currentPathindex = index;
		}

		break;
	}


	// Load quái type 3
	while (getline(readPlayer, line))
	{
		if (line.empty() || line[0] == '#') continue;
		if (line[0] == '@') break;
		istringstream iss(line);

		for (auto& enemy : m_entities.getEntities(m_enemyType3Config.tag))
		{
			float x, y;
			int index;

			if (!(iss >> x >> y >> index)) break;

			

			Vector2f pos(x, y);

			enemy->cPosition = make_shared<CPosition>(pos);
			enemy->cSet->sprite.setPosition(enemy->cPosition->position);
			enemy->active(true);

			enemy->cMovement->currentPathindex = index;
		}

		break;
	}


	// Load tháp type 1
	while (getline(readPlayer, line))
	{
		if (line.empty() || line[0] == '#') continue;
		if (line[0] == '@') break;
		istringstream iss(line);
		cout << line << endl;
		for (auto& tower : m_entities.getEntities(m_towerType1Config.tag))
		{
			float x, y;

			if (!(iss >> x >> y)) break;

			

			Vector2f pos(x, y);

			tower->cPosition = make_shared<CPosition>(pos);
			tower->cSet->sprite.setPosition(tower->cPosition->position);
			tower->active(true);
		}

		break;
	}


	// Load tháp type 2
	while (getline(readPlayer, line))
	{
		if (line.empty() || line[0] == '#') continue;
		if (line[0] == '@') break;
		istringstream iss(line);
		cout << line << endl;
		for (auto& tower : m_entities.getEntities(m_towerType2Config.tag))
		{
			float x, y;

			if (!(iss >> x >> y)) break;


			Vector2f pos(x, y);

			tower->cPosition = make_shared<CPosition>(pos);
			tower->cSet->sprite.setPosition(tower->cPosition->position);
			tower->active(true);
		}

		break;
	}

	
	// Load thap type 3
	while (getline(readPlayer, line))
	{
		if (line.empty() || line[0] == '#') continue;
		if (line[0] == '@') break;
		istringstream iss(line);
		cout << line << endl;
		for (auto& tower : m_entities.getEntities(m_towerType3Config.tag))
		{
			float x, y;

			if (!(iss >> x >> y)) break;


			Vector2f pos(x, y);

			tower->cPosition = make_shared<CPosition>(pos);
			tower->cSet->sprite.setPosition(tower->cPosition->position);
			tower->active(true);
		}

		break;
	}


	// Load thap type 4
	while (getline(readPlayer, line))
	{
		if (line.empty() || line[0] == '#') continue;
		if (line[0] == '@') break;
		istringstream iss(line);
		cout << line << endl;
		for (auto& tower : m_entities.getEntities(m_towerType4Config.tag))
		{
			float x, y;

			if (!(iss >> x >> y)) break;


			Vector2f pos(x, y);

			tower->cPosition = make_shared<CPosition>(pos);
			tower->cSet->sprite.setPosition(tower->cPosition->position);
			tower->active(true);
		}

		break;
	}


	// Load thap type 5
	while (getline(readPlayer, line))
	{
		if (line.empty() || line[0] == '#') continue;
		if (line[0] == '@') break;
		istringstream iss(line);
		cout << line << endl;
		for (auto& tower : m_entities.getEntities(m_towerType5Config.tag))
		{
			float x, y;

			if (!(iss >> x >> y)) break;


			Vector2f pos(x, y);

			tower->cPosition = make_shared<CPosition>(pos);
			tower->cSet->sprite.setPosition(tower->cPosition->position);
			tower->active(true);
		}

		break;
	}


	// Load thap type 6
	while (getline(readPlayer, line))
	{
		if (line.empty() || line[0] == '#') continue;
		if (line[0] == '@') break;
		istringstream iss(line);
		cout << line << endl;
		for (auto& tower : m_entities.getEntities(m_towerType6Config.tag))
		{
			float x, y;

			if (!(iss >> x >> y)) break;


			Vector2f pos(x, y);

			tower->cPosition = make_shared<CPosition>(pos);
			tower->cSet->sprite.setPosition(tower->cPosition->position);
			tower->active(true);
		}

		break;
	}


	// Load base
	while (getline(readPlayer, line))
	{
		if (line.empty() || line[0] == '#') continue;
		istringstream iss(line);
		bool value;

		for (auto& base : m_scenes[loadGames[m_loadIndex].m_save].getEntities("Base"))
		{
			if (!(iss >> value)) break;

			base->active(value);
		}


		break;
	}

	cout << "Game loaded successfully" << endl;
	readPlayer.close();
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
		else if (entity->tag().find("Enemy") != string::npos)
		{
			// Nếu như quái đi hết đường đi
			if (entity->cMovement->currentPathindex >= entity->cMovement->paths[m_mapindex].size())
			{
				auto heartvector = m_scenes[AppState::GamePlay].getEntities("Heart");
				int index = static_cast<int>(heartvector.size()) - 1;

				// Tìm trái tim cuối cùng còn active
				while (index >= 0 && !heartvector[index]->isActive())
				{
					index--;
				}

				if (heartvector.size() - index == 5)
				{
					m_window.close();
					// LOSE
				}
				else
				{
					heartvector[index]->active(false);
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


// --- Hàm hỗ trợ logic ---
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


// --- Kiểm tra va chạm ---
bool collisionDetection(const Entity& entity1, const Entity& entity2)
{
	if (!entity1.cSet || !entity2.cSet) return false;
	FloatRect bounds1 = scaleRect(entity1.cSet->sprite.getGlobalBounds(), entity2.cBoundaryScale->scale / 100.0f);
	FloatRect bounds2 = scaleRect(entity2.cSet->sprite.getGlobalBounds(), entity2.cBoundaryScale->scale / 100.0f);
	//return bounds1.intersects(bounds2);
	return isContained(bounds1, bounds2);
}


// --- Hàm va chạm ---
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
			
				if (cur->cHealth)
				{
					cur->cHealth->hp -= bullet->cDamage->damage;
					if (cur->cHealth->hp <= 0)
					{
						m_coin += cur->cMoney->money;
						DeactivateEnemy(*cur);
					}
				}
				DeactivateBullet(*bullet);
			}
		}
	}
}
