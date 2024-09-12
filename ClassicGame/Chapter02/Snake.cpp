
#include "Snake.h"
#include "AnimSpriteComponent.h"
#include "Game.h"
#include <iostream>

Snake::Snake(Game* game)
	:Actor(game)
	, direction(Vector2(1,0))
{	
	self = this;
	this->game = game;
	// Create an animated sprite component
	sprite = new SpriteComponent(this);
	sprite->SetTexture(game->GetTexture("Graphics/head_up.png"));
	deltaTimeCounter = 0;
	child = nullptr;
	visDir = 'u';

}

SnakeSegment* Snake::createSegment(int posX, int posY, SnakeSegment* child, char visDir) {
	SnakeSegment* segment = new SnakeSegment(game, self, nullptr, child, visDir);
	segment->setTilePos(xTilePos, yTilePos);
	segment->SetScale(1.0f);
	return segment;
}

void Snake::moveSnake(bool grow) {
	int targetPosX = 0;
	int targetPosY = 0;
	//std::cout << game->grid[xTilePos][yTilePos] << std::endl;
	char previousVisDir = this->visDir;

	if (direction.x == 1.0 && direction.y == 0.0) {
		sprite->SetTexture(game->GetTexture("Graphics/head_right.png"));
		targetPosX = xTilePos + 1;
		targetPosY = yTilePos;
		visDir = 'r';
	} else if (direction.x == 0.0 && direction.y == 1.0) {
		sprite->SetTexture(game->GetTexture("Graphics/head_up.png"));
		targetPosX = xTilePos;
		targetPosY = yTilePos - 1;
		visDir = 'u';
	} else if (direction.x == -1.0 && direction.y == 0.0) {
		sprite->SetTexture(game->GetTexture("Graphics/head_left.png"));
		targetPosX = xTilePos - 1;
		targetPosY = yTilePos;
		visDir = 'l';
	} else if (direction.x == 0.0 && direction.y == -1.0) {
		sprite->SetTexture(game->GetTexture("Graphics/head_down.png"));
		targetPosX = xTilePos;
		targetPosY = yTilePos + 1;	
		visDir = 'd';
	}
	if (game->grid[xTilePos][yTilePos] == 2) {
		child = createSegment(xTilePos, yTilePos, child, visDir);
		game->AddActor(child);
		child->propogateMovement(xTilePos, yTilePos, visDir, true);
	}
	else {//snake not elongated
		if (child != nullptr) {
			child->propogateMovement(xTilePos, yTilePos, visDir, false);
		}
	}
	
	if (game->grid[xTilePos][yTilePos] == 0) {
		game->grid[xTilePos][yTilePos] = 1;
	}
	
	std::cout << visDir << ", ";
	SnakeSegment* iter = child;
	while (iter != nullptr) {
		std::cout << iter->visDir << ", ";
		iter = iter->child;
	}
	std::cout << std::endl;
	setTilePos(targetPosX, targetPosY);
}


void Snake::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	// Update position based on speeds and delta time
	deltaTimeCounter += deltaTime;
	if (deltaTimeCounter >= 0.5) { // do an action once every 0.5 seconds.
		moveSnake(false);
		deltaTimeCounter = 0;
	}
}

void Snake::ProcessKeyboard(const uint8_t* state)
{
	// right/left
	if (state[SDL_SCANCODE_D])
	{
		direction.x = 1.0;
		direction.y = 0.0;
	}
	if (state[SDL_SCANCODE_A])
	{
		direction.x = -1.0;
		direction.y = 0.0;
	}
	// up/down
	if (state[SDL_SCANCODE_S])
	{
		direction.x = 0.0;
		direction.y = -1.0;
	}
	if (state[SDL_SCANCODE_W])
	{
		direction.x = 0.0;
		direction.y = 1.0;
	}
}
