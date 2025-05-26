#include <SFML/Graphics.hpp>
#include <iostream>
#include "Enemy.h"
#include "Map.h"
#include "GameState.h"

using namespace std;
using namespace sf;

int main()
{
    //===============================================INITIALIZATION===============================================
    ContextSettings settings;
    settings.antialiasingLevel = 8;
    RenderWindow window(VideoMode(1920, 1080), "Tower Defense", Style::Default,settings);

    Map Field;
    Field.InitializeMap();
    Field.LoadMap();

    Enemy skeleton;
    skeleton.LoadEnemy("IMGS/Skeletons_2vers 96x32/Skeletons_Free_Pack/Skeleton_Sword/Skeleton_White/Skeleton_With_VFX/Skeleton_01_White_Walk.png");
    skeleton.SetEnemy(Vector2u(10, 1), 0.3f, 50.f, 0);

    GameState state;
    state.loadGameState();

    Clock clock;
    float deltaTime = 0.0;
    //===============================================INITIALIZATION===============================================
   
    //=================================================GAME-LOOP==================================================
    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        skeleton.Update(deltaTime);
        window.clear(Color::Black);
        window.draw(Field);
        state.DrawGameState(window);
        skeleton.Draw(window);
        window.display();
    }

    //=================================================GAME-LOOP==================================================
    return 0;

}
  