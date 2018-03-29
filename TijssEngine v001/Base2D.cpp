#include "Base2D.h"

namespace Tijss
{
	XMMATRIX Base2D::CalculateWorldMatrix()
	{
		return ScaleMatrix * RotationMatrix * TranslationMatrix;
	}

	void Base2D::SetScale(float sx, float sy, float sz = 1.0f)
	{
		m_Changed = true;
		ScaleMatrix = XMMatrixScaling(sx, sy, sz);
	}

	void Base2D::SetRotation(float Pitch, float Yaw, float Roll)
	{
		m_Changed = true;
		RotationMatrix = XMMatrixRotationRollPitchYaw(Pitch*DEGREETORADIAN, Yaw*DEGREETORADIAN, Roll*DEGREETORADIAN);
	}


	void Base2D::SetPosition(float x, float y, float z = 0.0f)
	{
		m_Changed = true;
		TranslationMatrix = XMMatrixTranslation(x, y, z);
	}


	void Base2D::InitDrawable()
	{
		m_Changed = true;
		VB_Stride = 0;
		VB_Offset = 0;
		m_Shader = nullptr;
		VertexBuffer = nullptr;
		ShaderConstantBuffer = nullptr;

		// Matrix Default Configuration
		ScaleMatrix = XMMatrixScaling(1.0f, 1.0f, 1.0f);
		TranslationMatrix = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
		RotationMatrix = XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f);

		ColorModulation = sColour(1.0f, 1.0f, 1.0f, 1.0f);

		RotationCenter(0.0f, 0.0f);
	}

	void Base2D::ReleaseDrawable()
	{
		_RELEASE(ShaderConstantBuffer);
		_RELEASE(VertexBuffer);
		m_Shader = nullptr;
	}

	void Base2D::SetColorModulation(float r, float g, float b)
	{
		m_Changed = true;
		ColorModulation.r = r;
		ColorModulation.g = g;
		ColorModulation.b = b;
	}

	void Base2D::SetAlpha(float a)
	{
		m_Changed = true;
		ColorModulation.a = a;
	}


	void Base2D::CreateConstantBuffer(int pBufferSize, D3D11_USAGE pD3D11_USAGE)
	{
		_RELEASE(ShaderConstantBuffer);

		//Create the buffer to send to the cbuffer in effect file
		D3D11_BUFFER_DESC ConstantBufferDescribes;
		ZeroMemory(&ConstantBufferDescribes, sizeof(D3D11_BUFFER_DESC));
		ConstantBufferDescribes.ByteWidth = pBufferSize;
		ConstantBufferDescribes.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		ConstantBufferDescribes.MiscFlags = 0;
		ConstantBufferDescribes.Usage = (D3D11_USAGE)pD3D11_USAGE;

		if (pD3D11_USAGE == D3D11_USAGE_DYNAMIC)
			ConstantBufferDescribes.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		else
			ConstantBufferDescribes.CPUAccessFlags = 0;

		hr = cGraphics::GFXInstance()->GetDevice()->CreateBuffer(&ConstantBufferDescribes, NULL, &ShaderConstantBuffer);
		if (FAILED(hr))
			Log::Error("TxShader::CreateConstantBuffer CreateBuffer ");
	}


	void Base2D::UpdateConstantBufferData(const void* Data)
	{
		if (ShaderConstantBuffer == nullptr)
			Log::Warning("Drawable2D::UpdateConstantBufferData: Constant buffer not exist");
		else
			cEngine::GetContext()->UpdateSubresource(ShaderConstantBuffer, 0, NULL, Data, 0, 0);
	}

}