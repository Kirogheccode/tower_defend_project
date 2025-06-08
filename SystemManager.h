#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.h"

#include <iostream>

using namespace std;
using namespace sf;

void sAnimation(shared_ptr<Entity>& entity, float& deltaTime)
{
	if (entity->cSet)
	{
		entity->cSet->CurrImg.y = entity->cSet->row;
		entity->cSet->totalTime += deltaTime;

		if (entity->cSet->totalTime >= entity->cSet->switchTime)
		{
			entity->cSet->totalTime -= entity->cSet->switchTime;
			entity->cSet->CurrImg.x++;

			if (entity->cSet->CurrImg.x >= entity->cSet->ImgCount.x)
				entity->cSet->CurrImg.x = 0;
		}

		entity->cSet->uvRect.top = entity->cSet->CurrImg.y * entity->cSet->uvRect.height;
		entity->cSet->uvRect.left = entity->cSet->CurrImg.x * entity->cSet->uvRect.width;
	}
	else
	{
		cout << "Components are nullptr" << endl;
	}
}

void sMovement(vector<shared_ptr<Entity>>& entities, float& deltaTime, const int& mapIndex)
{
	for (auto& entity : entities)
	{
		if (entity->cMovement && entity->cSet)
		{
			if (entity->cMovement->currentPathindex >= entity->cMovement->paths[mapIndex].size())
				return;

			Vector2f target = entity->cMovement->paths[mapIndex][entity->cMovement->currentPathindex];
			Vector2f direction = target - entity->cMovement->position;

			float distance = sqrt(direction.x * direction.x + direction.y * direction.y);

			if (distance < 1.f) {
				entity->cMovement->currentPathindex++;
				if (entity->cMovement->currentPathindex >= entity->cMovement->paths[mapIndex].size()) {
					// At the finish (minusHealth())
				}

				target = entity->cMovement->paths[mapIndex][entity->cMovement->currentPathindex];
				direction = target - entity->cMovement->position;
				distance = sqrt(direction.x * direction.x + direction.y * direction.y);
			}

			Vector2f movement(0.f, 0.f);

			if (distance > 0) {
				movement = direction / distance;
			}

			entity->cMovement->position += movement * entity->cMovement->speed * deltaTime;

			sAnimation(entity, deltaTime);

			entity->cSet->sprite.setTextureRect(entity->cSet->uvRect);

			entity->cSet->sprite.setPosition(entity->cMovement->position);
		}
		else
		{
			cout << "Components are nullptr" << endl;
		}
	}
}

void sDraw(vector<shared_ptr<Entity>>& entities, RenderWindow& window)
{
	for (auto& entity : entities)
	{
		window.draw(entity->cSet->sprite);
	}
}

void sUpdate(vector<shared_ptr<Entity>>& entities, RenderWindow& window, float& DeltaTime, const int& mapIndex)
{
	sMovement(entities, DeltaTime, mapIndex);
	sDraw(entities, window);
}

void sDestory();
void sCollide();