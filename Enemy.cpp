#pragma once
#include "Enemy.h"
//void Enemy::SetEnemyPosition1()//Should in class map
//{
//	Y = Map_Height/ 2;
//	E_sprite.setPosition(Vector2f(X, Y));
//}
//void Enemy::SetEnenmyPosition2()
//{
//	X = Map_Width / 2;
//	E_sprite.setPosition(Vector2f(X, Y));
//}
//void Enemy::LoadEnemy(string Path)
//{
//	if (!E_texture.loadFromFile(Path))
//	{
//		cout << "Failed to load!" << endl;
//		return;
//	}
//	Size_IMG = E_texture.getSize();
//	E_sprite.setTexture(E_texture);
//	E_sprite.scale(Vector2f(2, 2));
//}
//void Enemy::MoveEnemy1(RenderWindow& window)
//{
//	if (X > Map_Width)
//		return;
//	window.draw(E_sprite);
//	X++;
//	E_sprite.setPosition(Vector2f(X, Y));
//}
//void Enemy::MoveEnemy2(RenderWindow& window)
//{
//	if (Y > Map_Height)
//		return;
//	window.draw(E_sprite);
//	Y++;
//	E_sprite.setPosition(Vector2f(X, Y));
//}
void Enemy::SetEnemy(Vector2u ImgCount, float switchTime, float speed, unsigned int row)
{
	this->speed = speed;
	this->row  = row;
	animation.setAnimation(&E_texture, ImgCount, switchTime);
	E_sprite.setTexture(E_texture);
	E_sprite.scale(Vector2f(1.0, 1.0));
	E_sprite.setPosition(Vector2f(0.0f, 500.0f));
}
void Enemy::Update(float deltaTime)
{
	Vector2f movement(0.0f, 0.0f);
	movement.x += speed * deltaTime;
	animation.Update(row, deltaTime);
	E_sprite.setTextureRect(animation.uvRect);
	E_sprite.move(movement);
    //consider movement as offset, the above statement 
	// equivalent to .setPosition(E_sprite.getSize()+offset)
}
void Enemy::Draw(RenderWindow& window)
{
	window.draw(E_sprite);
}
void Enemy::LoadEnemy(string Path)
{
	if (!E_texture.loadFromFile(Path))
	{
		cout << "Failed to load!" << endl;
		return;
    }
}

	//if (movement.x == 0.0f)
	//	row = 0; //Monster dung yen
	//else
	//{
	//	row = 1;//Di chuyen
	//	if (movement.x > 0.0f)
	//		faceRight = true;//Qua trai
	//	else
	//		faceRight = false;//Qua phai
	//}