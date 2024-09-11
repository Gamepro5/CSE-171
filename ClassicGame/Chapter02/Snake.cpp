
#include "Snake.h"
#include "AnimSpriteComponent.h"
#include "Game.h"

Snake::Snake(Game* game)
	:Actor(game)
	, direction(Vector2(0,0))
{	
	self = this;
	this->game = game;
	// Create an animated sprite component
	SpriteComponent* sprite = new SpriteComponent(this);
	sprite->SetTexture(game->GetTexture("Graphics/head_up.png"));

}

void Snake::setTilePos(int x, int y) {
	xTilePos = x;
	yTilePos = y;
	game->grid[x][y] = 1;

	float top_left_x = ((game->resolution.x) * x) / (17); // top left x
	float bottom_left_x = ((game->resolution.x) * x+1) / (17); // bottom left x;
	float top_left_y = ((game->resolution.y) * y) / (17); // top left y
	float bottom_left_y = ((game->resolution.y) * y+1) / (17); // bottom left y
	SetPosition(Vector2(top_left_x+(bottom_left_x - top_left_x / 2), top_left_y + (bottom_left_y - top_left_y / 2)));
}

void Snake::moveSnake(bool grow) {
	
	return;
	if (grow) {
		//SnakeSegment* segment = new SnakeSegment(game, self, nullptr);
		//segment->setTilePos();
		//segment->SetScale(1.0f);
	}
	else {

	}
}


void Snake::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	// Update position based on speeds and delta time
	Vector2 pos = GetPosition();
	pos.x += direction.x * deltaTime;
	pos.y += direction.y * deltaTime;
	// Restrict position to left half of screen
	
	if (pos.x < 25.0f)
	{
		pos.x = 25.0f;
	}
	else if (pos.x > 500.0f)
	{
		pos.x = 500.0f;
	}
	if (pos.y < 25.0f)
	{
		pos.y = 25.0f;
	}
	else if (pos.y > 743.0f)
	{
		pos.y = 743.0f;
	}
	SetPosition(pos);
}

void Snake::ProcessKeyboard(const uint8_t* state)
{
	
	// right/left
	if (state[SDL_SCANCODE_D])
	{
		direction.x = 1;
	}
	if (state[SDL_SCANCODE_A])
	{
		direction.x = -1;
	}
	// up/down
	if (state[SDL_SCANCODE_S])
	{
		direction.y = -1;
	}
	if (state[SDL_SCANCODE_W])
	{
		direction.y = 1;
	}
}
