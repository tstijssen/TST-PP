#pragma once

#include <wincodec.h>
#include "Graphics.h"

class SpriteSheet
{
	Graphics* gfx;
	ID2D1Bitmap* bmp;

	int spriteWidth, spriteHeight;

	int spritesAccross;

public:
	SpriteSheet(wchar_t* filename, Graphics* gfx);
	SpriteSheet(wchar_t* filename, Graphics* gfx, int spritewidth, int spriteheight);
	~SpriteSheet();

	void Draw();
	void Draw(int index, int x, int y);
};