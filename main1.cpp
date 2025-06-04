#include <SFML/Graphics.hpp>
#include <iostream>
#include "Enemy.h"
#include "Map.h"
#include "Tower.h"
#include "button.h"
#include "GameState.h"

using namespace std;
using namespace sf;

int main()
{
    //===============================================INITIALIZATION===============================================
    ContextSettings settings;
    settings.antialiasingLevel = 8;
    RenderWindow window(VideoMode(1920, 1080), "Tower Defense", Style::Default,settings);

    vector<Vector2f> path = {
        Vector2f(0.f, 500.f),  
        Vector2f(600.f, 500.f), 
        Vector2f(600.f, 700.f),   
        Vector2f(1200.f, 700.f),  
        Vector2f(1200.f, 400.f), 
        Vector2f(1920.f, 400.f)   
    };

    Map Field;
    Field.InitializeMap();
    Field.LoadMap();

    Enemy skeleton;
    skeleton.LoadEnemy("IMGS/Skeletons_2vers 96x32/Skeletons_Free_Pack/Skeleton_Sword/Skeleton_White/Skeleton_With_VFX/Skeleton_01_White_Walk.png");
    skeleton.SetEnemy(Vector2u(10, 1), 0.3f, 50, 80.f, 0, false);

    Enemy slime;
    slime.LoadEnemy("IMGS/Slime 32x25/slime-Sheet.png");
    slime.SetEnemy(Vector2u(8, 3), 0.3f, 50, 50.f, 0, true);

    vector<Enemy> spawned_enemy;
    spawned_enemy.push_back(skeleton);
    spawned_enemy.push_back(slime);

    Tower tower_type1;
    tower_type1.LoadTower("IMGS/BloodMoonTower/RedMoonTower.png");
    tower_type1.SetTower(Vector2u(11, 1), 0.3f, 0);

    vector<Tower> placed_tower;
    vector<Bullet> spawned_bullet;

    Tower ghost_tower;

    Button tower1("IMGS/BloodMoonTower/RedMoonTower.png", 1800, 0);

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

        if (tower1.isClicked(mousePos, event))
        {
            ghost_tower = tower_type1;
            isPlacingTower = true;
        }
        else if (isPlacingTower == true && event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
        {
             ghost_tower.setPosition(mousePos);
             placed_tower.push_back(ghost_tower);
             isPlacingTower = false;
        }
     
        for (auto& tower : placed_tower)
        {
            tower.Update(deltaTime);
            tower.HasEnemy(deltaTime, spawned_enemy, spawned_bullet);
        }
        
        spawned_enemy.erase(
            std::remove_if(spawned_enemy.begin(), spawned_enemy.end(),
                [&](Enemy& enemy) {
                    return enemy.GetHealth() <= 0;
                }),
            spawned_enemy.end());

        for (Enemy& enemy : spawned_enemy)
        {
            enemy.Update(deltaTime, path);
        }

        tower_type1.Update(deltaTime);

        window.clear(Color::Black);
        window.draw(Field);

        tower1.draw(window);
        state.DrawGameState(window);
        
        for (auto& bullet : spawned_bullet)
        {
            bullet.Draw(window);
        }

        for (auto& enemy : spawned_enemy)
        {
            enemy.Draw(window);
        }

        for (auto& tower : placed_tower)
        {
            tower.Draw(window);
        }

        window.display();
    }

    //=================================================GAME-LOOP==================================================
    return 0;
}
  