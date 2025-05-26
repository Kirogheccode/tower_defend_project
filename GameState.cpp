#include "GameState.h"
void GameState::formatGameState()
{
    // For Life
	Life.scale(Vector2f(0.05, 0.05));
	//Position of Life is (0,0) as default
	// For Budget
	Budget.scale(Vector2f(40.0 / 592, 40.0 / 592));
	Budget.setPosition(Vector2f(0, 36));
}
void GameState::loadGameState()
{
	if (!Heart.loadFromFile(HeartImg) || !Coin.loadFromFile(CoinImg))
	{
		cout << "Failed to load game state!" << endl;
		return;
	}
	Life.setTexture(Heart);
	Budget.setTexture(Coin);
	formatGameState();
}
void GameState::DrawGameState(RenderWindow& window)
{
	window.draw(Life);
	window.draw(Budget);
}