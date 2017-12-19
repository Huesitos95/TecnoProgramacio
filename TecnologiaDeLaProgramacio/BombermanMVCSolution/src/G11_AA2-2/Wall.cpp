#pragma once
#include "Wall.h"
#include "Constants.h"
#include "GameObject.h"



Wall::Wall()
{
	WallPath = "../../res/img/items.png";
	Wall_ID = INDESTRUCTIBLE_WALL;
	R->LoadTexture(Wall_ID, WallPath);
	R->GetTextureSize(Wall_ID);
	frameWidth = (textWidth / 3 );
	frameHeight = (textHeight / 2);
	Wall_Position.x = 0;
	Wall_Position.y = 0;
	Wall_Rect.x = 0;
	Wall_Rect.y = 0;
	Wall_Position.h = 48;
	Wall_Rect.h = frameHeight;
	Wall_Position.w = 48;
	Wall_Rect.w = frameWidth;
}


Wall::~Wall()
{
}

void::Wall::setup() {

}

void Wall::draw(std::string wall_ID, int i, int j)
{
	Wall_Position.x = i;
	Wall_Position.y = j;
	R->PushSprite(Wall_ID, Wall_Rect, Wall_Position);
}

void Wall::update()
{

}
