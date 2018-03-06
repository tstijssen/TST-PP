#include "GameController.h"
#include "Level1.h"
#include "Graphics.h"

void Level1::Load()
{
	y = ySpeed = 0.0f;
	sprites = new SpriteSheet(L"shadow.png", gfx, 80, 70);
	frame = 0;

	buffer.loadFromFile("engine.wav");
	sound.setBuffer(buffer);
	sound.setVolume(50.0f);
	sound.setPitch(1.0f);
	sound.setLoop(true);
	sf::Listener::setGlobalVolume(100.0f); // 0 to 100
	sf::Listener::setPosition(0.0f, 0.0f, 0.0f);
	sf::Listener::setDirection(0.0f, 0.0f, -1.0f);
	sf::Listener::setUpVector(0.0f, 1.0f, 0.0f);
	sound.play();
}

void Level1::Unload()
{
	sound.stop();
	delete sprites;
}

void Level1::Render()
{
	gfx->ClearScreen(0.0f, 0.0f, 0.5f);
	gfx->DrawCircle(375.0f, y, 50.0f, 10.0f, 1.0f, 1.0f, 1.0f);

	sprites->Draw(frame % 14, 100, 100);
}

void Level1::Update()
{
	// update
	ySpeed += 1.0f;
	y += ySpeed;

	if (y > 600)
	{
		y = 600;
		ySpeed = -30.0f;
	}

	frame++;
}