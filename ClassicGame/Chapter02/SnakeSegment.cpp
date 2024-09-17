
#include "SnakeSegment.h"
#include "AnimSpriteComponent.h"
#include "Game.h"
#include <iostream>
SnakeSegment::SnakeSegment(Game* game, Snake* head, SnakeSegment* parent, SnakeSegment* child, char visDir, char prevVisDir)
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
	this->prevVisDir = prevVisDir;
	
}

void SnakeSegment::propogateMovement(int posX, int posY, char visDir, char prevVisDir, bool newChild) {
	char previousVisDir = this->visDir;
	this->visDir = visDir;
	
	if (child == nullptr) {
		/*
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
		}*/
		
	}
	else {/*
		switch (prevVisDir) {
		case 'u':
			switch (child->prevVisDir) {
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
			switch (child->prevVisDir) {
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
			switch (child->prevVisDir) {
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
			switch (child->prevVisDir) {
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
		}*/
		child->propogateMovement(xTilePos, yTilePos, previousVisDir, prevVisDir, newChild);
	}

	if (!newChild) {
		
		setTilePos(posX, posY);
	}
}


void SnakeSegment::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	// Update position based on speeds and delta time
	
	
}

