#include "HUD.h"



HUD::HUD()
{
	font.id = "game_over";
	font.path = "../../res/ttf/game_over.ttf";
	font.size = 24;
	color = { 0, 255, 255, 0 };
	//P1lifes
	P1lifes.color = color;
	P1lifes.text = "works?";
	P1lifes.h = 50;
	P1lifes.w = 100;
	P1lifesxText= SCREEN_WIDTH / 2 - P1lifes.w / 2;
	P1lifesyText = SCREEN_HEIGHT / 2 - P1lifes.h / 2;
	R->LoadFont(font);
	P1lifes_Rect = { P1lifesxText, P1lifesyText, P1lifes.w, P1lifes.h };
	//P2lifes
	P2lifes.color = color;
	P2lifes.text = "works?";
	P2lifes.h = 50;
	P2lifes.w = 100;
	P2lifesxText = SCREEN_WIDTH / 2 - P2lifes.w / 2;
	P2lifesyText = SCREEN_HEIGHT / 2 - P2lifes.h / 2;
	P2lifes_Rect = { P2lifesxText, P2lifesyText, P2lifes.w, P2lifes.h };

	//P1score
	P1score.color = color;
	P1score.text = "works?";
	P1score.h = 50;
	P1score.w = 100;
	P1scorexText = SCREEN_WIDTH / 2 - P1score.w / 2;
	P1scoreyText = SCREEN_HEIGHT / 2 - P1score.h / 2;
	P1score_Rect = { P1scorexText, P1scoreyText, P1score.w, P1score.h };
	//P2score
	P2score.color = color;
	P2score.text = "works?";
	P2score.h = 50;
	P2score.w = 100;
	P2scorexText = SCREEN_WIDTH / 2 - P2score.w / 2;
	P2scoreyText = SCREEN_HEIGHT / 2 - P2score.h / 2;
	P2score_Rect = { P2scorexText, P2scoreyText, P2score.w, P2score.h };
	//Time
	Time.color = color;
	Time.text = "works?";
	Time.h = 50;
	Time.w = 100;
	TimexText = SCREEN_WIDTH / 2 - Time.w / 2;
	TimeyText = SCREEN_HEIGHT / 2 - Time.h / 2;
	P2score_Rect = { TimexText, TimeyText, Time.w, Time.h };
}


HUD::~HUD()
{

}

void HUD::Update() {
	R->LoadTextureText(font.id, Time);
	R->LoadTextureText(font.id, P1lifes);
	R->LoadTextureText(font.id, P1score);
	R->LoadTextureText(font.id, P2lifes);
	R->LoadTextureText(font.id, P2score);
	if (timeDown > 0) {
		deltaTime = (clock() - lastTime);
		lastTime = clock();
		deltaTime /= CLOCKS_PER_SEC;
		timeDown -= deltaTime;
		//std::cout << timeDown << std::endl;
		Time.text = "Time left:  " + (std::to_string(static_cast<int>(timeDown)));
	}
	if (timeDown <= 0) {
		//std::cout << "FIN DEL JUEGO" << std::endl;
		Time.text = "FIN DEL JUEGO";
		findeljuego = true;
	}
}

void HUD::Draw() {
	R->PushImage(P1lifes.id, P1lifes_Rect);
	R->PushImage(P2lifes.id, P2lifes_Rect);
	R->PushImage(P1score.id, P1score_Rect);
	R->PushImage(P2score.id, P2score_Rect);
	R->PushImage(Time.id, Time_Rect);
}