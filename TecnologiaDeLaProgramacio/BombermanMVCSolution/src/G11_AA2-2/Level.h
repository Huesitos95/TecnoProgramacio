#pragma once
#include "Scene.h"
#include "Types.h"
#include "GameObject.h"
#include "Constants.h"
#include "GameObject.h"
#include "Menu.h"
#include "Button.h"

class Level {
public:
	int auxrandomblock;
	int time;
	std::string BG_ID;
	std::string GameObject_ID;
	std::string GAMEOBJECT_ID;
	std::string LIMIT_ID;
	SDL_Rect BG_Rect{ 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };
	SDL_Rect Limit_Rect, Limit_Position;
	SDL_Rect GameObject_Rect, GameObject_Position;
	GameState gamestate;
	int cellW, cellH;
	Vector2 limiteIJ, limiteWH;
	cells **tablero;
	GameObject Destructible_wall;
	GameObject Indestructible_wall;
	GameObject Helmet;
	GameObject Rollers;
	Vector2 DestroyedWall;



	Vector2 CoordToCell(int x, int y);

	Vector2 CellToCoord(int i, int j);

	Level();
	~Level();


	void Draw(); 
	void Update(int i, int j); 

};

