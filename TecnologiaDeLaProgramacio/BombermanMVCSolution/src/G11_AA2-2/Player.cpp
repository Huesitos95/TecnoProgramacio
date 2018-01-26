#pragma once
#include "Player.h"


Player::Player(){
	PlayerPath = "../../res/img/player1.png";
	Player_ID = PLAYER1_SPRITE;
	R->LoadTexture(Player_ID, PlayerPath);
	R->GetTextureSize(Player_ID);
	PlayerPosXY = { 0,0 };
	frameWidth = textWidth / 3;
	frameHeight = textHeight / 4;
	Player_Position.x = PlayerPosXY.x;
	Player_Position.y = PlayerPosXY.y;
	Player_Rect.x = 0;
	Player_Rect.y = 0;
	Player_Position.h = CELLSIZE;
	Player_Rect.h = frameHeight;
	Player_Position.w = CELLSIZE;
	Player_Rect.w = frameWidth;
	frameTime = 0;
	lifes = 3;
	score = 0;
	bomb = Bomb();
}


Player::~Player()
{
}

void Player::HandleEvents(SDL_Event event) {
	switch (event.type) {
	default:
		break;
	}
}

Key Player::Update(SDL_Scancode UP, SDL_Scancode DOWN, SDL_Scancode LEFT, SDL_Scancode RIGHT, SDL_Scancode DropBomb) {
	frameTime++;
	if (FPS / frameTime <= 5) {
		frameTime = 0;
		//player 1
		if (Player_Rect.x == 48 * 2)
			swap = -1;
		else if (Player_Rect.x == 0)
			swap = 1;
		Player_Rect.x += 48*swap;

	}

	const Uint8 *keyboardstate = SDL_GetKeyboardState(NULL);

	if (keyboardstate[UP]) {
		return Key::UP;
	}
	else if (keyboardstate[DOWN]) {
		return Key::DOWN;
	}
	else if (keyboardstate[LEFT]) {
		return Key::LEFT;
	}
	else if (keyboardstate[RIGHT]) {
		return Key::RIGHT;
	}
	else {
		return Key::NONE;
	}
}
void Player::Draw() {
	if (dropbomb) {
		Player::SpawnBomb(pBomb.x, pBomb.y, up, up2, down, down2, left, left2, right, right2);
	}
	if (bomb.explosion) {
		bomb.lastTime = clock();
		bomb.timeDown = 3.;
		bomb.deltaTime = 0;
		up = true;
		up2 = true;
		down = true;
		down2 = true;
		left = true;
		left2 = true;
		right = true;
		right2 = true;
		dropbomb = false;
		bomb.explosion = false;
	}
	R->PushSprite(Player_ID, Player_Rect, Player_Position);
}

void Player::SpawnBomb(int i, int j, bool up, bool up2, bool down, bool down2, bool left, bool left2, bool right, bool right2) {
	bomb.Draw(i,  j,  up,  up2,  down,  down2,  left,  left2,  right,  right2);
	bomb.Update();
}