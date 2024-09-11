
#include "SnakeSegment.h"
#include "AnimSpriteComponent.h"
#include "Game.h"

SnakeSegment::SnakeSegment(Game* game, Snake* head, SnakeSegment* parent)
	:Actor(game)
{
	// Create an animated sprite component
	this->game = game;
	this->head = head;
	this->parent = parent;
	SpriteComponent* sprite = new SpriteComponent(this);
	sprite->SetTexture(game->GetTexture("Graphics/body_horizontal.png"));

}

void setTilePos(int x, int y) {

}

void SnakeSegment::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	// Update position based on speeds and delta time
	
	
}

