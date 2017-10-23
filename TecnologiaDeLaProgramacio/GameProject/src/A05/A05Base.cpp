#include <SDL.h>		// Always needs to be included for an SDL app
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>

//Game general information
#define SCREEN_WIDTH 1251
#define SCREEN_HEIGHT 705
#define FPS 60

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
				if (event.key.keysym.sym == SDLK_w)
				{
					if (playerPosition.y > 180) 
					{
						playerPosition.y--;
						playerDirection = 1;
					}
				}

				if (event.key.keysym.sym == SDLK_a) 
				{
					if (playerPosition.x > 0)
					{
						playerPosition.x--;
						playerDirection = 2;
					}
				}

				if (event.key.keysym.sym == SDLK_s)
				{
					if (playerPosition.y < 700 - frameHeight)
					{
						playerPosition.y++;
						playerDirection = 0;
					}
				}

				if (event.key.keysym.sym == SDLK_d)
				{
					if (playerPosition.x < 1251 - frameWidth)
					{
						playerPosition.x++;
						playerDirection = 3;
					}
				}
				break;
				
			default:;
			}
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
		}

		// UPDATE
		//playerRect.x += (playerTarget.x - playerRect.x) / 10;
		//playerRect.y += (playerTarget.y - playerRect.y) / 10;
		frameTime++;
		if (FPS / frameTime <= 9) {
			frameTime = 0;
			playerRect.x += frameWidth;
			if (playerRect.x >= textWidth / 4) {

				playerRect.x = 0;
			}
		}


		// DRAW
		//Background
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, bgTexture, nullptr, &bgRect);
		SDL_RenderCopy(renderer, playerTexture, &playerRect, &playerPosition);
		SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
		SDL_RenderCopy(renderer, textTexture2, nullptr, &text2Rect);
		//Animated Sprite
		SDL_RenderCopy(renderer, playerTexture, &playerRect, &playerPosition);
		SDL_RenderPresent(renderer);



	}

	// --- DESTROY ---
	SDL_DestroyTexture(bgTexture);
	SDL_DestroyTexture(playerTexture);
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




