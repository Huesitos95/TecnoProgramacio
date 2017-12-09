#pragma once 
#include <SDL.h>		// Always needs to be included for an SDL app
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include "Constants.h"
#include "Scene.h"
#include "Play.h"
#include "Menu.h"
#include "Renderer.h"

int main(int, char*[])
{
	// MENU DRAW
	//Background
	R->LoadTexture(PLAY_BG, "../../res/img/bgGame.jpg");
	SDL_Rect bgRect{ 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	R->PushImage(PLAY_BG, bgRect);

	//Buttons & Text
	Font Saiyan;
	Saiyan.id = "saiyan";
	Saiyan.path = "../../res/ttf/saiyan.ttf";
	Saiyan.size = 50;

	R->LoadFont(Saiyan);

	Text PlayButton{ "PlayButton","Play",{ 0,0,255,255 },200,50 };
	Text ExitButton{ "ExitButton","Exit",{ 255,0,0,255 },200,50 };
	Text RankingButton{ "RankingButton","Ranking",{ 255,0,255,255 },200,50 };
	Text SoundButton{ "SoundButton","So",{ 0,0,255,255 },50,50 };

	SDL_Rect buttonPlayRect{ 250,150,PlayButton.w,PlayButton.h };
	SDL_Rect exitButtonRect{ 250,250,ExitButton.w,ExitButton.h };
	SDL_Rect rankingButtonRect{ 250,350,RankingButton.w,RankingButton.h };
	SDL_Rect soundRect{ 325,450,SoundButton.w,SoundButton.h };
	R->LoadTextureText(Saiyan.id, PlayButton);
	R->LoadTextureText(Saiyan.id, ExitButton);
	R->LoadTextureText(Saiyan.id, RankingButton);
	R->LoadTextureText(Saiyan.id, SoundButton);

	R->PushImage(PlayButton.id, buttonPlayRect);
	R->PushImage(ExitButton.id, exitButtonRect);
	R->PushImage(RankingButton.id, rankingButtonRect);
	R->PushImage(SoundButton.id, soundRect);
	R->Render();
	SDL_Event event;
	bool isRunning = true;
	while (isRunning)
	{
		//Handle Events
		//Menu
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT: isRunning = false; break;
			case SDL_KEYDOWN: if (event.key.keysym.sym == SDLK_ESCAPE) isRunning = false;

			case SDL_MOUSEMOTION: 

				// EXIT BUTTON
				if (event.motion.x > exitButtonRect.x && event.motion.x < exitButtonRect.x + exitButtonRect.w && event.motion.y > exitButtonRect.y && event.motion.y < exitButtonRect.y + exitButtonRect.h) {
					//Hover color?
					std::cout << "EXIT" << std::endl;
					//isRunning = false;
					
				}

				// PLAY BUTTON
				if (event.motion.x > buttonPlayRect.x && event.motion.x < buttonPlayRect.x + buttonPlayRect.w && event.motion.y > buttonPlayRect.y && event.motion.y < buttonPlayRect.y + buttonPlayRect.h)
				{
					std::cout << "PLAY" << std::endl;
				}

				//RANKING BUTTON
				if (event.motion.x > rankingButtonRect.x && event.motion.x < rankingButtonRect.x + rankingButtonRect.w && event.motion.y > rankingButtonRect.y && event.motion.y < rankingButtonRect.y + rankingButtonRect.h)
				{
					std::cout << "RANK" << std::endl;
				}
			}
		}
	}
	R->~Renderer();

	return 0;
}