
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

}

void Snake::setTilePos(int x, int y) {
	if (x > 17 || y > 17 || x < 0 || y < 0)  {
		return;
	}
	xTilePos = x;
	yTilePos = y;
	game->grid[x][y] = 1;
	
	float top_left_x = ((game->resolution.x) * x) / (17); // top left x
	float bottom_left_x = ((game->resolution.x) * x+1) / (17); // bottom left x;
	float top_left_y = ((game->resolution.y) * y) / (17); // top left y
	float bottom_left_y = ((game->resolution.y) * y+1) / (17); // bottom left y
	SetPosition(Vector2(top_left_x/2+(bottom_left_x - top_left_x / 2), top_left_y/2 + (bottom_left_y - top_left_y / 2)));
}

void Snake::moveSnake(bool grow) {
	
	std::cout << xTilePos << "  " << yTilePos << std::endl;
	if (grow) {
		//SnakeSegment* segment = new SnakeSegment(game, self, nullptr);
		//segment->setTilePos();
		//segment->SetScale(1.0f);
	}
	else {
		if (direction.x == 1.0 && direction.y == 0.0) {
			sprite->SetTexture(game->GetTexture("Graphics/head_right.png"));
			setTilePos(xTilePos+1, yTilePos);
		} else if (direction.x == 0.0 && direction.y == 1.0) {
			sprite->SetTexture(game->GetTexture("Graphics/head_up.png"));
			setTilePos(xTilePos, yTilePos-1);
		} else if (direction.x == -1.0 && direction.y == 0.0) {
			sprite->SetTexture(game->GetTexture("Graphics/head_left.png"));
			setTilePos(xTilePos-1, yTilePos);
		} else if (direction.x == 0.0 && direction.y == -1.0) {
			sprite->SetTexture(game->GetTexture("Graphics/head_down.png"));
			setTilePos(xTilePos, yTilePos+1);
		}

	}
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
