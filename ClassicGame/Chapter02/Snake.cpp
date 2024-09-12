
#include "Snake.h"
#include "AnimSpriteComponent.h"
#include "Game.h"
#include <iostream>
#include <random>
#include "Apple.h"
#include "Ship.h"

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

	if (currentApple == nullptr) {
		//Create apples
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 16); // distribution in range [1, 6]

		bool ok = false;
		while (!ok) {
			int proposedX = dist6(rng);
			int proposedY = dist6(rng);
			if (game->grid[proposedX][proposedY] == 0) {
				// Create an apple (temporary!)
				Apple* apple = new Apple(game);
				game->grid[proposedX][proposedY] = 2; //2 means there is an apple in this slot.
				apple->setTilePos(proposedX, proposedY);
				apple->SetScale(1.0f);
				game->AddActor(apple);
				currentApple = apple;
				ok = true;
			}
		}
	}
	
		//Create bombs
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 16); // distribution in range [1, 6]

		bool ok = false;
		while (!ok) {
			int proposedX = dist6(rng);
			int proposedY = dist6(rng);
			if (game->grid[proposedX][proposedY] == 0) {
				// Create an apple (temporary!)
				Ship* ship = new Ship(game);
				game->grid[proposedX][proposedY] = 3; //2 means there is an apple in this slot.
				ship->setTilePos(proposedX, proposedY);
				ship->SetScale(1.0f);
				game->AddActor(ship);
				ok = true;
			}
		}
	
	








	int targetPosX = 0;
	int targetPosY = 0;
	
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
		game->grid[xTilePos][yTilePos] = 0;
		delete currentApple;
		currentApple = nullptr;
		child->propogateMovement(xTilePos, yTilePos, visDir, true);
	}
	else {//snake not elongated
		if (child != nullptr) {
			child->propogateMovement(xTilePos, yTilePos, visDir, false);
		}
	}

	std::cout << game->grid[targetPosX][targetPosY] << std::endl;
	if (game->grid[targetPosX][targetPosY] == 1 || game->grid[targetPosX][targetPosY] == 3) {
		game->Shutdown();
		return;
	}
	
	for (int i = 0; i < 17; i++) {
		for (int j = 0; j < 17; j++) {
			if (game->grid[i][j] == 1) {
				game->grid[i][j] = 0;
			}
		}

	}
	SnakeSegment* iter = child;
	/*
	std::cout << visDir << ", ";
	while (iter != nullptr) {
		std::cout << iter->visDir << ", ";
		iter = iter->child;
	}
	std::cout << std::endl;
	*/
	
	for (int i = 0; i < 17; i++) {
		for (int j = 0; j < 17; j++) {
			if (game->grid[i][j] == 1) {
				game->grid[i][j] = 0;
			}
		}
	}
	iter = child;
	if (game->grid[xTilePos][yTilePos] == 0) {
		game->grid[xTilePos][yTilePos] = 1;
	}
	while (iter != nullptr) {
		if (game->grid[iter->xTilePos][iter->yTilePos] == 0) {
			game->grid[iter->xTilePos][iter->yTilePos] = 1;
		}
		iter = iter->child;
	}
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
