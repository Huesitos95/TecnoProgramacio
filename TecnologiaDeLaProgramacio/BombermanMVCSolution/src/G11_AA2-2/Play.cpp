#pragma once
#include "Play.h"
#include "../../dep/inc/xml/rapidxml.hpp"
#include "../../dep/inc/xml/rapidxml_iterators.hpp"
#include "../../dep/inc/xml/rapidxml_utils.hpp"
#include "../../dep/inc/xml/rapidxml_print.hpp"

#include <sstream>


Play::Play(std::string level) {
	scenestate = SceneState::RUNNING;
	BG_ID = BACKGROUND;
	std::string BGPath = "../../res/img/bgGame.jpg";
	R->LoadTexture(BG_ID, BGPath);

	rapidxml::xml_document<> doc;
	std::ifstream file("../../res/files/config.xml");
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);

	if (level == "PLAY1") {
		lvl = Level();

		//Carrega XML
		rapidxml::xml_node<> *pRoot = doc.first_node();

		rapidxml::xml_node<> *pLevel = pRoot->first_node("Level");

		time = atoi(pLevel->first_attribute("time")->value());
		lives = atoi(pLevel->first_attribute("lives")->value());

		//LLegir i colocar bloc DESTRUCTIBLE
		for (rapidxml::xml_node<> *pWall = pLevel->first_node("Destructible")->first_node("Wall"); pWall; pWall = pWall->next_sibling("Wall")) {

			int i = atoi(pWall->first_attribute("j")->value());
			int j = atoi(pWall->first_attribute("i")->value());

			lvl.tablero[i][j] = cells::DESTRUCTIBLE_WALL;
		}
		//Llegir i colocar bloc INDESTRUCTIBLE
		for (rapidxml::xml_node<> *pWall = pLevel->first_node("Fixed")->first_node("Wall"); pWall; pWall = pWall->next_sibling("Wall")) {

			int i = atoi(pWall->first_attribute("j")->value());
			int j = atoi(pWall->first_attribute("i")->value());

			lvl.tablero[i][j] = cells::INDESTRUCTIBLE_WALL;

		}
		lvl.limiteIJ = { 0,0 };
		lvl.limiteWH = { lvl.cellW,lvl.cellH };
	}


	else if (level == "PLAY2") {
		lvl = Level();
		//Carrega XML
		rapidxml::xml_node<> *pRoot = doc.first_node();

		rapidxml::xml_node<> *pLevel = pRoot->first_node("Level");

		pLevel = pLevel->next_sibling("Level");

		time = atoi(pLevel->first_attribute("time")->value());
		lives = atoi(pLevel->first_attribute("lives")->value());

		//R->LoadTexture(BG_ID, "../../res/img/bgGame.jpg");

		//LLegir i colocar bloc DESTRUCTIBLE
		for (rapidxml::xml_node<> *pWall = pLevel->first_node("Destructible")->first_node("Wall"); pWall; pWall = pWall->next_sibling("Wall")) {

			int i = atoi(pWall->first_attribute("j")->value());
			int j = atoi(pWall->first_attribute("i")->value());

			lvl.tablero[i][j] = cells::DESTRUCTIBLE_WALL;
		}
		//Llegir i colocar bloc INDESTRUCTIBLE
		for (rapidxml::xml_node<> *pWall = pLevel->first_node("Fixed")->first_node("Wall"); pWall; pWall = pWall->next_sibling("Wall")) {

			int i = atoi(pWall->first_attribute("j")->value());
			int j = atoi(pWall->first_attribute("i")->value());

			lvl.tablero[i][j] = cells::INDESTRUCTIBLE_WALL;

		}
		lvl.limiteIJ = { 0, 0 };
		lvl.limiteWH = { lvl.cellW, lvl.cellH };
	}

	//Carregar P1
	player1 = Player();
	player1.Player_ID = PLAYER1_SPRITE;
	player1.PlayerPath = "../../res/img/player1.png";
	R->LoadTexture(player1.Player_ID, player1.PlayerPath);
	R->GetTextureSize(player1.Player_ID);
	player1.frameWidth = player1.textWidth / 3;
	player1.frameHeight = player1.textHeight / 4;
	player1.PlayerPosXY = lvl.CellToCoord(0, 0);
	player1.Player_Position.x = player1.PlayerPosXY.x;
	player1.Player_Position.y = player1.PlayerPosXY.y;
	player1.PlayerPosWH.x = player1.PlayerPosXY.x + CELLSIZE - 2;
	player1.PlayerPosWH.y = player1.PlayerPosXY.y + CELLSIZE - 2;
	player1.Player_Rect.x = 0;
	player1.Player_Rect.y = 0;
	player1.Player_Position.h = CELLSIZE;
	player1.Player_Rect.h = CELLSIZE;
	player1.Player_Position.w = CELLSIZE;
	player1.Player_Rect.w = CELLSIZE;
	player1.frameTime = 0;
	player1.lifes = lives;
	player1.score = 0;

	//Carregar P2
	player2 = Player();
	player2.Player_ID = PLAYER2_SPRITE;
	player2.PlayerPath = "../../res/img/player2.png";
	R->LoadTexture(player2.Player_ID, player2.PlayerPath);
	R->GetTextureSize(player2.Player_ID);
	player2.frameWidth = player2.textWidth / 3;
	player2.frameHeight = player2.textHeight / 4;
	player2.PlayerPosXY = lvl.CellToCoord(lvl.cellW-1, 0);
	player2.Player_Position.x = player2.PlayerPosXY.x;
	player2.Player_Position.y = player2.PlayerPosXY.y;
	player2.PlayerPosWH.x = player2.PlayerPosXY.x + CELLSIZE - 2;
	player2.PlayerPosWH.y = player2.PlayerPosXY.y + CELLSIZE - 2;
	player2.Player_Rect.x = 0;
	player2.Player_Rect.y = 0;
	player2.Player_Position.h = CELLSIZE;
	player2.Player_Rect.h = CELLSIZE;
	player2.Player_Position.w = CELLSIZE;
	player2.Player_Rect.w = CELLSIZE;
	player2.frameTime = 0;
	player2.lifes = lives;
	player2.score = 0;

	//HUD
	hud = HUD();
	hud.font = { "game_over","../../res/ttf/game_over.ttf",100 };
	hud.color = { 0, 0, 0, 0 };
	R->LoadFont(hud.font);

	//Players HUD
	//P1
	hud.P1lifes = { "P1lifesID" , "Lifes P1: " + std::to_string(player1.lifes), {0,0,255,0},80,50 };
	hud.P1lifesxText= 25;
	hud.P1lifesyText = -10;
	R->LoadTextureText(hud.font.id, hud.P1lifes);
	hud.P1lifes_Rect = { hud.P1lifesxText, hud.P1lifesyText, hud.P1lifes.w, hud.P1lifes.h };
	hud.P1score = { "P1ScoreID" , "Score P1: " + std::to_string(player1.score), {0,0,255,0} ,80, 50 };
	hud.P1scorexText = 25;
	hud.P1scoreyText = 30;
	R->LoadTextureText(hud.font.id, hud.P1score);
	hud.P1score_Rect = { hud.P1scorexText, hud.P1scoreyText, hud.P1score.w, hud.P1score.h };

	//P2
	hud.P2lifes = { "P2lifesID" , "Lifes P2:  " + std::to_string(player2.lifes),{ 255,0,0,0 },80,50 };
	hud.P2lifesxText = 620;
	hud.P2lifesyText = -10;
	R->LoadTextureText(hud.font.id, hud.P2lifes);
	hud.P2lifes_Rect = { hud.P2lifesxText, hud.P2lifesyText, hud.P2lifes.w, hud.P2lifes.h };
	hud.P2score = { "P2ScoreID" , "Score P2: " + std::to_string(player2.score),{ 255,0,0,0 } ,80, 50 };
	hud.P2scorexText = 620;
	hud.P2scoreyText = 30;
	R->LoadTextureText(hud.font.id, hud.P2score);
	hud.P2score_Rect = { hud.P2scorexText, hud.P2scoreyText, hud.P2score.w, hud.P2score.h };
	
	//TIME
	hud.Time = { "TimeID" , "Time left: " + std::to_string(hud.timeDown), {0,0,0,0} , 300,100 };
	hud.TimexText = 200;
	hud.TimeyText = -25;
	R->LoadTextureText(hud.font.id, hud.Time);
	hud.Time_Rect = { hud.TimexText, hud.TimeyText, hud.Time.w, hud.Time.h };
}


Play::~Play() {

}

//TODO UPDATE AND HANDLE EVENTS

void Play::HandleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		player1.HandleEvents(event);
		player2.HandleEvents(event);
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
	lvl.Draw();
	player1.Draw();
	player2.Draw();
	hud.Draw();
	R->Render();
	R->Clear();
}