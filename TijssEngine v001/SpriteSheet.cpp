#include "SpriteSheet.h"

string SpriteSheet::m_FolderPath;
smanager::SpriteManager *smanager::SpriteManager::m_Instance = 0;

SpriteSheet::SpriteSheet(string filename, Graphics* gfx, CollisionType::Type collision, bool isometric)
{
	// get instance of singleton and add this sprite to its list
	managerIndex = smanager::SpriteManager::instance().AddSprite(this);

	this->gfx = gfx;
	bmp = NULL;
	HRESULT hr;
	string filePath = m_FolderPath + filename;
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
		&bmp
	);

	if (wicFactory) wicFactory->Release();
	if (wicDecoder) wicDecoder->Release();
	if (wicConverter) wicConverter->Release();
	if (wicFrame) wicFrame->Release();

	size.x = bmp->GetSize().width;
	size.y = bmp->GetSize().height;
	spritesAccross = 1;
	position.x = size.x / 2;
	position.y = size.y / 2;
	layer = 0;
	scale.x = 1;
	scale.y = 1;
	radius = size.x / 2;
	active = true;
	tag = "";
	this->collision = collision;
	this->isometric = isometric;
}

SpriteSheet::~SpriteSheet()
{
	if (bmp)
	{
		bmp->Release();
	}
}

void SpriteSheet::Draw()
{
	if (active)
	{
		// source depends on animated
		D2D_RECT_F src;
		if (animated)
		{
			// advance frame
			frameIndex = (1 + frameIndex) % frames;

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
			position.x + scale.x + size.x / 2, position.y + scale.y + size.y / 2);

		gfx->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Rotation(rotationAngle, D2D1::Point2F(position.x, position.y)));

		gfx->GetRenderTarget()->DrawBitmap(bmp,
			dest,
			1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
			src);

		gfx->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
	}
}

void SpriteSheet::MakeAnimated(int frames, int width, int height)
{
	animated = true;
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
		if (collision != CollisionType::None)	// check collisions
		{
			if (smanager::SpriteManager::instance().DetectCollisions(managerIndex))// reset move if colliding
			{
				this->position.x -= x;
				this->position.y -= y;
				return;
			}
		}
	}
}

void SpriteSheet::MoveX(int x)
{
	if (active)
	{
		this->position.x += x;
		if (collision != CollisionType::None)	// check collisions
		{
			if (smanager::SpriteManager::instance().DetectCollisions(managerIndex))// reset move if colliding
			{
				this->position.x -= x;
				return;
			}
		}
	}
}

void SpriteSheet::MoveY(int y)
{
	if (active)
	{
		this->position.y += y;
		if (collision != CollisionType::None)	// check collisions
		{
			if (smanager::SpriteManager::instance().DetectCollisions(managerIndex))// reset move if colliding
			{
				this->position.y -= y;
				return;
			}
		}
	}
}

void SpriteSheet::SetPosition(Vector2 pos)
{
	position = pos;
}

void SpriteSheet::SetPosition(int x, int y)
{
	position.x = x;
	position.y = y;
}

void SpriteSheet::Rotate(int amount)
{
	rotationAngle += amount;
}