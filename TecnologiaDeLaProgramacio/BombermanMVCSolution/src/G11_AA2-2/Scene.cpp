#pragma once
#include "Scene.h"


Scene::Scene() {
	scenestate = SceneState::RUNNING;
}


Scene::~Scene() {
}

void Scene::Draw() {

}

void Scene::HandleEvents(){

}

void Scene::Update() {

}


SceneState Scene::getState() {
	return scenestate;
}