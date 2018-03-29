#pragma once
#include "_DllExport.h"

#define  _XM_NO_INTRINSICS_

#include "EngineManager.h"
#include "EngineDefines.h"
#include "Shader.h"
#include "SceneObject.h"


namespace Tijss
{
	class TIJSSEN_DECLSPEC Base2D : public cSceneObject
	{
	public:
		void CreateConstantBuffer(int32 pBufferSize, D3D11_USAGE pD3D11_USAGE);
		void UpdateConstantBufferData(const void* Data);

		void SetColorModulation(float32 r, float32 g, float32 b);
		void SetAlpha(float32 a);

		void SetRotation(float32 Pitch, float32 Yaw, float32 Roll);
		void SetPosition(float32 x, float32 y, float32 z);
		void SetScale(float32 x, float32 y, float32 z);

		XMMATRIX CalculateWorldMatrix();
	protected:

		// Shader
		cShader *m_Shader;
		ID3D11Buffer		*ShaderConstantBuffer;

		// Vertex Buffer
		ID3D11Buffer *VertexBuffer;
		UINT VB_Stride;
		UINT VB_Offset;

		// Matrix
		sFloat2 RotationCenter;
		XMMATRIX RotationMatrix;
		XMMATRIX ScaleMatrix;
		XMMATRIX TranslationMatrix;

		sColour ColorModulation;

		// Methods
		void InitDrawable();
		void ReleaseDrawable();

	};
}