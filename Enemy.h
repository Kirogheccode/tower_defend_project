#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Animation.h"
using namespace sf;
using namespace std;
class Enemy
{
	Texture E_texture;
	Sprite E_sprite;
	Animation animation;
	unsigned int row=0;
	float speed=1.0f;
	const int Map_Height = 1080;
	const int Map_Width = 1920;

public:
	void SetEnemy(Vector2u ImgCount, float switchTime, float speed, unsigned int row);
	void LoadEnemy(string Path);
	void Update(float deltaTime);
	void Draw(RenderWindow&);
};

//bool faceRight;
