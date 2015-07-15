/*
 * GameScene.cpp
 *
 *  Created on: 2015.7.12
 *      Author: kerlw
 */

#include "GameScene.h"
#include "Const.h"
#include "GameController.h"

#include "ui/UIButton.h"

GameScene::GameScene() {
}

GameScene::~GameScene() {
}

bool GameScene::init() {
	if (!Layer::init())
		return false;

	auto director = Director::getInstance();
	auto pView = director->getOpenGLView();
	pView->setDesignResolutionSize(RESOLUTION_WIDTH, RESOLUTION_HEIGHT, ResolutionPolicy::SHOW_ALL);

	Size visibleSize = director->getVisibleSize();
	Vec2 origin = director->getVisibleOrigin();

	return true;
}
