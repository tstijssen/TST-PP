#pragma once

#include "Game.h"

class GameController
{
	GameController() {};
	static GameLevel* currentLevel;
public:
	static bool Loading;

	static void Init();

	static void LoadInitialLevel(GameLevel* level);
	static void SwitchLevel(GameLevel* level);

	static void Render();
	static void Update();
};