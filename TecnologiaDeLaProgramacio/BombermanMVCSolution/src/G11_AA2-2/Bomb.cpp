#include "Bomb.h"

Bomb::Bomb()
{
	bombsPath = "../../res/img/items.png";
	ExplosionPath = "../../res/img/explosion.png";
	bombs_ID = BOMB;
	Explosion_ID1 = EXPLOSION1;
	Explosion_ID2 = EXPLOSION2;
	Explosion_ID3 = EXPLOSION3;
	Explosion_ID4 = EXPLOSION4;
	Explosion_ID5 = EXPLOSION5;
	Explosion_ID6 = EXPLOSION6;
	Explosion_ID7 = EXPLOSION7;
	Explosion_ID8 = EXPLOSION8;
	Explosion_ID = EXPLOSION;
	R->LoadTexture(bombs_ID, bombsPath);
	R->GetTextureSize(bombs_ID);
	R->LoadTexture(Explosion_ID, ExplosionPath);
	R->GetTextureSize(Explosion_ID);
	R->LoadTexture(Explosion_ID1, ExplosionPath);
	R->GetTextureSize(Explosion_ID1);
	R->LoadTexture(Explosion_ID2, ExplosionPath);
	R->GetTextureSize(Explosion_ID2);
	R->LoadTexture(Explosion_ID3, ExplosionPath);
	R->GetTextureSize(Explosion_ID3);
	R->LoadTexture(Explosion_ID4, ExplosionPath);
	R->GetTextureSize(Explosion_ID4);
	R->LoadTexture(Explosion_ID5, ExplosionPath);
	R->GetTextureSize(Explosion_ID5);
	R->LoadTexture(Explosion_ID6, ExplosionPath);
	R->GetTextureSize(Explosion_ID6);
	R->LoadTexture(Explosion_ID7, ExplosionPath);
	R->GetTextureSize(Explosion_ID7);
	R->LoadTexture(Explosion_ID8, ExplosionPath);
	R->GetTextureSize(Explosion_ID8);
	//BOMB
	frameWidth = textWidth / 3;
	frameHeight = textHeight / 2;
	PlayerPosXY;
	bombs_Rect.x = 0;
	bombs_Rect.y = frameHeight;
	bombs_Position.h = 48;
	bombs_Rect.h = frameHeight;
	bombs_Position.w = 48;
	bombs_Rect.w = frameWidth;
	//EXPLOSION
	Explosion_Position.x = 0;
	Explosion_Position.y = 0;
	Explosion_Rect.x = 0;
	Explosion_Rect.y = 0;
	Explosion_Position.h = 48;
	Explosion_Rect.h = frameHeight;
	Explosion_Position.w = 48;
	Explosion_Rect.w = frameWidth;
	lastTime = clock();
	timeDown = 5.;
	deltaTime = 0;
	explosion = false;
	//explosion arriba1
	Explosion1_Position.x = 0;
	Explosion1_Position.y = bombs_Position.x + frameWidth * 2;
	Explosion1_Rect.x = 0;
	Explosion1_Rect.y = bombs_Position.x + frameWidth * 2;
	Explosion1_Position.h = 48;
	Explosion1_Rect.h = frameHeight;
	Explosion1_Position.w = 48;
	Explosion1_Rect.w = frameWidth;
	//explosion arriba2
	Explosion2_Position.x = 0;
	Explosion2_Position.y = 100;
	Explosion2_Rect.x = 0;
	Explosion2_Rect.y = 0;
	Explosion2_Position.h = 48;
	Explosion2_Rect.h = frameHeight;
	Explosion2_Position.w = 48;
	Explosion2_Rect.w = frameWidth;
	//explosion dedrecha1
	Explosion3_Position.x = 0;
	Explosion3_Position.y = 200;
	Explosion3_Rect.x = 0;
	Explosion3_Rect.y = 0;
	Explosion3_Position.h = 48;
	Explosion3_Rect.h = frameHeight;
	Explosion3_Position.w = 48;
	Explosion3_Rect.w = frameWidth;
	//explosion derecha2
	Explosion4_Position.x = 0;
	Explosion4_Position.y = 300;
	Explosion4_Rect.x = 0;
	Explosion4_Rect.y = 0;
	Explosion4_Position.h = 48;
	Explosion4_Rect.h = frameHeight;
	Explosion4_Position.w = 48;
	Explosion4_Rect.w = frameWidth;
	//explosion izquierda1
	Explosion5_Position.x = 0;
	Explosion5_Position.y = 400;
	Explosion5_Rect.x = 0;
	Explosion5_Rect.y = 0;
	Explosion5_Position.h = 48;
	Explosion5_Rect.h = frameHeight;
	Explosion5_Position.w = 48;
	Explosion5_Rect.w = frameWidth;
	//explosion izquierda2
	Explosion6_Position.x = 0;
	Explosion6_Position.y = 500;
	Explosion6_Rect.x = 0;
	Explosion6_Rect.y = 0;
	Explosion6_Position.h = 48;
	Explosion6_Rect.h = frameHeight;
	Explosion6_Position.w = 48;
	Explosion6_Rect.w = frameWidth;
	//explosion abajo1
	Explosion7_Position.x = 0;
	Explosion7_Position.y = 600;
	Explosion7_Rect.x = 0;
	Explosion7_Rect.y = 0;
	Explosion7_Position.h = 48;
	Explosion7_Rect.h = frameHeight;
	Explosion7_Position.w = 48;
	Explosion7_Rect.w = frameWidth;
	//explosion abajo2
	Explosion8_Position.x = 0;
	Explosion8_Position.y = 700;
	Explosion8_Rect.x = 0;
	Explosion8_Rect.y = 0;
	Explosion8_Position.h = 48;
	Explosion8_Rect.h = frameHeight;
	Explosion8_Position.w = 48;
	Explosion8_Rect.w = frameWidth;
}


