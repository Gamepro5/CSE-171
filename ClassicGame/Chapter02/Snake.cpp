
#include "Snake.h"
#include "AnimSpriteComponent.h"
#include "Game.h"

Snake::Snake(Game* game)
	:Actor(game)
	, direction(Vector2(0,0))
{
	// Create an animated sprite component
	SpriteComponent* sprite = new SpriteComponent(this);
	sprite->SetTexture(game->GetTexture("Graphics/head_up.png"));

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
