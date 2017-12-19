#include "Button.h"

Button::Button()
{
	leftClick = false;
	font.id = "game_over";
	font.path = "../../res/ttf/game_over.ttf";
	font.size = 24;
	color = { 255, 0, 0, 0 };
	text.color = color;
	text.id = "text_ID";
	text.text = "Play";
	text.h = 50;
	text.w = 100;
	xText = SCREEN_WIDTH / 2 - text.w / 2;
	yText = SCREEN_HEIGHT / 2 - text.h / 2;
	R->LoadFont(font);
	R->LoadTextureText(font.id, text);
	text_Rect = { xText, yText, text.w, text.h };
}


Button::~Button()
{
}

bool Button::isClicked()
{
	if (isHovered()) {
		if (leftClick) {
			return true;
		}
	}
	return false;
}

bool Button::isHovered()
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (x < (xText + text.w) && x >(xText)) {
		if (y < (yText+ text.h) && y >(yText)) {
			return true;
		}
	}
	return false;
}

void Button::HandleEvents(SDL_Event event)
{
	switch (event.type) {
	case SDL_MOUSEBUTTONDOWN:
		switch (event.button.button) {
		case SDL_BUTTON_LEFT:
			leftClick = true;
			break;
		}
		break;
	default:
		leftClick = false;
	}

}

void Button::update()
{

}

void Button::draw()
{
	R->PushImage(text.id, text_Rect);
}
