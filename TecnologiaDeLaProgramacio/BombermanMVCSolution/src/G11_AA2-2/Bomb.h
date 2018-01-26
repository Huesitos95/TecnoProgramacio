#pragma once
#include <ctime>
#include <iostream>
#include "Types.h"
#include "Renderer.h"
#include "Level.h"




class Bomb
{
public:
	Vector2 PlayerPosXY;
	std::string bombs_ID, bombsPath;
	std::string Explosion_ID, ExplosionPath;
	std::string Explosion_ID1;
	std::string Explosion_ID2;
	std::string Explosion_ID3;
	std::string Explosion_ID4;
	std::string Explosion_ID5;
	std::string Explosion_ID6;
	std::string Explosion_ID7;
	std::string Explosion_ID8;
	SDL_Rect bombs_Rect, bombs_Position;
	SDL_Rect Explosion_Rect, Explosion_Position;
	SDL_Rect Explosion1_Rect, Explosion1_Position;
	SDL_Rect Explosion2_Rect, Explosion2_Position;
	SDL_Rect Explosion3_Rect, Explosion3_Position;
	SDL_Rect Explosion4_Rect, Explosion4_Position;
	SDL_Rect Explosion5_Rect, Explosion5_Position;
	SDL_Rect Explosion6_Rect, Explosion6_Position;
	SDL_Rect Explosion7_Rect, Explosion7_Position;
	SDL_Rect Explosion8_Rect, Explosion8_Position;

	int frameWidth, frameHeight;
	int textWidth = 144;
	int textHeight = 96;
	Bomb();
	~Bomb();
	void Update();
	void Draw(int i, int j, bool up, bool up2, bool down, bool down2, bool left, bool left2, bool right, bool right2);
	clock_t lastTime = clock();
	float timeDown = 5.;
	float deltaTime = 0;
	bool explosion = false;
	bool exploding = false;
	Level lvl;

};
