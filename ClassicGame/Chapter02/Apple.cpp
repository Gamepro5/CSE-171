
#include "Apple.h"
#include "SpriteComponent.h"
#include "Game.h"

Apple::Apple(Game* game)
	:Actor(game)
{
	// Create an animated sprite component
	SpriteComponent* sprite = new SpriteComponent(this);
	sprite->SetTexture(game->GetTexture("Graphics/apple.png"));
}

void Apple::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

}
