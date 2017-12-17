#pragma once
#include "Renderer.h"

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

