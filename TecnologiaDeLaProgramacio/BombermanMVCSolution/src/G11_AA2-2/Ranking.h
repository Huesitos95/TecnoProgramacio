#pragma once
#include "Scene.h"
#include "Renderer.h"
#include "Types.h"
#include "Constants.h"
#include "Button.h"


class Ranking : public Scene {

private:
	//variables
	std::string BG_ID;
	SDL_Rect BG_Rect{ 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };
public:
	Ranking();
	~Ranking();

	void HandleEvents() override;
	void Update() override;
	void Draw() override;

	Button ButtonMenu;

};
