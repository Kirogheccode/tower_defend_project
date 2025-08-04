#include "Game.h"

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

bool collisionDetection(const Entity& entity1, const Entity& entity2)
{
	if (!entity1.cSet || !entity2.cSet) return false;
	FloatRect bounds1 = scaleRect(entity1.cSet->sprite.getGlobalBounds(), entity2.cBoundaryScale->scale / 100.0f);
	FloatRect bounds2 = scaleRect(entity2.cSet->sprite.getGlobalBounds(), entity2.cBoundaryScale->scale / 100.0f);

	return isContained(bounds1, bounds2);
}


// --- Hệ thống ---
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

		if (e->cText)
		{
			m_window.draw(e->cText->text);
		}

		if (e->cBound)
			m_window.draw(e->cBound->rectangle);
	}

	if (m_state == AppState::StoryScene)
	{
		m_window.clear();
		for (auto& e : m_scenes[m_state].getEntities())
		{
			if (e->cSet)  m_window.draw(e->cSet->sprite);
			if (e->cText) m_window.draw(e->cText->text);
		}
		m_window.display();
		return;
	}

	// Hiển thị quái, đạn và tháp
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
					float trueRadius = e->cBound->radius * m_multiplies[e->cLevel->levelindex];
					e->cBound->circle.setRadius(trueRadius);
					e->cBound->circle.setOrigin(trueRadius, trueRadius);
					e->cBound->circle.setPosition(e->cPosition->position);
					m_window.draw(e->cBound->circle);

				}
			}

			if (e->cText)
				m_window.draw(e->cText->text);
		}
	}

	if (game_state == AppState::GamePlay)
	{
		// Vẽ các entity có sprite
		for (auto& e : m_scenes[game_state].getEntities())
		{
			if (!e->cSet || !e->cPosition) continue;

			e->cSet->sprite.setPosition(e->cPosition->position);

			if (e->tag() == "Heart")
			{
				if (e->isActive())
					m_window.draw(e->cSet->sprite);
			}
			else
			{
				m_window.draw(e->cSet->sprite);
			}
		}

		// Vẽ tiền
		for (auto& e : m_scenes[game_state].getEntities("MoneyText"))
		{
			if (e->cText)
			{
				e->cText->text.setString(to_string(m_coin));
				m_window.draw(e->cText->text);
			}
		}

		// Vẽ Wave nếu cần
		if (m_showWaveText && m_currentWave < 3)
		{
			for (auto& e : m_scenes[game_state].getEntities("WaveText"))
			{
				if (e->cText)
					m_window.draw(e->cText->text);
			}

			for (auto& e : m_scenes[game_state].getEntities("WaveNumber"))
			{
				if (e->cText)
				{
					e->cText->text.setString(to_string(m_currentWave + 1));
					m_window.draw(e->cText->text);
				}
			}

			if (m_waveClock.getElapsedTime().asSeconds() > m_waveDisplayDuration)
			{
				m_showWaveText = false;
			}
		}

		// Vẽ UI của tháp được chọn
		if (m_clickedTower)
		{
			for (auto& e : m_scenes[game_state].getEntities())
			{
				if (e->tag() == "towerName" || e->tag() == "towerDamage" || e->tag() == "towerCooldown" ||
					e->tag() == "towerRange" || e->tag() == "sellButton" || e->tag() == "upgradeButton" ||
					e->tag() == "towerDamageNext" || e->tag() == "towerCooldownNext" || e->tag() == "towerRangeNext" || e->tag() == "towerLevel")
				{
					if (e->cText)
						m_window.draw(e->cText->text);
				}
				else if (e->tag() == "rectangle")
				{
					if (e->cBound)
						m_window.draw(e->cBound->rectangle);
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

			if (e->cSet)
				m_window.draw(e->cSet->sprite);
			if (e->cText)
				m_window.draw(e->cText->text);

			if (e->cSlider)
			{
				m_window.draw(e->cSlider->track);
				m_window.draw(e->cSlider->handle);
			}

			if (e->cText)
				m_window.draw(e->cText->text);

			if (e->cBound)
				m_window.draw(e->cBound->rectangle);
		}

		if (m_state2 == AppState::TowerPlace)
		{
			sf::Vector2f mousePos = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
			for (auto& e : m_entities.getEntities("Cursor")) 
			{
				if (e->isActive())
				{
					e->cSet->sprite.setPosition(mousePos);
					m_window.draw(e->cSet->sprite);
				}
			}
		}
	}

	m_window.display();
}

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
				if (bullet->tag() == m_bullet01Config.tag)
					bullet->cDamage->damage = m_bullet01Config.damage;
				else if (bullet->tag() == m_bullet02Config.tag)
					bullet->cDamage->damage = m_bullet02Config.damage;

				DeactivateBullet(*bullet);
			}

			if (collisionDetection(*bullet, *cur))
			{
				playSfx(m_collide, bullet->cPosition->position);
				if (cur->cHealth)
				{
					// cout << "[DEBUG] Enenimes health: " << cur->cHealth->hp << endl;

					cur->cHealth->hp -= bullet->cDamage->damage;

					// cout << "[DEBUG] Damage bullet: " << bullet->cDamage->damage << endl;
					// cout << "[DEBUG] Enenimes health after being shoot: " << cur->cHealth->hp << endl;

					if (cur->cHealth->hp <= 0)
					{
						m_coin += cur->cMoney->money;
						DeactivateEnemy(*cur);
					}
				}

				if (bullet->tag() == m_bullet01Config.tag)
					bullet->cDamage->damage = m_bullet01Config.damage;
				else if (bullet->tag() == m_bullet02Config.tag)
					bullet->cDamage->damage = m_bullet02Config.damage;

				DeactivateBullet(*bullet);
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
			if (entity->cMovement->currentPathindex >= entity->cMovement->paths[m_mapindex][entity->cMovement->pathIndex].size())
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
					m_state1 = AppState::Defeat;
					m_paused = true;
					heartvector[index]->active(false);
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
			Vector2f target = entity->cMovement->paths[m_mapindex][entity->cMovement->pathIndex][entity->cMovement->currentPathindex];
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
				entity->cPosition->position += movement * (entity->cMovement->speed * m_speedup) * deltaTime;

				// Lật sprite theo hướng di chuyển
				float baseScale = 1.f;

				if (entity->cSpriteScale) baseScale = entity->cSpriteScale->scale;

				// Tính toán để dự đoán hướng quay mặt tiếp theo
				int currentIndex = entity->cMovement->currentPathindex;
				int nextIndex = currentIndex + 1;

				if (nextIndex < (int)entity->cMovement->paths[m_mapindex][entity->cMovement->pathIndex].size())
				{
					Vector2f currentTarget = entity->cMovement->paths[m_mapindex][entity->cMovement->pathIndex][currentIndex];
					Vector2f nextTarget = entity->cMovement->paths[m_mapindex][entity->cMovement->pathIndex][nextIndex];

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

		if (m_state == AppState::StoryScene)
		{
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				for (auto& e : m_scenes[AppState::StoryScene].getEntities("SkipButton"))
				{
					if (e->cText && e->cInput && e->cText->text.getGlobalBounds().contains(mousePos))
					{
						if (e->cInput->onClick)
							e->cInput->onClick();
						return;
					}
				}

				m_storyIndex++;
				if (m_storyIndex < m_storyQueue.size())
				{
					auto bgList = m_scenes[AppState::StoryScene].getEntities("StoryBG");
					auto textList = m_scenes[AppState::StoryScene].getEntities("StoryText");

					if (bgList.empty() || textList.empty()) return;

					auto& bg = bgList.front();
					auto& text = textList.front();


					bg->cSet->texture.loadFromFile(m_storyQueue[m_storyIndex].first);
					setStoryTextWrapped(m_storyQueue[m_storyIndex].second);
				}
				else
				{
					m_state = m_nextStateAfterStory;
				}
			}
			return;
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

		// --- Click chuột trái
		if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
		{
			if (!(m_state1 == AppState::OptionMenu || m_state1 == AppState::SettingsMenu || m_state1 == AppState::Defeat || m_state1 == AppState::Victory))
			{
				m_clickedTower = false;

				for (auto& tower : m_entities.getEntities("Tower"))
				{
					if (tower->isActive() && tower->cSet->sprite.getGlobalBounds().contains(mousePos))
					{
						// Reset hiển thị range hết tháp để chỉ hiển thị một tháp
						for (auto& other : m_entities.getEntities("Tower"))
						{
							if (other->cInput) other->cInput->isChoosing = false;
						}

						if (tower->cInput)
						{
							tower->cInput->onClick();
						}

						Vector2f basePos = tower->cPosition->position + Vector2f(60.f, -140.f);

						for (auto& e : m_scenes[AppState::GamePlay].getEntities())
						{
							if (e->tag() == "rectangle" && e->cBound)
							{
								e->cBound->rect.left = basePos.x;
								e->cBound->rect.top = basePos.y;

								e->cBound->rectangle.setPosition(e->cBound->rect.left, e->cBound->rect.top);
							}
							else if (e->cText)
							{
								if (e->tag() == "towerName")
								{
									e->cText->text.setString(tower->tag());
									e->cText->text.setPosition(basePos + Vector2f(10, 10));
								}
								else if (e->tag() == "towerLevel")
								{
									if (tower->cLevel->levelindex < 3)
									{
										e->cText->text.setString("LEVEL " + to_string(tower->cLevel->levelindex + 1));
									}
									else
									{
										e->cText->text.setString("LEVEL MAX");
									}

									e->cText->text.setPosition(basePos + Vector2f(160, 25));
								}
								else if (e->tag() == "towerDamage")
								{
									if (tower->cWeapon->tag == m_bullet01Config.tag)
										e->cText->text.setString("Damage " + to_string((int)(m_bullet01Config.damage * m_multiplies[tower->cLevel->levelindex])));
									else if (tower->cWeapon->tag == m_bullet02Config.tag)
										e->cText->text.setString("Damage " + to_string((int)(m_bullet02Config.damage * m_multiplies[tower->cLevel->levelindex])));
									else if (tower->cWeapon->tag == m_bullet03Config.tag)
										e->cText->text.setString("Damage " + to_string((int)(m_bullet03Config.damage * m_multiplies[tower->cLevel->levelindex])));
									else if (tower->cWeapon->tag == m_bullet04Config.tag)
										e->cText->text.setString("Damage " + to_string((int)(m_bullet04Config.damage * m_multiplies[tower->cLevel->levelindex])));
									else if (tower->cWeapon->tag == m_bullet05Config.tag)
										e->cText->text.setString("Damage " + to_string((int)(m_bullet05Config.damage * m_multiplies[tower->cLevel->levelindex])));
									else if (tower->cWeapon->tag == m_bullet06Config.tag)
										e->cText->text.setString("Damage " + to_string((int)(m_bullet06Config.damage * m_multiplies[tower->cLevel->levelindex])));

									e->cText->text.setPosition(basePos + Vector2f(10, 60));
								}
								else if (e->tag() == "towerDamageNext")
								{
									if (tower->cLevel->levelindex < 3)
									{
										if (tower->cWeapon->tag == m_bullet01Config.tag)
											e->cText->text.setString("Damage " + to_string((int)(m_bullet01Config.damage * m_multiplies[tower->cLevel->levelindex + 1])));
										else if (tower->cWeapon->tag == m_bullet02Config.tag)
											e->cText->text.setString("Damage " + to_string((int)(m_bullet02Config.damage * m_multiplies[tower->cLevel->levelindex + 1])));
										else if (tower->cWeapon->tag == m_bullet03Config.tag)
											e->cText->text.setString("Damage " + to_string((int)(m_bullet03Config.damage * m_multiplies[tower->cLevel->levelindex + 1])));
										else if (tower->cWeapon->tag == m_bullet04Config.tag)
											e->cText->text.setString("Damage " + to_string((int)(m_bullet04Config.damage * m_multiplies[tower->cLevel->levelindex + 1])));
										else if (tower->cWeapon->tag == m_bullet05Config.tag)
											e->cText->text.setString("Damage " + to_string((int)(m_bullet05Config.damage * m_multiplies[tower->cLevel->levelindex + 1])));
										else if (tower->cWeapon->tag == m_bullet06Config.tag)
											e->cText->text.setString("Damage " + to_string((int)(m_bullet06Config.damage * m_multiplies[tower->cLevel->levelindex + 1])));
									}
									else
									{
										e->cText->text.setString("MAX");
									}

									e->cText->text.setPosition(basePos + Vector2f(160, 60));
								}
								else if (e->tag() == "towerRange")
								{
									if (tower->cBound && tower->cLevel)
										e->cText->text.setString("Range " + to_string((int)(tower->cBound->radius * m_multiplies[tower->cLevel->levelindex])));

									e->cText->text.setPosition(basePos + Vector2f(10, 120));
								}
								else if (e->tag() == "towerRangeNext")
								{
									if (tower->cLevel->levelindex < 3)
									{
										if (tower->cBound && tower->cLevel)
											e->cText->text.setString(to_string((int)(tower->cBound->radius * m_multiplies[tower->cLevel->levelindex + 1])));
									}
									else
									{
										e->cText->text.setString("MAX");
									}

									e->cText->text.setPosition(basePos + Vector2f(160, 120));
								}
								else if (e->tag() == "towerCooldown")
								{
									if (tower->cCooldown && tower->cLevel)
									{
										float baseSeconds = tower->cCooldown->cooldownDuration.asSeconds();
										int realSeconds = (int)(baseSeconds / m_multiplies[tower->cLevel->levelindex]);

										e->cText->text.setString("Cooldown " + to_string(realSeconds));
									}

									e->cText->text.setPosition(basePos + Vector2f(10, 90));
								}
								else if (e->tag() == "towerCooldownNext")
								{
									if (tower->cCooldown && tower->cLevel)
									{
										if (tower->cLevel->levelindex < 3)
										{
											float baseSeconds = tower->cCooldown->cooldownDuration.asSeconds();
											int nextSeconds = (int)(baseSeconds / m_multiplies[tower->cLevel->levelindex + 1]);

											e->cText->text.setString(to_string(nextSeconds));
										}
										else
										{
											e->cText->text.setString("MAX");
										}
									}

									e->cText->text.setPosition(basePos + Vector2f(160, 90));
								}
								else if (e->tag() == "sellButton")
								{
									if (e->cInput)
										e->cInput->onClick = [this, tower]() {
										RemoveTower(*tower);
										};

									if (tower->cMoney && tower->cLevel)
									{
										int sellValue = tower->cMoney->money * m_multiplies[tower->cLevel->levelindex] * m_refund;
										e->cText->text.setString("SELL " + to_string(sellValue));
									}

									e->cText->text.setPosition(basePos + Vector2f(10, 160));
								}
								else if (e->tag() == "upgradeButton")
								{
									if (tower->cLevel)
									{
										if (tower->cLevel->levelindex < 3)
										{
											int upgradecost = tower->cMoney->money * m_multiplies[tower->cLevel->levelindex + 1];

											e->cText->text.setString("UPGRADE " + to_string(upgradecost));

											e->cText->text.setPosition(basePos + Vector2f(140, 160));

											if (e->cInput)
												e->cInput->onClick = [this, tower]() {
												m_clickedTower = true;
												UpgradeTower(*tower);
												};
										}
										else
										{
											e->cText->text.setString("UPGRADE MAX");

											e->cText->text.setPosition(basePos + Vector2f(140, 160));

											if (e->cInput)
												e->cInput->onClick = [this, &tower]() {
												m_clickedTower = true;
												};
										}
									}
								}
							}
						}

						m_clickedTower = true;
						break;
					}
				}
				for (auto& e : m_scenes[AppState::GamePlay].getEntities())
				{
					if (e->cText && e->cInput && e->cText->text.getGlobalBounds().contains(mousePos))
					{
						if (e->tag() == "sellButton")
						{
							playSfx(m_sell);
						}
						else
						{
							playSfx(m_clickBuffer);
						}
						e->cInput->onClick();
					}
				}


				// Reset hiển thị range nếu bấm ra ngoài tháp
				if (!m_clickedTower)
				{
					for (auto& tower : m_entities.getEntities("Tower"))
					{
						if (tower->cInput) tower->cInput->isChoosing = false;
					}
				}
			}
			bool clickedSlider = false;

			if (!clickedSlider)
			{
				// Ưu tiên state2 nếu đang chọn tower

				if (m_state2 == AppState::TowerPlace)
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
							placing.x = e->cSet->sprite.getGlobalBounds().left + e->cSet->sprite.getGlobalBounds().width / 2.f;
							placing.y = e->cSet->sprite.getGlobalBounds().top + e->cSet->sprite.getGlobalBounds().height / 2.f;

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
					for (auto& e : m_entities.getEntities("Cursor"))
					{
						e->active(false);
					}
					m_window.setMouseCursorVisible(true);
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
		else if (e->cText && e->cInput)
		{
			bool hovering = e->cText->text.getGlobalBounds().contains(mousePos);

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
	if (!(hoverState == AppState::OptionMenu || hoverState == AppState::SettingsMenu || hoverState == AppState::Defeat || hoverState == AppState::Victory))
	{

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

		for (auto& e : m_scenes[AppState::GamePlay].getEntities())
		{
			if (e->cText && e->cInput)
			{
				bool hovering = e->cText->text.getGlobalBounds().contains(mousePos);

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
}

void Game::run()
{
	while (m_running)
	{
		dt = m_clock.restart().asSeconds();

		sUserInput();
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
			sRender(dt); 
		}
	}
}


// --- Save/load ---
void Game::queueSave() {
	cout << "queueSave called\n";
	thread saveThread([this]() {
		lock_guard<mutex> lock(saveMutex);  // Lock for entire save
		sSaveGame();
		});
	saveThread.detach();  // Async
}

void Game::sSaveGame()
{

	cout << "sSaveGame called\n";

	cout << fileForSave << "\n";

	//std::ofstream writePlayer(fileName, std::ios::out | std::ios::trunc);
	//if (!writePlayer.is_open()) {
	//	std::cerr << "Error opening file: " << fileName << " (check permissions or path).\n";
	//	return;
	//}

	cout << "[DEBUG] Before write: State " << writePlayer.rdstate() << " (0 = good)\n";
	startWriting(fileForSave);  // Start writing to the file

	writePlayer.clear();  // Reset any potential error state

	// Helper to check stream after writes
	auto checkStream = [&]()
		{
			if (writePlayer.fail())
			{
				cerr << "Write error occurred. State: " << writePlayer.rdstate() << "\n";
				writePlayer.clear();  // Attempt to recover
				return false;
			}
			return true;
		};
	// Lưu tên game save - thời điểm save
	string map_name = "Map" + to_string(m_mapindex + 1);
	shared_ptr<Entity> mapButton = nullptr;
	for (auto& e : m_scenes[AppState::LoadGame].getEntities())
	{
		if (e->tag() == map_name)
		{
			mapButton = e;
			break;
		}
	}

	if (mapButton)
	{
		mapButton->cTime = make_shared<CTime>();
		auto& takeTime = mapButton->cTime;
		ostringstream oss;
		oss << setfill('0') << setw(2) << takeTime->local.tm_mday << "/"
			<< setw(2) << takeTime->local.tm_mon + 1 << "/"
			<< takeTime->local.tm_year + 1900;
		string date = oss.str();
		oss.str("");
		oss.clear();
		oss << setfill('0') << setw(2) << takeTime->local.tm_hour << ":"
			<< setw(2) << takeTime->local.tm_min << ":"
			<< setw(2) << takeTime->local.tm_sec;
		string TiMe = oss.str();

		mapButton->cText = make_shared<CText>(date + " " + TiMe);
		mapButton->cText->text.setFont(m_font1);
		mapButton->cText->text.setCharacterSize(25);
		mapButton->cText->text.setFillColor(Color::White);
		mapButton->cText->text.setStyle(Text::Bold);

		FloatRect bounds = mapButton->cText->text.getLocalBounds();
		mapButton->cText->text.setOrigin(bounds.left + bounds.width / 2.f, bounds.top);
		/*cout << "Saving" << endl;
		cout << bounds.width << " " << bounds.height << "\n";
		cout << bounds.left << " " << bounds.top << "\n";*/

		Vector2f buttonPos = mapButton->cPosition->position;
		Vector2f buttonSize(1920.f * 0.25f, 1080.f * 0.25f);

		mapButton->cText->text.setPosition(buttonPos.x + buttonSize.x / 2.f, buttonPos.y + buttonSize.y + 20.f);

		writePlayer << "# Information of game save: " << "\n";
		writePlayer << date << " " << TiMe << "\n";
	}

	if (!checkStream())
	{
		cerr << "Error writing health data.\n";
		writePlayer.close();
		return;
	}
	writePlayer << "\n";

	// Lưu wave
	writePlayer << "# Current wave index: " << "\n";
	writePlayer << m_currentWave << "\n";
	writePlayer << "\n";

	// Lưu index của máu còn lại
	writePlayer << "# Remaining health: " << "\n";
	for (auto& e : m_scenes[AppState::GamePlay].getEntities("Heart"))
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
		cerr << "Error writing health data.\n";
		writePlayer.close();
		return;
	}

	// Lưu tiền
	writePlayer << "# Money: " << "\n";
	writePlayer << m_coin << "\n";
	writePlayer << "\n";

	if (!checkStream())
	{
		cerr << "Error writing health data.\n";
		writePlayer.close();
		return;
	}

	// Lưu biến đếm khi spawn
	writePlayer << "# Spawning timer: " << "\n";
	writePlayer << m_spawnTimer << " " << m_spawningTimer << "\n";
	writePlayer << "\n";

	// Lưu số lượng quái đã spawn
	writePlayer << "# Spanwed enemies: " << "\n";
	writePlayer << m_spawnedType1 << " " << m_spawnedType2 << " " << m_spawnedType3 << "\n";
	writePlayer << "\n";

	// Lưu spawning stage
	writePlayer << "# Spawning stage" << "\n";
	if (m_spawnStage == SpawnStage::Type1)
	{
		writePlayer << "Type1" << "\n";
	}
	else if (m_spawnStage == SpawnStage::Type2)
	{
		writePlayer << "Type2" << "\n";
	}
	else if (m_spawnStage == SpawnStage::Type3)
	{
		writePlayer << "Type3" << "\n";
	}
	else if (m_spawnStage == SpawnStage::None)
	{
		writePlayer << "None" << "\n";
	}
	else if (m_spawnStage == SpawnStage::Done)
	{
		writePlayer << "Done" << "\n";
	}
	writePlayer << "\n";

	// Lưu vị trí quái
	writePlayer << "# Enemies position" << "\n";
	bool isExist = false;
	for (auto& entity : m_entities.getEntities(m_enemyType1Config.tag))
	{
		if (entity->isActive())
		{
			Vector2f originalScale = entity->cSet->sprite.getScale();

			writePlayer << entity->cPosition->position.x << " " << entity->cPosition->position.y << " " << originalScale.x << " " << originalScale.y << " " << entity->cMovement->currentPathindex << " " << entity->cMovement->pathIndex << " ";
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
		cerr << "Error writing health data.\n";
		writePlayer.close();
		return;
	}

	for (auto& entity : m_entities.getEntities(m_enemyType2Config.tag))
	{
		if (entity->isActive())
		{
			Vector2f originalScale = entity->cSet->sprite.getScale();

			writePlayer << entity->cPosition->position.x << " " << entity->cPosition->position.y << " " << originalScale.x << " " << originalScale.y << " " << entity->cMovement->currentPathindex << " " << entity->cMovement->pathIndex << " ";
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
			Vector2f originalScale = entity->cSet->sprite.getScale();

			writePlayer << entity->cPosition->position.x << " " << entity->cPosition->position.y << " " << originalScale.x << " " << originalScale.y << " " << entity->cMovement->currentPathindex << " " << entity->cMovement->pathIndex << " ";
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
			writePlayer << entity->cPosition->position.x << " " << entity->cPosition->position.y << " " << entity->cLevel->levelindex << " ";
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
			writePlayer << entity->cPosition->position.x << " " << entity->cPosition->position.y << " " << entity->cLevel->levelindex << " ";
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
			writePlayer << entity->cPosition->position.x << " " << entity->cPosition->position.y << " " << entity->cLevel->levelindex << " ";
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
			writePlayer << entity->cPosition->position.x << " " << entity->cPosition->position.y << " " << entity->cLevel->levelindex << " ";
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
			writePlayer << entity->cPosition->position.x << " " << entity->cPosition->position.y << " " << entity->cLevel->levelindex << " ";
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
			writePlayer << entity->cPosition->position.x << " " << entity->cPosition->position.y << " " << entity->cLevel->levelindex << " ";
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
		cerr << "Error writing health data.\n";
		writePlayer.close();
		return;
	}
	if (writePlayer.fail()) {
		cerr << "Error writing to file.\n";
	}

	cout << "has been written" << endl;
	writePlayer.flush();  // Ensure writes are committed
	this_thread::sleep_for(chrono::milliseconds(100));
	//writePlayer.close();
	stopWriting();  // Stop writing to the file


	cout << "[DEBUG] After write: State " << writePlayer.rdstate() << "\n";
	cout << "Game saved successfully.\n";
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
	// Bỏ qua 2 dòng đầu
	string line;
	while (getline(readPlayer, line))
	{
		if (line.empty() || line[0] == '#') continue;
		break;
	}

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

	// Load biến time cho việc spawning
	while (getline(readPlayer, line))
	{
		if (line.empty() || line[0] == '#') continue;
		istringstream iss(line);

		iss >> m_spawnTimer >> m_spawningTimer;

		break;
	}

	// Load số lượng quái đã spawn
	while (getline(readPlayer, line))
	{
		if (line.empty() || line[0] == '#') continue;
		istringstream iss(line);

		iss >> m_spawnedType1 >> m_spawnedType2 >> m_spawnedType3;

		break;
	}

	// Load spawnStage
	while (getline(readPlayer, line))
	{
		if (line.empty() || line[0] == '#') continue;
		if (line[0] == '@') break;
		istringstream iss(line);

		string stage;
		iss >> stage;

		if (stage == "None") m_spawnStage = SpawnStage::None;
		else if (stage == "Type1") m_spawnStage = SpawnStage::Type1;
		else if (stage == "Type2") m_spawnStage == SpawnStage::Type2;
		else if (stage == "Type3") m_spawnStage == SpawnStage::Type3;
		else if (stage == "Done") m_spawnStage == SpawnStage::Done;

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
			int path;
			float scaleX, scaleY;

			if (!(iss >> x >> y >> scaleX >> scaleY >> index >> path)) break;

			Vector2f pos(x, y);

			enemy->cPosition = make_shared<CPosition>(pos);
			enemy->cSet->sprite.setPosition(enemy->cPosition->position);
			enemy->cSet->sprite.setScale(scaleX, scaleY);
			enemy->cMovement->pathIndex = path;
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
			int path;
			float scaleX, scaleY;

			if (!(iss >> x >> y >> scaleX >> scaleY >> index >> path)) break;

			Vector2f pos(x, y);

			enemy->cPosition = make_shared<CPosition>(pos);
			enemy->cSet->sprite.setPosition(enemy->cPosition->position);
			enemy->cSet->sprite.setScale(scaleX, scaleY);
			enemy->active(true);
			enemy->cMovement->pathIndex = path;
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
			int path;
			float scaleX, scaleY;

			if (!(iss >> x >> y >> scaleX >> scaleY >> index >> path)) break;

			Vector2f pos(x, y);

			enemy->cPosition = make_shared<CPosition>(pos);
			enemy->cSet->sprite.setPosition(enemy->cPosition->position);
			enemy->cSet->sprite.setScale(scaleX, scaleY);
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
		// cout << line << endl;
		for (auto& tower : m_entities.getEntities(m_towerType1Config.tag))
		{
			float x, y;
			int index;

			if (!(iss >> x >> y >> index)) break;

			Vector2f pos(x, y);

			tower->cPosition = make_shared<CPosition>(pos);
			tower->cSet->sprite.setPosition(tower->cPosition->position);
			tower->cLevel = make_shared<CLevel>(index);
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
		// cout << line << endl;
		for (auto& tower : m_entities.getEntities(m_towerType2Config.tag))
		{
			float x, y;
			int index;

			if (!(iss >> x >> y >> index)) break;

			Vector2f pos(x, y);

			tower->cPosition = make_shared<CPosition>(pos);
			tower->cSet->sprite.setPosition(tower->cPosition->position);
			tower->cLevel = make_shared<CLevel>(index);
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
		// cout << line << endl;
		for (auto& tower : m_entities.getEntities(m_towerType3Config.tag))
		{
			float x, y;
			int index;

			if (!(iss >> x >> y >> index)) break;

			Vector2f pos(x, y);

			tower->cPosition = make_shared<CPosition>(pos);
			tower->cSet->sprite.setPosition(tower->cPosition->position);
			tower->cLevel = make_shared<CLevel>(index);
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
		// cout << line << endl;
		for (auto& tower : m_entities.getEntities(m_towerType4Config.tag))
		{
			float x, y;
			int index;

			if (!(iss >> x >> y >> index)) break;

			Vector2f pos(x, y);

			tower->cPosition = make_shared<CPosition>(pos);
			tower->cSet->sprite.setPosition(tower->cPosition->position);
			tower->cLevel = make_shared<CLevel>(index);
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
		// cout << line << endl;
		for (auto& tower : m_entities.getEntities(m_towerType5Config.tag))
		{
			float x, y;
			int index;

			if (!(iss >> x >> y >> index)) break;

			Vector2f pos(x, y);

			tower->cPosition = make_shared<CPosition>(pos);
			tower->cSet->sprite.setPosition(tower->cPosition->position);
			tower->cLevel = make_shared<CLevel>(index);
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
		// cout << line << endl;
		for (auto& tower : m_entities.getEntities(m_towerType6Config.tag))
		{
			float x, y;
			int index;

			if (!(iss >> x >> y >> index)) break;

			Vector2f pos(x, y);

			tower->cPosition = make_shared<CPosition>(pos);
			tower->cSet->sprite.setPosition(tower->cPosition->position);
			tower->cLevel = make_shared<CLevel>(index);
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

bool Game::isFileEmpty(const string& filename) {
	ifstream file(filename, ios::ate | ios::binary); // mở và nhảy đến cuối file
	if (!file.is_open())
		return true; // nếu không mở được thì coi như rỗng (tùy yêu cầu)

	return file.tellg() == 0; // nếu vị trí con trỏ là 0 => file rỗng
}

void Game::setSaveTime(shared_ptr<Entity> mapButton, ifstream& in)
{
	string date, TiMe, tmp;
	FloatRect bounds;
	
	getline(in, tmp);
	getline(in, tmp);
	istringstream iss(tmp);
	iss >> date >> TiMe;

	mapButton->cText = make_shared<CText>(date + " " + TiMe);

	mapButton->cText->text.setFont(m_font1);
	mapButton->cText->text.setCharacterSize(25);
	mapButton->cText->text.setFillColor(Color::White);
	mapButton->cText->text.setStyle(Text::Bold);


	FloatRect bounds1 = mapButton->cText->text.getLocalBounds();
	/*cout << bounds.width << " " << bounds.height << "\n";
	cout << bounds.left << " " << bounds.top << "\n";*/
	mapButton->cText->text.setOrigin(bounds1.left + bounds1.width / 2.f, bounds1.top);

	Vector2f buttonPos = mapButton->cPosition->position;
	Vector2f buttonSize(1920.f * 0.25f, 1080.f * 0.25f);

	mapButton->cText->text.setPosition(buttonPos.x + buttonSize.x / 2.f, buttonPos.y + buttonSize.y + 20.f);
	
}

void Game::startWriting(const string& filename) {
	writePlayer.open(filename, ios::out | ios::trunc);
	if (!writePlayer.is_open()) {
		cerr << "FATAL: Could not open file: " << filename << endl;
	}
	writePlayer.clear();
}

void Game::stopWriting() {
	if (writePlayer.is_open()) {
		writePlayer.flush();
		this_thread::sleep_for(chrono::milliseconds(100));
		writePlayer.close();
	}
}


// --- Âm thanh và Xử lý sự kiện ---
void Game::playSfx(const sf::SoundBuffer& buffer, sf::Vector2f position) {
	if (m_sfxMuted) return;
	m_activeSounds.remove_if([](const sf::Sound& s) { return s.getStatus() == Sound::Stopped; });
	Sound& newSound = m_activeSounds.emplace_back();
	newSound.setBuffer(buffer);
	newSound.setVolume(m_sfxVolume);
	newSound.play();
}

void Game::updateAudioSettings() {
	if (m_musicMuted) {
		m_backgroundMusic.setVolume(0);
		m_mapMusic[m_mapindex].setVolume(0);
		m_mapSelect.setVolume(0);
		m_defeatMusic.setVolume(0);
		m_victoryMusic.setVolume(0);
	}
	else {
		m_backgroundMusic.setVolume(m_musicVolume);
		m_mapMusic[m_mapindex].setVolume(m_musicVolume);
		m_mapSelect.setVolume(m_musicVolume);
		m_defeatMusic.setVolume(m_musicVolume);
		m_victoryMusic.setVolume(m_musicVolume);
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
		if (m_victoryMusic.getStatus() == Music::Playing)
			m_victoryMusic.stop();
		if (m_defeatMusic.getStatus() == Music::Playing)
			m_defeatMusic.stop();

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
		if (m_victoryMusic.getStatus() == Music::Playing)
			m_victoryMusic.stop();
		if (m_defeatMusic.getStatus() == Music::Playing)
			m_defeatMusic.stop();

		if (m_mapSelect.getStatus() != sf::Music::Playing)
			m_mapSelect.play();
	}
	else if (m_state1 == AppState::Defeat || m_state1 == AppState::Victory)
	{
		if (m_mapMusic[m_mapindex].getStatus() == Music::Playing)
			m_mapMusic[m_mapindex].stop();
		if (m_backgroundMusic.getStatus() == Music::Playing)
			m_backgroundMusic.stop();
		if (m_mapSelect.getStatus() == Music::Playing)
			m_mapSelect.stop();


		if (m_state1 == AppState::Defeat && m_defeatMusic.getStatus() != Music::Playing)
			m_defeatMusic.play();
		else if (m_state1 == AppState::Victory && m_victoryMusic.getStatus() != Music::Playing)
			m_victoryMusic.play();
		
	}
	else if (m_state == AppState::Map1) {
		if (m_backgroundMusic.getStatus() == sf::Music::Playing)
			m_backgroundMusic.stop();
		if (m_mapSelect.getStatus() == sf::Music::Playing)
			m_mapSelect.stop();
		if (m_victoryMusic.getStatus() == Music::Playing)
			m_victoryMusic.stop();
		if (m_defeatMusic.getStatus() == Music::Playing)
			m_defeatMusic.stop();
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
		if (m_victoryMusic.getStatus() == Music::Playing)
			m_victoryMusic.stop();
		if (m_defeatMusic.getStatus() == Music::Playing)
			m_defeatMusic.stop();
		playMapMusic(2);
	}
	else if (m_state == AppState::Map4) {
		if (m_backgroundMusic.getStatus() == sf::Music::Playing)
			m_backgroundMusic.stop();
		if (m_mapSelect.getStatus() == sf::Music::Playing)
			m_mapSelect.stop();
		if (m_victoryMusic.getStatus() == Music::Playing)
			m_victoryMusic.stop();
		if (m_defeatMusic.getStatus() == Music::Playing)
			m_defeatMusic.stop();
		playMapMusic(3);
	}
	else {
		// Các state khác thì dừng hết
		if (m_backgroundMusic.getStatus() == sf::Music::Playing)
			m_backgroundMusic.stop();
		if (m_mapSelect.getStatus() == sf::Music::Playing)
			m_mapSelect.stop();
		if (m_victoryMusic.getStatus() == Music::Playing)
			m_victoryMusic.stop();
		if (m_defeatMusic.getStatus() == Music::Playing)
			m_defeatMusic.stop();
		for (auto& [idx, music] : m_mapMusic) {
			if (music.getStatus() == sf::Music::Playing) {
				music.stop();
			}
		}
	}
}


// --- Xử lí Story ---
std::string wrapText(const std::string& text, sf::Font& font, unsigned int characterSize, float maxWidth)
{
	sf::Text test;
	test.setFont(font);
	test.setCharacterSize(characterSize);

	std::istringstream iss(text);
	std::string word, line, result;

	while (iss >> word)
	{
		std::string tempLine = line + (line.empty() ? "" : " ") + word;
		test.setString(tempLine);

		if (test.getLocalBounds().width > maxWidth)
		{
			result += line + "\n";
			line = word;
		}
		else
		{
			line = tempLine;
		}
	}

	if (!line.empty())
		result += line;

	return result;
}

void Game::setStoryTextWrapped(const std::string& str)
{
	auto textList = m_scenes[AppState::StoryScene].getEntities("StoryText");

	if (textList.empty())
	{
		std::cerr << "[FATAL] setStoryTextWrapped: No StoryText entity found!\n";
		return;
	}

	auto& text = textList.front();

	if (!text->cText)
	{
		std::cerr << "[FATAL] setStoryTextWrapped: Missing cText!\n";
		return;
	}

	std::string wrapped = wrapText(str, m_font, text->cText->text.getCharacterSize(), 1500.f);
	text->cText->text.setString(wrapped);
}

void Game::playStoryBlock(const std::string& blockName, AppState nextState)
{
	auto it = m_storyBlocks.find(blockName);
	if (it == m_storyBlocks.end() || it->second.empty())
	{
		std::cerr << "[ERROR] Block not found or empty: " << blockName << "\n";
		m_state = nextState;
		return;
	}

	// Thiết lập dữ liệu truyện
	m_storyQueue = it->second;
	m_storyIndex = 0;
	m_nextStateAfterStory = nextState;
	m_state = AppState::StoryScene;

	auto bgList = m_scenes[AppState::StoryScene].getEntities("StoryBG");
	auto textList = m_scenes[AppState::StoryScene].getEntities("StoryText");

	if (bgList.empty() || textList.empty())
	{
		std::cerr << "[FATAL] StoryBG or StoryText entity missing!\n";
		m_state = nextState;
		return;
	}

	auto& bg = bgList.front();
	auto& text = textList.front();

	if (!bg->cSet)
	{
		std::cerr << "[FATAL] StoryBG entity missing cSet!\n";
		m_state = nextState;
		return;
	}

	if (!text->cText)
	{
		cerr << "[FATAL] StoryText entity missing cText!\n";
		m_state = nextState;
		return;
	}

	const string& imgPath = m_storyQueue[0].first;
	const string& storyText = m_storyQueue[0].second;

	if (!bg->cSet->texture.loadFromFile(imgPath))
	{
		std::cerr << "[ERROR] Failed to load image: " << imgPath << "\n";
	}
	else
	{
		bg->cSet->sprite.setTexture(bg->cSet->texture, true);
	}

	// Gán lời thoại
	float maxTextWidth = 1500.f;
	unsigned int charSize = 40;

	string wrapped = wrapText(m_storyQueue[m_storyIndex].second, m_font, charSize, maxTextWidth);
	text->cText->text.setString(wrapped);

}


// --- Tháp (Tower) ---
void Game::Shoot(Entity& tower)
{
	if (!tower.cTarget) return;

	for (auto& bullet : m_entities.getEntities(tower.cWeapon->tag))
	{
		if (!bullet->isActive())
		{
			bullet->cPosition = make_shared<CPosition>(tower.cPosition->position);
			bullet->cSet->sprite.setPosition(tower.cPosition->position);

			bullet->cDamage->damage = bullet->cDamage->damage * m_multiplies[tower.cLevel->levelindex];

			Vector2f direction = tower.cTarget->cPosition->position - tower.cPosition->position;
			Vector2f normalized_direction = MathSupport::Normalize(direction);

			float speed = 0.f;
			const string& tag = tower.cWeapon->tag;

			if (tag == m_bullet01Config.tag) speed = m_bullet01Config.speed;
			else if (tag == m_bullet02Config.tag) speed = m_bullet02Config.speed;
			else if (tag == m_bullet03Config.tag) speed = m_bullet03Config.speed;
			else if (tag == m_bullet04Config.tag) speed = m_bullet04Config.speed;
			else if (tag == m_bullet05Config.tag) speed = m_bullet05Config.speed;
			else if (tag == m_bullet06Config.tag) speed = m_bullet06Config.speed;

			bullet->cMovement->velocity = normalized_direction * (speed * m_speedup);

			bullet->active(true);
			break;
		}
	}
}

void Game::TowerAttack()
{
	for (auto& curTower : m_entities.getEntities("Tower"))
	{
		float baseCooldown = curTower->cCooldown->cooldownDuration.asSeconds();
		float actualCooldown = baseCooldown / m_multiplies[curTower->cLevel->levelindex] / m_speedup;

		if (curTower->isActive() && curTower->cCooldown->shootClock.getElapsedTime().asSeconds() >= actualCooldown)
		{
			shared_ptr<Entity> closestEnemy = nullptr;
			float range = curTower->cBound->radius * m_multiplies[curTower->cLevel->levelindex];
			float minDistance = range;

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
				curTower->cTarget = closestEnemy;
				Shoot(*curTower);
				curTower->cCooldown->shootClock.restart();
			}
		}
	}
}

void Game::UpgradeTower(Entity& tower)
{
	if (m_coin >= tower.cMoney->money * m_multiplies[tower.cLevel->levelindex + 1])
	{
		m_coin -= tower.cMoney->money * m_multiplies[tower.cLevel->levelindex + 1];

		tower.cLevel->levelindex++;

		Vector2f basePos = tower.cPosition->position + Vector2f(60.f, -140.f);

		for (auto& e : m_scenes[AppState::GamePlay].getEntities())
		{
			if (e->tag() == "rectangle" && e->cBound)
			{
				e->cBound->rect.left = basePos.x;
				e->cBound->rect.top = basePos.y;

				e->cBound->rectangle.setPosition(e->cBound->rect.left, e->cBound->rect.top);
			}
			else if (e->cText)
			{
				if (e->tag() == "towerName")
				{
					e->cText->text.setString(tower.tag());
					e->cText->text.setPosition(basePos + Vector2f(10, 10));
				}
				else if (e->tag() == "towerLevel")
				{
					if (tower.cLevel->levelindex < 3)
					{
						e->cText->text.setString("LEVEL " + to_string(tower.cLevel->levelindex + 1));
					}
					else
					{
						e->cText->text.setString("LEVEL MAX");
					}

					e->cText->text.setPosition(basePos + Vector2f(160, 25));
				}
				else if (e->tag() == "towerDamage")
				{
					if (tower.cWeapon->tag == m_bullet01Config.tag)
						e->cText->text.setString("Damage " + to_string((int)(m_bullet01Config.damage * m_multiplies[tower.cLevel->levelindex])));
					else if (tower.cWeapon->tag == m_bullet02Config.tag)
						e->cText->text.setString("Damage " + to_string((int)(m_bullet02Config.damage * m_multiplies[tower.cLevel->levelindex])));
					else if (tower.cWeapon->tag == m_bullet03Config.tag) 
						e->cText->text.setString("Damage " + to_string((int)(m_bullet03Config.damage * m_multiplies[tower.cLevel->levelindex])));
					else if (tower.cWeapon->tag == m_bullet04Config.tag)
						e->cText->text.setString("Damage " + to_string((int)(m_bullet04Config.damage * m_multiplies[tower.cLevel->levelindex])));
					else if (tower.cWeapon->tag == m_bullet05Config.tag)
						e->cText->text.setString("Damage " + to_string((int)(m_bullet05Config.damage * m_multiplies[tower.cLevel->levelindex])));
					else if (tower.cWeapon->tag == m_bullet06Config.tag)
						e->cText->text.setString("Damage " + to_string((int)(m_bullet06Config.damage * m_multiplies[tower.cLevel->levelindex])));

					e->cText->text.setPosition(basePos + Vector2f(10, 60));
				}
				else if (e->tag() == "towerDamageNext")
				{
					if (tower.cLevel->levelindex < 3)
					{
						if (tower.cWeapon->tag == m_bullet01Config.tag)
							e->cText->text.setString("Damage " + to_string((int)(m_bullet01Config.damage * m_multiplies[tower.cLevel->levelindex + 1])));
						else if (tower.cWeapon->tag == m_bullet02Config.tag)
							e->cText->text.setString("Damage " + to_string((int)(m_bullet02Config.damage * m_multiplies[tower.cLevel->levelindex + 1])));
						else if (tower.cWeapon->tag == m_bullet03Config.tag)
							e->cText->text.setString("Damage " + to_string((int)(m_bullet03Config.damage * m_multiplies[tower.cLevel->levelindex + 1])));
						else if (tower.cWeapon->tag == m_bullet04Config.tag)
							e->cText->text.setString("Damage " + to_string((int)(m_bullet04Config.damage * m_multiplies[tower.cLevel->levelindex + 1])));
						else if (tower.cWeapon->tag == m_bullet05Config.tag)
							e->cText->text.setString("Damage " + to_string((int)(m_bullet05Config.damage * m_multiplies[tower.cLevel->levelindex + 1])));
						else if (tower.cWeapon->tag == m_bullet06Config.tag)
							e->cText->text.setString("Damage " + to_string((int)(m_bullet06Config.damage * m_multiplies[tower.cLevel->levelindex + 1])));
					}
					else
					{
						e->cText->text.setString("MAX");
					}

					e->cText->text.setPosition(basePos + Vector2f(160, 60));
				}
				else if (e->tag() == "towerRange")
				{
					if (tower.cBound && tower.cLevel)
						e->cText->text.setString("Range " + to_string((int)(tower.cBound->radius * m_multiplies[tower.cLevel->levelindex])));

					e->cText->text.setPosition(basePos + Vector2f(10, 120));
				}
				else if (e->tag() == "towerRangeNext")
				{
					if (tower.cLevel->levelindex < 3)
					{
						if (tower.cBound && tower.cLevel)
							e->cText->text.setString(to_string((int)(tower.cBound->radius * m_multiplies[tower.cLevel->levelindex + 1])));
					}
					else
					{
						e->cText->text.setString("MAX");
					}

					e->cText->text.setPosition(basePos + Vector2f(160, 120));
				}
				else if (e->tag() == "towerCooldown")
				{
					if (tower.cCooldown && tower.cLevel)
					{
						float baseSeconds = tower.cCooldown->cooldownDuration.asSeconds();
						int realSeconds = (int)(baseSeconds / m_multiplies[tower.cLevel->levelindex]);

						e->cText->text.setString("Cooldown " + to_string(realSeconds));
					}

					e->cText->text.setPosition(basePos + Vector2f(10, 90));
				}
				else if (e->tag() == "towerCooldownNext")
				{
					if (tower.cCooldown && tower.cLevel)
					{
						if (tower.cLevel->levelindex < 3)
						{
							float baseSeconds = tower.cCooldown->cooldownDuration.asSeconds();
							int nextSeconds = (int)(baseSeconds / m_multiplies[tower.cLevel->levelindex + 1]);

							e->cText->text.setString(to_string(nextSeconds));
						}
						else
						{
							e->cText->text.setString("MAX");
						}
					}

					e->cText->text.setPosition(basePos + Vector2f(160, 90));
				}
				else if (e->tag() == "sellButton")
				{
					if (e->cInput)
						e->cInput->onClick = [this, &tower]() {
						RemoveTower(tower);
						};

					if (tower.cMoney && tower.cLevel)
					{
						int sellValue = tower.cMoney->money * m_multiplies[tower.cLevel->levelindex] * m_refund;
						e->cText->text.setString("SELL " + to_string(sellValue));
					}

					e->cText->text.setPosition(basePos + Vector2f(10, 160));
				}
				else if (e->tag() == "upgradeButton")
				{
					if (tower.cLevel)
					{
						if (tower.cLevel->levelindex < 3)
						{
							int upgradecost = tower.cMoney->money * m_multiplies[tower.cLevel->levelindex + 1];

							e->cText->text.setString("UPGRADE " + to_string(upgradecost));

							e->cText->text.setPosition(basePos + Vector2f(140, 160));

							if (e->cInput)
								e->cInput->onClick = [this, &tower]() {
								m_clickedTower = true;
								UpgradeTower(tower);
								};
						}
						else
						{
							e->cText->text.setString("UPGRADE MAX");

							e->cText->text.setPosition(basePos + Vector2f(140, 160));

							if (e->cInput)
								e->cInput->onClick = [this, &tower]() {
								m_clickedTower = true;
								};
						}
					}
				}
			}
		}
	}
}

void Game::RemoveTower(Entity& tower)
{
	bool remove = false;
	Vector2f removing;

	m_coin += m_refund * tower.cMoney->money * m_multiplies[tower.cLevel->levelindex];

	removing = tower.cPosition->position;
	DeactivateTower(tower);

	remove = true;

	for (auto& e : m_scenes[m_state].getEntities("Base"))
	{
		if (!e->isActive() && e->cSet->sprite.getGlobalBounds().contains(removing))
		{
			e->active(true);
			break;
		}
	}
}


// --- Tiện ích ----
Vector2f Game::getWindowSize() const {
	sf::Vector2u size = m_window.getSize();
	return sf::Vector2f(static_cast<float>(size.x), static_cast<float>(size.y));
}

bool Game::isOutOfBounds(const Entity& entity, float margin) {
	if (!entity.cPosition) return false;

	Vector2f pos = entity.cPosition->position;
	sf::Vector2f windowSize = getWindowSize();

	return (pos.x < -margin ||
		pos.x > windowSize.x + margin ||
		pos.y < -margin ||
		pos.y > windowSize.y + margin);
}

int rollDice() {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distrib(1, 4);
	return distrib(gen);
}


void Game::sHealthRecover()
{
	auto heartvector = m_scenes[AppState::GamePlay].getEntities("Heart");
	int index = static_cast<int> (heartvector.size()) - 1;

	while (index >= 0 && !heartvector[index]->isActive())
	{
		index--;
	}

	if (heartvector.size() - index == 1)
		return;

	heartvector[index + 1]->active(true);
}


void Game::sGacha()
{
	cout << "[DEBUG]: " << rollDice() << endl;
	switch (rollDice())
	{
	case 1:
		m_coin *= 1.5;
		break;

	case 2:
		sHealthRecover();
		break;

	case 3:
		for (auto& tow : m_scenes[game_state].getEntities("Tower"))
		{
			if (tow->isActive())
			{
				RemoveTower(*tow);
				break;
			}
		}
		break;

	case 4:
		//save for special effect
		break;
	}
}
