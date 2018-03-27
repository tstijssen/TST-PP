#include "SpriteSheet.h"

using namespace nbsdx::concurrent;

string SpriteManager::m_FolderPath;

SpriteManager::SpriteManager(Graphics* gfx)
{
	this->gfx = gfx;
	// initial sprite layer
	spriteLayer backgroundLayer;
	backgroundLayer.isIsomentric = true;
	WorldSprites.push_back(backgroundLayer);
}

SpriteManager::~SpriteManager()
{
	std::vector<spriteLayer>::iterator layerIter;

	for (layerIter = WorldSprites.begin(); layerIter != WorldSprites.end(); ++layerIter)
	{
		if ((*layerIter).renderLayer)
		{
			(*layerIter).renderLayer->Release();
		}
		std::vector<SpriteSheet*>::iterator spriteIter;
		for (spriteIter = (*layerIter).sprites.begin(); spriteIter != (*layerIter).sprites.end(); ++spriteIter)
		{
			if ((*spriteIter))
			{
				delete (*spriteIter);
			}
		}
	}

}

SpriteSheet* SpriteManager::AddSprite(string fileName, int layer, CollisionType::Type collider, Vector2 position, bool isIsometric)
{
	// add new layers?
	if (layer >= WorldSprites.size())
	{
		for (int i = WorldSprites.size(); i <= layer; ++i)
		{
			spriteLayer newLayer;
			WorldSprites.push_back(newLayer);
		}
	}

	this->gfx = gfx;
	SpriteSheet* newSprite = new SpriteSheet(collider, position, &WorldSprites[layer].hasMoved, isIsometric);
	newSprite->bmp = NULL;

	HRESULT hr;
	string filePath = m_FolderPath + fileName;
	std::wstring widestr = std::wstring(filePath.begin(), filePath.end());

	// create path for sprite file
	const wchar_t* finalPath = widestr.c_str();

	// create factory
	IWICImagingFactory *wicFactory = NULL;

	hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		(LPVOID*)&wicFactory
	);

	IWICBitmapDecoder *wicDecoder = NULL;
	hr = wicFactory->CreateDecoderFromFilename(
		finalPath,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&wicDecoder
	);

	IWICBitmapFrameDecode* wicFrame = NULL;
	hr = wicDecoder->GetFrame(0, &wicFrame);

	IWICFormatConverter *wicConverter = NULL;
	hr = wicFactory->CreateFormatConverter(&wicConverter);

	hr = wicConverter->Initialize(
		wicFrame,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		NULL,
		0.0,
		WICBitmapPaletteTypeCustom
	);

	hr = gfx->GetRenderTarget()->CreateBitmapFromWicBitmap(
		wicConverter,
		NULL,
		&newSprite->bmp
	);

	if (wicFactory) wicFactory->Release();
	if (wicDecoder) wicDecoder->Release();
	if (wicConverter) wicConverter->Release();
	if (wicFrame) wicFrame->Release();

	newSprite->layer = layer;
	newSprite->Init();
	hr = gfx->GetRenderTarget()->CreateLayer(NULL, &WorldSprites[layer].renderLayer);
	WorldSprites[layer].active = true;
	WorldSprites[layer].isIsomentric = true;
	WorldSprites[layer].sprites.push_back(newSprite);
	return newSprite;
}

struct isometric_sort
{
	inline bool operator() (const SpriteSheet* spriteA, const SpriteSheet* spriteB)
	{
		return (spriteA->position.y + (spriteA->size.y / 2) < spriteB->position.y + (spriteB->size.y / 2));
	}
};

void SpriteManager::Draw(double frameTime)
{
	///////////////////MULTITHREADING...ONE LAYER EACH OR ONE SPRITE EACH?///////////////////////

	std::vector<spriteLayer>::iterator layerIter;

	for (layerIter = WorldSprites.begin(); layerIter != WorldSprites.end(); ++layerIter)
	{
		if ((*layerIter).active)
		{
			if ((*layerIter).hasMoved)
			{
				// sort sprites vector
				std::sort((*layerIter).sprites.begin(), (*layerIter).sprites.end(), isometric_sort());
			}
			gfx->GetRenderTarget()->PushLayer(
				D2D1::LayerParameters(D2D1::InfiniteRect(),
					NULL,
					D2D1_ANTIALIAS_MODE_PER_PRIMITIVE,
					D2D1::IdentityMatrix(),
					1.0f,
					(ID2D1Brush*)0,
					D2D1_LAYER_OPTIONS_NONE
				),
				(*layerIter).renderLayer
			);

			std::vector<SpriteSheet*>::iterator spriteIter;
			for (spriteIter = (*layerIter).sprites.begin(); spriteIter != (*layerIter).sprites.end(); ++spriteIter)
			{
				if ((*spriteIter)->active)
				{
					(*spriteIter)->Draw(gfx, frameTime);
				}
			}

			gfx->GetRenderTarget()->PopLayer();
			(*layerIter).hasMoved = false;
		}	
	}
}

