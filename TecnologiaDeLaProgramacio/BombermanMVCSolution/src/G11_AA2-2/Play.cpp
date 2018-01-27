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
		if (endGame || player1.lifes == 0 || player2.lifes == 0) {
			std::cout << "Has guanyat, introdueix el teu nom per consola" << std::endl;
			std::cin >> winner;
			std::cout << " Guanyador introduit" << std::endl;
			std::ofstream fsalida("../../res/files/ranking.bin", std::ios::binary | std::ios::app);
			if (player1.score > player2.score) { winscore = player1.score; }
			if (player2.score >= player1.score) { winscore = player2.score; }
			winRanking = winner + " " + std::to_string((winscore));
			fsalida << winner << ' ' << winscore << ' ';
			fsalida.close();
			//Tancar el binari
			//Tornar al menu
			scenestate = SceneState::GOTOMENU;
			return;
		}
	}
}

void Play::Update() {
	const Uint8 *keyboardstate = SDL_GetKeyboardState(NULL);
	//JUGADOR 1
	player1Key = player1.Update(SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_A, SDL_SCANCODE_D, SDL_SCANCODE_SPACE);
	player1.PlayerPosXY = lvl.CoordToCell(player1.Player_Position.x, player1.Player_Position.y - (CELLSIZE + 17) / 2);
	player1.PlayerPosWH = lvl.CoordToCell(player1.Player_Position.x + CELLSIZE - 1, player1.Player_Position.y - ((CELLSIZE + 17) / 2) + CELLSIZE - 1);
	//POWER UPs
	if (player1.Rollers) {
		player1.speed = 2 * 1.8;
		//debería ser 3.6 pero como se mueve por píxeles y los píxeles son enteros, se trunca a 3 así que el boost es casi inapreciable.
	}
	else {
		player1.speed = 2;
	}

	if (player1.PowerUp) {
		std::cout << player1.timeDown << std::endl;
		std::cout << "player 1 is poweredup so countdown" << std::endl;
		player1.deltaTime = (clock() - player1.lastTime);
		player1.lastTime = clock();
		player1.deltaTime /= CLOCKS_PER_SEC;
		player1.timeDown -= player1.deltaTime;
		if (player1.timeDown <= 0) {
			player1.Rollers = false;
			player1.Helmet = false;
			player1.PowerUp = false;
		}
	}
	else {
		std::cout << "player 1 is no more poweredup" << std::endl;
		player1.lastTime = clock();
		player1.timeDown = 10.;
		player1.deltaTime = 0;
	}
	//MOVIMIENTO
	if (player1Key == Key::UP && player1.PlayerPosXY.y >= lvl.limiteIJ.y && player1.Player_Position.x >= CELLSIZE) {
		if ((lvl.tablero[player1.PlayerPosXY.x][player1.PlayerPosXY.y] != cells::INDESTRUCTIBLE_WALL && lvl.tablero[player1.PlayerPosWH.x][player1.PlayerPosWH.y - 1] != cells::INDESTRUCTIBLE_WALL)
			&& (lvl.tablero[player1.PlayerPosXY.x][player1.PlayerPosXY.y] != cells::DESTRUCTIBLE_WALL && lvl.tablero[player1.PlayerPosWH.x][player1.PlayerPosWH.y - 1] != cells::DESTRUCTIBLE_WALL)) {
			player1.Player_Rect.y = 0;
			player1.Player_Position.y -= player1.speed;
		}
		else if (lvl.tablero[player1.PlayerPosXY.x][player1.PlayerPosXY.y] != cells::EMPTY || lvl.tablero[player1.PlayerPosWH.x][player1.PlayerPosWH.y - 1] != cells::EMPTY) {
			player1.Player_Position.y += player1.speed;
		}
	}
	else if (player1Key == Key::DOWN && player1.PlayerPosXY.y + 1 < lvl.limiteWH.y && player1.Player_Position.x >= CELLSIZE) {
		if ((lvl.tablero[player1.PlayerPosXY.x][player1.PlayerPosXY.y + 1] != cells::INDESTRUCTIBLE_WALL && lvl.tablero[player1.PlayerPosWH.x][player1.PlayerPosWH.y] != cells::INDESTRUCTIBLE_WALL)
			&& (lvl.tablero[player1.PlayerPosXY.x][player1.PlayerPosXY.y + 1] != cells::DESTRUCTIBLE_WALL && lvl.tablero[player1.PlayerPosWH.x][player1.PlayerPosWH.y] != cells::DESTRUCTIBLE_WALL)) {
			player1.Player_Rect.y = player1.Player_Rect.h * 2;
			player1.Player_Position.y += player1.speed;
		}
		else if (lvl.tablero[player1.PlayerPosXY.x][player1.PlayerPosXY.y + 1] != cells::EMPTY || lvl.tablero[player1.PlayerPosWH.x][player1.PlayerPosWH.y] != cells::EMPTY) {
			player1.Player_Position.y -= player1.speed;
		}
	}
	else if (player1Key == Key::LEFT && player1.PlayerPosXY.x >= lvl.limiteIJ.x && player1.PlayerPosWH.x - 1 >= lvl.limiteIJ.x && player1.Player_Position.y >= CELLSIZE + HUD_HEIGHT) {
		if ((lvl.tablero[player1.PlayerPosXY.x][player1.PlayerPosXY.y] != cells::INDESTRUCTIBLE_WALL && lvl.tablero[player1.PlayerPosWH.x - 1][player1.PlayerPosWH.y] != cells::INDESTRUCTIBLE_WALL)
			&& (lvl.tablero[player1.PlayerPosXY.x][player1.PlayerPosXY.y] != cells::DESTRUCTIBLE_WALL && lvl.tablero[player1.PlayerPosWH.x - 1][player1.PlayerPosWH.y] != cells::DESTRUCTIBLE_WALL)) {
			player1.Player_Rect.y = player1.Player_Rect.h;
			player1.Player_Position.x -= player1.speed;
		}
		else if (lvl.tablero[player1.PlayerPosXY.x][player1.PlayerPosXY.y] != cells::EMPTY || lvl.tablero[player1.PlayerPosWH.x - 1][player1.PlayerPosWH.y] != cells::EMPTY) {
			player1.Player_Position.x += player1.speed;
		}
	}
	else if (player1Key == Key::RIGHT && player1.PlayerPosXY.x + 1 < lvl.limiteWH.x && player1.Player_Position.y >= CELLSIZE + HUD_HEIGHT) {
		if ((lvl.tablero[player1.PlayerPosXY.x + 1][player1.PlayerPosXY.y] != cells::INDESTRUCTIBLE_WALL && lvl.tablero[player1.PlayerPosWH.x][player1.PlayerPosWH.y] != cells::INDESTRUCTIBLE_WALL)
			&& (lvl.tablero[player1.PlayerPosXY.x + 1][player1.PlayerPosXY.y] != cells::DESTRUCTIBLE_WALL && lvl.tablero[player1.PlayerPosWH.x][player1.PlayerPosWH.y] != cells::DESTRUCTIBLE_WALL)) {
			player1.Player_Rect.y = player1.Player_Rect.h * 3;
			player1.Player_Position.x += player1.speed;
		}
		else if (lvl.tablero[player1.PlayerPosXY.x + 1][player1.PlayerPosXY.y] != cells::EMPTY || lvl.tablero[player1.PlayerPosWH.x][player1.PlayerPosWH.y] != cells::EMPTY) {
			player1.Player_Position.x -= player1.speed;
		}
	}
	//BOMBA
	if (player1Key == Key::BOMB) {
		std::cout << "drop the bomb!" << std::endl;
		player1.pBombIJ = player1.PlayerPosXY;
		//ESTO DEBE COMPROBAR SI EN LA POSICIÓN DE LA ONDA EXPANSIVA HAY UN LADRILLO
		std::cout << player1.pBombIJ.x << " " << player1.pBombIJ.y << std::endl;

		//COMPRUEBA ARRIBA
		if (player1.pBombIJ.y > lvl.limiteIJ.y) {
			if (lvl.tablero[player1.pBombIJ.x][player1.pBombIJ.y - 1] == cells::INDESTRUCTIBLE_WALL)
			{
				player1.up = true;
			}
			else
			{
				player1.up = false;
			}

			if (player1.pBombIJ.y > lvl.limiteIJ.y + 1 && player1.up == false) {
				if (lvl.tablero[player1.pBombIJ.x][player1.pBombIJ.y - 2] == cells::INDESTRUCTIBLE_WALL)
				{
					player1.up2 = true;
				}
				else
				{
					player1.up2 = false;
				}
			}
		}

		//COMPRUEBA ABAJO
		if (player1.pBombIJ.y < lvl.limiteWH.y - 1) {
			if (lvl.tablero[player1.pBombIJ.x][player1.pBombIJ.y + 1] == cells::INDESTRUCTIBLE_WALL)
			{
				player1.down = true;
			}
			else
			{
				player1.down = false;
			}
			if (player1.pBombIJ.y < lvl.limiteWH.y - 2 && player1.down == false) {
				if (lvl.tablero[player1.pBombIJ.x][player1.pBombIJ.y + 2] == cells::INDESTRUCTIBLE_WALL)
				{
					player1.down2 = true;
				}
				else
				{
					player1.down2 = false;
				}
			}
		}

		//COMPRUEBA IZQUIERDA
		if (player1.pBombIJ.x > lvl.limiteIJ.x) {
			if (lvl.tablero[player1.pBombIJ.x - 1][player1.pBombIJ.y] == cells::INDESTRUCTIBLE_WALL)
			{
				player1.left = true;
			}
			else
			{
				player1.left = false;
			}

			if (player1.pBombIJ.x > lvl.limiteIJ.x + 1 && player1.left == false) {
				if (lvl.tablero[player1.pBombIJ.x - 2][player1.pBombIJ.y] == cells::INDESTRUCTIBLE_WALL)
				{
					player1.left2 = true;
				}
				else
				{
					player1.left2 = false;
				}
			}
		}

		//COMPRUEBA DERECHA
		if (player1.pBombIJ.x < lvl.limiteWH.x - 1) {
			if (lvl.tablero[player1.pBombIJ.x + 1][player1.pBombIJ.y] == cells::INDESTRUCTIBLE_WALL)
			{
				player1.right = true;
			}
			else
			{
				player1.right = false;
			}

			if (player1.pBombIJ.x < lvl.limiteWH.x - 2 && player1.right == false) {
				if (lvl.tablero[player1.pBombIJ.x + 2][player1.pBombIJ.y] == cells::INDESTRUCTIBLE_WALL)
				{
					player1.right2 = true;
				}
				else
				{
					player1.right2 = false;
				}
			}
		}

		player1.pBombXY = lvl.CellToCoord(player1.pBombIJ.x, player1.pBombIJ.y);
		player1.dropbomb = true;
	}

	//EXPLOSIÓN DE BOMBA, DESTRUCCIÓN DE MUROS Y DAÑO
	if (player1.bomb.exploding) {
		//ARRIBA
		if (player1.pBombIJ.y > lvl.limiteIJ.y && player1.up == false) {
			if (lvl.tablero[player1.pBombIJ.x][player1.pBombIJ.y - 1] == cells::DESTRUCTIBLE_WALL)
			{
				player1.score += WallScore;
				lvl.tablero[player1.pBombIJ.x][player1.pBombIJ.y - 1] = cells::EMPTY;
				lvl.Update(player1.pBombIJ.x, player1.pBombIJ.y - 1);
			}
			if (player1.pBombIJ.y > lvl.limiteIJ.y + 1 && player1.up2 == false) {
				if (lvl.tablero[player1.pBombIJ.x][player1.pBombIJ.y - 2] == cells::DESTRUCTIBLE_WALL)
				{
					player1.score += WallScore;
					lvl.tablero[player1.pBombIJ.x][player1.pBombIJ.y - 2] = cells::EMPTY;
					lvl.Update(player1.pBombIJ.x, player1.pBombIJ.y - 1);
				}
			}
		}
		//ABAJO
		if (player1.pBombIJ.y < lvl.limiteWH.y - 1 && player1.down == false) {
			if (lvl.tablero[player1.pBombIJ.x][player1.pBombIJ.y + 1] == cells::DESTRUCTIBLE_WALL)
			{
				player1.score += WallScore;
				lvl.tablero[player1.pBombIJ.x][player1.pBombIJ.y + 1] = cells::EMPTY;
				lvl.Update(player1.pBombIJ.x, player1.pBombIJ.y - 1);
			}
			if (player1.pBombIJ.y < lvl.limiteWH.y - 2 && player1.down2 == false) {
				if (lvl.tablero[player1.pBombIJ.x][player1.pBombIJ.y + 2] == cells::DESTRUCTIBLE_WALL)
				{
					player1.score += WallScore;
					lvl.tablero[player1.pBombIJ.x][player1.pBombIJ.y + 2] = cells::EMPTY;
					lvl.Update(player1.pBombIJ.x, player1.pBombIJ.y + 2);
				}
			}
		}
		//IZQUIERDA
		if (player1.pBombIJ.x > lvl.limiteIJ.x && player1.left == false) {
			if (lvl.tablero[player1.pBombIJ.x - 1][player1.pBombIJ.y] == cells::DESTRUCTIBLE_WALL)
			{
				player1.score += WallScore;
				lvl.tablero[player1.pBombIJ.x - 1][player1.pBombIJ.y] = cells::EMPTY;
				lvl.Update(player1.pBombIJ.x - 1, player1.pBombIJ.y);
			}
			if (player1.pBombIJ.x > lvl.limiteIJ.x + 1 && player1.left2 == false) {
				if (lvl.tablero[player1.pBombIJ.x - 2][player1.pBombIJ.y] == cells::DESTRUCTIBLE_WALL)
				{
					player1.score += WallScore;
					lvl.tablero[player1.pBombIJ.x - 2][player1.pBombIJ.y] = cells::EMPTY;
					lvl.Update(player1.pBombIJ.x - 2, player1.pBombIJ.y);
				}
			}
		}
		//DERECHA
		if (player1.pBombIJ.x < lvl.limiteWH.x - 1 && player1.right == false) {
			if (lvl.tablero[player1.pBombIJ.x + 1][player1.pBombIJ.y] == cells::DESTRUCTIBLE_WALL)
			{
				player1.score += WallScore;
				lvl.tablero[player1.pBombIJ.x + 1][player1.pBombIJ.y] = cells::EMPTY;
				lvl.Update(player1.pBombIJ.x + 1, player1.pBombIJ.y);
			}
			if (player1.pBombIJ.x < lvl.limiteWH.x - 2 && player1.right2 == false) {
				if (lvl.tablero[player1.pBombIJ.x + 2][player1.pBombIJ.y] == cells::DESTRUCTIBLE_WALL)
				{
					player1.score += WallScore;
					lvl.tablero[player1.pBombIJ.x + 2][player1.pBombIJ.y] = cells::EMPTY;
					lvl.Update(player1.pBombIJ.x + 2, player1.pBombIJ.y);
				}
			}
		}

		//DAÑO DE TU PROPIA BOMBA
		if (!player1.damaged) {
			if ((player1.pBombIJ.x == player1.PlayerPosXY.x && player1.pBombIJ.y - 1 == player1.PlayerPosXY.y)
				|| (player1.pBombIJ.x == player1.PlayerPosWH.x && player1.pBombIJ.y - 1 == player1.PlayerPosWH.y)
				|| (player1.pBombIJ.x == player1.PlayerPosXY.x && player1.pBombIJ.y - 2 == player1.PlayerPosXY.y)
				|| (player1.pBombIJ.x == player1.PlayerPosWH.x && player1.pBombIJ.y - 2 == player1.PlayerPosWH.y)
				|| (player1.pBombIJ.x == player1.PlayerPosXY.x && player1.pBombIJ.y + 1 == player1.PlayerPosXY.y)
				|| (player1.pBombIJ.x == player1.PlayerPosWH.x && player1.pBombIJ.y + 1 == player1.PlayerPosWH.y)
				|| (player1.pBombIJ.x == player1.PlayerPosXY.x && player1.pBombIJ.y + 2 == player1.PlayerPosXY.y)
				|| (player1.pBombIJ.x == player1.PlayerPosWH.x && player1.pBombIJ.y + 2 == player1.PlayerPosWH.y)
				|| (player1.pBombIJ.x - 1 == player1.PlayerPosXY.x && player1.pBombIJ.y == player1.PlayerPosXY.y)
				|| (player1.pBombIJ.x - 1 == player1.PlayerPosWH.x && player1.pBombIJ.y == player1.PlayerPosWH.y)
				|| (player1.pBombIJ.x - 2 == player1.PlayerPosXY.x && player1.pBombIJ.y == player1.PlayerPosXY.y)
				|| (player1.pBombIJ.x - 2 == player1.PlayerPosWH.x && player1.pBombIJ.y == player1.PlayerPosWH.y)
				|| (player1.pBombIJ.x + 1 == player1.PlayerPosXY.x && player1.pBombIJ.y == player1.PlayerPosXY.y)
				|| (player1.pBombIJ.x + 1 == player1.PlayerPosWH.x && player1.pBombIJ.y == player1.PlayerPosWH.y)
				|| (player1.pBombIJ.x + 2 == player1.PlayerPosXY.x && player1.pBombIJ.y == player1.PlayerPosXY.y)
				|| (player1.pBombIJ.x + 2 == player1.PlayerPosWH.x && player1.pBombIJ.y == player1.PlayerPosWH.y)) {
				if (player1.Helmet) {
					player1.Helmet = false;
					player1.PowerUp = false;
					player1.damaged = true;
				}
				else {
					std::cout << "oh no" << std::endl;
					player1.lifes -= 1;
					player1.damaged = true;
				}
			}
		}
		//DAÑO AL OTRO JUGADOR
		if (!player2.damaged) {
			if ((player1.pBombIJ.x == player2.PlayerPosXY.x && player1.pBombIJ.y - 1 == player2.PlayerPosXY.y)
				|| (player1.pBombIJ.x == player2.PlayerPosWH.x && player1.pBombIJ.y - 1 == player2.PlayerPosWH.y)
				|| (player1.pBombIJ.x == player2.PlayerPosXY.x && player1.pBombIJ.y - 2 == player2.PlayerPosXY.y)
				|| (player1.pBombIJ.x == player2.PlayerPosWH.x && player1.pBombIJ.y - 2 == player2.PlayerPosWH.y)
				|| (player1.pBombIJ.x == player2.PlayerPosXY.x && player1.pBombIJ.y + 1 == player2.PlayerPosXY.y)
				|| (player1.pBombIJ.x == player2.PlayerPosWH.x && player1.pBombIJ.y + 1 == player2.PlayerPosWH.y)
				|| (player1.pBombIJ.x == player2.PlayerPosXY.x && player1.pBombIJ.y + 2 == player2.PlayerPosXY.y)
				|| (player1.pBombIJ.x == player2.PlayerPosWH.x && player1.pBombIJ.y + 2 == player2.PlayerPosWH.y)
				|| (player1.pBombIJ.x - 1 == player2.PlayerPosXY.x && player1.pBombIJ.y == player2.PlayerPosXY.y)
				|| (player1.pBombIJ.x - 1 == player2.PlayerPosWH.x && player1.pBombIJ.y == player2.PlayerPosWH.y)
				|| (player1.pBombIJ.x - 2 == player2.PlayerPosXY.x && player1.pBombIJ.y == player2.PlayerPosXY.y)
				|| (player1.pBombIJ.x - 2 == player2.PlayerPosWH.x && player1.pBombIJ.y == player2.PlayerPosWH.y)
				|| (player1.pBombIJ.x + 1 == player2.PlayerPosXY.x && player1.pBombIJ.y == player2.PlayerPosXY.y)
				|| (player1.pBombIJ.x + 1 == player2.PlayerPosWH.x && player1.pBombIJ.y == player2.PlayerPosWH.y)
				|| (player1.pBombIJ.x + 2 == player2.PlayerPosXY.x && player1.pBombIJ.y == player2.PlayerPosXY.y)
				|| (player1.pBombIJ.x + 2 == player2.PlayerPosWH.x && player1.pBombIJ.y == player2.PlayerPosWH.y)) {
				if (player2.Helmet) {
					player2.Helmet = false;
					player2.PowerUp = false;
					player2.damaged = true;
				}
				else {
					player2.lifes -= 1;
					player2.damaged = true;
					player1.score += 100;
				}
			}
		}
	}
	else if (!player1.bomb.exploding && !player2.bomb.exploding) {
		player1.damaged = false;
		player2.damaged = false;
	}

	//CORRECCIÓN DE POSICIÓN
	if (player1.PlayerPosXY.y <= -1) {
		player1.Player_Position.y = CELLSIZE + HUD_HEIGHT;
	}
	if (player1.PlayerPosXY.x <= -1) {
		player1.Player_Position.x = CELLSIZE;
	}

	//COMPROBACIÓN DE SI HA COGIDO UN POWER UP
	if (player1.PlayerPosXY.y >= 0 && player1.PlayerPosXY.x >= 0 && player1.PlayerPosWH.x<lvl.limiteWH.x && player1.PlayerPosWH.y<lvl.limiteWH.y && !player1.PowerUp) {
		if (lvl.tablero[player1.PlayerPosXY.x][player1.PlayerPosXY.y] == cells::ROLLERS || lvl.tablero[player1.PlayerPosWH.x][player1.PlayerPosWH.y] == cells::ROLLERS) {
			lvl.tablero[player1.PlayerPosXY.x][player1.PlayerPosXY.y] = cells::EMPTY;
			lvl.tablero[player1.PlayerPosWH.x][player1.PlayerPosWH.y] = cells::EMPTY;
			player1.Rollers = true;
			player1.PowerUp = true;
		}
		if (lvl.tablero[player1.PlayerPosXY.x][player1.PlayerPosXY.y] == cells::HELMET || lvl.tablero[player1.PlayerPosWH.x][player1.PlayerPosWH.y] == cells::HELMET) {
			lvl.tablero[player1.PlayerPosXY.x][player1.PlayerPosXY.y] = cells::EMPTY;
			lvl.tablero[player1.PlayerPosWH.x][player1.PlayerPosWH.y] = cells::EMPTY;
			player1.Helmet = true;
			player1.PowerUp = true;
		}
	}


	//JUGADOR 2
	player2Key = player2.Update(SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT, SDL_SCANCODE_RCTRL);
	player2.PlayerPosXY = lvl.CoordToCell(player2.Player_Position.x, player2.Player_Position.y - (CELLSIZE + 17) / 2);
	player2.PlayerPosWH = lvl.CoordToCell(player2.Player_Position.x + CELLSIZE - 1, player2.Player_Position.y - ((CELLSIZE + 17) / 2) + CELLSIZE - 1);
	//POWER UPs
	if (player2.Rollers) {
		player2.speed = 2 * 1.8;
		//debería ser 3.6 pero como se mueve por píxeles y los píxeles son enteros, se trunca a 3 así que el boost es casi inapreciable.
	}
	else {
		player2.speed = 2;
	}

	if (player2.PowerUp) {
		player2.deltaTime = (clock() - player2.lastTime);
		player2.lastTime = clock();
		player2.deltaTime /= CLOCKS_PER_SEC;
		player2.timeDown -= player2.deltaTime;
		if (player2.timeDown <= 0) {
			player2.Rollers = false;
			player2.Helmet = false;
			player2.PowerUp = false;
		}
	}
	else {
		player2.lastTime = clock();
		player2.timeDown = 10.;
		player2.deltaTime = 0;
	}
	//MOVIMIENTO
	if (player2Key == Key::UP && player2.PlayerPosXY.y >= lvl.limiteIJ.y && player2.Player_Position.x >= CELLSIZE) {
		if ((lvl.tablero[player2.PlayerPosXY.x][player2.PlayerPosXY.y] != cells::INDESTRUCTIBLE_WALL && lvl.tablero[player2.PlayerPosWH.x][player2.PlayerPosWH.y - 1] != cells::INDESTRUCTIBLE_WALL)
			&& (lvl.tablero[player2.PlayerPosXY.x][player2.PlayerPosXY.y] != cells::DESTRUCTIBLE_WALL && lvl.tablero[player2.PlayerPosWH.x][player2.PlayerPosWH.y - 1] != cells::DESTRUCTIBLE_WALL)) {
			player2.Player_Rect.y = 0;
			player2.Player_Position.y -= player2.speed;
		}
		else if (lvl.tablero[player2.PlayerPosXY.x][player2.PlayerPosXY.y] != cells::EMPTY || lvl.tablero[player2.PlayerPosWH.x][player2.PlayerPosWH.y - 1] != cells::EMPTY) {
			player2.Player_Position.y += player2.speed;
		}
	}
	else if (player2Key == Key::DOWN && player2.PlayerPosXY.y + 1 < lvl.limiteWH.y && player2.Player_Position.x >= CELLSIZE) {
		if ((lvl.tablero[player2.PlayerPosXY.x][player2.PlayerPosXY.y + 1] != cells::INDESTRUCTIBLE_WALL && lvl.tablero[player2.PlayerPosWH.x][player2.PlayerPosWH.y] != cells::INDESTRUCTIBLE_WALL)
			&& (lvl.tablero[player2.PlayerPosXY.x][player2.PlayerPosXY.y + 1] != cells::DESTRUCTIBLE_WALL && lvl.tablero[player2.PlayerPosWH.x][player2.PlayerPosWH.y] != cells::DESTRUCTIBLE_WALL)) {
			player2.Player_Rect.y = player2.Player_Rect.h * 2;
			player2.Player_Position.y += player2.speed;
		}
		else if (lvl.tablero[player2.PlayerPosXY.x][player2.PlayerPosXY.y + 1] != cells::EMPTY || lvl.tablero[player2.PlayerPosWH.x][player2.PlayerPosWH.y] != cells::EMPTY) {
			player2.Player_Position.y -= player2.speed;
		}
	}
	else if (player2Key == Key::LEFT && player2.PlayerPosXY.x >= lvl.limiteIJ.x && player2.PlayerPosWH.x - 1 >= lvl.limiteIJ.x && player2.Player_Position.y >= CELLSIZE + HUD_HEIGHT) {
		if ((lvl.tablero[player2.PlayerPosXY.x][player2.PlayerPosXY.y] != cells::INDESTRUCTIBLE_WALL && lvl.tablero[player2.PlayerPosWH.x - 1][player2.PlayerPosWH.y] != cells::INDESTRUCTIBLE_WALL)
			&& (lvl.tablero[player2.PlayerPosXY.x][player2.PlayerPosXY.y] != cells::DESTRUCTIBLE_WALL && lvl.tablero[player2.PlayerPosWH.x - 1][player2.PlayerPosWH.y] != cells::DESTRUCTIBLE_WALL)) {
			player2.Player_Rect.y = player2.Player_Rect.h;
			player2.Player_Position.x -= player2.speed;
		}
		else if (lvl.tablero[player2.PlayerPosXY.x][player2.PlayerPosXY.y] != cells::EMPTY || lvl.tablero[player2.PlayerPosWH.x - 1][player2.PlayerPosWH.y] != cells::EMPTY) {
			player2.Player_Position.x += player2.speed;
		}
	}
	else if (player2Key == Key::RIGHT && player2.PlayerPosXY.x + 1 < lvl.limiteWH.x && player2.Player_Position.y >= CELLSIZE + HUD_HEIGHT) {
		if ((lvl.tablero[player2.PlayerPosXY.x + 1][player2.PlayerPosXY.y] != cells::INDESTRUCTIBLE_WALL && lvl.tablero[player2.PlayerPosWH.x][player2.PlayerPosWH.y] != cells::INDESTRUCTIBLE_WALL)
			&& (lvl.tablero[player2.PlayerPosXY.x + 1][player2.PlayerPosXY.y] != cells::DESTRUCTIBLE_WALL && lvl.tablero[player2.PlayerPosWH.x][player2.PlayerPosWH.y] != cells::DESTRUCTIBLE_WALL)) {
			player2.Player_Rect.y = player2.Player_Rect.h * 3;
			player2.Player_Position.x += player2.speed;
		}
		else if (lvl.tablero[player2.PlayerPosXY.x + 1][player2.PlayerPosXY.y] != cells::EMPTY || lvl.tablero[player2.PlayerPosWH.x][player2.PlayerPosWH.y] != cells::EMPTY) {
			player2.Player_Position.x -= player2.speed;
		}
	}
	//BOMBA
	if (player2Key == Key::BOMB) {
		std::cout << "drop the bomb!" << std::endl;
		player2.pBombIJ = player2.PlayerPosXY;
		//ESTO DEBE COMPROBAR SI EN LA POSICIÓN DE LA ONDA EXPANSIVA HAY UN LADRILLO
		std::cout << player2.pBombIJ.x << " " << player2.pBombIJ.y << std::endl;

		//COMPRUEBA ARRIBA
		if (player2.pBombIJ.y > lvl.limiteIJ.y) {
			if (lvl.tablero[player2.pBombIJ.x][player2.pBombIJ.y - 1] == cells::INDESTRUCTIBLE_WALL)
			{
				player2.up = true;
			}
			else
			{
				player2.up = false;
			}

			if (player2.pBombIJ.y > lvl.limiteIJ.y + 1 && player2.up == false) {
				if (lvl.tablero[player2.pBombIJ.x][player2.pBombIJ.y - 2] == cells::INDESTRUCTIBLE_WALL)
				{
					player2.up2 = true;
				}
				else
				{
					player2.up2 = false;
				}
			}
		}

		//COMPRUEBA ABAJO
		if (player2.pBombIJ.y < lvl.limiteWH.y - 1) {
			if (lvl.tablero[player2.pBombIJ.x][player2.pBombIJ.y + 1] == cells::INDESTRUCTIBLE_WALL)
			{
				player2.down = true;
			}
			else
			{
				player2.down = false;
			}
			if (player2.pBombIJ.y < lvl.limiteWH.y - 2 && player2.down == false) {
				if (lvl.tablero[player2.pBombIJ.x][player2.pBombIJ.y + 2] == cells::INDESTRUCTIBLE_WALL)
				{
					player2.down2 = true;
				}
				else
				{
					player2.down2 = false;
				}
			}
		}

		//COMPRUEBA IZQUIERDA
		if (player2.pBombIJ.x > lvl.limiteIJ.x) {
			if (lvl.tablero[player2.pBombIJ.x - 1][player2.pBombIJ.y] == cells::INDESTRUCTIBLE_WALL)
			{
				player2.left = true;
			}
			else
			{
				player2.left = false;
			}

			if (player2.pBombIJ.x > lvl.limiteIJ.x + 1 && player2.left == false) {
				if (lvl.tablero[player2.pBombIJ.x - 2][player2.pBombIJ.y] == cells::INDESTRUCTIBLE_WALL)
				{
					player2.left2 = true;
				}
				else
				{
					player2.left2 = false;
				}
			}
		}

		//COMPRUEBA DERECHA
		if (player2.pBombIJ.x < lvl.limiteWH.x - 1) {
			if (lvl.tablero[player2.pBombIJ.x + 1][player2.pBombIJ.y] == cells::INDESTRUCTIBLE_WALL)
			{
				player2.right = true;
			}
			else
			{
				player2.right = false;
			}

			if (player2.pBombIJ.x < lvl.limiteWH.x - 2 && player2.right == false) {
				if (lvl.tablero[player2.pBombIJ.x + 2][player2.pBombIJ.y] == cells::INDESTRUCTIBLE_WALL)
				{
					player2.right2 = true;
				}
				else
				{
					player2.right2 = false;
				}
			}
		}

		player2.pBombXY = lvl.CellToCoord(player2.pBombIJ.x, player2.pBombIJ.y);
		player2.dropbomb = true;
	}

	//EXPLOSIÓN DE BOMBA, DESTRUCCIÓN DE MUROS Y DAÑO
	if (player2.bomb.exploding) {
		//ARRIBA
		if (player2.pBombIJ.y > lvl.limiteIJ.y && player2.up == false) {
			if (lvl.tablero[player2.pBombIJ.x][player2.pBombIJ.y - 1] == cells::DESTRUCTIBLE_WALL)
			{
				player2.score += WallScore;
				lvl.tablero[player2.pBombIJ.x][player2.pBombIJ.y - 1] = cells::EMPTY;
				lvl.Update(player2.pBombIJ.x, player2.pBombIJ.y - 1);
			}
			if (player2.pBombIJ.y > lvl.limiteIJ.y + 1 && player2.up2 == false) {
				if (lvl.tablero[player2.pBombIJ.x][player2.pBombIJ.y - 2] == cells::DESTRUCTIBLE_WALL)
				{
					player2.score += WallScore;
					lvl.tablero[player2.pBombIJ.x][player2.pBombIJ.y - 2] = cells::EMPTY;
					lvl.Update(player2.pBombIJ.x, player2.pBombIJ.y - 1);
				}
			}
		}
		//ABAJO
		if (player2.pBombIJ.y < lvl.limiteWH.y - 1 && player2.down == false) {
			if (lvl.tablero[player2.pBombIJ.x][player2.pBombIJ.y + 1] == cells::DESTRUCTIBLE_WALL)
			{
				player2.score += WallScore;
				lvl.tablero[player2.pBombIJ.x][player2.pBombIJ.y + 1] = cells::EMPTY;
				lvl.Update(player2.pBombIJ.x, player2.pBombIJ.y - 1);
			}
			if (player2.pBombIJ.y < lvl.limiteWH.y - 2 && player2.down2 == false) {
				if (lvl.tablero[player2.pBombIJ.x][player2.pBombIJ.y + 2] == cells::DESTRUCTIBLE_WALL)
				{
					player2.score += WallScore;
					lvl.tablero[player2.pBombIJ.x][player2.pBombIJ.y + 2] = cells::EMPTY;
					lvl.Update(player2.pBombIJ.x, player2.pBombIJ.y + 2);
				}
			}
		}
		//IZQUIERDA
		if (player2.pBombIJ.x > lvl.limiteIJ.x && player2.left == false) {
			if (lvl.tablero[player2.pBombIJ.x - 1][player2.pBombIJ.y] == cells::DESTRUCTIBLE_WALL)
			{
				player2.score += WallScore;
				lvl.tablero[player2.pBombIJ.x - 1][player2.pBombIJ.y] = cells::EMPTY;
				lvl.Update(player2.pBombIJ.x - 1, player2.pBombIJ.y);
			}
			if (player2.pBombIJ.x > lvl.limiteIJ.x + 1 && player2.left2 == false) {
				if (lvl.tablero[player2.pBombIJ.x - 2][player2.pBombIJ.y] == cells::DESTRUCTIBLE_WALL)
				{
					player2.score += WallScore;
					lvl.tablero[player2.pBombIJ.x - 2][player2.pBombIJ.y] = cells::EMPTY;
					lvl.Update(player2.pBombIJ.x - 2, player2.pBombIJ.y);
				}
			}
		}
		//DERECHA
		if (player2.pBombIJ.x < lvl.limiteWH.x - 1 && player2.right == false) {
			if (lvl.tablero[player2.pBombIJ.x + 1][player2.pBombIJ.y] == cells::DESTRUCTIBLE_WALL)
			{
				player2.score += WallScore;
				lvl.tablero[player2.pBombIJ.x + 1][player2.pBombIJ.y] = cells::EMPTY;
				lvl.Update(player2.pBombIJ.x + 1, player2.pBombIJ.y);
			}
			if (player2.pBombIJ.x < lvl.limiteWH.x - 2 && player2.right2 == false) {
				if (lvl.tablero[player2.pBombIJ.x + 2][player2.pBombIJ.y] == cells::DESTRUCTIBLE_WALL)
				{
					player2.score += WallScore;
					lvl.tablero[player2.pBombIJ.x + 2][player2.pBombIJ.y] = cells::EMPTY;
					lvl.Update(player2.pBombIJ.x + 2, player2.pBombIJ.y);
				}
			}
		}

		//DAÑO DE TU PROPIA BOMBA
		if (!player2.damaged) {
			if ((player2.pBombIJ.x == player2.PlayerPosXY.x && player2.pBombIJ.y - 1 == player2.PlayerPosXY.y)
				|| (player2.pBombIJ.x == player2.PlayerPosWH.x && player2.pBombIJ.y - 1 == player2.PlayerPosWH.y)
				|| (player2.pBombIJ.x == player2.PlayerPosXY.x && player2.pBombIJ.y - 2 == player2.PlayerPosXY.y)
				|| (player2.pBombIJ.x == player2.PlayerPosWH.x && player2.pBombIJ.y - 2 == player2.PlayerPosWH.y)
				|| (player2.pBombIJ.x == player2.PlayerPosXY.x && player2.pBombIJ.y + 1 == player2.PlayerPosXY.y)
				|| (player2.pBombIJ.x == player2.PlayerPosWH.x && player2.pBombIJ.y + 1 == player2.PlayerPosWH.y)
				|| (player2.pBombIJ.x == player2.PlayerPosXY.x && player2.pBombIJ.y + 2 == player2.PlayerPosXY.y)
				|| (player2.pBombIJ.x == player2.PlayerPosWH.x && player2.pBombIJ.y + 2 == player2.PlayerPosWH.y)
				|| (player2.pBombIJ.x - 1 == player2.PlayerPosXY.x && player2.pBombIJ.y == player2.PlayerPosXY.y)
				|| (player2.pBombIJ.x - 1 == player2.PlayerPosWH.x && player2.pBombIJ.y == player2.PlayerPosWH.y)
				|| (player2.pBombIJ.x - 2 == player2.PlayerPosXY.x && player2.pBombIJ.y == player2.PlayerPosXY.y)
				|| (player2.pBombIJ.x - 2 == player2.PlayerPosWH.x && player2.pBombIJ.y == player2.PlayerPosWH.y)
				|| (player2.pBombIJ.x + 1 == player2.PlayerPosXY.x && player2.pBombIJ.y == player2.PlayerPosXY.y)
				|| (player2.pBombIJ.x + 1 == player2.PlayerPosWH.x && player2.pBombIJ.y == player2.PlayerPosWH.y)
				|| (player2.pBombIJ.x + 2 == player2.PlayerPosXY.x && player2.pBombIJ.y == player2.PlayerPosXY.y)
				|| (player2.pBombIJ.x + 2 == player2.PlayerPosWH.x && player2.pBombIJ.y == player2.PlayerPosWH.y)) {
				if (player2.Helmet) {
					player2.Helmet = false;
					player2.PowerUp = false;
					player2.damaged = true;
				}
				else {
					player2.lifes -= 1;
					player2.damaged = true;
				}
			}
		}
		//DAÑO AL OTRO JUGADOR
		if (!player1.damaged) {
			if ((player2.pBombIJ.x == player1.PlayerPosXY.x && player2.pBombIJ.y - 1 == player1.PlayerPosXY.y)
				|| (player2.pBombIJ.x == player1.PlayerPosWH.x && player2.pBombIJ.y - 1 == player1.PlayerPosWH.y)
				|| (player2.pBombIJ.x == player1.PlayerPosXY.x && player2.pBombIJ.y - 2 == player1.PlayerPosXY.y)
				|| (player2.pBombIJ.x == player1.PlayerPosWH.x && player2.pBombIJ.y - 2 == player1.PlayerPosWH.y)
				|| (player2.pBombIJ.x == player1.PlayerPosXY.x && player2.pBombIJ.y + 1 == player1.PlayerPosXY.y)
				|| (player2.pBombIJ.x == player1.PlayerPosWH.x && player2.pBombIJ.y + 1 == player1.PlayerPosWH.y)
				|| (player2.pBombIJ.x == player1.PlayerPosXY.x && player2.pBombIJ.y + 2 == player1.PlayerPosXY.y)
				|| (player2.pBombIJ.x == player1.PlayerPosWH.x && player2.pBombIJ.y + 2 == player1.PlayerPosWH.y)
				|| (player2.pBombIJ.x - 1 == player1.PlayerPosXY.x && player2.pBombIJ.y == player1.PlayerPosXY.y)
				|| (player2.pBombIJ.x - 1 == player1.PlayerPosWH.x && player2.pBombIJ.y == player1.PlayerPosWH.y)
				|| (player2.pBombIJ.x - 2 == player1.PlayerPosXY.x && player2.pBombIJ.y == player1.PlayerPosXY.y)
				|| (player2.pBombIJ.x - 2 == player1.PlayerPosWH.x && player2.pBombIJ.y == player1.PlayerPosWH.y)
				|| (player2.pBombIJ.x + 1 == player1.PlayerPosXY.x && player2.pBombIJ.y == player1.PlayerPosXY.y)
				|| (player2.pBombIJ.x + 1 == player1.PlayerPosWH.x && player2.pBombIJ.y == player1.PlayerPosWH.y)
				|| (player2.pBombIJ.x + 2 == player1.PlayerPosXY.x && player2.pBombIJ.y == player1.PlayerPosXY.y)
				|| (player2.pBombIJ.x + 2 == player1.PlayerPosWH.x && player2.pBombIJ.y == player1.PlayerPosWH.y)) {
				if (player1.Helmet) {
					player1.Helmet = false;
					player1.PowerUp = false;
					player1.damaged = true;
				}
				else {
					player1.lifes -= 1;
					player1.damaged = true;
					player2.score += 100;
				}
			}
		}
	}
	else if (!player2.bomb.exploding && !player1.bomb.exploding) {
		player1.damaged = false;
		player2.damaged = false;
	}

	//CORRECCIÓN DE POSICIÓN
	if (player2.PlayerPosXY.y <= -1) {
		player2.Player_Position.y = CELLSIZE + HUD_HEIGHT;
	}
	if (player2.PlayerPosXY.x <= -1) {
		player2.Player_Position.x = CELLSIZE;
	}

	//COMPROBACIÓN DE SI HA COGIDO UN POWER UP
	if (player2.PlayerPosXY.y >= 0 && player2.PlayerPosXY.x >= 0 && player2.PlayerPosWH.x<lvl.limiteWH.x && player2.PlayerPosWH.y<lvl.limiteWH.y && !player2.PowerUp) {
		if (lvl.tablero[player2.PlayerPosXY.x][player2.PlayerPosXY.y] == cells::ROLLERS || lvl.tablero[player2.PlayerPosWH.x][player2.PlayerPosWH.y] == cells::ROLLERS) {
			lvl.tablero[player2.PlayerPosXY.x][player2.PlayerPosXY.y] = cells::EMPTY;
			lvl.tablero[player2.PlayerPosWH.x][player2.PlayerPosWH.y] = cells::EMPTY;
			player2.Rollers = true;
			player2.PowerUp = true;
		}
		if (lvl.tablero[player2.PlayerPosXY.x][player2.PlayerPosXY.y] == cells::HELMET || lvl.tablero[player2.PlayerPosWH.x][player2.PlayerPosWH.y] == cells::HELMET) {
			lvl.tablero[player2.PlayerPosXY.x][player2.PlayerPosXY.y] = cells::EMPTY;
			lvl.tablero[player2.PlayerPosWH.x][player2.PlayerPosWH.y] = cells::EMPTY;
			player2.Helmet = true;
			player2.PowerUp = true;
		}
	}


	//Clock Update
	if (time > 0) {
		deltaTime = (clock() - lastTime);
		lastTime = clock();
		deltaTime /= CLOCKS_PER_SEC;
		time -= deltaTime;
		//std::cout << timeDown << std::endl;
		hud.Time.text = "Time left:  " + (std::to_string(static_cast<int>(time)));
		std::cout << lastTime << std::endl;
	}
	if (time <= 0) {
		hud.Time.text = "FINAL";
		endGame = true;
	}
	hud.P1score.text = "Score p1:  " + std::to_string(player1.score);
	hud.P2score.text = "Score p2:  " + std::to_string(player2.score);
	hud.P1lifes.text = "Lifes p1:  " + std::to_string(player1.lifes);
	hud.P2lifes.text = "Lifes p2:  " + std::to_string(player2.lifes);
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