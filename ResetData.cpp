#include "Game.h"

// --- Reset toàn bộ dữ liệu ---
void Game::sReset()
{
	// Reset quái
	for (auto& enemy : m_entities.getEntities("Enemy"))
		DeactivateEnemy(*enemy);

	m_finishWave = true;
	m_spawnStage = SpawnStage::None;

	// Reset tháp
	for (auto& tower : m_entities.getEntities("Tower"))
	{
		DeactivateTower(*tower);
	}

	// Reset đạn
	for (auto& bullet : m_entities.getEntities("Bullet"))
	{
		DeactivateBullet(*bullet);
	}

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

	// Reset tien (default: 1000)
	m_coin = 1000;

	// Reset wave
	m_currentWave = -1;

	// Reset text
	m_showWaveText = false;
	m_finishWave = false;
	m_paused = false;

	// Reset số lượng quái đã spawn
	m_spawnedType1 = 0;
	m_spawnedType2 = 0;
	m_spawnedType3 = 0;
}


// --- Reset dữ liệu đơn lẻ ---
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

	// Reset tốc độ
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

	// Đặt lại cấp độ của tháp về cấp đầu tiên
	tower.cLevel->levelindex = 0;

	// Vô hiệu hóa tháp
	tower.active(false);

	// Xóa vị trí nếu cần (tuỳ chọn)
	if (tower.cPosition)
		tower.cPosition = nullptr;

	// Xóa mục tiêu hiện tại
	if (tower.cTarget)
		tower.cTarget = nullptr;

	// Đặt lại đồng hồ bắn
	if (tower.cCooldown)
		tower.cCooldown->shootClock.restart();
}

void Game::DeactivateBullet(Entity& bullet)
{
	if (!bullet.isActive())
		return;

	// Vô hiệu hóa viên đạn
	bullet.active(false);

	// Đặt lại vị trí viên đạn ra ngoài màn hình (hoặc vị trí mặc định)
	if (bullet.cPosition)
		bullet.cPosition->position = Vector2f(-100.f, -100.f);
}
