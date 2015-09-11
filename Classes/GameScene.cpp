/*
 * GameScene.cpp
 *
 *  Created on: 2015.7.12
 *      Author: kerlw
 */

#include "GameScene.h"
#include "Const.h"
#include "GameController.h"
#include "Card.h"

#include "ui/UIButton.h"

static const char* COUNTING_STRING[] = { "3", "2", "1", "Go!" };
static const int GO_INDEX = 3;

GameScene::GameScene()
		: m_pLabelCounting(nullptr) {
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

	m_pLabelCounting = Label::create();
	m_pLabelCounting->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(m_pLabelCounting);

	return true;
}

void GameScene::onEnterTransitionDidFinish() {
	Layer::onEnterTransitionDidFinish();

	showStartCounting();
}

void GameScene::showStartCounting() {
	m_iCounter = 0;
	m_fTimeCounter = 0;
	m_pLabelCounting->setString(COUNTING_STRING[m_iCounter]);
	m_pLabelCounting->setSystemFontSize(300);
	schedule(schedule_selector(GameScene::startCountingCallback), 0.01f);
}

void GameScene::startCountingCallback(float tm) {
	if (!m_pLabelCounting)
		return;

	m_fTimeCounter += tm;
	if (m_fTimeCounter < 3.0f) {
		int index = (int) m_fTimeCounter;
		int size = ((int)(m_fTimeCounter * 100)) % 100 * 3;
		log("tm is %f, index is %d, size is %d", m_fTimeCounter, index, size);
		if (index != m_iCounter) {
			m_iCounter = index;
			m_pLabelCounting->setString(COUNTING_STRING[m_iCounter]);
		}
		m_pLabelCounting->setSystemFontSize(320 - size);
	} else if (m_fTimeCounter <= 3.5f) {
		m_pLabelCounting->setString(COUNTING_STRING[GO_INDEX]);
		m_pLabelCounting->setSystemFontSize(300);
	} else {
		unschedule(schedule_selector(GameScene::startCountingCallback));
		m_pLabelCounting->removeFromParent();

		showGameBoard();
	}
}

void GameScene::showGameBoard() {
	auto card = Card::create(Card::CardType::CARD_0, true);
	auto director = Director::getInstance();
	Size visibleSize = director->getVisibleSize();
	Vec2 origin = director->getVisibleOrigin();

	card->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(card);

	card->setClickable(true);
}
