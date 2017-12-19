#include "GameObject.h"



GameObject::GameObject()
{
	GameObjectPath = "../../res/img/items.png";
	GameObject_ID = GAMEOBJECT;
	R->LoadTexture(GameObject_ID, GameObjectPath);
	R->GetTextureSize(GameObject_ID);
	frameWidth = textWidth / 3;
	frameHeight = textHeight / 2;
	GameObject_Position.x = 0;
	GameObject_Position.y = 0;
	GameObject_Rect.x = 0;
	GameObject_Rect.y = frameHeight;
	GameObject_Position.h = 48;
	GameObject_Rect.h = frameHeight;
	GameObject_Position.w = 48;
	GameObject_Rect.w = frameWidth;
}


GameObject::~GameObject()
{
}

void GameObject::setup()
{
}

void GameObject::update()
{
}

void GameObject::draw()
{
	R->PushSprite(GameObject_ID, GameObject_Rect, GameObject_Position);
}