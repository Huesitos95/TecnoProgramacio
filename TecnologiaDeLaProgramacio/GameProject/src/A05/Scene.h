#pragma once

class Scene
{
protected:
	enum SceneState{MENU,PLAY}; // Running / Exit?
	SceneState currentState;
public:
	Scene();
	~Scene();
	virtual void Update();
	virtual void Draw();
	virtual void HandleEvents();
	int GetCurrentState();
};

