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
}

void Play::HandleEvents()
{
	/*
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:		isRunning = false; break;
		case SDL_KEYDOWN:	if (event.key.keysym.sym == SDLK_ESCAPE) isRunning = false;
			//PLayer1
			if (event.key.keysym.sym == SDLK_w)
			{
				if (playerPosition.y > 180)
				{
					playerPosition.y -= 5;
					playerDirection = 1;
				}
			}

			if (event.key.keysym.sym == SDLK_a)
			{
				if (playerPosition.x > 0)
				{
					playerPosition.x -= 5;
					playerDirection = 2;
				}
			}

			if (event.key.keysym.sym == SDLK_s)
			{
				if (playerPosition.y < 700 - frameHeight)
				{
					playerPosition.y += 5;
					playerDirection = 0;
				}
			}

			if (event.key.keysym.sym == SDLK_d)
			{
				if (playerPosition.x < 1251 - frameWidth)
				{
					playerPosition.x += 5;
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
	*/
}

