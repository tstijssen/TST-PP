#pragma once

#include "_DllExport.h"

#include "Base2D.h"
#include "TextureAtlas.h"
#include "EngineDefines.h"
#include "TextureRegion.h"
#include "DefaultShaderBase.h"




namespace Tuxis
{

	class TUXIS_DECLSPEC Sprite : public Drawable2D
	{
	private:
		TextureAtlas *mTexture;
		Vertex::vtxSprite vertices[4];

		floatRect AbsTexCoord;
		float2 HalfTexSize;
		CBSprite mCBValue;

		void Initialize();

	public:

		Sprite();


		void SetPosition2D(float tX, float tY, bool centered);
		void SetTextureRegion(TextureRegion *pTextureRegion);
		void SetTextureAtlas(TextureAtlas *pTexture);
		void SetShader(Shader *pShader);

		void Draw();
		void Update();
		void Release();
	};

}