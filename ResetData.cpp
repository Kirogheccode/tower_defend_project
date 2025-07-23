#include "Game.h"

// --- Reset quái, tháp và ??n khi thoát game ---
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

	// Reset ??n
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

	// Reset tien
	m_coin = 0;

	// Reset wave
	m_currentWave = -1;

	// Reset wave
	m_showWaveText = false;
	m_finishWave = false;
	m_paused = false;
}

// --- Reset d? li?u ---
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

	// Reset chuy?n ??ng
	if (enemy.cMovement)
	{
		if (enemy.tag() == "EnemyType1")
		{
			enemy.cMovement->speed = m_enemyType1Config.speed;
		}
		else if (enemy.tag() == "EnemyType2")
		{
			enemy.cMovement->speed = m_enemyType2Config.speed;
		}
		else if (enemy.tag() == "EnemyType3")
		{
			enemy.cMovement->speed = m_enemyType3Config.speed;
		}

		enemy.cMovement->currentPathindex = 0;
	}

	// Reset v? trí
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