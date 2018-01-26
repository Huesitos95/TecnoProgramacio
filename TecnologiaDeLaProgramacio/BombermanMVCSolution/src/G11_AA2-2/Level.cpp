#include "Level.h"




Level::Level()
{

	R->LoadTexture(BACKGROUND, "../../res/img/bgGame.jpg");
	cellW = 13;
	cellH= 11;

	//Setup INDESTRUCTIBLE
	Indestructible_wall = Wall();
	Indestructible_wall.Wall_ID = INDESTRUCTIBLE_WALL;
	R->LoadTexture(Indestructible_wall.Wall_ID, Indestructible_wall.WallPath);
	R->GetTextureSize(Indestructible_wall.Wall_ID);
	Indestructible_wall.frameWidth = (Indestructible_wall.textWidth / 3);
	Indestructible_wall.frameHeight = (Indestructible_wall.textHeight / 2);
	Indestructible_wall.Wall_Position.x = 0;
	Indestructible_wall.Wall_Position.y = 0;
	Indestructible_wall.Wall_Rect.x = 0;
	Indestructible_wall.Wall_Rect.y = 0;
	Indestructible_wall.Wall_Position.h = CELLSIZE;
	Indestructible_wall.Wall_Rect.h = Indestructible_wall.frameHeight;
	Indestructible_wall.Wall_Position.w = CELLSIZE;
	Indestructible_wall.Wall_Rect.w = Indestructible_wall.frameWidth;

	//Setup DESTRUCTIBLE
	Destructible_wall = Wall();
	Destructible_wall.Wall_ID = INDESTRUCTIBLE_WALL;
	R->LoadTexture(Destructible_wall.Wall_ID, Destructible_wall.WallPath);
	R->GetTextureSize(Destructible_wall.Wall_ID);
	Destructible_wall.frameWidth = (Destructible_wall.textWidth / 3);
	Destructible_wall.frameHeight = (Destructible_wall.textHeight / 2);
	Destructible_wall.Wall_Position.x = 0;
	Destructible_wall.Wall_Position.y = 0;
	Destructible_wall.Wall_Rect.x = Destructible_wall.frameWidth;
	Destructible_wall.Wall_Rect.y = 0;
	Destructible_wall.Wall_Position.h = CELLSIZE;
	Destructible_wall.Wall_Rect.h = Destructible_wall.frameHeight;
	Destructible_wall.Wall_Position.w = CELLSIZE;
	Destructible_wall.Wall_Rect.w = Destructible_wall.frameWidth;

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
				Vector2 coord = CellToCoord(i, j);
				Indestructible_wall.draw(Indestructible_wall.Wall_ID, coord.x, coord.y);
			}
			else if (tablero[i][j] == cells::DESTRUCTIBLE_WALL) {
				Vector2 coord = CellToCoord(i, j);
				Destructible_wall.draw(Destructible_wall.Wall_ID, coord.x, coord.y);
			}
		}
	}
}

void Level::Update()
{
	//TODO
	//Afegir Helmet i Rollers
}