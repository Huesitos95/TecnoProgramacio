#pragma once
#include "Renderer.h"

enum class SceneState { MENU, PLAY, RANKING };

class Scene
{
protected:
	
	SceneState currentState;
public:
	Scene();
	~Scene();
	virtual void Update();
	virtual void Draw();
	virtual void HandleEvents();
	SceneState GetCurrentState();
};

