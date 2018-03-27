#pragma once

#include <wincodec.h>
#include "TypeDefines.h"
#include "Graphics.h"
#include "ThreadPool.h"

namespace CollisionType
{
	enum Type { None, Circle, Box, Point };
}

class SpriteSheet;

class SpriteManager
{
public:
	SpriteManager(Graphics* gfx);
	~SpriteManager();

	// no built in collision resolutions
	SpriteSheet* DetectCollisions(SpriteSheet* sprite);
	SpriteSheet* DetectMouseCollisions(Vector2 mousePos, int32 layer);
	bool OnMouse(Vector2 mousePos, SpriteSheet* sprite);

	SpriteSheet* AddSprite(string fileName, int layer = 0, CollisionType::Type collider = CollisionType::None, Vector2 position = {0,0}, bool isIsometric = false);

	static void FolderInit(string spriteFolderPath)
	{
		m_FolderPath = spriteFolderPath + "\\";
	}

	void Draw(double frameTime);
	void RemoveSprite(int layer);

private:
	// layerstest
	struct spriteLayer
	{
		std::vector<SpriteSheet*> sprites;
		ID2D1Layer * renderLayer = NULL;
		bool active;
		bool isIsomentric;
		bool hasMoved;
	};

	std::vector<spriteLayer> WorldSprites;
	static string m_FolderPath;
	Graphics* gfx;
};

class SpriteSheet
{
	friend class SpriteManager;
	ID2D1Bitmap* bmp;

	bool *layerMoved;

	int rotationAngle;
	int spritesAccross;

	int managerIndex;
	bool isometric;

	// animation data
	bool animated;
	int frames;		// number of frames
	int frameIndex;	// currently used frame
	float frameTimer;	// time until next frame

	void Init();
	void Draw(Graphics* gfx, double frameTime);
	SpriteSheet(CollisionType::Type collider, Vector2 position, bool *layerMovedVar, bool isIsomtric);
	~SpriteSheet();
public:
	void MakeAnimated(int frames, float animspeed, int width, int height);

	// public variables
	CollisionType::Type collider;
	Vector2 position;
	Vector2 origin;
	float scale;
	Vector2 size;
	int radius;
	int layer;
	bool active;
	string tag;
	float animationspeed;

	// currently do not work with animated sprites
	void Scale(int x, int y);
	void ScaleX(int x);
	void ScaleY(int y);

	void Rotate(int angle);

	void Move(int x, int y);
	void MoveX(int x);
	void MoveY(int y);
	void SetPosition(Vector2 pos);
	void SetPosition(int x, int y);
};