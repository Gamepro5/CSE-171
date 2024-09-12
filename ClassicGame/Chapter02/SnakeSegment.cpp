
#include "SnakeSegment.h"
#include "AnimSpriteComponent.h"
#include "Game.h"
#include <iostream>
SnakeSegment::SnakeSegment(Game* game, Snake* head, SnakeSegment* parent, SnakeSegment* child, char visDir)
	:Actor(game)
{
	// Create an animated sprite component
	this->game = game;
	this->head = head;
	this->parent = parent;
	this->child = child;
	this->self = this;
	sprite = new SpriteComponent(this);
	this->visDir = visDir;
}

void SnakeSegment::propogateMovement(int posX, int posY, char visDir, bool newChild) {
	char previousVisDir = this->visDir;
	this->visDir = visDir;

	if (child == nullptr) {
		switch (visDir) {
			case 'u':
				sprite->SetTexture(game->GetTexture("Graphics/tail_down.png"));
				break;
			case 'r':
				sprite->SetTexture(game->GetTexture("Graphics/tail_left.png"));
				break;
			case 'l':
				sprite->SetTexture(game->GetTexture("Graphics/tail_right.png"));
				break;
			case 'd':
				sprite->SetTexture(game->GetTexture("Graphics/tail_up.png"));
				break;
		}
		
	}
	else {
		switch (visDir) {
		case 'u':
			switch (child->visDir) {
			case 'u':
				sprite->SetTexture(game->GetTexture("Graphics/body_vertical.png"));
				break;
			case 'r':
				sprite->SetTexture(game->GetTexture("Graphics/body_topleft.png"));
				break;
			case 'l':
				sprite->SetTexture(game->GetTexture("Graphics/body_topright.png"));
				break;
			case 'd':
				sprite->SetTexture(game->GetTexture("Graphics/body_vertical.png"));
				break;
			}
		case 'r':
			switch (child->visDir) {
			case 'u':
				sprite->SetTexture(game->GetTexture("Graphics/body_bottomright.png"));
				break;
			case 'r':
				sprite->SetTexture(game->GetTexture("Graphics/body_horizontal.png"));
				break;
			case 'l':
				sprite->SetTexture(game->GetTexture("Graphics/body_horizontal.png"));
				break;
			case 'd':
				sprite->SetTexture(game->GetTexture("Graphics/body_topright.png"));
				break;
			}
		case 'l':
			switch (child->visDir) {
			case 'u':
				sprite->SetTexture(game->GetTexture("Graphics/body_bottomleft.png"));
				break;
			case 'r':
				sprite->SetTexture(game->GetTexture("Graphics/body_horizontal.png"));
				break;
			case 'l':
				sprite->SetTexture(game->GetTexture("Graphics/body_horizontal.png"));
				break;
			case 'd':
				sprite->SetTexture(game->GetTexture("Graphics/body_topleft.png"));
				break;
			}
		case 'd':
			switch (child->visDir) {
			case 'u':
				sprite->SetTexture(game->GetTexture("Graphics/body_vertical.png"));
				break;
			case 'r':
				sprite->SetTexture(game->GetTexture("Graphics/body_bottomright.png"));
				break;
			case 'l':
				sprite->SetTexture(game->GetTexture("Graphics/body_bottomleft.png"));
				break;
			case 'd':
				sprite->SetTexture(game->GetTexture("Graphics/body_vertical.png"));
				break;
			}
		}
		child->propogateMovement(xTilePos, yTilePos, previousVisDir, newChild);
	}

	if (!newChild) {
		if (game->grid[posX][posX] == 0) {
			game->grid[posX][posX] = 1;
		}
		setTilePos(posX, posY);
	}
}


void SnakeSegment::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	// Update position based on speeds and delta time
	
	
}

