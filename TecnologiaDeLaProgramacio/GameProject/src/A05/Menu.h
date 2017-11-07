#pragma once
#include "Scene.h"

class Menu : public Scene
{
private:

public:
	Menu();
	~Menu();
	void Update() override;
	void Draw() override;
	void HandleEvents() override;
};

