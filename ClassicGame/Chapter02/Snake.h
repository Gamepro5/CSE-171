
#pragma once
#include "Actor.h"
#include "SnakeSegment.h"
#include <vector>
#include "SpriteComponent.h"
class Snake : public Actor
{
public:
	Snake(class Game* game);
	Game* game;
	Snake* self;
	SpriteComponent* sprite;
	float deltaTimeCounter;
	void UpdateActor(float deltaTime) override;
	void ProcessKeyboard(const uint8_t* state);
	Vector2 direction;
	int xTilePos;
	int yTilePos;
	void setTilePos(int x, int y);
	void moveSnake(bool grow);
	std::vector<class SnakeSegment*> segments;
};
