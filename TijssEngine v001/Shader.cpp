#include "Shader.h"


namespace Tijss
{
	cShader::cShader()
	{
		VS_Buffer = nullptr;
		PS_Buffer = nullptr;
		VertexShader = nullptr;
		PixelShader = nullptr;
		InputLayout = nullptr;
	}

	void cShader::Load(const WCHAR* FX_FileName)
	{
		DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

#if defined( DEBUG ) || defined( _DEBUG )
		dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

		// Compiling shaders
		hr = D3DX11CompileFromFileW(FX_FileName, 0, 0, "VS", "vs_4_0", dwShaderFlags, 0, 0, &VS_Buffer, 0, 0);
		if (FAILED(hr))
			Log::Error("TxShader::Load D3DX11CompileFromFile VS");

		hr = D3DX11CompileFromFileW(FX_FileName, 0, 0, "PS", "ps_4_0", dwShaderFlags, 0, 0, &PS_Buffer, 0, 0);
		if (FAILED(hr))
			Log::Error("TxShader::Load D3DX11CompileFromFile PS");

		// Creating 

		hr = cGraphics::GFXInstance()->GetDevice()->CreateVertexShader(VS_Buffer->GetBufferPointer(), VS_Buffer->GetBufferSize(), NULL, &VertexShader);
		if (FAILED(hr))
			Log::Error("TxShader::Load CreateVertexShader");

		hr = cGraphics::GFXInstance()->GetDevice()->CreatePixelShader(PS_Buffer->GetBufferPointer(), PS_Buffer->GetBufferSize(), NULL, &PixelShader);
		if (FAILED(hr))
			Log::Error("TxShader::Load CreatePixelShader");
	}


	void cShader::CreateInputLayout(D3D11_INPUT_ELEMENT_DESC *pLayout, int pNumElements)
	{
		if (!VS_Buffer)
			Log::Error("TxShader::CreateInputLayout VS_Buffer - null");

		hr = cGraphics::GFXInstance()->GetDevice()->CreateInputLayout(pLayout, pNumElements, VS_Buffer->GetBufferPointer(), VS_Buffer->GetBufferSize(), &InputLayout);

		if (FAILED(hr))
			Log::Error("TxShader::CreateInputLayout");
	}


	void cShader::Release()
	{
		InputLayout->Release();
		VertexShader->Release();
		PixelShader->Release();
		VS_Buffer->Release();
		PS_Buffer->Release();

		VS_Buffer = 0;
		PS_Buffer = 0;
		VertexShader = 0;
		PixelShader = 0;
		InputLayout = 0;
	}

	cShader::~cShader()
	{
		if (VertexShader || PixelShader)
			Release();
	}
}