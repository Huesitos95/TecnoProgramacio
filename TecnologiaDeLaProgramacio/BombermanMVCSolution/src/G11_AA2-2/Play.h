#pragma once
#include "Scene.h"
#include "Player.h"

class Play : public Scene
{
private:
	
	int level;
	 //Background;


public:
	Play();
	~Play();
	void Update() override;
	void Draw() override;
	void HandleEvents() override;
	void RestartLevel();
	
};

