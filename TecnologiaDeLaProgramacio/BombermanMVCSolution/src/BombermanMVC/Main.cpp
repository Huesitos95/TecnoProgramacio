#pragma once 
#include "Constants.h"
#include "Scene.h"
#include "Play.h"
#include "Menu.h"
#include "Renderer.h"

int main(int, char*[])
{
	R->Render();
	
	//Background
	R->LoadTexture(PLAY_BG, PATH_IMG);
	SDL_Rect bgRect{ 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	R->PushImage(PLAY_BG, bgRect);
	R->~Renderer();
	return 0;
}