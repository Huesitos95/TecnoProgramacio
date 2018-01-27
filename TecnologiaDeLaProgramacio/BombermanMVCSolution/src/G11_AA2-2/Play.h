#pragma once
#include <iostream>
#include <string>
#include "Scene.h"
#include "Renderer.h"
#include "Types.h"
#include "Constants.h"
#include "Player.h"
#include "Button.h"
#include "Level.h"
#include "Renderer.h"
#include "HUD.h"
#include "Game.h"
#include <time.h>

class Play : public Scene {

public:
	
	std::string BG_ID;
	std::string winner;
	int winscore;
	std::string winRanking;
	SDL_Rect BG_Rect{ 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };
	Player player1;
	Player player2;
	Key player1Key;
	Key player2Key;
	Level lvl;
	HUD hud;
	int lives;
	float time;
	bool endGame = false;
	clock_t lastTime = clock();
	float deltaTime = 0;
	int WallScore = 15;
	int KillScore = 100;

	Play(std::string level);
	~Play();

	void HandleEvents();
	void Update();
	void Draw();
};
