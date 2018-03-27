#pragma once
#include "Game.h"
#include <SFML\Audio.hpp>
#include "Input.h"
#include "ObjectPool.h"

class Player
{
public:
	Player(SpriteSheet* sprite, SpriteSheet* fireFX = NULL, SpriteSheet* shield = NULL)
	{
		this->sprite = sprite;
		active = true;
		if(fireFX != NULL)
			fireEffects = fireFX;
		if (shield != NULL)
		{
			this->shield = shield;
			shieldActive = true;
		}
	}
	~Player()
	{
		delete bulletPool;
	}
	
	void InitBulletPool(SpriteManager* manager, string bulletFile, int32 bulletSpeed, int32 bulletLayer);
	void InitSounds(string shootFile, string deathFile, string shieldFile);
	void Move(Vector2 thrust, SpriteManager* const manager);
	void Shoot();
	void Update(SpriteManager* manager);

private:
	SpriteSheet* sprite;
	SpriteSheet* shield;
	SpriteSheet* fireEffects;
	BulletPool* bulletPool;
	bool active;
	bool shieldActive;
	sf::SoundBuffer shootBuffer;
	sf::Sound shootSound;
	sf::SoundBuffer deathBuffer;
	sf::Sound deathSound;
	sf::SoundBuffer shieldBuffer;
	sf::Sound shieldSound;
};



class Level1 : public GameLevel
{
	SpriteManager* LevelSprites;


	SpriteSheet* teleporter;
	//Player* player;
	SpriteSheet* ship;
	SpriteSheet* aiSprites[10];

	//Player* aiPlayers[10];
	float timer;
	float startTimer;
	double frameTime;
public:
	void Load() override;
	void Unload() override;
	void Render() override;
	void Update(double timeTotal, double timeDelta) override;
};
