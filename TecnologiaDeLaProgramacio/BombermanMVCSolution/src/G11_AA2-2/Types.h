#pragma once
#include <string>
#include <SDL.h>
#include "Constants.h"

	using Rect = struct  Rect{ int  x; int y; int w; int h; };

	using Color = struct Color { Uint8 r; Uint8 g; Uint8 b; Uint8 a; };
	
	struct Vector2 { int x; int y; };

	using Font = struct {
		std::string id;
		std::string path;
		int size;
	};

	using Text = struct {
		std::string id;
		std::string text;
		Color color;
		int w;
		int h;
	};

	enum class Key {UP, DOWN, LEFT, RIGHT, NONE, BOMB};

	enum class GameState { PLAY1, PLAY2, MENU, RANKING, EXIT };

	enum class SceneState { RUNNING, GOTORANKING, GOTOLVL1, GOTOLVL2, GOTOMENU, EXIT };

	enum class cells : char {
		DESTRUCTIBLE_WALL = 'w', INDESTRUCTIBLE_WALL = 'W', EMPTY = 'E', PLAYER = 'P', BOMB = 'B', EXPLOSION = 'X', ROLLERS = 'R', HELMET = 'H'
	};
	


