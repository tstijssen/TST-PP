#pragma once

#include <wincodec.h>
#include "TypeDefines.h"
#include "Graphics.h"

namespace CollisionType
{
	enum Type { None, Circle, Box, Point };
}

class SpriteSheet;

namespace smanager
{
	class SpriteManager
	{
	public:

		static SpriteManager& instance()
		{
			if(!m_Instance)
				m_Instance = new SpriteManager;
			return *m_Instance;
		}

		bool DetectCollisions(int index);

		int AddSprite(SpriteSheet* newSprite);

		void RemoveSprite(int index);

	private:
		std::vector<SpriteSheet*> m_AllSprites;
		static SpriteManager *m_Instance;
		SpriteManager() {};
	};
};

class SpriteSheet
{
	Graphics* gfx;
	ID2D1Bitmap* bmp;

	int rotationAngle;
	int spritesAccross;

	static string m_FolderPath;
	int managerIndex;
	bool isometric;

	// animation data
	bool animated;
	int frames;		// number of frames
	int frameIndex;	// currently used frame

public:
	SpriteSheet(string filename, Graphics* gfx, CollisionType::Type collision = CollisionType::None, bool isometric = false);
	~SpriteSheet();
	
	static void FolderInit(string spriteFolderPath)
	{
		m_FolderPath = spriteFolderPath + "\\";
	}

	void Draw();

	void MakeAnimated(int frames, int width, int height);

	// public variables
	CollisionType::Type collision;
	Vector2 position;
	Vector2 origin;
	Vector2 scale;
	Vector2 size;
	int radius;
	int layer;
	bool active;
	string tag;

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