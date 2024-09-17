
#pragma once
#include "Actor.h"
#include <map>
#include "Snake.h"
#include "SnakeSegment.h"
#include "SpriteComponent.h"
class SnakeSegment : public Actor
{
public:
	SnakeSegment(class Game* game, class Snake* head, class SnakeSegment* parent, class SnakeSegment* child, char visDir, char prevVisDir);
	Game* game;
	Snake* head;
	SnakeSegment* self;
	SnakeSegment* parent;
	void UpdateActor(float deltaTime) override;
	SpriteComponent* sprite;
	SnakeSegment* child;
	void propogateMovement(int posX, int posY, char visDir, char prevVisDir, bool newChild);
	char visDir;
	char prevVisDir;
};