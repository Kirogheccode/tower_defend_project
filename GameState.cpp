#include "GameState.h"
void GameState::formatGameState()
{
    // For Life
	for (auto& heart : Life)
	{
		heart.setScale(Vector2f(0.05f, 0.05f));
	}

	//Position of Life is (0,0) as default
	// For Budget
	Budget.setScale(Vector2f(40.0 / 592, 40.0 / 592));
	Budget.setPosition(Vector2f(0, 36));
}

void GameState::loadGameState()
{
	if (!Heart.loadFromFile(HeartImg) || !Coin.loadFromFile(CoinImg))
	{
		cout << "Failed to load game state!" << endl;
		return;
	}

	int numHearts = 5;
	float spacing = 1.f;

	Life.clear();

	for (int i = 0; i < numHearts; i++)
	{
		Sprite heart;
		
		heart.setTexture(Heart);

		heart.setPosition(i * (Heart.getSize().x * 0.05f + 5.f), 0);
		 
		Life.push_back(heart);
	}

	Budget.setTexture(Coin);

	formatGameState();
}

void GameState::DrawGameState(RenderWindow& window)
{
	for (const auto& heart : Life)
	{
		window.draw(heart);
	}

	window.draw(Budget);
}