Bomb::~Bomb() {
}

void Bomb::Update() {
	PlayerPosXY = lvl.CoordToCell(bombs_Position.x, bombs_Position.y);
	if (timeDown > 0) {
		deltaTime = (clock() - lastTime);
		lastTime = clock();
		deltaTime /= CLOCKS_PER_SEC;
		timeDown -= deltaTime;
		//std::cout << timeDown << std::endl;
		if (timeDown <= 0) {
			explosion = true;
			exploding = false;
		}
	}

}

void Bomb::Draw(int i, int j, bool up, bool up2, bool down, bool down2, bool left, bool left2, bool right, bool right2) {
	bombs_Position.x = i;
	bombs_Position.y = j;
	if (timeDown >= 0) {
		if (timeDown > 1) {
			R->PushSprite(bombs_ID, bombs_Rect, bombs_Position);
		}
		else if (timeDown <= 1) {
			std::cout << "Deberia salir la explosion" << std::endl;
			exploding = true;
			//bomb0
			Explosion_Position.x = bombs_Position.x;
			Explosion_Position.y = bombs_Position.y;
			Explosion_Rect.x = frameWidth * 2;
			Explosion_Rect.y = 0;
			Explosion_Position.h = 48;
			Explosion_Rect.h = frameHeight;
			Explosion_Position.w = 48;
			Explosion_Rect.w = frameWidth;
			if (!up) {
				//bomb1 = arriba 1
				Explosion1_Position.x = bombs_Position.x;
				Explosion1_Position.y = bombs_Position.y - CELLSIZE * 1;
				Explosion1_Rect.x = frameWidth * 2;
				Explosion1_Rect.y = frameWidth * 6;
				Explosion1_Position.h = 48;
				Explosion1_Rect.h = frameHeight;
				Explosion1_Position.w = 48;
				Explosion1_Rect.w = frameWidth;
				R->PushSprite(Explosion_ID1, Explosion1_Rect, Explosion1_Position);
			}
			if (!up2) {
				//bomb2 = arriba 2
				Explosion2_Position.x = bombs_Position.x;
				Explosion2_Position.y = bombs_Position.y - CELLSIZE * 2;
				Explosion2_Rect.x = frameWidth * 2;
				Explosion2_Rect.y = frameWidth * 3;
				Explosion2_Position.h = 48;
				Explosion2_Rect.h = frameHeight;
				Explosion2_Position.w = 48;
				Explosion2_Rect.w = frameWidth;
				R->PushSprite(Explosion_ID2, Explosion2_Rect, Explosion2_Position);
			}
			if (!right) {
				//bomb3 = derecha 1
				Explosion3_Position.x = bombs_Position.x + CELLSIZE;
				Explosion3_Position.y = bombs_Position.y;
				Explosion3_Rect.x = frameWidth * 2;
				Explosion3_Rect.y = frameWidth * 5;
				Explosion3_Position.h = 48;
				Explosion3_Rect.h = frameHeight;
				Explosion3_Position.w = 48;
				Explosion3_Rect.w = frameWidth;
				R->PushSprite(Explosion_ID3, Explosion3_Rect, Explosion3_Position);
			}
			if (!right2) {
				//bomb4 = derecha 2
				Explosion4_Position.x = bombs_Position.x + CELLSIZE * 2;
				Explosion4_Position.y = bombs_Position.y;
				Explosion4_Rect.x = frameWidth * 2;
				Explosion4_Rect.y = frameWidth * 2;
				Explosion4_Position.h = 48;
				Explosion4_Rect.h = frameHeight;
				Explosion4_Position.w = 48;
				Explosion4_Rect.w = frameWidth;
				R->PushSprite(Explosion_ID4, Explosion4_Rect, Explosion4_Position);
			}
			if (!left) {
				//bomb5 = izquierda 1
				Explosion5_Position.x = bombs_Position.x - CELLSIZE;
				Explosion5_Position.y = bombs_Position.y;
				Explosion5_Rect.x = frameWidth * 2;
				Explosion5_Rect.y = frameWidth * 5;
				Explosion5_Position.h = 48;
				Explosion5_Rect.h = frameHeight;
				Explosion5_Position.w = 48;
				Explosion5_Rect.w = frameWidth;
				R->PushSprite(Explosion_ID5, Explosion5_Rect, Explosion5_Position);
			}
			if (!left2) {
				//bomb5 = izquierda 2
				Explosion6_Position.x = bombs_Position.x - CELLSIZE * 2;
				Explosion6_Position.y = bombs_Position.y;
				Explosion6_Rect.x = frameWidth * 2;;
				Explosion6_Rect.y = frameWidth * 1;
				Explosion6_Position.h = 48;
				Explosion6_Rect.h = frameHeight;
				Explosion6_Position.w = 48;
				Explosion6_Rect.w = frameWidth;
				R->PushSprite(Explosion_ID6, Explosion6_Rect, Explosion6_Position);
			}
			if (!down) {
				//bomb7 = abajo 1
				Explosion7_Position.x = bombs_Position.x;
				Explosion7_Position.y = bombs_Position.y + CELLSIZE * 1;
				Explosion7_Rect.x = frameWidth * 2;
				Explosion7_Rect.y = frameWidth * 6;
				Explosion7_Position.h = 48;
				Explosion7_Rect.h = frameHeight;
				Explosion7_Position.w = 48;
				Explosion7_Rect.w = frameWidth;
				R->PushSprite(Explosion_ID7, Explosion7_Rect, Explosion7_Position);
			}
			if (!down2) {
				//bomb7 = abajo 2
				Explosion8_Position.x = bombs_Position.x;
				Explosion8_Position.y = bombs_Position.y + CELLSIZE * 2;
				Explosion8_Rect.x = frameWidth * 2;
				Explosion8_Rect.y = frameWidth * 4;
				Explosion8_Position.h = 48;
				Explosion8_Rect.h = frameHeight;
				Explosion8_Position.w = 48;
				Explosion8_Rect.w = frameWidth;
				R->PushSprite(Explosion_ID8, Explosion8_Rect, Explosion8_Position);
			}

			R->PushSprite(Explosion_ID, Explosion_Rect, Explosion_Position);


		}
	}
}