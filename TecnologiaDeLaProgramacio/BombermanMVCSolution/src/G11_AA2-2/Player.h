#pragma once
#include <iostream>
#include "Renderer.h"
#include "Types.h"
#include "Bomb.h"
class Player
{
public:
	std::string Player_ID, PlayerPath;
	SDL_Rect Player_Rect, Player_Position;
	int textWidth = 192;
	int textHeight = 94;
	int frameWidth, frameHeight;
	int frameTime;
	int swap = 1;
	bool dropbomb = false;
	int dropX, dropY;
	int lifes;
	int score;
	int speed = 3;
	int RollersBoost = 1.8;
	Vector2 PlayerPosXY;
	Vector2 PlayerPosWH;
	Vector2 pBombXY;
	Vector2 pBombIJ;
	Bomb bomb;

	//Gestio Bomba
	bool up;
	bool up2;
	bool down;
	bool down2;
	bool left;
	bool left2;
	bool right;
	bool right2;

	//PowerUps
	bool Rollers = false;
	bool Helmet = false;

	Player();
	~Player();
	void HandleEvents(SDL_Event event);
	Key Update(SDL_Scancode UP, SDL_Scancode DOWN, SDL_Scancode LEFT, SDL_Scancode RIGHT, SDL_Scancode DropBomb);
	void Draw();
	void SpawnBomb(int i, int j, bool up, bool up2, bool down, bool down2, bool left, bool left2, bool right, bool right2);
};

