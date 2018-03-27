#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(CollisionType::Type collider, Vector2 position, bool *layerMovedVar, bool isIsometric)
{
	this->position.x = position.x;
	this->position.y = position.y;
	this->layerMoved = layerMovedVar;
	this->collider = collider;
	this->isometric = isIsometric;
}

void SpriteSheet::Init()
{
	size.x = bmp->GetSize().width;
	size.y = bmp->GetSize().height;
	position.x += size.x / 2;
	position.y += size.y / 2;
	spritesAccross = 1;
	scale = 1.0f;
	radius = size.x / 2;
	active = true;
	tag = "";
}

SpriteSheet::~SpriteSheet()
{
	if (bmp)
	{
		bmp->Release();
	}
}

void SpriteSheet::Draw(Graphics* gfx, double frameTime)
{
	// source depends on animated
	D2D_RECT_F src;
	if (animated)
	{
		if (frameTimer > 0.0f)
		{
			frameTimer -= frameTime;
		}
		else
		{
			// advance frame
			frameIndex = (1 + frameIndex) % frames;
			frameTimer = animationspeed;
		}

		src = D2D1::RectF(
			(float)((frameIndex % spritesAccross) * size.x),
			(float)((frameIndex / spritesAccross) * size.y),
			(float)((frameIndex % spritesAccross) * size.x) + size.x,
			(float)((frameIndex / spritesAccross) * size.y) + size.y);
	}
	else
	{
		src = D2D1::RectF(0.0f, 0.0f, size.x, size.y);
	}
	D2D_RECT_F dest = D2D1::RectF(
		position.x - size.x / 2, position.y - size.y / 2,
		scale + position.x + size.x / 2, scale + position.y + size.y / 2);

	gfx->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Rotation(rotationAngle, D2D1::Point2F(position.x, position.y)));

	gfx->GetRenderTarget()->DrawBitmap(bmp,
		dest,
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		src);

	gfx->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
}

void SpriteSheet::MakeAnimated(int frames, float animspeed, int width, int height)
{
	animated = true;
	animationspeed = animspeed;
	frameTimer = animspeed;
	this->frames = frames;
	size.x = width;
	size.y = height;
	this->spritesAccross = (int)bmp->GetSize().width / size.x;
	position.x = size.x / 2;
	position.y = size.y / 2;
	radius = 5;
}

void SpriteSheet::Move(int x, int y)
{
	if (active)
	{
		this->position.x += x;
		this->position.y += y;
		*layerMoved = true;
	}
}

void SpriteSheet::MoveX(int x)
{
	if (active)
	{
		this->position.x += x;
		*layerMoved = true;
	}
}

void SpriteSheet::MoveY(int y)
{
	if (active)
	{
		this->position.y += y;
		*layerMoved = true;
	}
}

void SpriteSheet::SetPosition(Vector2 pos)
{
	position = pos;
	*layerMoved = true;
}

void SpriteSheet::SetPosition(int x, int y)
{
	position.x = x;
	position.y = y;
	*layerMoved = true;
}

void SpriteSheet::Rotate(int amount)
{
	rotationAngle += amount;
}