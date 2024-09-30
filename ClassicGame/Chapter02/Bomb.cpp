// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Bomb.h"
#include "AnimSpriteComponent.h"
#include "Game.h"

Bomb::Bomb(Game* game)
	:Actor(game)
{
	// Create an animated sprite component
	AnimSpriteComponent* asc = new AnimSpriteComponent(this);
	std::vector<SDL_Texture*> anims = {
		game->GetTexture("Assets/Ship01.png"),
		game->GetTexture("Assets/Ship02.png"),
		game->GetTexture("Assets/Ship03.png"),
		game->GetTexture("Assets/Ship04.png"),
	};
	asc->SetAnimTextures(anims);
}

void Bomb::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	
	SetRotation(GetRotation() + 0.1);

}
