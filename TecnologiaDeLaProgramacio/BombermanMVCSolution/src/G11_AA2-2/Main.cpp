#include "Game.h"

#define SIZE_FILA_TABLERO 13
#define SIZE_COLUMNA_TABLERO 13


int main(int, char*[]) {
	Game* GameManager = new Game();
	srand(time(NULL));
	GameManager->LoopGame();
	return 0;
}