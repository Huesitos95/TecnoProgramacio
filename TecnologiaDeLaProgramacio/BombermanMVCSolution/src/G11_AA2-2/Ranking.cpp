#pragma onceXpositionText
#include "Ranking.h"



Ranking::Ranking()
{
	scenestate = SceneState::RUNNING;
	BG_ID = BACKGROUND;
	std::string BGPath = "../../res/img/bgGame.jpg";
	R->LoadTexture(BG_ID, BGPath);
	ButtonMenu = Button();
	ButtonMenu.font.id = "game_over";
	ButtonMenu.font.path = "../../res/ttf/game_over.ttf";
	ButtonMenu.font.size = 24;
	ButtonMenu.color = { 255, 0, 0, 0 };
	ButtonMenu.text.color = ButtonMenu.color;
	ButtonMenu.text.id = "text3_ID";
	ButtonMenu.text.text = "Menu";
	ButtonMenu.text.h = 50;
	ButtonMenu.text.w = 100;
	ButtonMenu.xText= SCREEN_WIDTH / 2 - ButtonMenu.text.w / 2;
	ButtonMenu.yText = 600;
	R->LoadFont(ButtonMenu.font);
	R->LoadTextureText(ButtonMenu.font.id, ButtonMenu.text);
	ButtonMenu.text_Rect = { ButtonMenu.xText, ButtonMenu.yText, ButtonMenu.text.w, ButtonMenu.text.h };
}


Ranking::~Ranking()
{
}

void Ranking::Update() {
	ButtonMenu.update();
}


void Ranking::HandleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		ButtonMenu.HandleEvents(event);
		ButtonMenu.HandleEvents(event);
		if (ButtonMenu.isClicked()) {
			scenestate = SceneState::GOTOMENU;
		}
	}
}

void Ranking::Draw() {
	R->PushImage(BG_ID, BG_Rect);
	ButtonMenu.draw();
	R->Render();
	R->Clear();
}