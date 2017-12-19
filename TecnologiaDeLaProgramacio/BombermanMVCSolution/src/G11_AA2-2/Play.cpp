#pragma once
#include "Play.h"


Play::Play(std::string level) {
	scenestate = SceneState::RUNNING;
	BG_ID = BACKGROUND;
	std::string BGPath = "../../res/img/bgGame.jpg";
	R->LoadTexture(BG_ID, BGPath);
	if (level == "PLAY1") {
		lvl1 = Level();
	}
	else if (level == "PLAY2") {
		lvl2 = Level();
		std::cout << "He entrado en el nivel 2" << std::endl;
		R->LoadTexture(BACKGROUND, "../../res/img/bgGame.jpg");
		for (int i = 0; i < lvl2.casillasAncho; i++) {
			lvl2.tablero[i] = new casillas[lvl2.casillasAlto];
			for (int j = 0; j < lvl2.casillasAlto; j++) {
				if ((j == 0) && (i == 0) || (j == 1) && (i == 0) || (j == 0) && (i == 1) || (j == 12) && (i == 10) || (j == 11) && (i == 10) || (j == 12) && (i == 9)) {
					lvl2.tablero[i][j] = casillas::EMPTY;
					//std::cout << "Casillas vacias" << std::endl;
				}
				else if (((j == 0) && (i == 10) || (j == 0) && (i == 9) || (j == 1) && (i == 10) || (j == 11) && (i == 0) || (j == 12) && (i == 0) || (j == 12) && (i == 1))) {
					lvl2.tablero[i][j] = casillas::EMPTY;
					//std::cout << "Casillas vacias" << std::endl;
				}
				else if ((i == 1 || i == 3 || i == 5 || i == 7 || i == 9) && (j == 1 || j == 3 || j == 5 || j == 7 || j == 9 || j == 11)) {
					lvl2.tablero[i][j] = casillas::INDESTRUCTIBLE_WALL;
				}
				else {
					lvl2.auxrandomblock = (std::rand() % (2));
					std::cout << lvl2.auxrandomblock << std::endl;
					if (lvl2.auxrandomblock == 1)
						lvl2.tablero[i][j] = casillas::DESTRUCTIBLE_WALL;
				}
			}
		}
		lvl2.limiteIJ = { 0, 0 };
		lvl2.limiteWH = { lvl2.casillasAncho, lvl2.casillasAlto };
	}

	//Load player 1
	player1 = Player();
	player1.Player_ID = PLAYER1_SPRITE;
	player1.PlayerPath = "../../res/img/player1.png";
	R->LoadTexture(player1.Player_ID, player1.PlayerPath);
	R->GetTextureSize(player1.Player_ID);
	player1.frameWidth = player1.textWidth / 3;
	player1.frameHeight = player1.textHeight / 4;
	player1.tmpPosXY = lvl1.CasillaACoordenada(0, 0);
	player1.Player_Position.x = player1.tmpPosXY.x;
	player1.Player_Position.y = player1.tmpPosXY.y;
	player1.Player_Rect.x = 0;
	player1.Player_Rect.y = 0;
	player1.Player_Position.h = LADO_CASILLA;
	player1.Player_Rect.h = LADO_CASILLA;
	player1.Player_Position.w = LADO_CASILLA;
	player1.Player_Rect.w = LADO_CASILLA;
	player1.frameTime = 0;
	player1.lifes = 3;
	player1.score = 0;

	//Load player 2
	player2 = Player();
	player2.Player_ID = PLAYER2_SPRITE;
	player2.PlayerPath = "../../res/img/player2.png";
	R->LoadTexture(player2.Player_ID, player2.PlayerPath);
	R->GetTextureSize(player2.Player_ID);
	player2.frameWidth = player2.textWidth / 3;
	player2.frameHeight = player2.textHeight / 4;
	player2.tmpPosXY = lvl1.CasillaACoordenada(lvl1.casillasAncho-1, 0);
	player2.Player_Position.x = player2.tmpPosXY.x;
	player2.Player_Position.y = player2.tmpPosXY.y;
	player2.Player_Rect.x = 0;
	player2.Player_Rect.y = 0;
	player2.Player_Position.h = LADO_CASILLA;
	player2.Player_Rect.h = LADO_CASILLA;
	player2.Player_Position.w = LADO_CASILLA;
	player2.Player_Rect.w = LADO_CASILLA;
	player2.frameTime = 0;
	player2.lifes = 3;
	player2.score = 0;

	//HUD
	hud = HUD();
	hud.font.id = "game_over";
	hud.font.path = "../../res/ttf/game_over.ttf";
	hud.font.size = 100;
	hud.color = { 0, 0, 0, 0 };
	R->LoadFont(hud.font);
	//P1lifes
	hud.P1lifes.color = hud.color;
	hud.P1lifes.id = "Buttonlvl1ID";
	hud.P1lifes.text = "Lifes p1:  " + std::to_string(player1.lifes);
	hud.P1lifes.h = 50;
	hud.P1lifes.w = 80;
	hud.P1lifesxText= 25;
	hud.P1lifesyText = -10;
	R->LoadTextureText(hud.font.id, hud.P1lifes);
	hud.P1lifes_Rect = { hud.P1lifesxText, hud.P1lifesyText, hud.P1lifes.w, hud.P1lifes.h };
	//P2lifes
	hud.P2lifes.color = hud.color;
	hud.P2lifes.id = "text2_ID";
	hud.P2lifes.text = "Lifes p2:  " + std::to_string(player2.lifes);
	hud.P2lifes.h = 50;
	hud.P2lifes.w = 80;
	hud.P2lifesxText = 620;
	hud.P2lifesyText = -10;
	R->LoadTextureText(hud.font.id, hud.P2lifes);
	hud.P2lifes_Rect = { hud.P2lifesxText, hud.P2lifesyText, hud.P2lifes.w, hud.P2lifes.h };

	//P1score
	hud.P1score.color = hud.color;
	hud.P1score.id = "text3_ID";
	hud.P1score.text = "Score p1:  " + std::to_string(player1.score);
	hud.P1score.h = 50;
	hud.P1score.w = 80;
	hud.P1scorexText = 25;
	hud.P1scoreyText = 30;
	R->LoadTextureText(hud.font.id, hud.P1score);
	hud.P1score_Rect = { hud.P1scorexText, hud.P1scoreyText, hud.P1score.w, hud.P1score.h };
	//P2score
	hud.P2score.color = hud.color;
	hud.P2score.id = "text4_ID";
	hud.P2score.text = "Score p2:  " + std::to_string(player2.score);
	hud.P2score.h = 50;
	hud.P2score.w = 80;
	hud.P2scorexText = 620;
	hud.P2scoreyText = 30;
	R->LoadTextureText(hud.font.id, hud.P2score);
	hud.P2score_Rect = { hud.P2scorexText, hud.P2scoreyText, hud.P2score.w, hud.P2score.h };
	//TIME
	hud.Time.color = hud.color;
	hud.Time.id = "text5_ID";
	hud.Time.text = "Time left:  " + (std::to_string(hud.timeDown));
	hud.Time.h = 100;
	hud.Time.w = 300;
	hud.TimexText = 200;
	hud.TimeyText = -15;
	R->LoadTextureText(hud.font.id, hud.Time);
	hud.Time_Rect = { hud.TimexText, hud.TimeyText, hud.Time.w, hud.Time.h };
}


Play::~Play() {

}


void Play::HandleEvents() {
	SDL_Event evento;
	while (SDL_PollEvent(&evento)) {
		player1.HandleEvents(evento);
		player2.HandleEvents(evento);
	}
}

void Play::Update() {
	const Uint8 *keyboardstate = SDL_GetKeyboardState(NULL);
	player1.Update(SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_A, SDL_SCANCODE_D, SDL_SCANCODE_SPACE);
	player2.Update(SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT, SDL_SCANCODE_RCTRL);
	hud.Update();
}

void Play::Draw() {
	R->PushImage(BG_ID, BG_Rect);
	lvl1.Draw();
	lvl2.Draw();
	player1.Draw();
	player2.Draw();
	hud.Draw();
	R->Render();
	R->Clear();
}