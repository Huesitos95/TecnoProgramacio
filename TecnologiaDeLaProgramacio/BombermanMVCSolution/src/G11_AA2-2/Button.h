#pragma once
#include <iostream>
#include "Renderer.h"
#include "Types.h"

class Button {
public:
	Button();
	~Button();
	void HandleEvents(SDL_Event buttonevent);
	bool isClicked();
	bool isHovered();
	void update();
	void draw();

	Font font;
	Text text;
	Color color;
	SDL_Rect text_Rect;
	int xText, yText;


private:
	bool leftClick;
};
