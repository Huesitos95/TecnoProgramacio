#include "Menu.h"



Menu::Menu()
{

}


Menu::~Menu()
{

}

void Menu::Update()
{
}

void Menu::Draw()
{
	R->Render();

	//Background
	R->LoadTexture(PLAY_BG, "../../res/img/bgGame.jpg");
	SDL_Rect bgRect{ 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	R->PushImage(PLAY_BG, bgRect);

	//Buttons & Text
	Font Saiyan;
	Saiyan.id = "saiyan";
	Saiyan.path = "../../res/ttf/saiyan.ttf";
	Saiyan.size = 20;

	R->LoadFont(Saiyan);

	Text PlayButton;
	PlayButton.id = "PlayButton";
	PlayButton.text = "Play Level 1";
	PlayButton.color={ 0, 0, 255, 255 };
	PlayButton.w = 250;
	PlayButton.h = 150;

	R->LoadTextureText(Saiyan.id, PlayButton);


	R->Render();
}

void Menu::HandleEvents()
{
}
