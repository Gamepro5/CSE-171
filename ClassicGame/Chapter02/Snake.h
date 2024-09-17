
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
	float bombSpawnTimeCounter;
	void UpdateActor(float deltaTime) override;
	void ProcessKeyboard(const uint8_t* state);
	Vector2 direction;
	class SnakeSegment* child;
	void moveSnake(bool grow);
	std::vector<class SnakeSegment*> segments;
	char visDir;
	char prevVisDir;
	class Apple* currentApple;
	bool currentAppleAlive;
	void setSequenceVisDir();
private:
	SnakeSegment* createSegment(int posX, int posY, class SnakeSegment* child, char visDir, char prevVisDir);
};
