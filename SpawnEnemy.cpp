#include "Game.h"

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
		m_currentWave++;
		if (m_currentWave == 3)
		{
			m_state1 = AppState::Victory;
			m_paused = true;
			m_showWaveText = false;
			return;
		}


		m_finishWave = true;
		m_showWaveText = true;
		m_waveClock.restart();
	}
}

void Game::sSpawnWave(float& deltaTime)
{
	if (m_spawnStage == SpawnStage::None && m_finishWave)
	{
		m_spawnStage = SpawnStage::Type1;
		m_spawnTimer = 2.f;

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

	m_spawnTimer += deltaTime * m_speedup;

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

	m_spawningTimer += deltaTime * m_speedup;

	if (type == 1)
	{
		if (m_spawnedType1 >= wave.enemyType1Count) return true;

		for (auto& e : m_entities.getEntities(m_enemyType1Config.tag))
		{
			if (m_spawningTimer < m_spawningDelay + 0.1f) return false;

			if (!e->isActive())
			{
				m_spawningTimer = 0;

				if (m_mapindex == 3)
				{
					static random_device rd;
					static mt19937 gen(rd());
					static uniform_int_distribution<> dis(0, 3);
					int pathIndex = dis(gen);

					e->cMovement->pathIndex = pathIndex;
				}

				e->cPosition = make_shared<CPosition>(e->cMovement->starting_pos[m_mapindex]);
				e->cHealth->hp = e->cHealth->hp * m_multiplies[m_mapindex];
				e->cMovement->speed = e->cMovement->speed * m_multiplies[m_mapindex];
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
			if (m_spawningTimer < (m_spawningDelay) + 0.25f) return false;

			if (!e->isActive())
			{
				m_spawningTimer = 0;

				if (m_mapindex == 3)
				{
					static random_device rd;
					static mt19937 gen(rd());
					static uniform_int_distribution<> dis(0, 3);
					int pathIndex = dis(gen);

					e->cMovement->pathIndex = pathIndex;
				}

				e->cPosition = make_shared<CPosition>(e->cMovement->starting_pos[m_mapindex]);
				e->cHealth->hp = e->cHealth->hp * m_multiplies[m_mapindex];
				e->cMovement->speed = e->cMovement->speed * m_multiplies[m_mapindex];
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
			if (m_spawningTimer < (m_spawningDelay) + 0.5f) return false;

			if (!e->isActive())
			{
				m_spawningTimer = 0;

				if (m_mapindex == 3)
				{
					static random_device rd;
					static mt19937 gen(rd());
					static uniform_int_distribution<> dis(0, 3);
					int pathIndex = dis(gen);

					e->cMovement->pathIndex = pathIndex;
				}

				e->cPosition = make_shared<CPosition>(e->cMovement->starting_pos[m_mapindex]);
				e->cHealth->hp = e->cHealth->hp * m_multiplies[m_mapindex];
				e->cMovement->speed = e->cMovement->speed * m_multiplies[m_mapindex];
				e->active(true);

				m_spawnedType3++;
				break;
			}
		}

		return m_spawnedType3 >= wave.enemyType3Count;
	}

	return true;
}