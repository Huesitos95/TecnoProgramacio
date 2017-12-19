#pragma once
#include "Scene.h"
#include "Types.h"
#include "GameObject.h"
#include "Constants.h"
#include "GameObject.h"
#include "Wall.h"
#include "Menu.h"
#include "Button.h"

class Level {
public:
	int auxrandomblock;
	int time;
	std::string BG_ID;
	std::string WALL_ID;
	std::string GAMEOBJECT_ID;
	std::string LIMIT_ID;
	SDL_Rect BG_Rect{ 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };
	SDL_Rect Limit_Rect, Limit_Position;
	SDL_Rect Wall_Rect, Wall_Position;
	SDL_Rect GameObject_Rect, GameObject_Position;
	GameState gamestate;
	int casillasAncho, casillasAlto;
	Vector2 limiteIJ, limiteWH;
	casillas **tablero;
	Wall Destructible_wall;
	Wall Indestructible_wall;


	Vector2 CoordToPos(int x, int y);

	Vector2 PosToCoord(int i, int j);

	Level();
	~Level();


	void Draw(); 
	void Update(); 
	void InputHandler(); 
	void SpawnObject();
	void DestroyObject();

};

