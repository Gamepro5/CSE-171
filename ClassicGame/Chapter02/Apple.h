#pragma once
#include "Actor.h"
class Apple : public Actor
{
public:
	Apple(class Game* game);
	void UpdateActor(float deltaTime) override;
};