void SpriteManager::RemoveSprite(int index)
{
}

SpriteSheet* SpriteManager::DetectCollisions(SpriteSheet* sprite)
{
	int aX;
	int aY;
	int aWidth;
	int aHeight;
	int aRadius;

	switch (sprite->collider)
	{
	case CollisionType::Box:
	{
		aWidth = sprite->size.x;		 // maxX
		aHeight = sprite->size.y;		 // maxY
		aX = sprite->position.x - aWidth / 2;	 // minX
		aY = sprite->position.y - aWidth / 2;	 // minY
		break;
	}
	case CollisionType::Circle:
	{
		aX = sprite->position.x;
		aY = sprite->position.y;
		aRadius = sprite->radius;
		break;
	}
	case CollisionType::Point:
	{
		aX = sprite->position.x;
		aY = sprite->position.y;
		break;
	}
	default:
		break;
	}

	///////////////////MULTITHREADING...ONE WORLD SPRITE EACH?///////////////////////
	for (std::vector<SpriteSheet*>::iterator it = WorldSprites[sprite->layer].sprites.begin(); it != WorldSprites[sprite->layer].sprites.end(); ++it)
	{
		if ((*it)->collider != CollisionType::None && (*it)->active && (*it) != sprite)
		{
			int bX;
			int bY;
			int bWidth;
			int bHeight;
			int bRadius;
			switch ((*it)->collider)
			{
			case CollisionType::Box:
			{
				bWidth = (*it)->size.x;				// maxX
				bHeight = (*it)->size.y;			// maxY
				bX = (*it)->position.x - bWidth / 2;				// minX
				bY = (*it)->position.y - bWidth / 2;				// minY

				switch (sprite->collider)
				{
					// static = box, moving = box
				case CollisionType::Box:
				{
					if ((abs(aX - bX) * 2 < (aWidth + bWidth)) &&
						(abs(aY - bY) * 2 < (aHeight + bHeight)))
					{
						return (*it);
					}
					break;
				}
				// static = box, moving = circle
				case CollisionType::Circle:
				{
					auto halfWidth = bWidth / 2;
					auto halfHeight = bHeight / 2;

					auto distX = abs(aX - bX - halfWidth);
					auto distY = abs(aY - bY - halfHeight);

					if (distX > (halfWidth + aRadius)) { return false; };
					if (distY > (halfHeight + aRadius)) { return false; };

					if (distX <= (halfWidth)) { return (*it); };
					if (distY <= (halfHeight)) { return (*it); };

					auto pX = distX - halfWidth;
					auto pY = distY - halfHeight;

					return ((pX * pX + pY * pY <= (aRadius * aRadius)) ? (*it) : NULL);

					break;
				}
				// static = box, moving = point
				case CollisionType::Point:
				{
					if (aX > bX && aX < bWidth && aY > bY && aY < bHeight)
					{
						return (*it);
					}
					break;
				}
				default:
					break;
				}
				break;
			}			
			case CollisionType::Circle:
			{
				bX = (*it)->position.x;
				bY = (*it)->position.y;
				bRadius = (*it)->radius;

				switch (sprite->collider)
				{
					// static = circle, moving = box
				case CollisionType::Box:
				{
					auto halfWidth = aWidth / 2;
					auto halfHeight = aHeight / 2;

					auto distX = abs(bX - aX - halfWidth);
					auto distY = abs(bY - aY - halfHeight);

					if (distX > (halfWidth + bRadius)) { return false; };
					if (distY > (halfHeight + bRadius)) { return false; };

					if (distX <= (halfWidth)) { return (*it); };
					if (distY <= (halfHeight)) { return (*it); };

					auto pX = distX - halfWidth;
					auto pY = distY - halfHeight;

					return	((pX * pX + pY * pY <= (bRadius * bRadius)) ? (*it) : NULL);
					break;
				}
				// static = circle, moving = circle
				case CollisionType::Circle:
				{
					int x = abs(aX - bX);
					int y = abs(aY - bY);
					int distance = sqrt(x * x + y * y);

					if (distance < aRadius + bRadius)
					{
						return (*it);
					}
					break;
				}
				// static = circle, moving = point
				case CollisionType::Point:
				{
					int x = abs(bX - aX);
					int y = abs(bY - aY);
					int distance = sqrt(x * x + y * y);

					if (distance < bRadius)
					{
						return (*it);
					}
					break;
				}
				default:
					break;
				}
				break;
			}			
			case CollisionType::Point:
			{
				bX = (*it)->position.x;
				bY = (*it)->position.y;

				switch (sprite->collider)
				{
					// static = point, moving = box
				case CollisionType::Box:
				{
					if (bX > aX && bX < aWidth && bY > aY && bY < aHeight)
					{
						return (*it);
					}
					break;
				}
				// static = point, moving = circle
				case CollisionType::Circle:
				{
					int x = abs(aX + bX);
					int y = abs(aY + bY);
					int distance = sqrt(x * x + y * y);

					if (distance < aRadius)
					{
						return (*it);
					}
					break;
				}
				// static = point, moving = point
				case CollisionType::Point:
				{
					if (aX == bX && aY == bY)
					{
						return (*it);
					}
					break;
				}
				default:
					break;
				}
				break;
			}	
			default:
				break;
			}
		}
	}
	return NULL;
}

