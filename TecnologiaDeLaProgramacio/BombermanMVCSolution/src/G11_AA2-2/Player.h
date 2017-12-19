#pragma once
#include <iostream>
#include "Renderer.h"
#include "Level.h"
#include "Bomb.h"
class Player
{
public:
	//Variables
	std::string Player_ID, PlayerPath;
	SDL_Rect Player_Rect, Player_Position;
	int textWidth = 192;
	int textHeight = 94;
	int frameWidth, frameHeight;
	int frameTime;
	int cambiop = 1;
	bool dropbomb = false;
	int dropX, dropY;
	int lifes;
	int score;
	bool Rollers = false;
	bool Helmet = false;
	int speed = 5;
	int RollersBoost = 1.8;
	Vector2 tmpPosXY;
	Vector2 pBomb;
	Bomb bomb;
	Level lvl;
	bool up;
	bool up2;
	bool down;
	bool down2;
	bool left;
	bool left2;
	bool right;
	bool right2;


	//Métodos
	Player();
	~Player();
	void HandleEvents(SDL_Event event);
	void Update(SDL_Scancode UP, SDL_Scancode DOWN, SDL_Scancode LEFT, SDL_Scancode RIGHT, SDL_Scancode DropBomb);
	void Draw();
	void SpawnBomb(int i, int j, bool up, bool up2, bool down, bool down2, bool left, bool left2, bool right, bool right2);

};

