#include <SFML/Graphics.hpp>
#include <iostream>
#include "Enemy.h"
#include "Map.h"
#include "Tower.h"
#include "button.h"
#include "GameState.h"

#include "EntityManager.h"
#include "ComponentManager.h"
#include "SystemManager.h"

using namespace std;
using namespace sf;

int main()
{
    //===============================================INITIALIZATION===============================================
    ContextSettings settings;
    settings.antialiasingLevel = 8;
    RenderWindow window(VideoMode(1920, 1080), "Tower Defense", Style::Default,settings);

    EntityManager em;
    auto skeleton = em.addEntity("Skeleton");
    skeleton->cMovement = make_shared<CMovement>(Vector2f(100.f, 200.f), 50.f);
    skeleton->cSet = make_shared<CSet>("IMGS/Skeletons_2vers 96x32/Skeletons_Free_Pack/Skeleton_Sword/Skeleton_White/Skeleton_With_VFX/Skeleton_01_White_Walk.png", Vector2u(10, 1), 0.3f, 0);

    Map Field;
    Field.InitializeMap();
    Field.LoadMap();

    GameState state;
    state.loadGameState();

    Clock clock;
    float deltaTime = 0.0;
    bool isPlacingTower = false;

    //===============================================INITIALIZATION===============================================
   
    //=================================================GAME-LOOP==================================================
    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();

        Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear(Color::Black);
        window.draw(Field);
        state.DrawGameState(window);

        sUpdate(em.getEntites("Skeleton"), window, deltaTime, 0);

        window.display();
    }

    //=================================================GAME-LOOP==================================================
    return 0;
}
  