SpriteSheet* SpriteManager::DetectMouseCollisions(Vector2 mousePos, int32 layer)
{
	for (std::vector<SpriteSheet*>::iterator it = WorldSprites[layer].sprites.begin(); it != WorldSprites[layer].sprites.end(); ++it)
	{
		if ((*it)->collider != CollisionType::None)
		{
			int bX;
			int bY;
			int bWidth;
			int bHeight;
			int bRadius;
			switch ((*it)->collider)
			{
			case CollisionType::Box:
			{
				bWidth = (*it)->size.x;				// maxX
				bHeight = (*it)->size.y;			// maxY
				bX = (*it)->position.x - bWidth / 2;				// minX
				bY = (*it)->position.y - bWidth / 2;				// minY
				if (mousePos.x > bX && mousePos.x < bWidth && mousePos.y > bY && mousePos.y < bHeight)
				{
					return (*it);
				}
				break;
			}
			case CollisionType::Circle:
			{
				bX = (*it)->position.x;
				bY = (*it)->position.y;
				bRadius = (*it)->radius;
				int x = abs(bX - mousePos.x);
				int y = abs(bY - mousePos.y);
				int distance = sqrt(x * x + y * y);

				if (distance < bRadius)
				{
					return (*it);
				}
				break;
			}
			case CollisionType::Point:
			{
				bX = (*it)->position.x;
				bY = (*it)->position.y;

				if (mousePos.x == bX && mousePos.y == bY)
				{
					return (*it);
				}
				break;
			}
			default:
				break;
			}
		}
	}
	return NULL;
}

bool SpriteManager::OnMouse(Vector2 mousePos, SpriteSheet* sprite)
{
	int bX;
	int bY;
	int bWidth;
	int bHeight;
	int bRadius;
	switch (sprite->collider)
	{
	case CollisionType::Box:
	{
		bWidth = sprite->size.x;				// maxX
		bHeight = sprite->size.y;			// maxY
		bX = sprite->position.x - bWidth / 2;				// minX
		bY = sprite->position.y - bWidth / 2;				// minY
		if (mousePos.x > bX && mousePos.x < bWidth && mousePos.y > bY && mousePos.y < bHeight)
		{
			return true;
		}
		break;
	}
	case CollisionType::Circle:
	{
		bX = sprite->position.x;
		bY = sprite->position.y;
		bRadius = sprite->radius;
		int x = abs(bX - mousePos.x);
		int y = abs(bY - mousePos.y);
		int distance = sqrt(x * x + y * y);

		if (distance < bRadius)
		{
			return true;
		}
		break;
	}
	case CollisionType::Point:
	{
		bX = sprite->position.x;
		bY = sprite->position.y;

		if (mousePos.x == bX && mousePos.y == bY)
		{
			return true;
		}
		break;
	}
	default:
		break;
	}
	return false;
}