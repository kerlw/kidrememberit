/*
 * GameController.cpp
 *
 *  Created on: 2015年5月26日
 *      Author: kerlw
 */

#include "GameController.h"
#include "MainScene.h"

static GameController* s_pGameController;

GameController::GameController() {
}
GameController::~GameController() {
}

GameController* GameController::getInstance() {
	if (!s_pGameController) {
		s_pGameController = new (std::nothrow) GameController();
		CCASSERT(s_pGameController, "FATAL: Not enough memory");
		s_pGameController->init();
	}
	return s_pGameController;
}

bool GameController::init() {
	return false;
}

void GameController::enterScene(const SceneType& eType) {
	auto scene = Scene::create();

	Layer* layer = nullptr;
	switch (eType) {
	case SceneType::eMainScene:
		layer = MainScene::create();
		break;
	}

	if (layer) {
		scene->addChild(layer);
		Director::getInstance()->pushScene(scene);
	}
}

void GameController::leaveScene() {
	Director::getInstance()->popScene();
}
