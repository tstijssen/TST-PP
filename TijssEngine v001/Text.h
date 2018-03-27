#pragma once
#include "TypeDefines.h"
#include "Graphics.h"

class TextRenderer
{
	string font;
	int32 size;
public:
	TextRenderer(string fontName, int32 fontSize);

	void Draw();
};