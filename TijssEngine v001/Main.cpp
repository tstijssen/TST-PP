// TijssEngineconsoleappv1.cpp : Defines the entry point for the console application.

// Windows Header Files:
#include <windows.h>

// C RunTime Header Files:
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <wchar.h>
#include <math.h>
#include <iostream>

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>

#include "Render\EngineManager.h"
#include <SFML\Audio.hpp>


#ifndef Assert
#if defined( DEBUG ) || defined( _DEBUG )
#define Assert(b) do {if (!(b)) {OutputDebugStringA("Assert: " #b "\n");}} while(0)
#else
#define Assert(b)
#endif //DEBUG || _DEBUG
#endif

int WINAPI WinMain(
	HINSTANCE /* hInstance */,
	HINSTANCE /* hPrevInstance */,
	LPSTR /* lpCmdLine */,
	int /* nCmdShow */
)
{
	// Use HeapSetInformation to specify that the process should
	// terminate if the heap manager detects an error in any heap used
	// by the process.
	// The return value is ignored, because we want to continue running in the
	// unlikely event that HeapSetInformation fails.
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);
	
	int width = 1920;
	int height = 1080;

	if (SUCCEEDED(CoInitialize(NULL)))
	{
		{
			std::unique_ptr<TijssEngine> app = std::make_unique<TijssEngine>();

			if (SUCCEEDED(app->Initialize(width, height)))
			{
				app->RunMessageLoop();
			}
		}
		CoUninitialize();
	}

	return 0;
}
