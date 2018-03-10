#include "GameController.h"
#include "Level1.h"
#include "Graphics.h"

void Level1::Load()
{
	sprites = new SpriteSheet("gnu.png", gfx, CollisionType::Circle);
	sprites->MakeAnimated(10, 120, 100);
	sprites->position.x = 300;

	collisionTest = new SpriteSheet("gnu.png", gfx, CollisionType::Circle);
	collisionTest->MakeAnimated(10, 120, 100);

	collisionTest->position.x = 100.0f;
	collisionTest->position.y = 200.0f;

	teleport = new SpriteSheet("teleport_512.png", gfx, CollisionType::None);
	teleport->MakeAnimated(4, 256, 512);
	teleport->Rotate(90);

	teleport->position.x = 500.0f;
	teleport->position.y = 250.0f;
	//background->scale.x = -500;
	//background->scale.y = -500;


}

void Level1::Unload()
{
	delete sprites;
}

void Level1::Render()
{
	gfx->ClearScreen(0.0f, 0.0f, 0.5f);

	//sprites->Draw(frame % 14, 100, 100);
	sprites->Draw();
	collisionTest->Draw();
	teleport->Draw();
}

void Level1::Update()
{
	// update
	if (KeyHeld(Key_W))
	{
		sprites->MoveY(-1);
	}
	if (KeyHeld(Key_A))
	{
		sprites->MoveX(-1);
	}
	if (KeyHeld(Key_S))
	{
		sprites->MoveY(1);
	}
	if (KeyHeld(Key_D))
	{
		sprites->MoveX(1);
	}

	if (KeyHeld(Key_R))
	{
		sprites->Rotate(1);
	}

	if (KeyHit(Key_I))
	{
		sprites->active = false;
	}

	if (KeyHit(Key_O))
	{
		sprites->active = true;
	}
}