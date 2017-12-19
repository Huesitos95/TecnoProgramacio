#pragma once
#include "Player.h"


Player::Player(){
	PlayerPath = "../../res/img/player1.png";
	Player_ID = PLAYER1_SPRITE;
	R->LoadTexture(Player_ID, PlayerPath);
	R->GetTextureSize(Player_ID);
	tmpPosXY = lvl.CasillaACoordenada(0, 0);
	frameWidth = textWidth / 3;
	frameHeight = textHeight / 4;
	Player_Position.x = tmpPosXY.x;
	Player_Position.y = tmpPosXY.y;
	Player_Rect.x = 0;
	Player_Rect.y = 0;
	Player_Position.h = LADO_CASILLA;
	Player_Rect.h = frameHeight;
	Player_Position.w = LADO_CASILLA;
	Player_Rect.w = frameWidth;
	frameTime = 0;
	lifes = 3;
	score = 0;
	bomb = Bomb();
	lvl = Level();

	lvl.limiteIJ = lvl.CasillaACoordenada(lvl.limiteIJ.x, lvl.limiteIJ.y);
	lvl.limiteWH = lvl.CasillaACoordenada(lvl.limiteWH.x, lvl.limiteWH.y);
}


Player::~Player()
{
}

void Player::HandleEvents(SDL_Event evento) {
	switch (evento.type) {
	default:
		break;
	}
}

void Player::Update(SDL_Scancode UP, SDL_Scancode DOWN, SDL_Scancode LEFT, SDL_Scancode RIGHT, SDL_Scancode DropBomb) {
	frameTime++;
	if (FPS / frameTime <= 5) {
		frameTime = 0;
		//player 1
		if (Player_Rect.x == 48 * 2)
			cambiop = -1;
		else if (Player_Rect.x == 0)
			cambiop = 1;
		Player_Rect.x += 48*cambiop;

	}

	const Uint8 *keyboardstate = SDL_GetKeyboardState(NULL);

	if (keyboardstate[UP] && Player_Position.y > lvl.limiteIJ.y) {
		tmpPosXY = lvl.CoordenadaACasilla(Player_Position.x + LADO_CASILLA / 2, Player_Position.y + LADO_CASILLA*2);
		if (lvl.tablero[tmpPosXY.x][tmpPosXY.y - 1] != casillas::INDESTRUCTIBLE_WALL && lvl.tablero[tmpPosXY.x][tmpPosXY.y - 1] != casillas::DESTRUCTIBLE_WALL && lvl.tablero[tmpPosXY.x][tmpPosXY.y - 1] != casillas::BOMB) {
			lvl.tablero[tmpPosXY.x][tmpPosXY.y - 1] = casillas::PLAYER;
			Player_Rect.y = 0;
			if (Rollers) {
				Player_Position.y -= speed * RollersBoost;
			}
			else {
				Player_Position.y -= speed;
			}
		}
	}
	else if (keyboardstate[DOWN] && Player_Position.y + Player_Position.h < lvl.limiteWH.y) {
		tmpPosXY = lvl.CoordenadaACasilla(Player_Position.x + LADO_CASILLA / 2, Player_Position.y + LADO_CASILLA*1.3);
		if (lvl.tablero[tmpPosXY.x][tmpPosXY.y + 1] != casillas::INDESTRUCTIBLE_WALL && lvl.tablero[tmpPosXY.x][tmpPosXY.y + 1] != casillas::DESTRUCTIBLE_WALL && lvl.tablero[tmpPosXY.x][tmpPosXY.y + 1] != casillas::BOMB) {
			lvl.tablero[tmpPosXY.x][tmpPosXY.y + 1] = casillas::PLAYER;
			Player_Rect.y = 48 * 2;
			if (Rollers) {
				Player_Position.y += speed * RollersBoost;
			}
			else {
				Player_Position.y += speed;
			}
		}
	}
	else if (keyboardstate[LEFT] && Player_Position.x > lvl.limiteIJ.x) {
		tmpPosXY = lvl.CoordenadaACasilla(Player_Position.x + Player_Position.w, Player_Position.y);
		if (lvl.tablero[tmpPosXY.x - 1][tmpPosXY.y] != casillas::INDESTRUCTIBLE_WALL && lvl.tablero[tmpPosXY.x - 1][tmpPosXY.y] != casillas::DESTRUCTIBLE_WALL && lvl.tablero[tmpPosXY.x - 1][tmpPosXY.y] != casillas::BOMB) {
			lvl.tablero[tmpPosXY.x - 1][tmpPosXY.y] = casillas::PLAYER;
			Player_Rect.y = 48;
			if (Rollers) {
				Player_Position.x -= speed * RollersBoost;
			}
			else {
				Player_Position.x -= speed;
			}
		}
	}
	else if (keyboardstate[RIGHT] && Player_Position.x + Player_Position.w < lvl.limiteWH.x) {
		tmpPosXY = lvl.CoordenadaACasilla(Player_Position.x, Player_Position.y);
		if (lvl.tablero[tmpPosXY.x + 1][tmpPosXY.y] != casillas::INDESTRUCTIBLE_WALL && lvl.tablero[tmpPosXY.x + 1][tmpPosXY.y] != casillas::DESTRUCTIBLE_WALL && lvl.tablero[tmpPosXY.x + 1][tmpPosXY.y] != casillas::BOMB) {
			lvl.tablero[tmpPosXY.x + 1][tmpPosXY.y] = casillas::PLAYER;
			Player_Rect.y = 48 * 3;
			if (Rollers) {
				Player_Position.x += speed * RollersBoost;
			}
			else {
				Player_Position.x += speed;
			}
		}
	}
	if (!dropbomb) {
		if (keyboardstate[DropBomb]) {
			tmpPosXY = lvl.CoordenadaACasilla(Player_Position.x, Player_Position.y);
			tmpPosXY = lvl.CasillaACoordenada(tmpPosXY.x, tmpPosXY.y);
			bomb.lastTime = clock();
			bomb.timeDown = 3.;
			bomb.deltaTime = 0;
			std::cout << "drop bomb" << std::endl;			
			pBomb = tmpPosXY;
			dropbomb = true;
		}
	}
}
void Player::Draw() {
	if (dropbomb) {
		Player::SpawnBomb(pBomb.x, pBomb.y, up, up2, down, down2, left, left2, right, right2);
		//std::cout << pBomb.x <<" "<< pBomb.y  << std::endl;
	}
	if (bomb.explosion) {
		bomb.lastTime = clock();
		bomb.timeDown = 3.;
		bomb.deltaTime = 0;
		dropbomb = false;
		bomb.explosion = false;
	}
	R->PushSprite(Player_ID, Player_Rect, Player_Position);
}

void Player::SpawnBomb(int i, int j, bool up, bool up2, bool down, bool down2, bool left, bool left2, bool right, bool right2) {
	bomb.Draw(i,  j,  up,  up2,  down,  down2,  left,  left2,  right,  right2);
	bomb.Update();
}