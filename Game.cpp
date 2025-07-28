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

			if (e->cText)
				m_window.draw(e->cText->text);

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

			if (e->cText)
				m_window.draw(e->cText->text);
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

			if (e->cInput)
			{
				if (e->cInput->isChoosing)
				{
					e->cBound->circle.setPosition(e->cPosition->position);
					m_window.draw(e->cBound->circle);
				}
			}
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
			bool clickedOnTower = false;

			for (auto& tower : m_entities.getEntities("Tower"))
			{
				if (tower->isActive() && tower->cSet->sprite.getGlobalBounds().contains(mousePos))
				{
					if (tower->cInput)
					{
						tower->cInput->onClick();
					}

					// Bật isChoosing = true cho tháp vừa click
					if (tower->cInput->isChoosing) tower->cInput->isChoosing = true; // hoặc tower->setChoosing(true);

					clickedOnTower = true;
					break;
				}
			}

			if (!clickedOnTower)
			{
				// Nếu click ngoài tháp, thì reset tất cả tháp
				for (auto& tower : m_entities.getEntities("Tower"))
				{
					if (tower->cInput->isChoosing) tower->cInput->isChoosing = false; // hoặc tower->setChoosing(false);
				}
			}

			bool clickedSlider = false;

			if (!clickedSlider)
			{
				// Ưu tiên state2 nếu đang chọn tower

				if (m_state2 == AppState::TowerPlace)
				{
					if (m_selected == "DeleteTower")
					{
						bool remove = false;
						Vector2f removing;
						for (auto& e : m_entities.getEntities("Tower"))
						{
							if (e->isActive() && e->cSet->sprite.getGlobalBounds().contains(mousePos))
							{
								// Hoàn lại 70% khi xoá tháp

								if (e->tag() == m_towerType1Config.tag) m_coin += m_refund * m_towerType1Config.cost;
								else if (e->tag() == m_towerType2Config.tag) m_coin += m_refund * m_towerType2Config.cost;
								else if (e->tag() == m_towerType3Config.tag) m_coin += m_refund * m_towerType3Config.cost;
								else if (e->tag() == m_towerType4Config.tag) m_coin += m_refund * m_towerType4Config.cost;
								else if (e->tag() == m_towerType5Config.tag) m_coin += m_refund * m_towerType5Config.cost;
								else if (e->tag() == m_towerType6Config.tag) m_coin += m_refund * m_towerType6Config.cost;
								removing = e->cPosition->position;
								DeactivateTower(*e);
								remove = true;
								break;
							}
						}
						if (remove)
						{
							
							for (auto& e : m_scenes[m_state].getEntities("Base"))
							{
								if (!e->isActive() && e->cSet->sprite.getGlobalBounds().contains(removing))
								{
										e->active(true);
										break;
								}
							}
						}
					}
					else
					{
						bool placed = false;
						Vector2f placing;
						for (auto& e : m_scenes[m_state].getEntities("Base"))
						{
							if (e->isActive() && e->cSet->sprite.getGlobalBounds().contains(mousePos) && m_coin >= m_cost)
							{
								m_coin -= m_cost;
								e->active(false);
								placed = true;
								placing.x = e->cSet->sprite.getGlobalBounds().left + e->cSet->sprite.getGlobalBounds().width/ 2.f;
								placing.y = e->cSet->sprite.getGlobalBounds().top + e->cSet->sprite.getGlobalBounds().height/ 2.f;

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
									e->cPosition = make_shared<CPosition>(placing);
									e->cSet->sprite.setPosition(e->cPosition->position);
									
									break;
								}
							}
						}
						else
						{
							playSfx(m_error);
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
						{
							m_state1 = AppState::Dummy;
						}
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
			{
				e->cInput->onHover();
				e->cInput->isHovered = true;
			}
			else if (!hovering && e->cInput->isHovered && e->cInput->offHover)
			{
				e->cInput->offHover();
				e->cInput->isHovered = false;
			}

			e->cInput->isHovered = hovering;
		}
	}

	for (auto& e : m_entities.getEntities())
	{
		if (e->cSet && e->cInput)
		{
			bool hovering = e->cSet->sprite.getGlobalBounds().contains(mousePos);

			if (hovering && !e->cInput->isHovered && e->cInput->onHover)
			{
				e->cInput->onHover();
				e->cInput->isHovered = true;
			}
			else if (!hovering && e->cInput->isHovered && e->cInput->offHover)
			{
				e->cInput->offHover();
				e->cInput->isHovered = false;
			}

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
		updateMusicState();

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



// Simplified start/stop without locks (locking is higher-level)
void Game::startWriting(const std::string& filename) {
	writePlayer.open(filename, std::ios::out | std::ios::trunc);
	if (!writePlayer.is_open()) {
		std::cerr << "FATAL: Could not open file: " << filename << std::endl;
	}
	writePlayer.clear();
}

void Game::stopWriting() {
	if (writePlayer.is_open()) {
		writePlayer.flush();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Delay here if needed
		writePlayer.close();
	}
}

// Restore async queueSave with thread (from history)
void Game::queueSave() {
	cout << "queueSave called\n";
	std::thread saveThread([this]() {
		std::lock_guard<std::mutex> lock(saveMutex);  // Lock for entire save
		sSaveGame();
		});
	saveThread.detach();  // Async
}

// --- Lưu tên người chơi khi nhập ở PlayMenu ---
void Game::sSaveGame()
{

	cout << "sSaveGame called\n";
	//if (m_playerName.empty())
	//	return;
	cout << "Saving game for player: " << m_playerName << "\n";

	string fileName;
	switch (m_state)
	{
	case AppState::Map1:
		fileName = "map1.txt";
		break;
	case AppState::Map2:
		fileName = "map2.txt";
		break;
	case AppState::Map3:
		fileName = "map3.txt";
		break;
	case AppState::Map4:
		fileName = "map4.txt";
		break;
	}

	cout << fileName << "\n";

	//std::ofstream writePlayer(fileName, std::ios::out | std::ios::trunc);
	//if (!writePlayer.is_open()) {
	//	std::cerr << "Error opening file: " << fileName << " (check permissions or path).\n";
	//	return;
	//}

	std::cout << "[DEBUG] Before write: State " << writePlayer.rdstate() << " (0 = good)\n";
	startWriting(fileName);  // Start writing to the file

	writePlayer.clear();  // Reset any potential error state

	// Helper to check stream after writes
	auto checkStream = [&]() 
	{
		if (writePlayer.fail()) 
		{
			std::cerr << "Write error occurred. State: " << writePlayer.rdstate() << "\n";
			writePlayer.clear();  // Attempt to recover
			return false;
		}
		return true;
	};

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

	if (!checkStream())
	{
		std::cerr << "Error writing health data.\n";
		writePlayer.close();
		return;
	}

	// Lưu tiền
	writePlayer << "# Money: " << "\n";
	writePlayer << m_coin << "\n";
	writePlayer << "\n";

	if (!checkStream())
	{
		std::cerr << "Error writing health data.\n";
		writePlayer.close();
		return;
	}
		
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

	if (!checkStream())
	{
		std::cerr << "Error writing health data.\n";
		writePlayer.close();
		return;
	}

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

	if (!checkStream())
	{
		std::cerr << "Error writing health data.\n";
		writePlayer.close();
		return;
	}

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

	if (!checkStream())
	{
		std::cerr << "Error writing health data.\n";
		writePlayer.close();
		return;
	}
	if (writePlayer.fail()) {
		std::cerr << "Error writing to file.\n";
	}

	cout << "has been written" << endl;
	writePlayer.flush();  // Ensure writes are committed
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	//writePlayer.close();
	stopWriting();  // Stop writing to the file


	std::cout << "[DEBUG] After write: State " << writePlayer.rdstate() << "\n";
	std::cout << "Game saved successfully.\n";
}

void Game::sLoadGame()
{
	string fileName = fileForSave;
	cout << fileName << endl;
	ifstream readPlayer(fileName);
	
	if (!readPlayer.is_open())
	{
		// thông báo trên màn hình 
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

		for (auto& heart : m_scenes[AppState::GamePlay].getEntities("Heart"))
		{
			heart->active(false);
		}

		for (auto& heart : m_scenes[AppState::GamePlay].getEntities("Heart"))
		{
			if (!(iss >> value)) break;

			heart->active(true);
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

		for (auto& base : m_scenes[m_state].getEntities("Base"))
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


void Game::playSfx(const sf::SoundBuffer& buffer, sf::Vector2f position) {
	if (m_sfxMuted) return;
	m_activeSounds.remove_if([](const sf::Sound& s) { return s.getStatus() == Sound::Stopped; });
	Sound& newSound = m_activeSounds.emplace_back();
	newSound.setBuffer(buffer);
	newSound.setVolume(m_sfxVolume);
	newSound.play();
}

// --- Âm thanh và Xử lý sự kiện ---
void Game::updateAudioSettings() {
	if (m_musicMuted) {
		m_backgroundMusic.setVolume(0);
		m_mapMusic[m_mapindex].setVolume(0);
		m_mapSelect.setVolume(0);
	}
	else {
		m_backgroundMusic.setVolume(m_musicVolume);
		m_mapMusic[m_mapindex].setVolume(m_musicVolume);
		m_mapSelect.setVolume(m_musicVolume);
	}
}

void Game::playMapMusic(int mapIdx) {
	for (auto& [idx, music] : m_mapMusic) {
		if (idx != mapIdx && music.getStatus() == sf::Music::Playing) {
			music.stop();
		}
	}

	auto& currentMusic = m_mapMusic[mapIdx];
	if (currentMusic.getStatus() != sf::Music::Playing) {
		currentMusic.play();
	}
}

void Game::updateMusicState() {
	bool isMenuState = (m_state == AppState::MainMenu ||
		m_state == AppState::SettingsMenu);

	if (isMenuState) {
		// Nếu chưa phát menuMusic thì bật, đồng thời tắt gameplayMusic
		for (auto& [idx, music] : m_mapMusic) {
			if (music.getStatus() == sf::Music::Playing) {
				music.stop();
			}
		}

		if (m_mapSelect.getStatus() == sf::Music::Playing)
			m_mapSelect.stop();

		if (m_backgroundMusic.getStatus() != sf::Music::Playing)
			m_backgroundMusic.play();
	}
	else if (m_state == AppState::PlayMenu || m_state == AppState::MapSelect) {
		for (auto& [idx, music] : m_mapMusic) {
			if (music.getStatus() == sf::Music::Playing) {
				music.stop();
			}
		}

		if (m_backgroundMusic.getStatus() == sf::Music::Playing)
			m_backgroundMusic.stop();

		if (m_mapSelect.getStatus() != sf::Music::Playing)
			m_mapSelect.play();
	}
	else if (m_state == AppState::Map1) {
		if (m_backgroundMusic.getStatus() == sf::Music::Playing)
			m_backgroundMusic.stop();
		if (m_mapSelect.getStatus() == sf::Music::Playing)
			m_mapSelect.stop();
		playMapMusic(0);
	}
	else if (m_state == AppState::Map2) {
		if (m_backgroundMusic.getStatus() == sf::Music::Playing)
			m_backgroundMusic.stop();
		if (m_mapSelect.getStatus() == sf::Music::Playing)
			m_mapSelect.stop();
		playMapMusic(1);
	}
	else if (m_state == AppState::Map3) {
		if (m_backgroundMusic.getStatus() == sf::Music::Playing)
			m_backgroundMusic.stop();
		if (m_mapSelect.getStatus() == sf::Music::Playing)
			m_mapSelect.stop();
		playMapMusic(2);
	}
	else if (m_state == AppState::Map4) {
		if (m_backgroundMusic.getStatus() == sf::Music::Playing)
			m_backgroundMusic.stop();
		if (m_mapSelect.getStatus() == sf::Music::Playing)
			m_mapSelect.stop();
		playMapMusic(3);
	}
	else {
		// Các state khác thì dừng hết
		if (m_backgroundMusic.getStatus() == sf::Music::Playing)
			m_backgroundMusic.stop();
		if (m_mapSelect.getStatus() == sf::Music::Playing)
			m_mapSelect.stop();
		for (auto& [idx, music] : m_mapMusic) {
			if (music.getStatus() == sf::Music::Playing) {
				music.stop();
			}
		}
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

	return isContained(bounds1, bounds2);
}


sf::Vector2f Game::getWindowSize() const {
	sf::Vector2u size = m_window.getSize();
	return sf::Vector2f(static_cast<float>(size.x), static_cast<float>(size.y));
}

// --- Kiểm tra xem entity (bullet) có nằm ngoài ranh giới không ---
bool Game::isOutOfBounds(const Entity& entity, float margin) {
	if (!entity.cPosition) return false;

	Vector2f pos = entity.cPosition->position;
	sf::Vector2f windowSize = getWindowSize();

	return (pos.x < -margin ||
		pos.x > windowSize.x + margin ||
		pos.y < -margin ||
		pos.y > windowSize.y + margin);
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

			if (isOutOfBounds(*bullet, 100.0f)) 
			{
				DeactivateBullet(*bullet);
			}

			if (collisionDetection(*bullet, *cur))
			{
				playSfx(m_collide, bullet->cPosition->position);
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
