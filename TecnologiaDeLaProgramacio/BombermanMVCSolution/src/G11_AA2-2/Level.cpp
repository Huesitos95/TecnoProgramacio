#include "Level.h"




Level::Level()
{

	R->LoadTexture(BACKGROUND, "../../res/img/bgGame.jpg");
	cellW = 13;
	cellH= 11;

	//Setup INDESTRUCTIBLE
	Indestructible_wall = GameObject();
	Indestructible_wall.GameObject_ID = INDESTRUCTIBLE_WALL;
	R->LoadTexture(Indestructible_wall.GameObject_ID, Indestructible_wall.GameObjectPath);
	R->GetTextureSize(Indestructible_wall.GameObject_ID);
	Indestructible_wall.frameWidth = (Indestructible_wall.textWidth / 3);
	Indestructible_wall.frameHeight = (Indestructible_wall.textHeight / 2);
	Indestructible_wall.GameObject_Position.x = 0;
	Indestructible_wall.GameObject_Position.y = 0;
	Indestructible_wall.GameObject_Rect.x = 0;
	Indestructible_wall.GameObject_Rect.y = 0;
	Indestructible_wall.GameObject_Position.h = CELLSIZE;
	Indestructible_wall.GameObject_Rect.h = Indestructible_wall.frameHeight;
	Indestructible_wall.GameObject_Position.w = CELLSIZE;
	Indestructible_wall.GameObject_Rect.w = Indestructible_wall.frameWidth;

	//Setup DESTRUCTIBLE
	Destructible_wall = GameObject();
	Destructible_wall.GameObject_ID = INDESTRUCTIBLE_WALL;
	R->LoadTexture(Destructible_wall.GameObject_ID, Destructible_wall.GameObjectPath);
	R->GetTextureSize(Destructible_wall.GameObject_ID);
	Destructible_wall.frameWidth = (Destructible_wall.textWidth / 3);
	Destructible_wall.frameHeight = (Destructible_wall.textHeight / 2);
	Destructible_wall.GameObject_Position.x = 0;
	Destructible_wall.GameObject_Position.y = 0;
	Destructible_wall.GameObject_Rect.x = Destructible_wall.frameWidth;
	Destructible_wall.GameObject_Rect.y = 0;
	Destructible_wall.GameObject_Position.h = CELLSIZE;
	Destructible_wall.GameObject_Rect.h = Destructible_wall.frameHeight;
	Destructible_wall.GameObject_Position.w = CELLSIZE;
	Destructible_wall.GameObject_Rect.w = Destructible_wall.frameWidth;

	Helmet = GameObject();
	Helmet.GameObject_ID = HELMET;
	Renderer::Instance()->LoadTexture(Helmet.GameObject_ID, Helmet.GameObjectPath);
	Renderer::Instance()->GetTextureSize(Helmet.GameObject_ID);
	Helmet.frameWidth = (Helmet.textWidth / 3);
	Helmet.frameHeight = (Helmet.textHeight / 2);
	Helmet.GameObject_Position.x = 0;
	Helmet.GameObject_Position.y = 0;
	Helmet.GameObject_Rect.x = Helmet.frameWidth * 2;
	Helmet.GameObject_Rect.y = Helmet.frameHeight;
	Helmet.GameObject_Position.h = CELLSIZE;
	Helmet.GameObject_Rect.h = Helmet.frameHeight;
	Helmet.GameObject_Position.w = CELLSIZE;
	Helmet.GameObject_Rect.w = Helmet.frameWidth;

	Rollers = GameObject();
	Rollers.GameObject_ID = ROLLER;
	Renderer::Instance()->LoadTexture(Rollers.GameObject_ID, Rollers.GameObjectPath);
	Renderer::Instance()->GetTextureSize(Rollers.GameObject_ID);
	Rollers.frameWidth = (Rollers.textWidth / 3);
	Rollers.frameHeight = (Rollers.textHeight / 2);
	Rollers.GameObject_Position.x = 0;
	Rollers.GameObject_Position.y = 0;
	Rollers.GameObject_Rect.x = Rollers.frameWidth;
	Rollers.GameObject_Rect.y = Rollers.frameHeight;
	Rollers.GameObject_Position.h = CELLSIZE;
	Rollers.GameObject_Rect.h = Rollers.frameHeight;
	Rollers.GameObject_Position.w = CELLSIZE;
	Rollers.GameObject_Rect.w = Rollers.frameWidth;

	tablero = new cells*[cellW];
	for (int i = 0; i <= cellW; i++) {
		tablero[i] = new cells[cellH];
		for (int j = 0; j <= cellH; j++) {
			tablero[i][j] = cells::EMPTY;
		}
	}
	limiteIJ = { 0, 0 };
	limiteWH = { cellW, cellH };

}


Level::~Level()
{

}

Vector2 Level::CoordToCell(int x, int y)
{
	int iCoord;
	int jCoord;
	iCoord = (x / CELLSIZE) - 1;
	jCoord = (y / CELLSIZE) - (HUD_HEIGHT / CELLSIZE) - 1;
	Vector2 casilla{ iCoord, jCoord };
	return casilla;
}

Vector2 Level::CellToCoord(int i, int j)
{
	int iCell;
	int jCell;
	iCell = (i * CELLSIZE) + CELLSIZE;
	jCell = (j * CELLSIZE) + HUD_HEIGHT + CELLSIZE;
	Vector2 coordenada{ iCell, jCell };
	return coordenada;
}

void Level::Draw()
{
	for (int i = 0; i < cellW; ++i) {
		for (int j = 0; j < cellH; ++j) {
			if (tablero[i][j] == cells::INDESTRUCTIBLE_WALL) {
				Vector2 coordenadas = CellToCoord(i, j);
				Indestructible_wall.draw(Indestructible_wall.GameObject_ID, coordenadas.x, coordenadas.y);
			}
			else if (tablero[i][j] == cells::DESTRUCTIBLE_WALL) {
				Vector2 coordenadas = CellToCoord(i, j);
				Destructible_wall.draw(Destructible_wall.GameObject_ID, coordenadas.x, coordenadas.y);
			}
			else if (tablero[i][j] == cells::HELMET) {
				Vector2 coordenadas = CellToCoord(i, j);
				Helmet.draw(Helmet.GameObject_ID, coordenadas.x, coordenadas.y);
			}
			else if (tablero[i][j] == cells::ROLLERS) {
				Vector2 coordenadas = CellToCoord(i, j);
				Rollers.draw(Rollers.GameObject_ID, coordenadas.x, coordenadas.y);
			}
		}
	}
}

void Level::Update(int i, int j)
{
	//TODO
	//Afegir Helmet i Rollers
	if (rand() % 100 <= 19) {
		if (rand() % 100 <= 49) {
			tablero[i][j] = cells::HELMET;
		}
		else {
			tablero[i][j] = cells::ROLLERS;
		}
		//std::cout << "power-up" << std::endl;
	}
}