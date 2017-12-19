#pragma once
#include <iostream>
#include <string>
#include "Scene.h"
#include "Renderer.h"
#include "Types.h"
#include "Constants.h"
#include "Button.h"
#include "Player.h"
#include "Button.h"
#include "Level.h"
#include "Renderer.h"
#include "HUD.h"
#include "Game.h"

class Play : public Scene {

public:
	//variables
	std::string BG_ID;
	SDL_Rect BG_Rect{ 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };
	Player player1;
	Player player2;
	Level lvl1;
	Level lvl2;
	HUD hud;


	Play(std::string level);
	~Play();

	void HandleEvents();
	void Update();
	void Draw();
};
