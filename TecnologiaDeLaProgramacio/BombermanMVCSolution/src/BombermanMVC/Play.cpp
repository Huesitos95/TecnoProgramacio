#include "Play.h"



Play::Play()
{

}


Play::~Play()
{
}

void Play::Update()
{
}

void Play::Draw()
{
	R->Render();

	//Background
	R->LoadTexture(PLAY_BG, "../../res/img/bgGame.jpg");
	SDL_Rect bgRect{ 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	R->PushImage(PLAY_BG, bgRect);


	R->Render();
}

void Play::HandleEvents()
{
	/*
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:		isRunning = false; break;
		case SDL_KEYDOWN:	if (event.key.keysym.sym == SDLK_ESCAPE) isRunning = false;
			*/
}

void Play::RestartLevel()
{

}

