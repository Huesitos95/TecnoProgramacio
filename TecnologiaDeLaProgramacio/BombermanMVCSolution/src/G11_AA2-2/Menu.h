#pragma once
#include <iostream>
#include <string>
#include "Scene.h"
#include "Renderer.h"
#include "Types.h"
#include "Constants.h"
#include "Button.h"
#include "Ranking.h"


class Menu : public Scene {

private:
	std::string BG_ID;
	SDL_Rect BG_Rect{ 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };
public:
	Menu();
	~Menu();

	void HandleEvents() override;
	void Update() override;
	void Draw() override;

	Button ButtonLVL1;
	Button ButtonLVL2;
	Button ButtonRanking;
	Button ButtonMute;
	
};

