#pragma once
#include "Game.h"


Game::Game() {
	//puntero de tipo escena que controla menu y play y ranking
	gamestate = GameState::MENU;
	currentscene = new Menu();
}

Game::~Game()
{
}

void Game::LoopGame() {
	while (gamestate != GameState::EXIT) {
		if (currentscene->getState() == SceneState::RUNNING) {
			//std::cout << "estoy en estado running" << std::endl;
			currentscene->HandleEvents();
			currentscene->Update();
			currentscene->Draw();
		}
		else if (currentscene->getState() == SceneState::GOTOLVL1) {
			//std::cout << "Deberia estar en lvl 1" << std::endl;
			/*if (gamestate == GameState::PLAY1) {
				delete currentscene;
				currentscene = new Menu();
				gamestate = GameState::MENU;
			}*/
			if (gamestate == GameState::MENU) {
				delete currentscene;
				gamestate = GameState::PLAY1;
				currentscene = new Play("PLAY1");
			}
			/*else if (gamestate == GameState::RANKING) {
				delete currentscene;
				currentscene = new Ranking();
				gamestate = GameState::MENU;
			}*/
		}
		else if (currentscene->getState() == SceneState::GOTOLVL2) {
			//std::cout << "Deberia estar en Ranking" << std::endl;
			if (gamestate == GameState::MENU) {
				delete currentscene;
				gamestate = GameState::PLAY2;
				currentscene = new Play("PLAY2");
			}
			/*else if (gamestate == GameState::MENU) {
			delete currentscene;
			currentscene = new Ranking();
			gamestate = GameState::RANKING;
			}
			else if (gamestate == GameState::PLAY) {
			delete currentscene;
			currentscene = new Ranking();
			gamestate = GameState::MENU;
			}*/
		}
		else if (currentscene->getState() == SceneState::GOTORANKING) {
			//std::cout << "Deberia estar en Ranking" << std::endl;
			if (gamestate == GameState::MENU) {
				delete currentscene;
				currentscene = new Ranking();
				gamestate = GameState::RANKING;
			}
			/*else if (gamestate == GameState::MENU) {
				delete currentscene;
				currentscene = new Ranking();
				gamestate = GameState::RANKING;
			}
			else if (gamestate == GameState::PLAY) {
				delete currentscene;
				currentscene = new Ranking();
				gamestate = GameState::MENU;
			}*/
		}
		else if (currentscene->getState() == SceneState::GOTOMENU) {
			if (gamestate == GameState::RANKING) {
				delete currentscene;
				currentscene = new Menu();
				gamestate = GameState::MENU;
			}
		}
	}
}