#pragma once
#include "Menu.h"



Menu::Menu()
{
	scenestate = SceneState::RUNNING;
	BG_ID = BACKGROUND;
	std::string BGPath = "../../res/img/bgGame.jpg";
	R->LoadTexture(BG_ID, BGPath);

	//Button Play Level 1
	ButtonLVL1 = Button();
	ButtonLVL1.font = { "game_over" ,"../../res/ttf/game_over.ttf" ,50 };
	ButtonLVL1.text = {"Buttonlvl1ID" , " Play Level 1" ,{ 255, 0, 0, 0 }, 200 , 75 };
	ButtonLVL1.xText = SCREEN_WIDTH / 2 - ButtonLVL1.text.w / 2;
	ButtonLVL1.yText = (SCREEN_HEIGHT / 2 - ButtonLVL1.text.h / 2)-100;
	R->LoadFont(ButtonLVL1.font);
	R->LoadTextureText(ButtonLVL1.font.id, ButtonLVL1.text);
	ButtonLVL1.text_Rect = { ButtonLVL1.xText, ButtonLVL1.yText, ButtonLVL1.text.w, ButtonLVL1.text.h };

	//Button Play Level 2
	ButtonLVL2 = Button();
	ButtonLVL2.text = { "Buttonlvl2ID" , " Play Level 2" ,{ 255, 0, 0, 0 }, 200 , 75 };
	ButtonLVL2.xText = SCREEN_WIDTH / 2 - ButtonLVL2.text.w / 2;
	ButtonLVL2.yText = (SCREEN_HEIGHT / 2 - ButtonLVL2.text.h / 2);
	R->LoadTextureText(ButtonLVL1.font.id, ButtonLVL2.text);
	ButtonLVL2.text_Rect = { ButtonLVL2.xText, ButtonLVL2.yText, ButtonLVL2.text.w, ButtonLVL2.text.h };

	//Button Ranking
	ButtonRanking = Button();
	ButtonRanking.font = { "saiyan" ,"../../res/ttf/saiyan.ttf" ,50 };
	ButtonRanking.text = { "Buttonlvl3ID" , " Ranking" ,{ 0, 0, 255, 0 }, 200 , 100 };
	ButtonRanking.xText = SCREEN_WIDTH / 2 - ButtonRanking.text.w / 2;
	ButtonRanking.yText = (SCREEN_HEIGHT / 2)+100;
	R->LoadFont(ButtonRanking.font);
	R->LoadTextureText(ButtonRanking.font.id, ButtonRanking.text);
	ButtonRanking.text_Rect = { ButtonRanking.xText, ButtonRanking.yText, ButtonRanking.text.w, ButtonRanking.text.h };
}


Menu::~Menu()
{
}

void Menu::HandleEvents() {
	SDL_Event evento;
	while (SDL_PollEvent(&evento)) {
		ButtonLVL1.HandleEvents(evento);
		ButtonLVL2.HandleEvents(evento);
		ButtonRanking.HandleEvents(evento);
		if (ButtonLVL1.isClicked()) {
			scenestate = SceneState::GOTOLVL1;
		}
		if (ButtonLVL2.isClicked()) {
			scenestate = SceneState::GOTOLVL2;
		}
		else if (ButtonRanking.isClicked()) {
			scenestate = SceneState::GOTORANKING;
		}
	}
}

void Menu::Update() {
	ButtonLVL1.update();
	ButtonLVL2.update();
	ButtonRanking.update();
}

void Menu::Draw() {
	R->PushImage(BG_ID, BG_Rect);
	ButtonLVL1.draw();
	ButtonLVL2.draw();
	ButtonRanking.draw();
	R->Render();
	R->Clear();
}