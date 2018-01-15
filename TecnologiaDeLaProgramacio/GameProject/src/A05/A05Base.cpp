#include <SDL.h>		// Always needs to be included for an SDL app
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include "Renderer.h"
#include "Constants.h"

int main(int, char*[]) {

	// --- INIT ---
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) throw "No es pot inicialitzar SDL subsystems";
	//init SDL_image
	const Uint8 imgFlags{ IMG_INIT_JPG | IMG_INIT_PNG };
	if (!(IMG_Init(imgFlags) & imgFlags)) throw "Error: SDL_image init";
	if (TTF_Init() != 0) throw "No es pot inicialitzar SDL_ttf";
	const Uint8 mixFlags{ MIX_INIT_MP3 | MIX_INIT_OGG };
	if (!(Mix_Init(mixFlags)&mixFlags)) throw "Error: SDL_mixer init";

	// --- WINDOW ---
	SDL_Window *window{ SDL_CreateWindow("SDL...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN) };
	if (window == nullptr) throw "No es pot inicialitzar SDL_Window";

	// --- RENDERER ---
	SDL_Renderer *renderer{ SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) };
	if (renderer == nullptr) throw "No es pot inicialitzar SDL_Renderer";

	// --- SPRITES ---
	SDL_Texture *bgTexture{ IMG_LoadTexture(renderer, "../../res/img/bgCastle.jpg") };
	if (bgTexture == nullptr) throw "No s'han pogut crear les textures";
	SDL_Rect bgRect{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	SDL_Texture *goldTexture{ IMG_LoadTexture(renderer, "../../res/img/gold.png") };
	if (goldTexture == nullptr) throw "No s'han pogut crear les textures";
	SDL_Rect goldRect { rand() % 1200,rand() % 480 + 200,50,50 };
	SDL_Rect goldRect2{ rand() % 1200,rand() % 480 + 200,50,50 };
	SDL_Rect goldRect3{ rand() % 1200,rand() % 480 + 200,50,50 };
	SDL_Rect goldRect4{ rand() % 1200,rand() % 480 + 200,50,50 };
	SDL_Rect goldRect5{ rand() % 1200,rand() % 480 + 200,50,50 };

	// --- Animated Sprite ---
	SDL_Rect playerTarget{ 0,0,100,100 };
	int playerDirection = 0; // 0 Abajo, 1 Arriba, 2 IZQ, 3 DER

	SDL_Texture *playerTexture{ IMG_LoadTexture(renderer, "../../res/img/spCastle.png") };
	SDL_Rect playerRect, playerPosition;
	int textWidth, textHeight, frameWidth, frameHeight;
	SDL_QueryTexture(playerTexture, NULL, NULL, &textWidth, &textHeight);
	frameWidth = textWidth / 12;
	frameHeight = textHeight / 8;
	playerPosition.x = playerPosition.y = 200;
	playerRect.x = playerRect.y = 0;
	playerPosition.h = playerRect.h = frameHeight;
	playerPosition.w = playerRect.w = frameWidth;
	int frameTime = 0;

	//Player 2
	SDL_Rect player2Target{ 0,0,100,100 };
	int player2Direction = 0; // 0 Abajo, 1 Arriba, 2 IZQ, 3 DER

	SDL_Texture *player2Texture{ IMG_LoadTexture(renderer, "../../res/img/spCastle.png") };
	SDL_Rect player2Rect, player2Position;
	SDL_QueryTexture(player2Texture, NULL, NULL, &textWidth, &textHeight);
	player2Position.x = 1000;
	player2Position.y = 200;
	player2Rect.x = 3*frameWidth;
	player2Rect.y = 0;
	player2Position.h = player2Rect.h = frameHeight;
	player2Position.w = player2Rect.w = frameWidth;

	// --- TEXT ---
	TTF_Font *font{ TTF_OpenFont("../../res/ttf/MarioLuigi2.ttf",30) };
	if (font == nullptr) throw "No es pot inicialitzar el TTF_Font";
	SDL_Surface *tmpSurf{ TTF_RenderText_Blended(font,"Player 1: ",SDL_Color{ 0,0,0,250 }) };
	if (tmpSurf == nullptr) throw "Unable to create SDL Text Surface";
	SDL_Texture *textTexture{ SDL_CreateTextureFromSurface(renderer,tmpSurf) };
	SDL_Rect textRect{ 50,50,tmpSurf->w,tmpSurf->h };
	SDL_FreeSurface(tmpSurf);

	SDL_Surface *tmpSurf2{ TTF_RenderText_Blended(font,"Player 2: ",SDL_Color{ 0,0,0,250 }) };
	if (tmpSurf2 == nullptr) throw "Unable to create SDL Text Surface";
	SDL_Texture *textTexture2{ SDL_CreateTextureFromSurface(renderer,tmpSurf2) };
	SDL_Rect text2Rect{ 1000,50,tmpSurf2->w,tmpSurf2->h };
	SDL_FreeSurface(tmpSurf2);
	TTF_CloseFont(font);

	// --- AUDIO ---
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
		throw "Unable to initialize SDL_mixer audio systems";
	}
	Mix_Music *soundtrack{ Mix_LoadMUS("../../res/au/maintheme.mp3") };
	if (!soundtrack) throw "Unable to load the Mix_Music soundtrack";
	Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
	Mix_PlayMusic(soundtrack, -1);

	// --- GAME LOOP ---
	SDL_Event event;
	bool isRunning = true;
	while (isRunning) {
		// HANDLE EVENTS
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:		isRunning = false; break;
			case SDL_KEYDOWN:	if (event.key.keysym.sym == SDLK_ESCAPE) isRunning = false; 
				//PLayer1
				if (event.key.keysym.sym == SDLK_w)
				{
					if (playerPosition.y > 180) 
					{
						playerPosition.y-=5;
						playerDirection = 1;
					}
				}

				if (event.key.keysym.sym == SDLK_a) 
				{
					if (playerPosition.x > 0)
					{
						playerPosition.x-=5;
						playerDirection = 2;
					}
				}

				if (event.key.keysym.sym == SDLK_s)
				{
					if (playerPosition.y < 700 - frameHeight)
					{
						playerPosition.y+=5;
						playerDirection = 0;
					}
				}

				if (event.key.keysym.sym == SDLK_d)
				{
					if (playerPosition.x < 1251 - frameWidth)
					{
						playerPosition.x+=5;
						playerDirection = 3;
					}
				}

				//Player2
				if (event.key.keysym.sym == SDLK_UP)
				{
					if (player2Position.y > 180)
					{
						player2Position.y -= 5;
						player2Direction = 1;
					}
				}

				if (event.key.keysym.sym == SDLK_LEFT)
				{
					if (player2Position.x > 0)
					{
						player2Position.x -= 5;
						player2Direction = 2;
					}
				}

				if (event.key.keysym.sym == SDLK_DOWN)
				{
					if (player2Position.y < 700 - frameHeight)
					{
						player2Position.y += 5;
						player2Direction = 0;
					}
				}

				if (event.key.keysym.sym == SDLK_RIGHT)
				{
					if (player2Position.x < 1251 - frameWidth)
					{
						player2Position.x += 5;
						player2Direction = 3;
					}
				}
				break;
				
			default:;
			}
			//PLAYER 1
			if (playerDirection == 0) // ABAJO
			{
				playerRect.y = 0;
			}
			if (playerDirection == 1) // ARRIBA
			{
				playerRect.y = 96;
			}
			if (playerDirection == 2) // IZQ
			{
				playerRect.y = 32;
			}
			if (playerDirection == 3) // DER
			{
				playerRect.y = 64;
			}
			//PLAYER 2
			if (player2Direction == 0) // ABAJO
			{
				player2Rect.y = 0;
			}
			if (player2Direction == 1) // ARRIBA
			{
				player2Rect.y = 96;
			}
			if (player2Direction == 2) // IZQ
			{
				player2Rect.y = 32;
			}
			if (player2Direction == 3) // DER
			{
				player2Rect.y = 64;
			}
		}

		// UPDATE
		//playerRect.x += (playerTarget.x - playerRect.x) / 10;
		//playerRect.y += (playerTarget.y - playerRect.y) / 10;
		frameTime++;
		if (SCREEN_FPS / frameTime <= 9) {
			frameTime = 0;
			playerRect.x += frameWidth;
			player2Rect.x += frameWidth;
			if (playerRect.x >= textWidth / 4) {

				playerRect.x = 0;
			}
			if (player2Rect.x >= textWidth / 4 + 96)
			{
				player2Rect.x = 96;
			}
		}


		// DRAW
		//Background
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, bgTexture, nullptr, &bgRect);
		SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
		SDL_RenderCopy(renderer, textTexture2, nullptr, &text2Rect);
		SDL_RenderCopy(renderer, goldTexture, nullptr, &goldRect);
		SDL_RenderCopy(renderer, goldTexture, nullptr, &goldRect2);
		SDL_RenderCopy(renderer, goldTexture, nullptr, &goldRect3);
		SDL_RenderCopy(renderer, goldTexture, nullptr, &goldRect4);
		SDL_RenderCopy(renderer, goldTexture, nullptr, &goldRect5);
		//Animated Sprite
		SDL_RenderCopy(renderer, playerTexture, &playerRect, &playerPosition);
		SDL_RenderCopy(renderer, player2Texture, &player2Rect, &player2Position);
		SDL_RenderPresent(renderer);



	}

	// --- DESTROY ---
	SDL_DestroyTexture(bgTexture);
	SDL_DestroyTexture(playerTexture);
	SDL_DestroyTexture(player2Texture);
	SDL_DestroyTexture(goldTexture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(textTexture);
	SDL_DestroyTexture(textTexture2);
	SDL_DestroyWindow(window);

	
	// --- QUIT ---
	IMG_Quit();
	TTF_Quit();
	Mix_CloseAudio();
	Mix_Quit();
	SDL_Quit();
	return 0;
}

bool Colision(SDL_Rect a, SDL_Rect b)
{
	// AABB Objecte 1
	int x1Min = a.x;
	int x1Max = a.x + a.w;
	int y1Max = a.y + a.h;
	int y1Min = a.y;

	// AABB 2 Objecte 2
	int x2Min = b.x;
	int x2Max = b.x + b.w;
	int y2Max = b.y + b.h;
	int y2Min = b.y;

	// Collision tests
	if (x1Max < x2Min || x1Min > x2Max) return false;
	if (y1Max < y2Min || y1Min > y2Max) return false;

	else
	{
		return true;
	}
}