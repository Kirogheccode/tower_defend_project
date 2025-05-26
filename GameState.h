#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;
class GameState
{
	const string HeartImg = "IMGS/Heart.png";
	const string CoinImg = "IMGS/Coin.png";
	Texture Heart;
	Texture Coin;
	Sprite Life;
	Sprite Budget;
public:
	void loadGameState();
	void formatGameState();
	void DrawGameState(RenderWindow& window);
};

