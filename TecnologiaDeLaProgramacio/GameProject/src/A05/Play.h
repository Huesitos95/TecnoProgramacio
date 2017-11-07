#pragma once
#include "Scene.h"
#include "Player.h"

class Play : public Scene
{
private:

public:
	Play();
	~Play();
	void Update() override;
	void Draw() override;
	void HandleEvents() override;
};

