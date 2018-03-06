#include "GameController.h"

GameLevel* GameController::currentLevel;
bool GameController::Loading;

void GameController::Init()
{
	Loading = true;
	currentLevel = 0;
}

void GameController::LoadInitialLevel(GameLevel* level)
{
	Loading = true;
	currentLevel = level;
	currentLevel->Load();
	Loading = false;
}
void GameController::SwitchLevel(GameLevel* level)
{
	Loading = true;
	currentLevel->Unload();
	level->Load();
	delete currentLevel;
	currentLevel = level;
	Loading = false;
}

void GameController::Render()
{
	if (Loading) return;
	currentLevel->Render();
}
void GameController::Update()
{
	if (Loading) return;
	currentLevel->Update();
}