#include "GameController.h"
#include "Level1.h"
#include "Graphics.h"



void Level1::Load()
{
	LevelSprites = new SpriteManager(gfx);

	ship = LevelSprites->AddSprite("blueSquare.jpg", 3, CollisionType::Point, {450, 800});
	//SpriteSheet* shield = LevelSprites->AddSprite("shield.png", 3, CollisionType::Circle, {415, 760});
	//character->MakeAnimated(10, 120, 100);

	int32 windowHeight = gfx->GetRenderTarget()->GetPixelSize().height;
	int32 windowWidth = gfx->GetRenderTarget()->GetPixelSize().width;
	//SpriteSheet* fire = LevelSprites->AddSprite("fire_02.png", 2);
	//fire->MakeAnimated(64, 0.0f, 128, 128);
	//fire->position = ship->position;
	//fire->MoveY(100);

	for (int i = 0; i < 3; ++i)
	{
		aiSprites[i] = LevelSprites->AddSprite("tree1 - Copy.png", 3, CollisionType::Point);
		aiSprites[i]->Move(130 * i, 100 * i);
	}
	//teleporter = LevelSprites->AddSprite("teleport_512.png", 1, CollisionType::Box, { windowWidth, windowHeight});
	//teleporter->MakeAnimated(4, 1.0f, 256, 512);
	//teleporter->Rotate(90);
	//teleporter->SetPosition(windowWidth / 2, windowHeight / 2);
	
	SpriteSheet* background = LevelSprites->AddSprite("bg5.jpg", 0);
	timer = 0;
	startTimer = 0.5f;
}

void Level1::Update(double timeTotal, double timeDelta)
{
	frameTime = timeDelta;
	//player->Update(LevelSprites);
	// update
	timer -= frameTime;
	if (KeyHeld(Key_W))
	{
		//ship->Move( 0, -5 );
		gfx->GetRenderTarget()->SetTransform(
			D2D1::Matrix3x2F::Rotation(
				45.0f,
				D2D1::Point2F(468.0f, 331.5f))
		);
	}
	if (KeyHeld(Key_A))
	{
		//ship->Move( -5, 0 );
		gfx->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Translation(-10, 0));
	}
	if (KeyHeld(Key_S))
	{
		//ship->Move( 0, 5 );
		gfx->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Translation(0, 10));
	}
	if (KeyHeld(Key_D))
	{
		//ship->Move( 5, 0 );
		gfx->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Translation(10, 0));

	}

	if (KeyHit(Key_Space))
	{
		//player->Shoot();
	}


	//for (int i = 0; i < 10; ++i)
	//{
	//	aiPlayers[i]->Update(LevelSprites);
	//}
	//// tiles software for tilemap
	//if (timer < 0.0f)
	//{
	//	timer = startTimer;
	//	int i = rand() % 10;
	//	//aiPlayers[i]->Move({ 0, -5 }, LevelSprites);
	//	aiPlayers[i]->Shoot();
	//	aiPlayers[i]->Move({ 0, 10 }, LevelSprites);

	//	if (startTimer > 0.2f)
	//		startTimer -= 0.01f;

	//}
}

void Player::InitBulletPool(SpriteManager* manager, string bulletFile, int32 bulletSpeed, int32 bulletLayer)
{
	bulletPool = new BulletPool(manager, bulletFile, bulletSpeed, bulletLayer);

}

void Player::InitSounds(string shootFile, string deathFile, string shieldFile)
{
	shootBuffer.loadFromFile(shootFile);
	deathBuffer.loadFromFile(deathFile);
	deathSound.setBuffer(deathBuffer);
	shootSound.setBuffer(shootBuffer);
	if (shieldFile != "")
	{
		shieldBuffer.loadFromFile(shieldFile);
		shieldSound.setBuffer(shieldBuffer);
	}
}

void Player::Move(Vector2 thrust, SpriteManager* const manager)
{
	if (active)
	{
		sprite->Move(thrust.x, thrust.y);
		if (fireEffects != NULL)
			fireEffects->Move(thrust.x, thrust.y);
		if (shield != NULL)
			shield->Move(thrust.x, thrust.y);
		//if (manager->DetectCollisions(sprite))
		//{
		//	sprite->Move(-thrust.x, -thrust.y);
		//}
	}
}

void Player::Shoot()
{
	if (active)
	{
		bulletPool->ActivateBullet({ sprite->position.x, sprite->position.y - 2 });
		shootSound.play();
	}
}

void Player::Update(SpriteManager* manager)
{

	bulletPool->Update();

	if (shieldActive)
	{
		if (!shield->active)
		{
			shieldSound.play();
			shieldActive = false;
		}
	}

	if (!sprite->active && active)
	{
		deathSound.play();
		active = false;
		if(fireEffects != NULL)
			fireEffects->active = false;
	}
}

void Level1::Unload()
{
	delete LevelSprites;
}

void Level1::Render()
{
	gfx->ClearScreen(0.0f, 0.0f, 0.5f);
	LevelSprites->Draw(frameTime);
}
