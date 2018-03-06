#pragma once
#include "Game.h"
#include <SFML\Audio.hpp>

class Level1 : public GameLevel
{
	float y;
	float ySpeed;
	sf::SoundBuffer buffer;
	sf::Sound sound;

	int frame;
public:
	SpriteSheet* sprites;
	void Load() override;
	void Unload() override;
	void Render() override;
	void Update() override;
};
