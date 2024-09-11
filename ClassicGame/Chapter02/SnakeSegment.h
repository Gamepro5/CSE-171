
#pragma once
#include "Actor.h"
#include <map>
#include "Snake.h"
#include "SnakeSegment.h"
#include "SpriteComponent.h"
class SnakeSegment : public Actor
{
public:
	SnakeSegment(class Game* game, class Snake* head, class SnakeSegment* parent);
	Game* game;
	Snake* head;
	SnakeSegment* parent;
	int xTilePos;
	int yTilePos;
	void setTilePos(int x, int y);
	void UpdateActor(float deltaTime) override;
	SpriteComponent* sprite;
};