#pragma once
#include <iostream>
#include "Renderer.h"
#include "Menu.h"
#include "Play.h"
#include "Ranking.h"



class Game
{
public:
	GameState gamestate;
	Scene *currentscene;

	Game();
	~Game();

	void LoopGame();

};

