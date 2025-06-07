#include "Tower.h"

void Tower::SetTower(const Vector2u& ImgCount, const float& switchTime, const unsigned int& row)
{
	this->row = row;

	animation.setAnimation(&E_texture, ImgCount, switchTime);

	width = E_texture.getSize().x / float(ImgCount.x);
	height = E_texture.getSize().y / float(ImgCount.y);
}

void Tower::LoadTower(const string& path)
{
	if (!E_texture.loadFromFile(path))
	{
		cout << "Failed to load!" << endl;
		return;
	}

	E_sprite.setTexture(E_texture);

	boundary.setRadius(125.f);
	boundary.setOrigin(boundary.getRadius(), boundary.getRadius());
}

void Tower::Update(float& deltaTime)
{
	animation.Update(row, deltaTime);
	E_sprite.setTextureRect(animation.uvRect);
}

void Tower::setPosition(Vector2f& mousePos)
{
	Vector2f pos(mousePos.x - (width / 2), mousePos.y - (height / 2) - 20);

	position = pos;

	E_sprite.setPosition(pos);
	boundary.setPosition(mousePos.x, mousePos.y);
}

void Tower::HasEnemy(float& deltaTime, vector<Enemy>& Enemies, vector<Bullet>& spawned_bullet)
{
    delayTime += deltaTime;

    if (delayTime >= 3)
    {
        Enemy* targetEnemy = nullptr;

        for (Enemy& enemy : Enemies)
        {
            if (boundary.getGlobalBounds().contains(enemy.GetPosition()))
            {
                targetEnemy = &enemy;
                break;
            }
        }

        if (targetEnemy != nullptr)
        {
            Bullet readyBullet;
            readyBullet.LoadBullet("IMGS/bullet.png");
            readyBullet.SetBullet(position, targetEnemy);
            spawned_bullet.push_back(readyBullet);

            delayTime = 0.0f;
        }
    }
}

void Tower::Draw(RenderWindow& window)
{
	window.draw(E_sprite);
}