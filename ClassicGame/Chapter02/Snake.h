
#pragma once
#include "Actor.h"
class Snake : public Actor
{
public:
	Snake(class Game* game);
	void UpdateActor(float deltaTime) override;
	void ProcessKeyboard(const uint8_t* state);
	Vector2 direction;
};