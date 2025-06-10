#include <SFML/Graphics.hpp>
#include <iostream>

#include "EntityManager.h"
#include "Components.h"
#include "Game.h"

using namespace std;
using namespace sf;

int main()
{
	Game g("config.txt");
	g.run();
}
  