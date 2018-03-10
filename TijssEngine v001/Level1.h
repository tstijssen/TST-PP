#pragma once
#include "Game.h"
#include <SFML\Audio.hpp>
#include "Input.h"

class Level1 : public GameLevel
{
	SpriteSheet* sprites;
	SpriteSheet* collisionTest;
	SpriteSheet* teleport;

public:
	void Load() override;
	void Unload() override;
	void Render() override;
	void Update() override;
};
