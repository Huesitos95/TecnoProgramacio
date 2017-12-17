#pragma once
#include <iostream>
#include "Renderer.h"
#include "Menu.h"
#include "Play.h"
#include "Ranking.h"

class GameManager
{

public:
	GameState gameState;
	SceneState currentScene;

	GameManager();
	~GameManager();

	void Loop();
};

